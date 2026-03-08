const std = @import("std");

pub const MaterialSummary = struct {
    name: []const u8,
    texture_filename: ?[]const u8 = null,
};

pub const MeshSummary = struct {
    name: []const u8,
    vertex_count: usize,
    face_count: usize,
};

pub const Summary = struct {
    arena: std.heap.ArenaAllocator,
    source_len: usize,
    trailing_nul_count: usize,
    frame_count: usize,
    material_count: usize,
    mesh_texture_coord_block_count: usize,
    texture_filename_count: usize,
    mesh_count: usize,
    total_texture_coords: usize,
    total_vertices: usize,
    total_faces: usize,
    materials: []const MaterialSummary,
    meshes: []const MeshSummary,
    texture_filenames: []const []const u8,

    pub fn deinit(self: *Summary) void {
        self.arena.deinit();
    }
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
    materials: std.ArrayList(MaterialSummary),
    meshes: std.ArrayList(MeshSummary),
    texture_filenames: std.ArrayList([]const u8),
    frame_count: usize = 0,
    material_count: usize = 0,
    mesh_texture_coord_block_count: usize = 0,
    texture_filename_count: usize = 0,
    mesh_count: usize = 0,
    total_texture_coords: usize = 0,
    total_vertices: usize = 0,
    total_faces: usize = 0,

    fn advance(self: *Parser) !void {
        self.current = try self.lexer.next();
    }

    fn parseDocument(self: *Parser) !void {
        try self.advance();
        while (self.current.tag != .eof) {
            if (self.current.tag != .identifier) {
                try self.advance();
                continue;
            }

            if (std.mem.eql(u8, self.current.lexeme, "Frame")) {
                try self.parseFrame();
                continue;
            }
            if (std.mem.eql(u8, self.current.lexeme, "Material")) {
                try self.parseMaterial();
                continue;
            }
            if (std.mem.eql(u8, self.current.lexeme, "MeshTextureCoords")) {
                try self.parseMeshTextureCoords();
                continue;
            }
            if (std.mem.eql(u8, self.current.lexeme, "Mesh")) {
                try self.parseMesh();
                continue;
            }
            if (std.mem.eql(u8, self.current.lexeme, "TextureFilename")) {
                _ = try self.parseTextureFilename();
                continue;
            }

            try self.advance();
        }
    }

    fn parseFrame(self: *Parser) !void {
        self.frame_count += 1;
        try self.advance();

        if (self.current.tag == .identifier) {
            try self.advance();
        }

        if (self.current.tag != .lbrace) {
            return error.ExpectedBlockStart;
        }
        try self.advance();

        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            if (self.current.tag == .identifier and std.mem.eql(u8, self.current.lexeme, "Material")) {
                try self.parseMaterial();
                continue;
            }
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }
    }

    fn parseMaterial(self: *Parser) !void {
        self.material_count += 1;
        try self.advance();

        var material = MaterialSummary{
            .name = "",
            .texture_filename = null,
        };
        if (self.current.tag == .identifier) {
            material.name = try self.dupe(self.current.lexeme);
            try self.advance();
        }

        if (self.current.tag != .lbrace) {
            return error.ExpectedBlockStart;
        }
        try self.advance();

        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            if (self.current.tag == .identifier and std.mem.eql(u8, self.current.lexeme, "TextureFilename")) {
                material.texture_filename = try self.parseTextureFilename();
                continue;
            }
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }

        try self.materials.append(self.allocator, material);
    }

    fn parseTextureFilename(self: *Parser) !?[]const u8 {
        self.texture_filename_count += 1;
        try self.advance();

        if (self.current.tag != .lbrace) {
            return error.ExpectedBlockStart;
        }
        try self.advance();

        var filename: ?[]const u8 = null;
        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            if (self.current.tag == .string and filename == null) {
                filename = try self.dupe(self.current.lexeme);
                try self.texture_filenames.append(self.allocator, filename.?);
            }
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }

        return filename;
    }

    fn parseMeshTextureCoords(self: *Parser) !void {
        self.mesh_texture_coord_block_count += 1;
        try self.advance();

        if (self.current.tag != .lbrace) {
            return error.ExpectedBlockStart;
        }
        try self.advance();

        const texture_coord_count = try self.expectUnsigned();
        self.total_texture_coords += texture_coord_count;

        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }
    }

    fn parseMesh(self: *Parser) !void {
        self.mesh_count += 1;
        try self.advance();

        var mesh = MeshSummary{
            .name = "",
            .vertex_count = 0,
            .face_count = 0,
        };
        if (self.current.tag == .identifier) {
            mesh.name = try self.dupe(self.current.lexeme);
            try self.advance();
        }

        if (self.current.tag != .lbrace) {
            return error.ExpectedBlockStart;
        }
        try self.advance();

        mesh.vertex_count = try self.expectUnsigned();
        try self.skipNumbers(try std.math.mul(usize, mesh.vertex_count, 3));

        mesh.face_count = try self.expectUnsigned();
        for (0..mesh.face_count) |_| {
            const face_vertex_count = try self.expectUnsigned();
            try self.skipNumbers(face_vertex_count);
        }

        self.total_vertices += mesh.vertex_count;
        self.total_faces += mesh.face_count;
        try self.meshes.append(self.allocator, mesh);

        while (self.current.tag != .eof and self.current.tag != .rbrace) {
            try self.advance();
        }

        if (self.current.tag == .rbrace) {
            try self.advance();
        }
    }

    fn skipNumbers(self: *Parser, count: usize) !void {
        for (0..count) |_| {
            _ = try self.expectNumber();
        }
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

    fn dupe(self: *Parser, value: []const u8) ![]const u8 {
        return self.allocator.dupe(u8, value);
    }
};

