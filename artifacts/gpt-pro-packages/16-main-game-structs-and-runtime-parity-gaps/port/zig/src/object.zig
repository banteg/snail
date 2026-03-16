const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

pub const Vec2 = struct {
    x: f32,
    y: f32,
};

pub const Vec3 = struct {
    x: f32,
    y: f32,
    z: f32,
};

pub const ObjectVertex = struct {
    index: usize,
    position: Vec3,
};

pub const FaceQuad = struct {
    index: usize,
    vertex_indices: [4]u16,
    texcoords: [4]Vec2,
    texture_name: []const u8,
};

pub const ParsedObject = struct {
    arena: std.heap.ArenaAllocator,
    source_path: []const u8,
    vertices: []const ObjectVertex,
    vertex_positions: std.AutoHashMapUnmanaged(usize, Vec3),
    faces: []const FaceQuad,
    texture_names: []const []const u8,

    pub fn deinit(self: *ParsedObject) void {
        self.arena.deinit();
    }
};

pub const LoadedSubmesh = struct {
    allocator: std.mem.Allocator,
    mesh: rl.Mesh,
    material: rl.Material,
    texture: ?assets.LoadedTexture,
    texture_name: []const u8,
    archive_texture_path: ?[]const u8,
    triangle_count: usize,

    pub fn unload(self: *LoadedSubmesh) void {
        self.material.unload();
        if (self.texture) |*texture| {
            texture.unload();
            self.texture = null;
        }
        self.mesh.unload();
        if (self.archive_texture_path) |path| {
            self.allocator.free(path);
            self.archive_texture_path = null;
        }
    }
};

pub const LoadedObject = struct {
    allocator: std.mem.Allocator,
    parsed: ParsedObject,
    submeshes: []LoadedSubmesh,
    bounds_min: rl.Vector3,
    bounds_max: rl.Vector3,
    center: rl.Vector3,
    radius: f32,

    pub fn loadFromArchive(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        entry: archive.Entry,
        flip_v: bool,
    ) !LoadedObject {
        const decoded = try catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        var parsed = try parseObject(allocator, decoded, entry.path);
        errdefer parsed.deinit();

        const submeshes = try buildSubmeshes(allocator, catalog, &parsed, entry.path, flip_v);
        errdefer {
            for (submeshes) |*submesh| {
                submesh.unload();
            }
            allocator.free(submeshes);
        }

        const bounds = computeBounds(parsed.vertices);
        return .{
            .allocator = allocator,
            .parsed = parsed,
            .submeshes = submeshes,
            .bounds_min = bounds.min,
            .bounds_max = bounds.max,
            .center = bounds.center,
            .radius = bounds.radius,
        };
    }

    pub fn deinit(self: *LoadedObject) void {
        for (self.submeshes) |*submesh| {
            submesh.unload();
        }
        self.allocator.free(self.submeshes);
        self.parsed.deinit();
    }

    pub fn previewCamera(self: *const LoadedObject, time_seconds: f32) rl.Camera3D {
        const distance = @max(self.radius * 3.0, 3.0);
        return .{
            .position = .{
                .x = self.center.x + std.math.cos(time_seconds * 0.45) * distance,
                .y = self.center.y + distance * 0.65,
                .z = self.center.z + std.math.sin(time_seconds * 0.45) * distance,
            },
            .target = self.center,
            .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
            .fovy = 45.0,
            .projection = .perspective,
        };
    }

    pub fn draw(self: *const LoadedObject) void {
        self.drawEx(rl.Matrix.identity());
    }

    pub fn drawEx(self: *const LoadedObject, transform: rl.Matrix) void {
        for (self.submeshes) |submesh| {
            rl.drawMesh(submesh.mesh, submesh.material, transform);
        }
    }

    pub fn drawTintedEx(self: *const LoadedObject, transform: rl.Matrix, tint: rl.Color) void {
        const submeshes = @constCast(self.submeshes);
        for (submeshes) |*submesh| {
            const albedo_map = &submesh.material.maps[@intFromEnum(rl.MaterialMapIndex.albedo)];
            const previous_tint = albedo_map.color;
            albedo_map.color = tint;
            rl.drawMesh(submesh.mesh, submesh.material, transform);
            albedo_map.color = previous_tint;
        }
    }
};

