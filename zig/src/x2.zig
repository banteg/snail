const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

const io = std.Options.debug_io;

// Custom text X2 loader for the small legacy mesh subset used by Snail Mail.
//
// The shipped corpus uses:
//   Frame MeshMaterialList { ... Material ... }
//   MeshTextureCoords { ... }
//   Mesh <name> { ... }
//
// The loader keeps parsing and GPU upload separate:
//   - parse(): text -> arena-backed Document
//   - uploadParsed(): Document -> raylib meshes/materials
//   - parseAndUpload(): convenience wrapper
//
// We validate against the shipped corpus instead of trying to support a larger superset.

pub const Vec2 = struct {
    x: f32,
    y: f32,
};

pub const Vec3 = struct {
    x: f32,
    y: f32,
    z: f32,

    fn lerp(a: Vec3, b: Vec3, t: f32) Vec3 {
        const inv_t = 1.0 - t;
        return .{
            .x = a.x * inv_t + b.x * t,
            .y = a.y * inv_t + b.y * t,
            .z = a.z * inv_t + b.z * t,
        };
    }
};

pub const MaterialInfo = struct {
    name: []const u8,
    texture_filename: ?[]const u8 = null,
};

pub const Polygon = struct {
    indices: []const u16,
    material_index: usize = 0,

    pub fn triangleCount(self: Polygon) usize {
        return self.indices.len -| 2;
    }
};

pub const Document = struct {
    arena: std.heap.ArenaAllocator,
    frame_name: []const u8 = "",
    mesh_name: []const u8 = "",
    materials: []const MaterialInfo = &.{},
    texcoords: []const Vec2 = &.{},
    vertices: []Vec3 = &.{},
    polygons: []const Polygon = &.{},
    triangle_count: usize = 0,

    pub fn deinit(self: *Document) void {
        self.arena.deinit();
    }
};

pub const Bounds = struct {
    min: rl.Vector3,
    max: rl.Vector3,
    center: rl.Vector3,
    radius: f32,
};

const ToonOutlineFace = struct {
    vertex_indices: [3]u16,
};

const ToonOutlineEdge = struct {
    vertex_indices: [2]u16,
    face_a: usize,
    face_b: ?usize = null,
    is_boundary: bool = true,
};

const ToonOutlineData = struct {
    faces: []ToonOutlineFace,
    edges: []ToonOutlineEdge,

    fn deinit(self: *ToonOutlineData, allocator: std.mem.Allocator) void {
        allocator.free(self.faces);
        allocator.free(self.edges);
    }
};

const PendingToonOutlineEdge = struct {
    vertex_indices: [2]u16,
    face_a: usize,
    face_b: ?usize = null,
};

const EdgeKey = struct {
    low: u16,
    high: u16,
};

pub const UploadOptions = struct {
    flip_v: bool = true,
};

pub const UploadedSubmesh = struct {
    allocator: std.mem.Allocator,
    mesh: rl.Mesh,
    material: rl.Material,
    texture: ?assets.LoadedTexture = null,
    material_slot: usize,
    material_name: []const u8,
    texture_filename: ?[]const u8,
    triangle_count: usize,
    source_indices: []u16,

    pub fn unload(self: *UploadedSubmesh) void {
        self.material.unload();
        if (self.texture) |*texture| {
            texture.unload();
            self.texture = null;
        }
        self.mesh.unload();
        self.allocator.free(self.source_indices);
    }

    fn rewriteGeometry(self: *UploadedSubmesh, vertices: []const Vec3) !void {
        const vertex_count: usize = @intCast(self.mesh.vertexCount);
        const positions = @as([*]f32, @ptrCast(self.mesh.vertices))[0 .. vertex_count * 3];
        const normals = @as([*]f32, @ptrCast(self.mesh.normals))[0 .. vertex_count * 3];

        var pos_at: usize = 0;
        var normal_at: usize = 0;

        for (0..self.source_indices.len / 3) |tri_index| {
            const base = tri_index * 3;
            const index0 = self.source_indices[base];
            const index1 = self.source_indices[base + 1];
            const index2 = self.source_indices[base + 2];

            const p0 = try vertexAt(vertices, index0);
            const p1 = try vertexAt(vertices, index1);
            const p2 = try vertexAt(vertices, index2);
            const n = faceNormal(p0, p1, p2);

            writeVec3(positions, &pos_at, p0);
            writeVec3(positions, &pos_at, p1);
            writeVec3(positions, &pos_at, p2);

            writeVec3(normals, &normal_at, n);
            writeVec3(normals, &normal_at, n);
            writeVec3(normals, &normal_at, n);
        }

        rl.updateMeshBuffer(
            self.mesh,
            0,
            positions.ptr,
            @intCast(positions.len * @sizeOf(f32)),
            0,
        );
        rl.updateMeshBuffer(
            self.mesh,
            2,
            normals.ptr,
            @intCast(normals.len * @sizeOf(f32)),
            0,
        );
    }
};

