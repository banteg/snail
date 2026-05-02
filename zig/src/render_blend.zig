const rl = @import("raylib");

pub const gl_src_color = 0x0300;
pub const gl_src_alpha = 0x0302;
pub const gl_one_minus_src_alpha = 0x0303;
pub const gl_zero = 0;
pub const gl_one = 1;
pub const gl_func_add = 0x8006;

pub fn beginPreservingFramebufferAlpha(src_rgb: i32, dst_rgb: i32) void {
    rl.gl.rlSetBlendFactorsSeparate(src_rgb, dst_rgb, gl_zero, gl_one, gl_func_add, gl_func_add);
    rl.beginBlendMode(.custom_separate);
}

pub fn beginAlphaPreservingFramebufferAlpha() void {
    beginPreservingFramebufferAlpha(gl_src_alpha, gl_one_minus_src_alpha);
}

pub fn beginAdditivePreservingFramebufferAlpha() void {
    beginPreservingFramebufferAlpha(gl_src_alpha, gl_one);
}

pub fn beginOneOnePreservingFramebufferAlpha() void {
    beginPreservingFramebufferAlpha(gl_one, gl_one);
}

pub fn beginSrcAlphaSrcColorPreservingFramebufferAlpha() void {
    beginPreservingFramebufferAlpha(gl_src_alpha, gl_src_color);
}