const Bounds = struct {
    min: rl.Vector3,
    max: rl.Vector3,
    center: rl.Vector3,
    radius: f32,
};

pub fn parseObject(
    allocator: std.mem.Allocator,
    data: []const u8,
    source_path: []const u8,
) !ParsedObject {
    var arena = std.heap.ArenaAllocator.init(allocator);
    errdefer arena.deinit();
    const arena_allocator = arena.allocator();

    var vertices_list: std.ArrayList(ObjectVertex) = .empty;
    defer vertices_list.deinit(arena_allocator);
    var vertex_positions: std.AutoHashMapUnmanaged(usize, Vec3) = .empty;

    var faces_list: std.ArrayList(FaceQuad) = .empty;
    defer faces_list.deinit(arena_allocator);

    var texture_names: std.ArrayList([]const u8) = .empty;
    defer texture_names.deinit(arena_allocator);

    var in_vertices = false;
    var in_faces = false;

    var lines = std.mem.splitScalar(u8, data, '\n');
    while (lines.next()) |raw_line| {
        const line = std.mem.trim(u8, raw_line, " \t\r");
        if (line.len == 0 or line[0] == '*') continue;

        if (std.mem.eql(u8, line, "[VERTEX START]")) {
            in_vertices = true;
            in_faces = false;
            continue;
        }
        if (std.mem.eql(u8, line, "[VERTEX END]")) {
            in_vertices = false;
            continue;
        }
        if (std.mem.eql(u8, line, "[FACEQUAD START]")) {
            in_faces = true;
            in_vertices = false;
            continue;
        }
        if (std.mem.eql(u8, line, "[FACEQUAD END]")) {
            in_faces = false;
            continue;
        }

        if (in_vertices) {
            var parts = std.mem.tokenizeAny(u8, line, " \t");
            const index_text = parts.next() orelse return error.InvalidObjectVertex;
            const x_text = parts.next() orelse return error.InvalidObjectVertex;
            const y_text = parts.next() orelse return error.InvalidObjectVertex;
            const z_text = parts.next() orelse return error.InvalidObjectVertex;
            if (parts.next() != null) return error.InvalidObjectVertex;

            const vertex_index = try std.fmt.parseUnsigned(usize, index_text, 10);
            const position = Vec3{
                .x = try std.fmt.parseFloat(f32, x_text),
                .y = try std.fmt.parseFloat(f32, y_text),
                .z = try std.fmt.parseFloat(f32, z_text),
            };

            try vertices_list.append(arena_allocator, .{
                .index = vertex_index,
                .position = position,
            });
            try vertex_positions.put(arena_allocator, vertex_index, position);
            continue;
        }

        if (in_faces) {
            var parts = std.mem.tokenizeAny(u8, line, " \t");
            const index_text = parts.next() orelse return error.InvalidObjectFace;
            const v0_text = parts.next() orelse return error.InvalidObjectFace;
            const v1_text = parts.next() orelse return error.InvalidObjectFace;
            const v2_text = parts.next() orelse return error.InvalidObjectFace;
            const v3_text = parts.next() orelse return error.InvalidObjectFace;
            const tex_u0 = parts.next() orelse return error.InvalidObjectFace;
            const tex_v0 = parts.next() orelse return error.InvalidObjectFace;
            const tex_u1 = parts.next() orelse return error.InvalidObjectFace;
            const tex_v1 = parts.next() orelse return error.InvalidObjectFace;
            const tex_u2 = parts.next() orelse return error.InvalidObjectFace;
            const tex_v2 = parts.next() orelse return error.InvalidObjectFace;
            const tex_u3 = parts.next() orelse return error.InvalidObjectFace;
            const tex_v3 = parts.next() orelse return error.InvalidObjectFace;
            const texture_name_text = parts.next() orelse return error.InvalidObjectFace;
            if (parts.next() != null) return error.InvalidObjectFace;

            const texture_name = try arena_allocator.dupe(u8, texture_name_text);
            try appendTextureName(arena_allocator, &texture_names, texture_name);
            try faces_list.append(arena_allocator, .{
                .index = try std.fmt.parseUnsigned(usize, index_text, 10),
                .vertex_indices = .{
                    @intCast(try std.fmt.parseUnsigned(usize, v0_text, 10)),
                    @intCast(try std.fmt.parseUnsigned(usize, v1_text, 10)),
                    @intCast(try std.fmt.parseUnsigned(usize, v2_text, 10)),
                    @intCast(try std.fmt.parseUnsigned(usize, v3_text, 10)),
                },
                .texcoords = .{
                    .{ .x = try std.fmt.parseFloat(f32, tex_u0), .y = try std.fmt.parseFloat(f32, tex_v0) },
                    .{ .x = try std.fmt.parseFloat(f32, tex_u1), .y = try std.fmt.parseFloat(f32, tex_v1) },
                    .{ .x = try std.fmt.parseFloat(f32, tex_u2), .y = try std.fmt.parseFloat(f32, tex_v2) },
                    .{ .x = try std.fmt.parseFloat(f32, tex_u3), .y = try std.fmt.parseFloat(f32, tex_v3) },
                },
                .texture_name = texture_name,
            });
        }
    }

    return .{
        .arena = arena,
        .source_path = try arena_allocator.dupe(u8, source_path),
        .vertices = try vertices_list.toOwnedSlice(arena_allocator),
        .vertex_positions = vertex_positions,
        .faces = try faces_list.toOwnedSlice(arena_allocator),
        .texture_names = try texture_names.toOwnedSlice(arena_allocator),
    };
}