pub const Uploaded = struct {
    allocator: std.mem.Allocator,
    doc: Document,
    submeshes: []UploadedSubmesh,
    bounds: Bounds,
    toon_outline: ?ToonOutlineData = null,
    owns_handle: bool = true,

    pub fn borrowed(self: Uploaded) Uploaded {
        var copy = self;
        copy.owns_handle = false;
        return copy;
    }

    pub fn deinit(self: *Uploaded) void {
        if (!self.owns_handle) return;
        if (self.toon_outline) |*toon_outline| {
            toon_outline.deinit(self.allocator);
            self.toon_outline = null;
        }
        for (self.submeshes) |*submesh| submesh.unload();
        self.allocator.free(self.submeshes);
        self.doc.deinit();
        self.owns_handle = false;
    }

    pub fn draw(self: *const Uploaded) void {
        self.drawEx(rl.Matrix.identity());
    }

    pub fn drawEx(self: *const Uploaded, transform: rl.Matrix) void {
        for (self.submeshes) |submesh| {
            rl.drawMesh(submesh.mesh, submesh.material, transform);
        }
    }

    pub fn drawTintedEx(self: *const Uploaded, transform: rl.Matrix, tint: rl.Color) void {
        const submeshes = @constCast(self.submeshes);
        for (submeshes) |*submesh| {
            const albedo_map = &submesh.material.maps[@intFromEnum(rl.MaterialMapIndex.albedo)];
            const previous_tint = albedo_map.color;
            albedo_map.color = tint;
            rl.drawMesh(submesh.mesh, submesh.material, transform);
            albedo_map.color = previous_tint;
        }
    }

    pub fn previewCamera(self: *const Uploaded, seconds: f32) rl.Camera3D {
        const distance = @max(self.bounds.radius * 3.0, 3.0);
        return .{
            .position = .{
                .x = self.bounds.center.x + std.math.cos(seconds * 0.45) * distance,
                .y = self.bounds.center.y + distance * 0.5,
                .z = self.bounds.center.z + std.math.sin(seconds * 0.45) * distance,
            },
            .target = self.bounds.center,
            .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
            .fovy = 45.0,
            .projection = .perspective,
        };
    }

    pub fn enableToonOutline(self: *Uploaded) !void {
        if (self.toon_outline != null) return;
        self.toon_outline = try buildToonOutlineData(self.allocator, &self.doc);
    }

    pub fn drawToonOutlineEx(
        self: *const Uploaded,
        transform: rl.Matrix,
        camera: rl.Camera3D,
        color: rl.Color,
    ) void {
        const toon_outline = self.toon_outline orelse return;
        if (toon_outline.edges.len == 0) return;

        const inverse_transform = rl.math.matrixInvert(transform);
        const world_radius = transformedBoundsRadius(self.bounds.radius, transform);
        const camera_local = vec3FromVector3(transformPointByMatrix(inverse_transform, camera.position));
        const bias_distance = outlineDepthBiasDistance(world_radius);

        rl.gl.rlDisableDepthMask();
        defer rl.gl.rlEnableDepthMask();
        rl.gl.rlDisableBackfaceCulling();
        defer rl.gl.rlEnableBackfaceCulling();
        rl.gl.rlSetTexture(0);
        rl.gl.rlBegin(rl.gl.rl_triangles);
        defer rl.gl.rlEnd();
        rl.gl.rlColor4ub(color.r, color.g, color.b, color.a);

        for (toon_outline.edges) |edge| {
            if (!toonOutlineEdgeVisible(self.doc.vertices, toon_outline.faces, edge, camera_local)) continue;

            const local_a = vertexAt(self.doc.vertices, edge.vertex_indices[0]) catch continue;
            const local_b = vertexAt(self.doc.vertices, edge.vertex_indices[1]) catch continue;
            var world_a = transformPointByMatrix(transform, vector3FromVec3(local_a));
            var world_b = transformPointByMatrix(transform, vector3FromVec3(local_b));
            world_a = applyCameraFacingBias(world_a, camera.position, bias_distance);
            world_b = applyCameraFacingBias(world_b, camera.position, bias_distance);
            const midpoint = scaleVector3(addVector3(world_a, world_b), 0.5);
            const half_width = outlineHalfWidth(world_radius, camera, midpoint);
            emitOutlineEdgeStrip(world_a, world_b, camera.position, half_width);
        }
    }

    pub fn applyBlend(
        self: *Uploaded,
        from: *const Document,
        to: *const Document,
        t: f32,
    ) !void {
        if (!sameTopology(from, to)) return error.AnimationTopologyMismatch;
        if (!sameTopology(from, &self.doc)) return error.AnimationTopologyMismatch;

        for (self.doc.vertices, 0..) |_, i| {
            self.doc.vertices[i] = Vec3.lerp(from.vertices[i], to.vertices[i], t);
        }

        for (self.submeshes) |*submesh| {
            try submesh.rewriteGeometry(self.doc.vertices);
        }

        self.bounds = computeBounds(self.doc.vertices);
    }

    pub fn applyInterpolatedVertices(
        self: *Uploaded,
        from: *const Document,
        to: *const Document,
        t: f32,
    ) !void {
        return self.applyBlend(from, to, t);
    }

    pub fn loadFromArchive(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        entry: archive.Entry,
        flip_v: bool,
    ) !Uploaded {
        return loadFromArchiveWithOptions(allocator, catalog, entry, .{ .flip_v = flip_v });
    }

    pub fn loadFromArchiveWithOptions(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        entry: archive.Entry,
        options: UploadOptions,
    ) !Uploaded {
        const source = try catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(source);
        return parseAndUploadWithCatalog(allocator, catalog, source, options);
    }
};

pub fn parse(allocator: std.mem.Allocator, source: []const u8) !Document {
    var arena = std.heap.ArenaAllocator.init(allocator);
    errdefer arena.deinit();

    var parser = Parser{
        .arena = arena.allocator(),
        .lexer = .{ .input = source },
    };

    return parser.parse(&arena);
}

pub fn uploadParsed(
    allocator: std.mem.Allocator,
    doc: Document,
    options: UploadOptions,
) !Uploaded {
    const submeshes = try buildSubmeshes(allocator, null, &doc, options);
    errdefer {
        for (submeshes) |*submesh| submesh.unload();
        allocator.free(submeshes);
    }

    return .{
        .allocator = allocator,
        .doc = doc,
        .submeshes = submeshes,
        .bounds = computeBounds(doc.vertices),
        .toon_outline = null,
    };
}

pub fn uploadParsedWithCatalog(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    doc: Document,
    options: UploadOptions,
) !Uploaded {
    const submeshes = try buildSubmeshes(allocator, catalog, &doc, options);
    errdefer {
        for (submeshes) |*submesh| submesh.unload();
        allocator.free(submeshes);
    }

    return .{
        .allocator = allocator,
        .doc = doc,
        .submeshes = submeshes,
        .bounds = computeBounds(doc.vertices),
        .toon_outline = null,
    };
}

fn buildToonOutlineData(allocator: std.mem.Allocator, doc: *const Document) !ToonOutlineData {
    var faces: std.ArrayList(ToonOutlineFace) = .empty;
    defer faces.deinit(allocator);

    var pending_edges: std.ArrayList(PendingToonOutlineEdge) = .empty;
    defer pending_edges.deinit(allocator);

    var edge_map: std.AutoHashMapUnmanaged(EdgeKey, usize) = .empty;
    defer edge_map.deinit(allocator);

    for (doc.polygons) |polygon| {
        if (polygon.indices.len < 3) continue;
        for (0..polygon.indices.len - 2) |triangle_index| {
            const face = ToonOutlineFace{
                .vertex_indices = .{
                    polygon.indices[0],
                    polygon.indices[triangle_index + 1],
                    polygon.indices[triangle_index + 2],
                },
            };
            const face_index = faces.items.len;
            try faces.append(allocator, face);

            try addPendingToonOutlineEdge(allocator, &pending_edges, &edge_map, face.vertex_indices[0], face.vertex_indices[1], face_index);
            try addPendingToonOutlineEdge(allocator, &pending_edges, &edge_map, face.vertex_indices[1], face.vertex_indices[2], face_index);
            try addPendingToonOutlineEdge(allocator, &pending_edges, &edge_map, face.vertex_indices[2], face.vertex_indices[0], face_index);
        }
    }

    const owned_faces = try faces.toOwnedSlice(allocator);
    errdefer allocator.free(owned_faces);

    const bind_pose_normals = try allocator.alloc(Vec3, owned_faces.len);
    defer allocator.free(bind_pose_normals);
    for (owned_faces, bind_pose_normals) |face, *normal| {
        normal.* = try faceNormalForIndices(doc.vertices, face.vertex_indices);
    }

    var final_edges: std.ArrayList(ToonOutlineEdge) = .empty;
    defer final_edges.deinit(allocator);

    for (pending_edges.items) |pending_edge| {
        if (pending_edge.face_b) |face_b| {
            if (outlineFacesNearlyCoplanar(bind_pose_normals[pending_edge.face_a], bind_pose_normals[face_b])) {
                continue;
            }
        }
        try final_edges.append(allocator, .{
            .vertex_indices = pending_edge.vertex_indices,
            .face_a = pending_edge.face_a,
            .face_b = pending_edge.face_b,
            .is_boundary = pending_edge.face_b == null,
        });
    }

    return .{
        .faces = owned_faces,
        .edges = try final_edges.toOwnedSlice(allocator),
    };
}

