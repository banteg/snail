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

pub const MaterialDef = struct {
    name: []const u8,
    texture_filename: ?[]const u8 = null,
    archive_texture_path: ?[]const u8 = null,
};

pub const Face = struct {
    indices: []const u16,
    material_index: usize = 0,
};

pub const ParsedModel = struct {
    arena: std.heap.ArenaAllocator,
    source_len: usize,
    trailing_nul_count: usize,
    frame_name: []const u8,
    mesh_name: []const u8,
    materials: []const MaterialDef,
    texcoords: []const Vec2,
    vertices: []const Vec3,
    faces: []const Face,
    total_triangle_count: usize,

    pub fn deinit(self: *ParsedModel) void {
        self.arena.deinit();
    }
};

pub const LoadedSubmesh = struct {
    mesh: rl.Mesh,
    material: rl.Material,
    texture: ?assets.LoadedTexture,
    material_name: []const u8,
    archive_texture_path: ?[]const u8,
    triangle_count: usize,

    pub fn unload(self: *LoadedSubmesh) void {
        self.material.unload();
        if (self.texture) |*texture| {
            texture.unload();
            self.texture = null;
        }
        self.mesh.unload();
    }
};

pub const LoadedModel = struct {
    allocator: std.mem.Allocator,
    parsed: ParsedModel,
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
    ) !LoadedModel {
        const decoded = try catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        var parsed = try parseModel(allocator, decoded);
        errdefer parsed.deinit();

        const submeshes = try buildSubmeshes(allocator, catalog, &parsed, flip_v);
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

    pub fn deinit(self: *LoadedModel) void {
        for (self.submeshes) |*submesh| {
            submesh.unload();
        }
        self.allocator.free(self.submeshes);
        self.parsed.deinit();
    }

    pub fn previewCamera(self: *const LoadedModel, time_seconds: f32) rl.Camera3D {
        const distance = @max(self.radius * 3.0, 3.0);
        return .{
            .position = .{
                .x = self.center.x + std.math.cos(time_seconds * 0.45) * distance,
                .y = self.center.y + distance * 0.5,
                .z = self.center.z + std.math.sin(time_seconds * 0.45) * distance,
            },
            .target = self.center,
            .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
            .fovy = 45.0,
            .projection = .perspective,
        };
    }

    pub fn draw(self: *const LoadedModel) void {
        for (self.submeshes) |submesh| {
            rl.drawMesh(submesh.mesh, submesh.material, rl.Matrix.identity());
        }
    }
};