fn appendTextureName(
    allocator: std.mem.Allocator,
    texture_names: *std.ArrayList([]const u8),
    texture_name: []const u8,
) !void {
    for (texture_names.items) |existing| {
        if (std.ascii.eqlIgnoreCase(existing, texture_name)) return;
    }
    try texture_names.append(allocator, texture_name);
}

fn buildSubmeshes(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    parsed: *const ParsedObject,
    object_entry_path: []const u8,
    flip_v: bool,
) ![]LoadedSubmesh {
    var submeshes: std.ArrayList(LoadedSubmesh) = .empty;
    defer submeshes.deinit(allocator);

    for (parsed.texture_names) |texture_name| {
        const face_count = countFacesForTexture(parsed.faces, texture_name);
        if (face_count == 0) continue;

        const submesh = try buildSubmesh(allocator, catalog, parsed, object_entry_path, texture_name, face_count, flip_v);
        errdefer {
            var doomed = submesh;
            doomed.unload();
        }
        try submeshes.append(allocator, submesh);
    }

    return submeshes.toOwnedSlice(allocator);
}

fn countFacesForTexture(faces: []const FaceQuad, texture_name: []const u8) usize {
    var count: usize = 0;
    for (faces) |face| {
        if (std.ascii.eqlIgnoreCase(face.texture_name, texture_name)) count += 1;
    }
    return count;
}

fn buildSubmesh(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    parsed: *const ParsedObject,
    object_entry_path: []const u8,
    texture_name: []const u8,
    face_count: usize,
    flip_v: bool,
) !LoadedSubmesh {
    const triangle_count = face_count * 2;
    const vertex_count = triangle_count * 3;

    const vertices = try rl.mem.alloc(f32, vertex_count * 3);
    errdefer rl.mem.free(vertices);
    const texcoords = try rl.mem.alloc(f32, vertex_count * 2);
    errdefer rl.mem.free(texcoords);
    const normals = try rl.mem.alloc(f32, vertex_count * 3);
    errdefer rl.mem.free(normals);

    @memset(vertices, 0);
    @memset(texcoords, 0);
    @memset(normals, 0);

    var vertex_cursor: usize = 0;
    var texcoord_cursor: usize = 0;
    var normal_cursor: usize = 0;

    for (parsed.faces) |face| {
        if (!std.ascii.eqlIgnoreCase(face.texture_name, texture_name)) continue;

        const p0 = try positionForIndex(parsed, face.vertex_indices[0]);
        const p1 = try positionForIndex(parsed, face.vertex_indices[1]);
        const p2 = try positionForIndex(parsed, face.vertex_indices[2]);
        const p3 = try positionForIndex(parsed, face.vertex_indices[3]);

        writeTriangle(
            vertices,
            &vertex_cursor,
            texcoords,
            &texcoord_cursor,
            normals,
            &normal_cursor,
            p0,
            p1,
            p2,
            transformTexcoord(face.texcoords[0], flip_v),
            transformTexcoord(face.texcoords[1], flip_v),
            transformTexcoord(face.texcoords[2], flip_v),
        );
        writeTriangle(
            vertices,
            &vertex_cursor,
            texcoords,
            &texcoord_cursor,
            normals,
            &normal_cursor,
            p0,
            p2,
            p3,
            transformTexcoord(face.texcoords[0], flip_v),
            transformTexcoord(face.texcoords[2], flip_v),
            transformTexcoord(face.texcoords[3], flip_v),
        );
    }

    var mesh = std.mem.zeroes(rl.Mesh);
    mesh.vertexCount = @intCast(vertex_count);
    mesh.triangleCount = @intCast(triangle_count);
    mesh.vertices = @ptrCast(vertices.ptr);
    mesh.texcoords = @ptrCast(texcoords.ptr);
    mesh.normals = @ptrCast(normals.ptr);
    rl.uploadMesh(&mesh, false);

    var material = try rl.loadMaterialDefault();
    errdefer material.unload();

    const texture_path = try resolveTextureArchivePath(allocator, object_entry_path, texture_name);
    var loaded_texture: ?assets.LoadedTexture = null;
    if (texture_path) |path| {
        if (catalog.dat.entryByPath(path)) |entry| {
            const texture = try catalog.loadTexture(allocator, entry);
            rl.setMaterialTexture(&material, .albedo, texture.texture);
            loaded_texture = texture;
        }
    }

    return .{
        .allocator = allocator,
        .mesh = mesh,
        .material = material,
        .texture = loaded_texture,
        .texture_name = texture_name,
        .archive_texture_path = texture_path,
        .triangle_count = triangle_count,
    };
}