fn addPendingToonOutlineEdge(
    allocator: std.mem.Allocator,
    pending_edges: *std.ArrayList(PendingToonOutlineEdge),
    edge_map: *std.AutoHashMapUnmanaged(EdgeKey, usize),
    index_a: u16,
    index_b: u16,
    face_index: usize,
) !void {
    const key = EdgeKey{
        .low = @min(index_a, index_b),
        .high = @max(index_a, index_b),
    };

    if (edge_map.get(key)) |existing_index| {
        if (pending_edges.items[existing_index].face_b == null) {
            pending_edges.items[existing_index].face_b = face_index;
        }
        return;
    }

    const edge_index = pending_edges.items.len;
    try pending_edges.append(allocator, .{
        .vertex_indices = .{ index_a, index_b },
        .face_a = face_index,
        .face_b = null,
    });
    try edge_map.put(allocator, key, edge_index);
}

fn toonOutlineEdgeVisible(
    vertices: []const Vec3,
    faces: []const ToonOutlineFace,
    edge: ToonOutlineEdge,
    camera_local: Vec3,
) bool {
    if (edge.is_boundary or edge.face_b == null) return true;

    const reference = vertexAt(vertices, edge.vertex_indices[0]) catch return false;
    const normal_a = faceNormalForIndices(vertices, faces[edge.face_a].vertex_indices) catch return false;
    const normal_b = faceNormalForIndices(vertices, faces[edge.face_b.?].vertex_indices) catch return false;
    const view = subtractVec3(camera_local, reference);

    return dotVec3(view, normal_a) * dotVec3(view, normal_b) < 0.01;
}

fn outlineFacesNearlyCoplanar(lhs: Vec3, rhs: Vec3) bool {
    return @abs(dotVec3(lhs, rhs)) >= 0.99875;
}

pub fn parseAndUpload(
    allocator: std.mem.Allocator,
    source: []const u8,
    options: UploadOptions,
) !Uploaded {
    var doc = try parse(allocator, source);
    errdefer doc.deinit();
    return uploadParsed(allocator, doc, options);
}

pub fn parseAndUploadWithCatalog(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    source: []const u8,
    options: UploadOptions,
) !Uploaded {
    var doc = try parse(allocator, source);
    errdefer doc.deinit();
    return uploadParsedWithCatalog(allocator, catalog, doc, options);
}

pub fn sameTopology(a: *const Document, b: *const Document) bool {
    if (a.vertices.len != b.vertices.len) return false;
    if (a.texcoords.len != b.texcoords.len) return false;
    if (a.polygons.len != b.polygons.len) return false;
    if (a.materials.len != b.materials.len) return false;
    if (a.triangle_count != b.triangle_count) return false;

    for (a.texcoords, b.texcoords) |lhs, rhs| {
        if (lhs.x != rhs.x or lhs.y != rhs.y) return false;
    }

    for (a.materials, b.materials) |lhs, rhs| {
        if (!std.mem.eql(u8, lhs.name, rhs.name)) return false;
        if ((lhs.texture_filename == null) != (rhs.texture_filename == null)) return false;
        if (lhs.texture_filename) |lhs_tex| {
            if (!std.mem.eql(u8, lhs_tex, rhs.texture_filename.?)) return false;
        }
    }

    for (a.polygons, b.polygons) |lhs, rhs| {
        if (lhs.material_index != rhs.material_index) return false;
        if (lhs.indices.len != rhs.indices.len) return false;
        for (lhs.indices, rhs.indices) |li, ri| {
            if (li != ri) return false;
        }
    }

    return true;
}

pub fn materialBounds(doc: *const Document, material_index: usize) ?Bounds {
    if (material_index >= doc.materials.len) return null;

    var found = false;
    var min = rl.Vector3{ .x = 0.0, .y = 0.0, .z = 0.0 };
    var max = min;

    for (doc.polygons) |poly| {
        if (poly.material_index != material_index) continue;
        for (poly.indices) |vertex_index| {
            const vertex = doc.vertices[vertex_index];
            const world = rl.Vector3{ .x = vertex.x, .y = vertex.y, .z = vertex.z };
            if (!found) {
                min = world;
                max = world;
                found = true;
                continue;
            }
            min.x = @min(min.x, world.x);
            min.y = @min(min.y, world.y);
            min.z = @min(min.z, world.z);
            max.x = @max(max.x, world.x);
            max.y = @max(max.y, world.y);
            max.z = @max(max.z, world.z);
        }
    }

    if (!found) return null;

    const center = rl.Vector3{
        .x = (min.x + max.x) * 0.5,
        .y = (min.y + max.y) * 0.5,
        .z = (min.z + max.z) * 0.5,
    };

    var radius: f32 = 0.5;
    for (doc.polygons) |poly| {
        if (poly.material_index != material_index) continue;
        for (poly.indices) |vertex_index| {
            const vertex = doc.vertices[vertex_index];
            const dx = vertex.x - center.x;
            const dy = vertex.y - center.y;
            const dz = vertex.z - center.z;
            radius = @max(radius, std.math.sqrt(dx * dx + dy * dy + dz * dz));
        }
    }

    return .{
        .min = min,
        .max = max,
        .center = center,
        .radius = radius,
    };
}

pub fn materialBoundsByTextureFilename(doc: *const Document, texture_filename: []const u8) ?Bounds {
    for (doc.materials, 0..) |material, material_index| {
        const candidate = material.texture_filename orelse continue;
        if (!std.mem.eql(u8, candidate, texture_filename)) continue;
        return materialBounds(doc, material_index);
    }
    return null;
}

pub fn materialBoundsByName(doc: *const Document, material_name: []const u8) ?Bounds {
    for (doc.materials, 0..) |material, material_index| {
        if (!std.mem.eql(u8, material.name, material_name)) continue;
        return materialBounds(doc, material_index);
    }
    return null;
}

const TokenTag = enum {
    identifier,
    string,
    number,
    lbrace,
    rbrace,
    eof,
};

const Token = struct {
    tag: TokenTag,
    lexeme: []const u8 = "",
};

