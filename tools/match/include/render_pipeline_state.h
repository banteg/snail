// Process-owned state shared across camera setup, object/sprite submission,
// overlay transform saves, and per-frame render accounting.
#ifndef RENDER_PIPELINE_STATE_H
#define RENDER_PIPELINE_STATE_H

#include "transform_matrix.h"

extern int g_render_triangle_count; // data_4f7450
extern int g_render_successful_primitive_count; // data_4f7454
extern int g_draw_primitive_call_count; // data_503170

extern float g_render_projection_param_b; // data_50316c
extern TransformMatrix g_saved_d3d_view_transform; // data_503178
extern TransformMatrix* g_render_camera_source_matrix; // data_5031b8
extern int g_texture_bind_call_count; // data_5031c0
extern float g_render_projection_near_z; // data_5031cc
extern float g_render_projection_far_z; // data_5031d0
extern float g_render_projection_param_a; // data_5031d4
extern TransformMatrix g_object_texture_transform_matrix; // data_5031d8
extern TransformMatrix* g_render_camera_view_matrix; // data_503218
extern TransformMatrix g_saved_d3d_projection_transform; // data_503220
extern unsigned char g_object_render_pass_filter; // data_503260

#endif