pub fn parseSummary(allocator: std.mem.Allocator, data: []const u8) !Summary {
    var arena = std.heap.ArenaAllocator.init(allocator);
    errdefer arena.deinit();
    const arena_allocator = arena.allocator();

    var parser = Parser{
        .allocator = arena_allocator,
        .lexer = .{ .input = data },
        .materials = .empty,
        .meshes = .empty,
        .texture_filenames = .empty,
    };

    try parser.parseDocument();

    return .{
        .arena = arena,
        .source_len = data.len,
        .trailing_nul_count = countTrailingNuls(data),
        .frame_count = parser.frame_count,
        .material_count = parser.material_count,
        .mesh_texture_coord_block_count = parser.mesh_texture_coord_block_count,
        .texture_filename_count = parser.texture_filename_count,
        .mesh_count = parser.mesh_count,
        .total_texture_coords = parser.total_texture_coords,
        .total_vertices = parser.total_vertices,
        .total_faces = parser.total_faces,
        .materials = try parser.materials.toOwnedSlice(arena_allocator),
        .meshes = try parser.meshes.toOwnedSlice(arena_allocator),
        .texture_filenames = try parser.texture_filenames.toOwnedSlice(arena_allocator),
    };
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

test "parse signstop summary" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/X/SIGNSTOP.X2", 1 << 20);
    defer std.testing.allocator.free(data);

    var summary = try parseSummary(std.testing.allocator, data);
    defer summary.deinit();

    try std.testing.expectEqual(@as(usize, 1), summary.frame_count);
    try std.testing.expectEqual(@as(usize, 1), summary.material_count);
    try std.testing.expectEqual(@as(usize, 1), summary.mesh_texture_coord_block_count);
    try std.testing.expectEqual(@as(usize, 1), summary.mesh_count);
    try std.testing.expectEqual(@as(usize, 4), summary.total_texture_coords);
    try std.testing.expectEqual(@as(usize, 4), summary.total_vertices);
    try std.testing.expectEqual(@as(usize, 1), summary.total_faces);
    try std.testing.expectEqualStrings("mStopSG", summary.materials[0].name);
    try std.testing.expectEqualStrings("signStop.tga", summary.texture_filenames[0]);
    try std.testing.expectEqualStrings("pStopShape", summary.meshes[0].name);
    try std.testing.expect(summary.trailing_nul_count > 0);
}

test "parse pillar summary" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/X/PILLAR2.X2", 1 << 20);
    defer std.testing.allocator.free(data);

    var summary = try parseSummary(std.testing.allocator, data);
    defer summary.deinit();

    try std.testing.expectEqual(@as(usize, 1), summary.frame_count);
    try std.testing.expectEqual(@as(usize, 2), summary.material_count);
    try std.testing.expectEqual(@as(usize, 1), summary.mesh_texture_coord_block_count);
    try std.testing.expectEqual(@as(usize, 1), summary.mesh_count);
    try std.testing.expectEqual(@as(usize, 39), summary.total_texture_coords);
    try std.testing.expectEqual(@as(usize, 39), summary.total_vertices);
    try std.testing.expectEqual(@as(usize, 32), summary.total_faces);
    try std.testing.expectEqualStrings("pillar.tga", summary.texture_filenames[0]);
    try std.testing.expectEqualStrings("polySurfaceShape2", summary.meshes[0].name);
}