const Lexer = struct {
    input: []const u8,
    index: usize = 0,

    fn next(self: *Lexer) !Token {
        self.skipTrivia();

        if (self.index >= self.input.len) return .{ .tag = .eof };

        const start = self.index;
        const ch = self.input[self.index];
        switch (ch) {
            '{' => {
                self.index += 1;
                return .{ .tag = .lbrace, .lexeme = self.input[start..self.index] };
            },
            '}' => {
                self.index += 1;
                return .{ .tag = .rbrace, .lexeme = self.input[start..self.index] };
            },
            '"' => {
                self.index += 1;
                const string_start = self.index;
                while (self.index < self.input.len and self.input[self.index] != '"') {
                    self.index += 1;
                }
                const string_end = self.index;
                if (self.index < self.input.len) self.index += 1;
                return .{ .tag = .string, .lexeme = self.input[string_start..string_end] };
            },
            else => {},
        }

        if (isIdentifierStart(ch)) {
            self.index += 1;
            while (self.index < self.input.len and isIdentifierContinue(self.input[self.index])) {
                self.index += 1;
            }
            return .{ .tag = .identifier, .lexeme = self.input[start..self.index] };
        }

        if (isNumberStart(ch)) {
            self.index += 1;
            while (self.index < self.input.len and isNumberContinue(self.input[self.index])) {
                self.index += 1;
            }
            return .{ .tag = .number, .lexeme = self.input[start..self.index] };
        }

        self.index += 1;
        return self.next();
    }

    fn skipTrivia(self: *Lexer) void {
        while (self.index < self.input.len) {
            const ch = self.input[self.index];
            switch (ch) {
                ' ', '\t', '\r', '\n', ';', ',', 0 => {
                    self.index += 1;
                    continue;
                },
                '/' => {
                    if (self.index + 1 >= self.input.len) return;
                    const next_ch = self.input[self.index + 1];
                    if (next_ch == '/') {
                        self.index += 2;
                        while (self.index < self.input.len and self.input[self.index] != '\n') self.index += 1;
                        continue;
                    }
                    if (next_ch == '*') {
                        self.index += 2;
                        while (self.index + 1 < self.input.len and !(self.input[self.index] == '*' and self.input[self.index + 1] == '/')) {
                            self.index += 1;
                        }
                        if (self.index + 1 < self.input.len) {
                            self.index += 2;
                        } else {
                            self.index = self.input.len;
                        }
                        continue;
                    }
                    return;
                },
                else => return,
            }
        }
    }
};

const Parser = struct {
    arena: std.mem.Allocator,
    lexer: Lexer,
    tok: Token = .{ .tag = .eof },

    const ParseScratch = struct {
        frame_name: []const u8 = "",
        mesh_name: []const u8 = "",
        materials: []MaterialInfo = &.{},
        face_materials: []u16 = &.{},
        texcoords: []Vec2 = &.{},
        vertices: []Vec3 = &.{},
        polygons: []Polygon = &.{},
        triangle_count: usize = 0,
    };

    fn parse(self: *Parser, arena_owner: *std.heap.ArenaAllocator) !Document {
        var materials_buf: std.ArrayList(MaterialInfo) = .empty;
        var polygons_buf: std.ArrayList(Polygon) = .empty;
        errdefer materials_buf.deinit(self.arena);
        errdefer polygons_buf.deinit(self.arena);

        var scratch: ParseScratch = .{};

        try self.advance();
        while (self.tok.tag != .eof) {
            if (self.at("Frame") and scratch.materials.len == 0) {
                try self.parseFrame(&materials_buf, &scratch);
                continue;
            }
            if (self.at("MeshTextureCoords") and scratch.texcoords.len == 0) {
                scratch.texcoords = try self.parseTexcoords();
                continue;
            }
            if (self.at("Mesh") and scratch.vertices.len == 0) {
                try self.parseMesh(&polygons_buf, &scratch);
                continue;
            }
            try self.skipUnknown();
        }

        if (scratch.materials.len == 0) return error.MissingMaterialList;
        if (scratch.vertices.len == 0) return error.MissingMesh;
        if (scratch.texcoords.len != scratch.vertices.len) return error.InvalidTextureCoordinateCount;
        if (scratch.face_materials.len != scratch.polygons.len) return error.InvalidMaterialIndexCount;

        for (scratch.polygons, 0..) |*poly, i| {
            const material_index: usize = scratch.face_materials[i];
            if (material_index >= scratch.materials.len) return error.InvalidMaterialIndex;
            poly.material_index = material_index;
        }

        return .{
            .arena = arena_owner.*,
            .frame_name = scratch.frame_name,
            .mesh_name = scratch.mesh_name,
            .materials = scratch.materials,
            .texcoords = scratch.texcoords,
            .vertices = scratch.vertices,
            .polygons = scratch.polygons,
            .triangle_count = scratch.triangle_count,
        };
    }

    fn parseFrame(
        self: *Parser,
        materials_buf: *std.ArrayList(MaterialInfo),
        scratch: *ParseScratch,
    ) !void {
        _ = try self.expectIdentifier("Frame");
        scratch.frame_name = try self.takeOptionalName();
        try self.expectTag(.lbrace);

        const material_count = try self.expectUnsigned();
        const face_material_count = try self.expectUnsigned();
        const face_materials = try self.arena.alloc(u16, face_material_count);
        for (face_materials) |*slot| slot.* = try self.expectIndex();
        scratch.face_materials = face_materials;

        while (self.tok.tag != .eof and self.tok.tag != .rbrace) {
            if (self.at("Material")) {
                try materials_buf.append(self.arena, try self.parseMaterial());
                continue;
            }
            try self.skipUnknown();
        }

        try self.expectTag(.rbrace);

        if (materials_buf.items.len != material_count) return error.InvalidMaterialCount;
        scratch.materials = try materials_buf.toOwnedSlice(self.arena);
    }

    fn parseMaterial(self: *Parser) !MaterialInfo {
        _ = try self.expectIdentifier("Material");

        var material = MaterialInfo{
            .name = try self.takeOptionalName(),
            .texture_filename = null,
        };

        try self.expectTag(.lbrace);
        while (self.tok.tag != .eof and self.tok.tag != .rbrace) {
            if (self.at("TextureFilename") and material.texture_filename == null) {
                material.texture_filename = try self.parseTextureFilename();
                continue;
            }
            try self.skipUnknown();
        }
        try self.expectTag(.rbrace);

        return material;
    }

    fn parseTextureFilename(self: *Parser) !?[]const u8 {
        _ = try self.expectIdentifier("TextureFilename");
        try self.expectTag(.lbrace);

        var filename: ?[]const u8 = null;
        if (self.tok.tag == .string) {
            filename = try self.arena.dupe(u8, self.tok.lexeme);
            try self.advance();
        }

        while (self.tok.tag != .eof and self.tok.tag != .rbrace) {
            try self.skipUnknown();
        }
        if (self.tok.tag == .rbrace) {
            try self.expectTag(.rbrace);
        }
        return filename;
    }

    fn parseTexcoords(self: *Parser) ![]Vec2 {
        _ = try self.expectIdentifier("MeshTextureCoords");
        try self.expectTag(.lbrace);

        const count = try self.expectUnsigned();
        const texcoords = try self.arena.alloc(Vec2, count);
        for (texcoords) |*uv| {
            uv.* = .{
                .x = try self.expectFloat(),
                .y = try self.expectFloat(),
            };
        }

        while (self.tok.tag != .eof and self.tok.tag != .rbrace) {
            try self.skipUnknown();
        }
        try self.expectTag(.rbrace);

        return texcoords;
    }

    fn parseMesh(
        self: *Parser,
        polygons_buf: *std.ArrayList(Polygon),
        scratch: *ParseScratch,
    ) !void {
        _ = try self.expectIdentifier("Mesh");
        scratch.mesh_name = try self.takeOptionalName();
        try self.expectTag(.lbrace);

        const vertex_count = try self.expectUnsigned();
        const vertices = try self.arena.alloc(Vec3, vertex_count);
        for (vertices) |*vertex| {
            vertex.* = .{
                .x = try self.expectFloat(),
                .y = try self.expectFloat(),
                .z = try self.expectFloat(),
            };
        }
        scratch.vertices = vertices;

        const polygon_count = try self.expectUnsigned();
        var triangle_count: usize = 0;
        for (0..polygon_count) |_| {
            const index_count = try self.expectUnsigned();
            if (index_count < 3) return error.UnsupportedPolygon;

            const indices = try self.arena.alloc(u16, index_count);
            for (indices) |*index| index.* = try self.expectIndex();
            triangle_count += index_count - 2;

            try polygons_buf.append(self.arena, .{
                .indices = indices,
            });
        }
        scratch.polygons = try polygons_buf.toOwnedSlice(self.arena);
        scratch.triangle_count = triangle_count;

        while (self.tok.tag != .eof and self.tok.tag != .rbrace) {
            try self.skipUnknown();
        }
        if (self.tok.tag == .rbrace) {
            try self.expectTag(.rbrace);
        }
    }

    fn advance(self: *Parser) !void {
        self.tok = try self.lexer.next();
    }

    fn at(self: *const Parser, text: []const u8) bool {
        return self.tok.tag == .identifier and std.mem.eql(u8, self.tok.lexeme, text);
    }

    fn expectTag(self: *Parser, tag: TokenTag) !void {
        if (self.tok.tag != tag) return error.UnexpectedToken;
        try self.advance();
    }

    fn expectIdentifier(self: *Parser, expected: []const u8) ![]const u8 {
        if (self.tok.tag != .identifier) return error.ExpectedIdentifier;
        if (!std.mem.eql(u8, self.tok.lexeme, expected)) return error.UnexpectedIdentifier;

        const lexeme = self.tok.lexeme;
        try self.advance();
        return lexeme;
    }

    fn takeOptionalName(self: *Parser) ![]const u8 {
        if (self.tok.tag != .identifier) return "";

        const out = try self.arena.dupe(u8, self.tok.lexeme);
        try self.advance();
        return out;
    }

    fn expectNumber(self: *Parser) ![]const u8 {
        if (self.tok.tag != .number) return error.ExpectedNumber;

        const lexeme = self.tok.lexeme;
        try self.advance();
        return lexeme;
    }

    fn expectUnsigned(self: *Parser) !usize {
        const lexeme = try self.expectNumber();
        return std.fmt.parseUnsigned(usize, lexeme, 10);
    }

    fn expectIndex(self: *Parser) !u16 {
        const value = try self.expectUnsigned();
        return std.math.cast(u16, value) orelse error.IndexOverflow;
    }

    fn expectFloat(self: *Parser) !f32 {
        const lexeme = try self.expectNumber();
        return std.fmt.parseFloat(f32, lexeme);
    }

    fn skipUnknown(self: *Parser) !void {
        if (self.tok.tag != .identifier) {
            try self.advance();
            return;
        }

        try self.advance();
        if (self.tok.tag == .identifier) try self.advance();
        if (self.tok.tag != .lbrace) return;

        var depth: usize = 1;
        while (depth > 0) {
            try self.advance();
            switch (self.tok.tag) {
                .lbrace => depth += 1,
                .rbrace => depth -= 1,
                .eof => return error.UnexpectedEof,
                else => {},
            }
        }
        try self.advance();
    }
};