fn positionForIndex(parsed: *const ParsedObject, index: u16) !Vec3 {
    return parsed.vertex_positions.get(@as(usize, index)) orelse error.InvalidObjectVertexIndex;
}

fn writeTriangle(
    vertices: []f32,
    vertex_cursor: *usize,
    texcoords: []f32,
    texcoord_cursor: *usize,
    normals: []f32,
    normal_cursor: *usize,
    p0: Vec3,
    p1: Vec3,
    p2: Vec3,
    uv0: Vec2,
    uv1: Vec2,
    uv2: Vec2,
) void {
    const normal = computeNormal(p0, p1, p2);

    writeVertex(vertices, vertex_cursor, p0);
    writeVertex(vertices, vertex_cursor, p1);
    writeVertex(vertices, vertex_cursor, p2);

    writeTexcoord(texcoords, texcoord_cursor, uv0);
    writeTexcoord(texcoords, texcoord_cursor, uv1);
    writeTexcoord(texcoords, texcoord_cursor, uv2);

    writeVertex(normals, normal_cursor, normal);
    writeVertex(normals, normal_cursor, normal);
    writeVertex(normals, normal_cursor, normal);
}

fn transformTexcoord(coord: Vec2, flip_v: bool) Vec2 {
    if (!flip_v) return coord;
    return .{ .x = coord.x, .y = 1.0 - coord.y };
}

fn writeVertex(buffer: []f32, cursor: *usize, vertex: Vec3) void {
    buffer[cursor.*] = vertex.x;
    buffer[cursor.* + 1] = vertex.y;
    buffer[cursor.* + 2] = vertex.z;
    cursor.* += 3;
}

fn writeTexcoord(buffer: []f32, cursor: *usize, coord: Vec2) void {
    buffer[cursor.*] = coord.x;
    buffer[cursor.* + 1] = coord.y;
    cursor.* += 2;
}

fn computeNormal(a: Vec3, b: Vec3, c: Vec3) Vec3 {
    const ab = Vec3{ .x = b.x - a.x, .y = b.y - a.y, .z = b.z - a.z };
    const ac = Vec3{ .x = c.x - a.x, .y = c.y - a.y, .z = c.z - a.z };
    const cross = Vec3{
        .x = ab.y * ac.z - ab.z * ac.y,
        .y = ab.z * ac.x - ab.x * ac.z,
        .z = ab.x * ac.y - ab.y * ac.x,
    };
    const length = std.math.sqrt(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);
    if (length <= 0.0001) return .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    return .{ .x = cross.x / length, .y = cross.y / length, .z = cross.z / length };
}

