const std = @import("std");

const app = @import("../app.zig");
const assets = @import("../assets.zig");
const frontend_widget = @import("widget.zig");
const galaxy = @import("../galaxy.zig");
const resource_store = @import("../resource_store.zig");

pub const SliderArt = struct {
    less: assets.LoadedTexture,
    less_hover: assets.LoadedTexture,
    more: assets.LoadedTexture,
    more_hover: assets.LoadedTexture,
    bar: assets.LoadedTexture,
    bar_full: assets.LoadedTexture,

    pub fn unload(self: *SliderArt) void {
        self.less.unload();
        self.less_hover.unload();
        self.more.unload();
        self.more_hover.unload();
        self.bar.unload();
        self.bar_full.unload();
    }

    pub fn textures(self: SliderArt) frontend_widget.SliderTextures {
        return .{
            .less = self.less.texture,
            .less_hover = self.less_hover.texture,
            .more = self.more.texture,
            .more_hover = self.more_hover.texture,
            .bar = self.bar.texture,
            .bar_full = self.bar_full.texture,
        };
    }
};

pub const FrontendWidgetArt = struct {
    border: assets.LoadedTexture,
    parcel_icon: assets.LoadedTexture,

    pub fn unload(self: *FrontendWidgetArt) void {
        self.border.unload();
        self.parcel_icon.unload();
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
    logo: assets.LoadedTexture,
    border: assets.LoadedTexture,
    galaxy_select: assets.LoadedTexture,
    level_select: assets.LoadedTexture,
    level_star: assets.LoadedTexture,
    line: assets.LoadedTexture,
    line_star: assets.LoadedTexture,
    galaxies: [galaxy.map_galaxy_count]assets.LoadedTexture,

    pub fn unload(self: *RouteMapArt) void {
        self.logo.unload();
        self.border.unload();
        self.galaxy_select.unload();
        self.level_select.unload();
        self.level_star.unload();
        self.line.unload();
        self.line_star.unload();
        for (&self.galaxies) |*texture| {
            texture.unload();
        }
    }
};

pub fn loadFrontendWidgetArt(store: *resource_store.Store) !FrontendWidgetArt {
    var border = try store.texture(app.widget_border_texture_path);
    errdefer border.unload();
    var parcel_icon = try store.texture(app.completion_parcel_icon_texture_path);
    errdefer parcel_icon.unload();

    return .{
        .border = border,
        .parcel_icon = parcel_icon,
    };
}

pub fn loadFrontendSoundFx(store: *resource_store.Store) !FrontendSoundFx {
    var sound_fx = FrontendSoundFx{};
    errdefer sound_fx.unload();

    sound_fx.highlight = try store.sound(app.frontend_highlight_sound_path);
    sound_fx.select = try store.sound(app.frontend_select_sound_path);

    return sound_fx;
}

pub fn loadSliderArt(store: *resource_store.Store) !SliderArt {
    var less = try store.texture(app.slider_less_texture_path);
    errdefer less.unload();
    var less_hover = try store.texture(app.slider_less_hover_texture_path);
    errdefer less_hover.unload();
    var more = try store.texture(app.slider_more_texture_path);
    errdefer more.unload();
    var more_hover = try store.texture(app.slider_more_hover_texture_path);
    errdefer more_hover.unload();
    var bar = try store.texture(app.slider_bar_texture_path);
    errdefer bar.unload();
    var bar_full = try store.texture(app.slider_bar_full_texture_path);
    errdefer bar_full.unload();

    return .{
        .less = less,
        .less_hover = less_hover,
        .more = more,
        .more_hover = more_hover,
        .bar = bar,
        .bar_full = bar_full,
    };
}

pub fn loadRouteMapArt(store: *resource_store.Store) !RouteMapArt {
    var logo = try store.texture(app.route_map_logo_texture_path);
    errdefer logo.unload();
    var border = try store.texture(app.route_map_border_texture_path);
    errdefer border.unload();
    var galaxy_select = try store.texture(app.route_map_galaxy_select_texture_path);
    errdefer galaxy_select.unload();
    var level_select = try store.texture(app.route_map_level_select_texture_path);
    errdefer level_select.unload();
    var level_star = try store.texture(app.route_map_level_star_texture_path);
    errdefer level_star.unload();
    var line = try store.texture(app.route_map_line_texture_path);
    errdefer line.unload();
    var line_star = try store.texture(app.route_map_line_star_texture_path);
    errdefer line_star.unload();

    var galaxies: [galaxy.map_galaxy_count]assets.LoadedTexture = undefined;
    var loaded_galaxy_count: usize = 0;
    errdefer {
        for (galaxies[0..loaded_galaxy_count]) |*loaded| {
            loaded.unload();
        }
    }
    for (app.route_map_galaxy_texture_paths, 0..) |path, index| {
        galaxies[index] = try store.texture(path);
        loaded_galaxy_count += 1;
    }

    return .{
        .logo = logo,
        .border = border,
        .galaxy_select = galaxy_select,
        .level_select = level_select,
        .level_star = level_star,
        .line = line,
        .line_star = line_star,
        .galaxies = galaxies,
    };
}