fn buildSubmeshes(
    allocator: std.mem.Allocator,
    catalog: ?*const assets.Catalog,
    doc: *const Document,
    options: UploadOptions,
) ![]UploadedSubmesh {
    const material_slots = @max(doc.materials.len, 1);
    const triangles_per_slot = try allocator.alloc(usize, material_slots);
    defer allocator.free(triangles_per_slot);
    @memset(triangles_per_slot, 0);

    for (doc.polygons) |poly| {
        const slot = if (poly.material_index < material_slots) poly.material_index else 0;
        triangles_per_slot[slot] += poly.triangleCount();
    }

    var out: std.ArrayList(UploadedSubmesh) = .empty;
    defer out.deinit(allocator);

    for (triangles_per_slot, 0..) |triangle_count, slot| {
        if (triangle_count == 0) continue;
        const submesh = try buildSubmesh(allocator, catalog, doc, slot, triangle_count, options);
        errdefer {
            var doomed = submesh;
            doomed.unload();
        }
        try out.append(allocator, submesh);
    }

    return out.toOwnedSlice(allocator);
}

fn buildSubmesh(
    allocator: std.mem.Allocator,
    catalog: ?*const assets.Catalog,
    doc: *const Document,
    slot: usize,
    triangle_count: usize,
    options: UploadOptions,
) !UploadedSubmesh {
    const vertex_count = triangle_count * 3;

    const positions = try rl.mem.alloc(f32, vertex_count * 3);
    errdefer rl.mem.free(positions);

    const texcoords = try rl.mem.alloc(f32, vertex_count * 2);
    errdefer rl.mem.free(texcoords);

    const normals = try rl.mem.alloc(f32, vertex_count * 3);
    errdefer rl.mem.free(normals);

    const source_indices = try allocator.alloc(u16, vertex_count);
    errdefer allocator.free(source_indices);

    @memset(positions, 0);
    @memset(texcoords, 0);
    @memset(normals, 0);
    @memset(source_indices, 0);

    var writer = MeshWriter{
        .positions = positions,
        .texcoords = texcoords,
        .normals = normals,
        .source_indices = source_indices,
        .vertices = doc.vertices,
        .uvs = doc.texcoords,
        .flip_v = options.flip_v,
    };

    for (doc.polygons) |poly| {
        if (poly.material_index != slot or poly.indices.len < 3) continue;
        for (1..poly.indices.len - 1) |fan| {
            try writer.push(poly.indices[0], poly.indices[fan], poly.indices[fan + 1]);
        }
    }

    var mesh = std.mem.zeroes(rl.Mesh);
    mesh.vertexCount = @intCast(vertex_count);
    mesh.triangleCount = @intCast(triangle_count);
    mesh.vertices = @ptrCast(positions.ptr);
    mesh.texcoords = @ptrCast(texcoords.ptr);
    mesh.normals = @ptrCast(normals.ptr);
    rl.uploadMesh(&mesh, true);

    var material = try rl.loadMaterialDefault();
    errdefer material.unload();

    var texture: ?assets.LoadedTexture = null;
    const texture_filename = if (slot < doc.materials.len) doc.materials[slot].texture_filename else null;
    if (catalog) |asset_catalog| {
        if (texture_filename) |filename| {
            const texture_path = try archiveTexturePath(allocator, filename);
            defer allocator.free(texture_path);

            if (asset_catalog.findTextureEntry(texture_path)) |texture_entry| {
                const loaded_texture = try asset_catalog.loadTexture(allocator, texture_entry);
                rl.setMaterialTexture(&material, .albedo, loaded_texture.texture);
                texture = loaded_texture;
            }
        }
    }

    return .{
        .allocator = allocator,
        .mesh = mesh,
        .material = material,
        .texture = texture,
        .material_slot = slot,
        .material_name = if (slot < doc.materials.len) doc.materials[slot].name else "default",
        .texture_filename = texture_filename,
        .triangle_count = triangle_count,
        .source_indices = source_indices,
    };
}

