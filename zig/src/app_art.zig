const std = @import("std");

const app = @import("app.zig");
const assets = @import("assets.zig");
const frontend_widget = @import("frontend/widget.zig");
const galaxy = @import("galaxy.zig");
const resource_store = @import("resource_store.zig");

pub const SliderArt = struct {
    less: ?assets.LoadedTexture = null,
    less_hover: ?assets.LoadedTexture = null,
    more: ?assets.LoadedTexture = null,
    more_hover: ?assets.LoadedTexture = null,
    bar: ?assets.LoadedTexture = null,
    bar_full: ?assets.LoadedTexture = null,

    pub fn unload(self: *SliderArt) void {
        if (self.less) |*texture| {
            texture.unload();
            self.less = null;
        }
        if (self.less_hover) |*texture| {
            texture.unload();
            self.less_hover = null;
        }
        if (self.more) |*texture| {
            texture.unload();
            self.more = null;
        }
        if (self.more_hover) |*texture| {
            texture.unload();
            self.more_hover = null;
        }
        if (self.bar) |*texture| {
            texture.unload();
            self.bar = null;
        }
        if (self.bar_full) |*texture| {
            texture.unload();
            self.bar_full = null;
        }
    }

    pub fn textures(self: SliderArt) frontend_widget.SliderTextures {
        return .{
            .less = if (self.less) |texture| texture.texture else null,
            .less_hover = if (self.less_hover) |texture| texture.texture else null,
            .more = if (self.more) |texture| texture.texture else null,
            .more_hover = if (self.more_hover) |texture| texture.texture else null,
            .bar = if (self.bar) |texture| texture.texture else null,
            .bar_full = if (self.bar_full) |texture| texture.texture else null,
        };
    }
};

pub const FrontendWidgetArt = struct {
    border: ?assets.LoadedTexture = null,
    parcel_icon: ?assets.LoadedTexture = null,

    pub fn unload(self: *FrontendWidgetArt) void {
        if (self.border) |*texture| {
            texture.unload();
            self.border = null;
        }
        if (self.parcel_icon) |*texture| {
            texture.unload();
            self.parcel_icon = null;
        }
    }
};

pub const FrontendSoundFx = struct {
    highlight: ?assets.LoadedSound = null,
    select: ?assets.LoadedSound = null,

    pub fn unload(self: *FrontendSoundFx) void {
        if (self.highlight) |*sound| {
            sound.unload();
            self.highlight = null;
        }
        if (self.select) |*sound| {
            sound.unload();
            self.select = null;
        }
    }
};

pub const RouteMapArt = struct {
    logo: ?assets.LoadedTexture = null,
    border: ?assets.LoadedTexture = null,
    galaxy_select: ?assets.LoadedTexture = null,
    level_select: ?assets.LoadedTexture = null,
    level_star: ?assets.LoadedTexture = null,
    line: ?assets.LoadedTexture = null,
    line_star: ?assets.LoadedTexture = null,
    galaxies: [galaxy.map_galaxy_count]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** galaxy.map_galaxy_count,

    pub fn unload(self: *RouteMapArt) void {
        if (self.logo) |*texture| {
            texture.unload();
            self.logo = null;
        }
        if (self.border) |*texture| {
            texture.unload();
            self.border = null;
        }
        if (self.galaxy_select) |*texture| {
            texture.unload();
            self.galaxy_select = null;
        }
        if (self.level_select) |*texture| {
            texture.unload();
            self.level_select = null;
        }
        if (self.level_star) |*texture| {
            texture.unload();
            self.level_star = null;
        }
        if (self.line) |*texture| {
            texture.unload();
            self.line = null;
        }
        if (self.line_star) |*texture| {
            texture.unload();
            self.line_star = null;
        }
        for (&self.galaxies) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
    }
};

pub fn loadFrontendWidgetArt(store: *resource_store.Store) !FrontendWidgetArt {
    var art = FrontendWidgetArt{};
    errdefer art.unload();

    art.border = try store.texture(app.widget_border_texture_path);
    art.parcel_icon = try store.texture(app.completion_parcel_icon_texture_path);

    return art;
}

pub fn loadFrontendSoundFx(store: *resource_store.Store) !FrontendSoundFx {
    var sound_fx = FrontendSoundFx{};
    errdefer sound_fx.unload();

    sound_fx.highlight = try store.sound(app.frontend_highlight_sound_path);
    sound_fx.select = try store.sound(app.frontend_select_sound_path);

    return sound_fx;
}

pub fn loadSliderArt(store: *resource_store.Store) !SliderArt {
    var art = SliderArt{};
    errdefer art.unload();

    art.less = try store.texture(app.slider_less_texture_path);
    art.less_hover = try store.texture(app.slider_less_hover_texture_path);
    art.more = try store.texture(app.slider_more_texture_path);
    art.more_hover = try store.texture(app.slider_more_hover_texture_path);
    art.bar = try store.texture(app.slider_bar_texture_path);
    art.bar_full = try store.texture(app.slider_bar_full_texture_path);

    return art;
}

pub fn loadRouteMapArt(store: *resource_store.Store) !RouteMapArt {
    var art = RouteMapArt{};
    errdefer art.unload();

    art.logo = try store.texture(app.route_map_logo_texture_path);
    art.border = try store.texture(app.route_map_border_texture_path);
    art.galaxy_select = try store.texture(app.route_map_galaxy_select_texture_path);
    art.level_select = try store.texture(app.route_map_level_select_texture_path);
    art.level_star = try store.texture(app.route_map_level_star_texture_path);
    art.line = try store.texture(app.route_map_line_texture_path);
    art.line_star = try store.texture(app.route_map_line_star_texture_path);
    for (app.route_map_galaxy_texture_paths, 0..) |path, index| {
        art.galaxies[index] = try store.texture(path);
    }

    return art;
}