const Bounds = struct {
    min: rl.Vector3,
    max: rl.Vector3,
    center: rl.Vector3,
    radius: f32,
};

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
        self.skipIgnored();

        if (self.index >= self.input.len) {
            return .{ .tag = .eof };
        }

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
                if (self.index < self.input.len) {
                    self.index += 1;
                }
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

    fn skipIgnored(self: *Lexer) void {
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
                        while (self.index < self.input.len and self.input[self.index] != '\n') {
                            self.index += 1;
                        }
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
    allocator: std.mem.Allocator,
    lexer: Lexer,
    current: Token = .{ .tag = .eof },

    fn parseDocument(self: *Parser) !ParsedModel {
        var arena = std.heap.ArenaAllocator.init(self.allocator);
        errdefer arena.deinit();
        const arena_allocator = arena.allocator();

        var materials_list: std.ArrayList(MaterialDef) = .empty;
        var faces_list: std.ArrayList(Face) = .empty;
        errdefer {
            materials_list.deinit(arena_allocator);
            faces_list.deinit(arena_allocator);
        }

        var frame_name: []const u8 = "";
        var mesh_name: []const u8 = "";
        var face_material_indices: []u16 = &.{};
        var texcoords: []Vec2 = &.{};
        var vertices: []Vec3 = &.{};
        var total_triangle_count: usize = 0;

        try self.advance();
        while (self.current.tag != .eof) {
            if (self.current.tag != .identifier) {
                try self.advance();
                continue;
            }

            if (std.mem.eql(u8, self.current.lexeme, "Frame") and frame_name.len == 0) {
                frame_name = try self.parseFrameMaterialList(arena_allocator, &materials_list, &face_material_indices);
                continue;
            }

            if (std.mem.eql(u8, self.current.lexeme, "MeshTextureCoords") and texcoords.len == 0) {
                texcoords = try self.parseMeshTextureCoords(arena_allocator);
                continue;
            }

            if (std.mem.eql(u8, self.current.lexeme, "Mesh") and mesh_name.len == 0) {
                const mesh = try self.parseMesh(arena_allocator, &faces_list);
                mesh_name = mesh.name;
                vertices = mesh.vertices;
                total_triangle_count = mesh.total_triangle_count;
                continue;
            }

            try self.advance();
        }

        if (materials_list.items.len == 0) {
            return error.MissingMaterialList;
        }
        if (vertices.len == 0) {
            return error.MissingMeshVertices;
        }
        if (texcoords.len != 0 and texcoords.len != vertices.len) {
            return error.InvalidTextureCoordinateCount;
        }
        if (face_material_indices.len != 0 and face_material_indices.len != faces_list.items.len) {
            return error.InvalidMaterialIndexCount;
        }

        const materials = try materials_list.toOwnedSlice(arena_allocator);
        const faces = try faces_list.toOwnedSlice(arena_allocator);

        for (materials) |*material| {
            material.archive_texture_path = try resolveTextureArchivePath(arena_allocator, material.texture_filename);
        }

        for (faces, 0..) |*face, face_index| {
            const material_index = if (face_material_indices.len > 0) face_material_indices[face_index] else 0;
            if (material_index >= materials.len) {
                face.material_index = 0;
            } else {
                face.material_index = material_index;
            }
        }

        return .{
            .arena = arena,
            .source_len = self.lexer.input.len,
            .trailing_nul_count = countTrailingNuls(self.lexer.input),
            .frame_name = frame_name,
            .mesh_name = mesh_name,
            .materials = materials,
            .texcoords = texcoords,
            .vertices = vertices,
            .faces = faces,
            .total_triangle_count = total_triangle_count,
        };
    }

    fn parseFrameMaterialList(
        self: *Parser,
        allocator: std.mem.Allocator,
        materials_list: *std.ArrayList(MaterialDef),
        face_material_indices: *[]u16,
    ) ![]const u8 {
        try self.advance();

        var frame_name: []const u8 = "";
        if (self.current.tag == .identifier) {
            frame_name = try allocator.dupe(u8, self.current.lexeme);
            try self.advance();
        }

        try self.expectTag(.lbrace);

        const material_count = try self.expectUnsigned();
        const face_material_count = try self.expectUnsigned();
        const indices = try allocator.alloc(u16, face_material_count);
        for (indices) |*index| {
            index.* = @intCast(try self.expectUnsigned());
        }
        face_material_indices.* = indices;

        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            if (self.current.tag == .identifier and std.mem.eql(u8, self.current.lexeme, "Material")) {
                try materials_list.append(allocator, try self.parseMaterial(allocator));
                continue;
            }
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }

        if (materials_list.items.len != material_count) {
            return error.InvalidMaterialCount;
        }

        return frame_name;
    }

    fn parseMaterial(self: *Parser, allocator: std.mem.Allocator) !MaterialDef {
        try self.advance();

        var material = MaterialDef{
            .name = "",
            .texture_filename = null,
        };
        if (self.current.tag == .identifier) {
            material.name = try allocator.dupe(u8, self.current.lexeme);
            try self.advance();
        }

        try self.expectTag(.lbrace);

        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            if (self.current.tag == .identifier and std.mem.eql(u8, self.current.lexeme, "TextureFilename")) {
                material.texture_filename = try self.parseTextureFilename(allocator);
                continue;
            }
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }

        return material;
    }

    fn parseTextureFilename(self: *Parser, allocator: std.mem.Allocator) !?[]const u8 {
        try self.advance();
        try self.expectTag(.lbrace);

        var filename: ?[]const u8 = null;
        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            if (self.current.tag == .string and filename == null) {
                filename = try allocator.dupe(u8, self.current.lexeme);
            }
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }

        return filename;
    }

    fn parseMeshTextureCoords(self: *Parser, allocator: std.mem.Allocator) ![]Vec2 {
        try self.advance();
        try self.expectTag(.lbrace);

        const texture_coord_count = try self.expectUnsigned();
        const texcoords = try allocator.alloc(Vec2, texture_coord_count);
        for (texcoords) |*coord| {
            coord.* = .{
                .x = try self.expectFloat(),
                .y = try self.expectFloat(),
            };
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }

        return texcoords;
    }

    fn parseMesh(
        self: *Parser,
        allocator: std.mem.Allocator,
        faces_list: *std.ArrayList(Face),
    ) !struct {
        name: []const u8,
        vertices: []Vec3,
        total_triangle_count: usize,
    } {
        try self.advance();

        var mesh_name: []const u8 = "";
        if (self.current.tag == .identifier) {
            mesh_name = try allocator.dupe(u8, self.current.lexeme);
            try self.advance();
        }

        try self.expectTag(.lbrace);

        const vertex_count = try self.expectUnsigned();
        const vertices = try allocator.alloc(Vec3, vertex_count);
        for (vertices) |*vertex| {
            vertex.* = .{
                .x = try self.expectFloat(),
                .y = try self.expectFloat(),
                .z = try self.expectFloat(),
            };
        }

        const face_count = try self.expectUnsigned();
        var total_triangle_count: usize = 0;
        for (0..face_count) |_| {
            const index_count = try self.expectUnsigned();
            if (index_count < 3) {
                return error.UnsupportedFace;
            }
            const indices = try allocator.alloc(u16, index_count);
            for (indices) |*index| {
                index.* = @intCast(try self.expectUnsigned());
            }
            total_triangle_count += index_count - 2;
            try faces_list.append(allocator, .{ .indices = indices });
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }

        return .{
            .name = mesh_name,
            .vertices = vertices,
            .total_triangle_count = total_triangle_count,
        };
    }

    fn advance(self: *Parser) !void {
        self.current = try self.lexer.next();
    }

    fn expectTag(self: *Parser, tag: TokenTag) !void {
        if (self.current.tag != tag) {
            return error.UnexpectedToken;
        }
        try self.advance();
    }

    fn expectNumber(self: *Parser) ![]const u8 {
        if (self.current.tag != .number) {
            return error.ExpectedNumber;
        }

        const lexeme = self.current.lexeme;
        try self.advance();
        return lexeme;
    }

    fn expectUnsigned(self: *Parser) !usize {
        const lexeme = try self.expectNumber();
        return std.fmt.parseUnsigned(usize, lexeme, 10);
    }

    fn expectFloat(self: *Parser) !f32 {
        const lexeme = try self.expectNumber();
        return std.fmt.parseFloat(f32, lexeme);
    }
};