const MeshWriter = struct {
    positions: []f32,
    texcoords: []f32,
    normals: []f32,
    source_indices: []u16,
    vertices: []const Vec3,
    uvs: []const Vec2,
    flip_v: bool,
    pos_at: usize = 0,
    uv_at: usize = 0,
    normal_at: usize = 0,
    src_at: usize = 0,

    fn push(self: *MeshWriter, index0: u16, index1: u16, index2: u16) !void {
        const p0 = try vertexAt(self.vertices, index0);
        const p1 = try vertexAt(self.vertices, index1);
        const p2 = try vertexAt(self.vertices, index2);
        const n = faceNormal(p0, p1, p2);

        const uv0 = transformUv(try texcoordAt(self.uvs, index0), self.flip_v);
        const uv1 = transformUv(try texcoordAt(self.uvs, index1), self.flip_v);
        const uv2 = transformUv(try texcoordAt(self.uvs, index2), self.flip_v);

        writeVec3(self.positions, &self.pos_at, p0);
        writeVec3(self.positions, &self.pos_at, p1);
        writeVec3(self.positions, &self.pos_at, p2);

        self.source_indices[self.src_at] = index0;
        self.source_indices[self.src_at + 1] = index1;
        self.source_indices[self.src_at + 2] = index2;
        self.src_at += 3;

        writeVec2(self.texcoords, &self.uv_at, uv0);
        writeVec2(self.texcoords, &self.uv_at, uv1);
        writeVec2(self.texcoords, &self.uv_at, uv2);

        writeVec3(self.normals, &self.normal_at, n);
        writeVec3(self.normals, &self.normal_at, n);
        writeVec3(self.normals, &self.normal_at, n);
    }
};

fn vertexAt(vertices: []const Vec3, index: u16) !Vec3 {
    const i: usize = index;
    if (i >= vertices.len) return error.InvalidVertexIndex;
    return vertices[i];
}

fn texcoordAt(uvs: []const Vec2, index: u16) !Vec2 {
    const i: usize = index;
    if (i >= uvs.len) return error.InvalidTextureCoordinateIndex;
    return uvs[i];
}

fn transformUv(uv: Vec2, flip_v: bool) Vec2 {
    if (!flip_v) return uv;
    return .{ .x = uv.x, .y = 1.0 - uv.y };
}

fn faceNormal(a: Vec3, b: Vec3, c: Vec3) Vec3 {
    const ab = Vec3{ .x = b.x - a.x, .y = b.y - a.y, .z = b.z - a.z };
    const ac = Vec3{ .x = c.x - a.x, .y = c.y - a.y, .z = c.z - a.z };

    const cross = Vec3{
        .x = ab.y * ac.z - ab.z * ac.y,
        .y = ab.z * ac.x - ab.x * ac.z,
        .z = ab.x * ac.y - ab.y * ac.x,
    };

    const len = std.math.sqrt(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);
    if (len <= 0.0001) return .{ .x = 0.0, .y = 1.0, .z = 0.0 };

    return .{
        .x = cross.x / len,
        .y = cross.y / len,
        .z = cross.z / len,
    };
}

fn faceNormalForIndices(vertices: []const Vec3, indices: [3]u16) !Vec3 {
    const a = try vertexAt(vertices, indices[0]);
    const b = try vertexAt(vertices, indices[1]);
    const c = try vertexAt(vertices, indices[2]);
    return faceNormal(a, b, c);
}

fn dotVec3(lhs: Vec3, rhs: Vec3) f32 {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

fn subtractVec3(lhs: Vec3, rhs: Vec3) Vec3 {
    return .{
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
    };
}

fn vector3FromVec3(value: Vec3) rl.Vector3 {
    return .{ .x = value.x, .y = value.y, .z = value.z };
}

fn vec3FromVector3(value: rl.Vector3) Vec3 {
    return .{ .x = value.x, .y = value.y, .z = value.z };
}

fn transformPointByMatrix(matrix: rl.Matrix, point: rl.Vector3) rl.Vector3 {
    return .{
        .x = matrix.m12 + (matrix.m0 * point.x) + (matrix.m4 * point.y) + (matrix.m8 * point.z),
        .y = matrix.m13 + (matrix.m1 * point.x) + (matrix.m5 * point.y) + (matrix.m9 * point.z),
        .z = matrix.m14 + (matrix.m2 * point.x) + (matrix.m6 * point.y) + (matrix.m10 * point.z),
    };
}

fn vectorLength3(value: rl.Vector3) f32 {
    return std.math.sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
}

fn addVector3(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
    };
}

fn subtractVector3(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
    };
}

fn scaleVector3(value: rl.Vector3, scale: f32) rl.Vector3 {
    return .{
        .x = value.x * scale,
        .y = value.y * scale,
        .z = value.z * scale,
    };
}

fn crossVector3(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x,
    };
}

fn normalizeVector3Safe(value: rl.Vector3) rl.Vector3 {
    const length = vectorLength3(value);
    if (length <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 0.0 };
    return .{
        .x = value.x / length,
        .y = value.y / length,
        .z = value.z / length,
    };
}

fn applyCameraFacingBias(point: rl.Vector3, camera_position: rl.Vector3, bias_distance: f32) rl.Vector3 {
    if (bias_distance <= 0.0) return point;
    const toward_camera = normalizeVector3Safe(subtractVector3(camera_position, point));
    return .{
        .x = point.x + toward_camera.x * bias_distance,
        .y = point.y + toward_camera.y * bias_distance,
        .z = point.z + toward_camera.z * bias_distance,
    };
}

fn transformedBoundsRadius(bounds_radius: f32, transform: rl.Matrix) f32 {
    const scale_x = std.math.sqrt(transform.m0 * transform.m0 + transform.m1 * transform.m1 + transform.m2 * transform.m2);
    const scale_y = std.math.sqrt(transform.m4 * transform.m4 + transform.m5 * transform.m5 + transform.m6 * transform.m6);
    const scale_z = std.math.sqrt(transform.m8 * transform.m8 + transform.m9 * transform.m9 + transform.m10 * transform.m10);
    return bounds_radius * @max(scale_x, @max(scale_y, scale_z));
}

fn outlineDepthBiasDistance(world_radius: f32) f32 {
    return @max(world_radius * 0.004, 0.002);
}

fn outlineHalfWidth(world_radius: f32, camera: rl.Camera3D, world_midpoint: rl.Vector3) f32 {
    const units_per_pixel = worldUnitsPerPixelAtPoint(camera, world_midpoint);
    if (units_per_pixel <= 0.0) return @max(world_radius * 0.022, 0.0045);

    const projected_radius_px = world_radius / units_per_pixel;
    const width_pixels = std.math.clamp(projected_radius_px * 0.10, 2.75, 6.5);
    return width_pixels * 0.5 * units_per_pixel;
}