fn computeBounds(vertices: []const ObjectVertex) Bounds {
    if (vertices.len == 0) {
        return .{
            .min = .{ .x = -1.0, .y = -1.0, .z = -1.0 },
            .max = .{ .x = 1.0, .y = 1.0, .z = 1.0 },
            .center = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .radius = 1.0,
        };
    }

    var min = rl.Vector3{
        .x = vertices[0].position.x,
        .y = vertices[0].position.y,
        .z = vertices[0].position.z,
    };
    var max = min;

    for (vertices[1..]) |vertex| {
        min.x = @min(min.x, vertex.position.x);
        min.y = @min(min.y, vertex.position.y);
        min.z = @min(min.z, vertex.position.z);
        max.x = @max(max.x, vertex.position.x);
        max.y = @max(max.y, vertex.position.y);
        max.z = @max(max.z, vertex.position.z);
    }

    const center = rl.Vector3{
        .x = (min.x + max.x) * 0.5,
        .y = (min.y + max.y) * 0.5,
        .z = (min.z + max.z) * 0.5,
    };

    var radius: f32 = 0.5;
    for (vertices) |vertex| {
        const dx = vertex.position.x - center.x;
        const dy = vertex.position.y - center.y;
        const dz = vertex.position.z - center.z;
        radius = @max(radius, std.math.sqrt(dx * dx + dy * dy + dz * dz));
    }

    return .{ .min = min, .max = max, .center = center, .radius = radius };
}

fn resolveTextureArchivePath(
    allocator: std.mem.Allocator,
    object_entry_path: []const u8,
    texture_name: []const u8,
) !?[]const u8 {
    const slash_index = std.mem.lastIndexOfScalar(u8, object_entry_path, '/') orelse return null;

    var path: std.ArrayList(u8) = .empty;
    defer path.deinit(allocator);
    try path.appendSlice(allocator, object_entry_path[0..slash_index]);
    try path.append(allocator, '/');
    try path.appendSlice(allocator, texture_name);
    try path.appendSlice(allocator, ".TGA");
    return try path.toOwnedSlice(allocator);
}

test "parse font3d object definition" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/OBJECTS/FONT3D/_OBJECT.TXT", 1 << 16);
    defer std.testing.allocator.free(data);

    var parsed = try parseObject(std.testing.allocator, data, "OBJECTS/FONT3D/_OBJECT.TXT");
    defer parsed.deinit();

    try std.testing.expectEqual(@as(usize, 4), parsed.vertices.len);
    try std.testing.expectEqual(@as(usize, 1), parsed.faces.len);
    try std.testing.expectEqualStrings("Letter", parsed.texture_names[0]);
    try std.testing.expectEqual(@as(f32, 0.5), parsed.vertices[0].position.z);
    try std.testing.expectEqual(@as(u16, 3), parsed.faces[0].vertex_indices[3]);
}

test "resolve object texture archive path" {
    const path = try resolveTextureArchivePath(std.testing.allocator, "OBJECTS/FONT3D/_OBJECT.TXT", "Letter");
    defer if (path) |owned_path| std.testing.allocator.free(owned_path);

    try std.testing.expect(path != null);
    try std.testing.expectEqualStrings("OBJECTS/FONT3D/Letter.TGA", path.?);
}

test "parse shipped object corpus" {
    var dir = try std.fs.cwd().openDir("artifacts/extracted/SnailMail.dat/OBJECTS", .{ .iterate = true });
    defer dir.close();

    var object_dir_iterator = dir.iterate();
    var parsed_count: usize = 0;
    while (try object_dir_iterator.next()) |entry| {
        if (entry.kind != .directory) continue;

        var path_buffer: [512]u8 = undefined;
        const object_path = try std.fmt.bufPrint(&path_buffer, "artifacts/extracted/SnailMail.dat/OBJECTS/{s}/_OBJECT.TXT", .{entry.name});
        const data = std.fs.cwd().readFileAlloc(std.testing.allocator, object_path, 1 << 20) catch |err| switch (err) {
            error.FileNotFound => continue,
            else => return err,
        };
        defer std.testing.allocator.free(data);

        var parsed = try parseObject(std.testing.allocator, data, object_path);
        defer parsed.deinit();

        try std.testing.expect(parsed.vertices.len > 0);
        try std.testing.expect(parsed.faces.len > 0);
        try std.testing.expect(parsed.texture_names.len > 0);
        parsed_count += 1;
    }

    try std.testing.expectEqual(@as(usize, 4), parsed_count);
}