pub fn parseModel(allocator: std.mem.Allocator, data: []const u8) !ParsedModel {
    var parser = Parser{
        .allocator = allocator,
        .lexer = .{ .input = data },
    };
    return parser.parseDocument();
}

fn buildSubmeshes(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    parsed: *const ParsedModel,
    flip_v: bool,
) ![]LoadedSubmesh {
    const material_slot_count = @max(parsed.materials.len, 1);
    const triangles_per_material = try allocator.alloc(usize, material_slot_count);
    defer allocator.free(triangles_per_material);
    @memset(triangles_per_material, 0);

    for (parsed.faces) |face| {
        const material_index = if (face.material_index < material_slot_count) face.material_index else 0;
        triangles_per_material[material_index] += face.indices.len - 2;
    }

    var submeshes: std.ArrayList(LoadedSubmesh) = .empty;
    defer submeshes.deinit(allocator);

    for (triangles_per_material, 0..) |triangle_count, material_index| {
        if (triangle_count == 0) continue;
        const submesh = try buildSubmesh(allocator, catalog, parsed, material_index, triangle_count, flip_v);
        errdefer {
            var doomed = submesh;
            doomed.unload();
        }
        try submeshes.append(allocator, submesh);
    }

    return submeshes.toOwnedSlice(allocator);
}