fn worldUnitsPerPixelAtPoint(camera: rl.Camera3D, world_point: rl.Vector3) f32 {
    const screen_height = @as(f32, @floatFromInt(rl.getScreenHeight()));
    if (screen_height <= 0.0) return 0.0;

    return switch (camera.projection) {
        .perspective => blk: {
            const forward = normalizeVector3Safe(subtractVector3(camera.target, camera.position));
            const depth = dotVector3(subtractVector3(world_point, camera.position), forward);
            if (depth <= 0.0001) break :blk 0.0;

            const fovy_radians = std.math.degreesToRadians(camera.fovy);
            const frustum_height = 2.0 * depth * std.math.tan(fovy_radians * 0.5);
            break :blk frustum_height / screen_height;
        },
        .orthographic => camera.fovy / screen_height,
    };
}

fn dotVector3(lhs: rl.Vector3, rhs: rl.Vector3) f32 {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

fn emitOutlineEdgeStrip(
    start: rl.Vector3,
    finish: rl.Vector3,
    camera_position: rl.Vector3,
    half_width: f32,
) void {
    const edge_direction = normalizeVector3Safe(subtractVector3(finish, start));
    if (vectorLength3(edge_direction) <= 0.0001) return;

    const midpoint = scaleVector3(addVector3(start, finish), 0.5);
    const toward_camera = normalizeVector3Safe(subtractVector3(camera_position, midpoint));
    var side = normalizeVector3Safe(crossVector3(toward_camera, edge_direction));
    if (vectorLength3(side) <= 0.0001) {
        side = normalizeVector3Safe(crossVector3(.{ .x = 0.0, .y = 1.0, .z = 0.0 }, edge_direction));
        if (vectorLength3(side) <= 0.0001) return;
    }

    const offset = scaleVector3(side, half_width);
    const start_left = addVector3(start, offset);
    const start_right = subtractVector3(start, offset);
    const finish_left = addVector3(finish, offset);
    const finish_right = subtractVector3(finish, offset);

    rl.gl.rlVertex3f(start_left.x, start_left.y, start_left.z);
    rl.gl.rlVertex3f(start_right.x, start_right.y, start_right.z);
    rl.gl.rlVertex3f(finish_right.x, finish_right.y, finish_right.z);

    rl.gl.rlVertex3f(start_left.x, start_left.y, start_left.z);
    rl.gl.rlVertex3f(finish_right.x, finish_right.y, finish_right.z);
    rl.gl.rlVertex3f(finish_left.x, finish_left.y, finish_left.z);
}

fn writeVec3(buffer: []f32, at: *usize, v: Vec3) void {
    buffer[at.*] = v.x;
    buffer[at.* + 1] = v.y;
    buffer[at.* + 2] = v.z;
    at.* += 3;
}

fn writeVec2(buffer: []f32, at: *usize, v: Vec2) void {
    buffer[at.*] = v.x;
    buffer[at.* + 1] = v.y;
    at.* += 2;
}

fn computeBounds(vertices: []const Vec3) Bounds {
    if (vertices.len == 0) {
        return .{
            .min = .{ .x = -1.0, .y = -1.0, .z = -1.0 },
            .max = .{ .x = 1.0, .y = 1.0, .z = 1.0 },
            .center = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .radius = 1.0,
        };
    }

    var min = rl.Vector3{ .x = vertices[0].x, .y = vertices[0].y, .z = vertices[0].z };
    var max = min;

    for (vertices[1..]) |v| {
        min.x = @min(min.x, v.x);
        min.y = @min(min.y, v.y);
        min.z = @min(min.z, v.z);
        max.x = @max(max.x, v.x);
        max.y = @max(max.y, v.y);
        max.z = @max(max.z, v.z);
    }

    const center = rl.Vector3{
        .x = (min.x + max.x) * 0.5,
        .y = (min.y + max.y) * 0.5,
        .z = (min.z + max.z) * 0.5,
    };

    var radius: f32 = 0.5;
    for (vertices) |v| {
        const dx = v.x - center.x;
        const dy = v.y - center.y;
        const dz = v.z - center.z;
        radius = @max(radius, std.math.sqrt(dx * dx + dy * dy + dz * dz));
    }

    return .{
        .min = min,
        .max = max,
        .center = center,
        .radius = radius,
    };
}

fn archiveTexturePath(allocator: std.mem.Allocator, texture_filename: []const u8) ![]u8 {
    const dot_index = std.mem.indexOfScalar(u8, texture_filename, '.') orelse texture_filename.len;

    var path: std.ArrayList(u8) = .empty;
    defer path.deinit(allocator);
    try path.appendSlice(allocator, "X/");
    try path.appendSlice(allocator, texture_filename[0..dot_index]);
    try path.appendSlice(allocator, ".tga");
    return path.toOwnedSlice(allocator);
}

fn isIdentifierStart(ch: u8) bool {
    return std.ascii.isAlphabetic(ch) or ch == '_';
}

fn isIdentifierContinue(ch: u8) bool {
    return std.ascii.isAlphanumeric(ch) or ch == '_' or ch == '-';
}

fn isNumberStart(ch: u8) bool {
    return std.ascii.isDigit(ch) or ch == '-' or ch == '+' or ch == '.';
}

fn isNumberContinue(ch: u8) bool {
    return std.ascii.isDigit(ch) or ch == '-' or ch == '+' or ch == '.' or ch == 'e' or ch == 'E';
}

test "parse minimal x2 snippet" {
    const source =
        \\Frame MeshMaterialList {
        \\  1; 1;
        \\  0;
        \\  Material mSnail {
        \\    1.0;1.0;1.0;1.0;;
        \\    1.0;
        \\    1.0;1.0;1.0;;
        \\    0.0;0.0;0.0;;
        \\    TextureFilename { "snail.tga"; }
        \\  }
        \\}
        \\MeshTextureCoords {
        \\  3;
        \\  0.0;0.0;,
        \\  1.0;0.0;,
        \\  0.0;1.0;;
        \\}
        \\Mesh pSnailShape {
        \\  3;
        \\  0;0;0;,
        \\  1;0;0;,
        \\  0;1;0;;
        \\  1;
        \\  3;0,1,2;;
        \\}
    ;

    var doc = try parse(std.testing.allocator, source);
    defer doc.deinit();

    try std.testing.expectEqualStrings("MeshMaterialList", doc.frame_name);
    try std.testing.expectEqualStrings("pSnailShape", doc.mesh_name);
    try std.testing.expectEqual(@as(usize, 1), doc.materials.len);
    try std.testing.expectEqual(@as(usize, 3), doc.vertices.len);
    try std.testing.expectEqual(@as(usize, 3), doc.texcoords.len);
    try std.testing.expectEqual(@as(usize, 1), doc.polygons.len);
    try std.testing.expectEqual(@as(usize, 1), doc.triangle_count);
    try std.testing.expectEqualStrings("mSnail", doc.materials[0].name);
    try std.testing.expectEqualStrings("snail.tga", doc.materials[0].texture_filename.?);
}

test "topology matches across same mesh with different positions" {
    const source_a =
        \\Frame MeshMaterialList { 1; 1; 0; Material m { TextureFilename { "a.tga"; } } }
        \\MeshTextureCoords { 3; 0;0;, 1;0;, 0;1;; }
        \\Mesh shape { 3; 0;0;0;, 1;0;0;, 0;1;0;; 1; 3;0,1,2;; }
    ;
    const source_b =
        \\Frame MeshMaterialList { 1; 1; 0; Material m { TextureFilename { "a.tga"; } } }
        \\MeshTextureCoords { 3; 0;0;, 1;0;, 0;1;; }
        \\Mesh shape { 3; 0;0;1;, 1;0;1;, 0;1;1;; 1; 3;0,1,2;; }
    ;

    var a = try parse(std.testing.allocator, source_a);
    defer a.deinit();
    var b = try parse(std.testing.allocator, source_b);
    defer b.deinit();

    try std.testing.expect(sameTopology(&a, &b));
}

test "parse signstop model" {
    const data = try std.Io.Dir.cwd().readFileAlloc(io, "artifacts/extracted/SnailMail.dat/X/SIGNSTOP.X2", std.testing.allocator, .limited(1 << 20));
    defer std.testing.allocator.free(data);

    var doc = try parse(std.testing.allocator, data);
    defer doc.deinit();

    try std.testing.expectEqualStrings("MeshMaterialList", doc.frame_name);
    try std.testing.expectEqualStrings("pStopShape", doc.mesh_name);
    try std.testing.expectEqual(@as(usize, 1), doc.materials.len);
    try std.testing.expectEqual(@as(usize, 4), doc.vertices.len);
    try std.testing.expectEqual(@as(usize, 4), doc.texcoords.len);
    try std.testing.expectEqual(@as(usize, 1), doc.polygons.len);
    try std.testing.expectEqual(@as(usize, 2), doc.triangle_count);
    try std.testing.expectEqualStrings("mStopSG", doc.materials[0].name);
    try std.testing.expectEqualStrings("signStop.tga", doc.materials[0].texture_filename.?);
    try std.testing.expectEqual(@as(usize, 4), doc.polygons[0].indices.len);
}

test "parse pillar model" {
    const data = try std.Io.Dir.cwd().readFileAlloc(io, "artifacts/extracted/SnailMail.dat/X/PILLAR2.X2", std.testing.allocator, .limited(1 << 20));
    defer std.testing.allocator.free(data);

    var doc = try parse(std.testing.allocator, data);
    defer doc.deinit();

    try std.testing.expectEqualStrings("polySurfaceShape2", doc.mesh_name);
    try std.testing.expectEqual(@as(usize, 2), doc.materials.len);
    try std.testing.expectEqual(@as(usize, 39), doc.vertices.len);
    try std.testing.expectEqual(@as(usize, 39), doc.texcoords.len);
    try std.testing.expectEqual(@as(usize, 32), doc.polygons.len);
    try std.testing.expectEqual(@as(usize, 40), doc.triangle_count);
    try std.testing.expectEqualStrings("pillar.tga", doc.materials[0].texture_filename.?);
    try std.testing.expectEqual(@as(usize, 4), doc.polygons[0].indices.len);
    try std.testing.expectEqual(@as(usize, 3), doc.polygons[31].indices.len);
}

test "animation topology matches across turbo bobalong frames" {
    const first = try std.Io.Dir.cwd().readFileAlloc(io, "artifacts/extracted/SnailMail.dat/X/TURBO-BOBALONG-000.X2", std.testing.allocator, .limited(1 << 20));
    defer std.testing.allocator.free(first);
    const second = try std.Io.Dir.cwd().readFileAlloc(io, "artifacts/extracted/SnailMail.dat/X/TURBO-BOBALONG-001.X2", std.testing.allocator, .limited(1 << 20));
    defer std.testing.allocator.free(second);

    var doc_a = try parse(std.testing.allocator, first);
    defer doc_a.deinit();
    var doc_b = try parse(std.testing.allocator, second);
    defer doc_b.deinit();

    try std.testing.expect(sameTopology(&doc_a, &doc_b));
}

test "parse shipped x2 corpus" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    var parsed_count: usize = 0;
    for (catalog.model_entries) |entry| {
        const data = try catalog.readEntryAlloc(std.testing.allocator, entry);
        defer std.testing.allocator.free(data);

        var doc = try parse(std.testing.allocator, data);
        defer doc.deinit();

        try std.testing.expect(doc.materials.len > 0);
        try std.testing.expect(doc.vertices.len > 0);
        try std.testing.expect(doc.polygons.len > 0);
        try std.testing.expectEqual(doc.vertices.len, doc.texcoords.len);
        parsed_count += 1;
    }

    try std.testing.expectEqual(@as(usize, 124), parsed_count);
}

test "only hotspot pseudo-textures are unresolved in shipped x2 corpus" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    var unresolved_count: usize = 0;
    for (catalog.model_entries) |entry| {
        const data = try catalog.readEntryAlloc(std.testing.allocator, entry);
        defer std.testing.allocator.free(data);

        var doc = try parse(std.testing.allocator, data);
        defer doc.deinit();

        for (doc.materials) |material| {
            const texture_filename = material.texture_filename orelse continue;
            const texture_path = try archiveTexturePath(std.testing.allocator, texture_filename);
            defer std.testing.allocator.free(texture_path);

            if (catalog.findTextureEntry(texture_path) == null) {
                unresolved_count += 1;
                try std.testing.expectEqualStrings("X/TURBOHOTSPOTS.X2", entry.path);
            }
        }
    }

    try std.testing.expectEqual(@as(usize, 19), unresolved_count);
}

test "turbo hotspot camera centers match the shipped hotspot asset" {
    const data = try std.Io.Dir.cwd().readFileAlloc(io, "artifacts/extracted/SnailMail.dat/X/TURBOHOTSPOTS.X2", std.testing.allocator, .limited(1 << 20));
    defer std.testing.allocator.free(data);

    var doc = try parse(std.testing.allocator, data);
    defer doc.deinit();

    const skid_stop = materialBoundsByTextureFilename(&doc, "CameraSkidStop.tga").?;
    const slug_death = materialBoundsByTextureFilename(&doc, "CameraSlugDeath.tga").?;
    const intro_talk = materialBoundsByTextureFilename(&doc, "CameraIntroTalk.tga").?;

    try std.testing.expectApproxEqAbs(@as(f32, -0.54505), skid_stop.center.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), skid_stop.center.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.8749), skid_stop.center.z, 0.0001);

    try std.testing.expectApproxEqAbs(@as(f32, -0.0088), slug_death.center.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.7189), slug_death.center.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -5.4915), slug_death.center.z, 0.0001);

    try std.testing.expectApproxEqAbs(@as(f32, 0.862), intro_talk.center.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -0.13765), intro_talk.center.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.87215), intro_talk.center.z, 0.0001);
}