fn buildSubmesh(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    parsed: *const ParsedModel,
    material_index: usize,
    triangle_count: usize,
    flip_v: bool,
) !LoadedSubmesh {
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
        if (face.material_index != material_index) continue;
        if (face.indices.len < 3) continue;

        for (1..face.indices.len - 1) |fan_index| {
            const index0 = face.indices[0];
            const index1 = face.indices[fan_index];
            const index2 = face.indices[fan_index + 1];

            if (index0 >= parsed.vertices.len or index1 >= parsed.vertices.len or index2 >= parsed.vertices.len) {
                return error.InvalidVertexIndex;
            }

            const p0 = parsed.vertices[index0];
            const p1 = parsed.vertices[index1];
            const p2 = parsed.vertices[index2];
            const normal = computeNormal(p0, p1, p2);

            const uv0 = transformTexcoord(texcoordForIndex(parsed, index0), flip_v);
            const uv1 = transformTexcoord(texcoordForIndex(parsed, index1), flip_v);
            const uv2 = transformTexcoord(texcoordForIndex(parsed, index2), flip_v);

            writeVertex(vertices, &vertex_cursor, p0);
            writeVertex(vertices, &vertex_cursor, p1);
            writeVertex(vertices, &vertex_cursor, p2);

            writeTexcoord(texcoords, &texcoord_cursor, uv0);
            writeTexcoord(texcoords, &texcoord_cursor, uv1);
            writeTexcoord(texcoords, &texcoord_cursor, uv2);

            writeVertex(normals, &normal_cursor, normal);
            writeVertex(normals, &normal_cursor, normal);
            writeVertex(normals, &normal_cursor, normal);
        }
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

    var texture: ?assets.LoadedTexture = null;
    if (parsed.materials.len > material_index) {
        if (parsed.materials[material_index].archive_texture_path) |texture_path| {
            if (catalog.dat.entryByPath(texture_path)) |entry| {
                const loaded_texture = try catalog.loadTexture(allocator, entry);
                rl.setMaterialTexture(&material, .albedo, loaded_texture.texture);
                texture = loaded_texture;
            }
        }
    }

    return .{
        .mesh = mesh,
        .material = material,
        .texture = texture,
        .material_name = if (parsed.materials.len > material_index) parsed.materials[material_index].name else "default",
        .archive_texture_path = if (parsed.materials.len > material_index) parsed.materials[material_index].archive_texture_path else null,
        .triangle_count = triangle_count,
    };
}

fn texcoordForIndex(parsed: *const ParsedModel, index: usize) Vec2 {
    if (index < parsed.texcoords.len) {
        return parsed.texcoords[index];
    }
    return .{ .x = 0.0, .y = 0.0 };
}

fn transformTexcoord(coord: Vec2, flip_v: bool) Vec2 {
    if (!flip_v) return coord;
    return .{
        .x = coord.x,
        .y = 1.0 - coord.y,
    };
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
    const ab = Vec3{
        .x = b.x - a.x,
        .y = b.y - a.y,
        .z = b.z - a.z,
    };
    const ac = Vec3{
        .x = c.x - a.x,
        .y = c.y - a.y,
        .z = c.z - a.z,
    };

    const cross = Vec3{
        .x = ab.y * ac.z - ab.z * ac.y,
        .y = ab.z * ac.x - ab.x * ac.z,
        .z = ab.x * ac.y - ab.y * ac.x,
    };
    const length = std.math.sqrt(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);
    if (length <= 0.0001) {
        return .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    }

    return .{
        .x = cross.x / length,
        .y = cross.y / length,
        .z = cross.z / length,
    };
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

    var min = rl.Vector3{
        .x = vertices[0].x,
        .y = vertices[0].y,
        .z = vertices[0].z,
    };
    var max = min;

    for (vertices[1..]) |vertex| {
        min.x = @min(min.x, vertex.x);
        min.y = @min(min.y, vertex.y);
        min.z = @min(min.z, vertex.z);
        max.x = @max(max.x, vertex.x);
        max.y = @max(max.y, vertex.y);
        max.z = @max(max.z, vertex.z);
    }

    const center = rl.Vector3{
        .x = (min.x + max.x) * 0.5,
        .y = (min.y + max.y) * 0.5,
        .z = (min.z + max.z) * 0.5,
    };

    var radius: f32 = 0.5;
    for (vertices) |vertex| {
        const dx = vertex.x - center.x;
        const dy = vertex.y - center.y;
        const dz = vertex.z - center.z;
        radius = @max(radius, std.math.sqrt(dx * dx + dy * dy + dz * dz));
    }

    return .{
        .min = min,
        .max = max,
        .center = center,
        .radius = radius,
    };
}

fn resolveTextureArchivePath(allocator: std.mem.Allocator, texture_filename: ?[]const u8) !?[]const u8 {
    const filename = texture_filename orelse return null;
    const dot_index = std.mem.indexOfScalar(u8, filename, '.') orelse filename.len;

    var path: std.ArrayList(u8) = .empty;
    defer path.deinit(allocator);
    try path.appendSlice(allocator, "X/");
    try path.appendSlice(allocator, filename[0..dot_index]);
    try path.appendSlice(allocator, ".tga");
    return @as([]const u8, try path.toOwnedSlice(allocator));
}

fn countTrailingNuls(data: []const u8) usize {
    var count: usize = 0;
    var index = data.len;
    while (index > 0 and data[index - 1] == 0) {
        index -= 1;
        count += 1;
    }
    return count;
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

test "parse signstop model" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/X/SIGNSTOP.X2", 1 << 20);
    defer std.testing.allocator.free(data);

    var model = try parseModel(std.testing.allocator, data);
    defer model.deinit();

    try std.testing.expectEqualStrings("MeshMaterialList", model.frame_name);
    try std.testing.expectEqualStrings("pStopShape", model.mesh_name);
    try std.testing.expectEqual(@as(usize, 1), model.materials.len);
    try std.testing.expectEqual(@as(usize, 4), model.vertices.len);
    try std.testing.expectEqual(@as(usize, 4), model.texcoords.len);
    try std.testing.expectEqual(@as(usize, 1), model.faces.len);
    try std.testing.expectEqual(@as(usize, 2), model.total_triangle_count);
    try std.testing.expectEqualStrings("mStopSG", model.materials[0].name);
    try std.testing.expectEqualStrings("signStop.tga", model.materials[0].texture_filename.?);
    try std.testing.expectEqualStrings("X/signStop.tga", model.materials[0].archive_texture_path.?);
    try std.testing.expectEqual(@as(usize, 4), model.faces[0].indices.len);
    try std.testing.expectEqual(@as(usize, 1), model.trailing_nul_count);
}

test "parse pillar model" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/X/PILLAR2.X2", 1 << 20);
    defer std.testing.allocator.free(data);

    var model = try parseModel(std.testing.allocator, data);
    defer model.deinit();

    try std.testing.expectEqualStrings("polySurfaceShape2", model.mesh_name);
    try std.testing.expectEqual(@as(usize, 2), model.materials.len);
    try std.testing.expectEqual(@as(usize, 39), model.vertices.len);
    try std.testing.expectEqual(@as(usize, 39), model.texcoords.len);
    try std.testing.expectEqual(@as(usize, 32), model.faces.len);
    try std.testing.expectEqual(@as(usize, 56), model.total_triangle_count);
    try std.testing.expectEqualStrings("pillar.tga", model.materials[0].texture_filename.?);
    try std.testing.expectEqualStrings("X/pillar.tga", model.materials[0].archive_texture_path.?);
    try std.testing.expectEqual(@as(usize, 4), model.faces[0].indices.len);
    try std.testing.expectEqual(@as(usize, 4), model.faces[31].indices.len);
}
