import json
import pathlib
import re
import sys

import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc


TRUSTED_NAMES = [
    (0x404580, "border_mouse_test"),
    (0x4086D0, "initialize_player_presentation_controller"),
    (0x44C870, "initialize_global_identity_matrix_thunk"),
    (0x44C880, "initialize_global_identity_matrix"),
    (0x44CAC0, "multiply_vector_by_matrix_copy"),
    (0x44CB50, "dot_vectors"),
    (0x44CB70, "dot_vector"),
    (0x44CB90, "multiply_vector_by_matrix"),
    (0x44CC20, "rotate_vector_by_matrix"),
    (0x44CCA0, "normalize_vector"),
    (0x44CCF0, "vector_magnitude"),
    (0x44CD20, "normalize_vector_from_source"),
    (0x44CD40, "cross_vectors"),
    (0x44CDE0, "initialize_uniform_scale_matrix"),
    (0x44CE30, "rotate_matrix_local_x"),
    (0x44CEC0, "rotate_matrix_local_y"),
    (0x44CF50, "rotate_matrix_local_z"),
    (0x44CFE0, "initialize_matrix_from_values"),
    (0x44D060, "multiply_matrices"),
    (0x44D1A0, "multiply_matrix"),
    (0x44D1D0, "multiply_matrix_in_place_forward_thunk"),
    (0x44D1E0, "premultiply_matrix_in_place"),
    (0x44D530, "initialize_quaternion_from_axis"),
    (0x44D580, "initialize_axis_from_quaternion"),
    (0x44D5D0, "initialize_quaternion_from_matrix"),
    (0x44D820, "initialize_matrix_from_quaternion"),
    (0x44D920, "interpolate_matrix_rotation"),
    (0x4AC5C8, "g_default_tip_message"),
    (0x497354, "g_player_presentation_noop_vtable"),
    (0x497358, "g_invincible_shell_update_vtable"),
    (0x49735C, "g_presentation_animation_channel_noop_vtable"),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x4AC5C8, "g_default_tip_message", "TipData g_default_tip_message;"),
]


TRUSTED_DECLARATIONS = [
    (
        "uninit_pause_menu",
        "void __thiscall uninit_pause_menu(SubPause* pause);",
    ),
    (
        "initialize_pause_menu",
        "void __thiscall initialize_pause_menu(SubPause* pause);",
    ),
    (
        "update_pause_menu",
        "void __thiscall update_pause_menu(SubPause* pause);",
    ),
    (
        "initialize_sub_loc",
        "SubLoc* __thiscall initialize_sub_loc(SubLoc* cell);",
    ),
    (
        "remove_sub_loc",
        "void __thiscall remove_sub_loc(SubLoc* cell);",
    ),
    (
        "update_sub_loc",
        "void __thiscall update_sub_loc(SubLoc* cell);",
    ),
    (
        "get_track_cell_row_index",
        "int32_t __thiscall get_track_cell_row_index(SubLoc* cell);",
    ),
    (
        "find_segment_path_index_by_name",
        "int32_t __thiscall find_segment_path_index_by_name(PathManager *manager, char *name);",
    ),
    (
        "border_mouse_test",
        "uint8_t __thiscall border_mouse_test(FrontendWidget* widget);",
    ),
    (
        "initialize_player_presentation_controller",
        "Snail* __thiscall initialize_player_presentation_controller(Snail* snail);",
    ),
    (
        "initialize_global_identity_matrix_thunk",
        "void __cdecl initialize_global_identity_matrix_thunk();",
    ),
    (
        "initialize_global_identity_matrix",
        "void __cdecl initialize_global_identity_matrix();",
    ),
    (
        "initialize_uniform_scale_matrix",
        "TransformMatrix* __thiscall initialize_uniform_scale_matrix(TransformMatrix* transform, float scale);",
    ),
    (
        "multiply_vector_by_matrix_copy",
        "Vec3* __thiscall multiply_vector_by_matrix_copy(const Vec3* vector, Vec3* out, const TransformMatrix* matrix);",
    ),
    (
        "multiply_vector_by_matrix",
        "void __thiscall multiply_vector_by_matrix(Vec3* vector, TransformMatrix matrix);",
    ),
    (
        "rotate_vector_by_matrix",
        "Vec3* __thiscall rotate_vector_by_matrix(Vec3* vector, const TransformMatrix* matrix);",
    ),
    (
        "dot_vectors",
        "double __stdcall dot_vectors(const Vec3* lhs, const Vec3* rhs);",
    ),
    (
        "dot_vector",
        "float __thiscall dot_vector(const Vec3* vector, const Vec3* rhs);",
    ),
    (
        "normalize_vector",
        "float __thiscall normalize_vector(Vec3* vector);",
    ),
    (
        "vector_magnitude",
        "float __thiscall vector_magnitude(const Vec3* vector);",
    ),
    (
        "normalize_vector_from_source",
        "float __thiscall normalize_vector_from_source(Vec3* out, const Vec3* src);",
    ),
    (
        "cross_vectors",
        "void __thiscall cross_vectors(Vec3* out, const Vec3* lhs, const Vec3* rhs);",
    ),
    (
        "noop_this_constructor",
        "void* __thiscall noop_this_constructor(void* self);",
    ),
    (
        "get_or_create_texture_ref",
        "TextureRef* __thiscall get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, int32_t arg3, int16_t arg4);",
    ),
    (
        "allocate_path_template_samples",
        "void __fastcall allocate_path_template_samples(Path* self);",
    ),
    (
        "finalize_path_template",
        "int32_t __fastcall finalize_path_template(Path* self);",
    ),
    (
        "mirror_path_template_pair_x",
        "int32_t __thiscall mirror_path_template_pair_x(Path* self, Path* source);",
    ),
    (
        "set_matrix_identity",
        "void __thiscall set_matrix_identity(TransformMatrix* transform);",
    ),
    (
        "set_matrix_rotation_identity",
        "void __thiscall set_matrix_rotation_identity(TransformMatrix* transform);",
    ),
    (
        "initialize_matrix_from_values",
        "TransformMatrix* __thiscall initialize_matrix_from_values(TransformMatrix* transform, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);",
    ),
    (
        "initialize_quaternion_from_axis",
        "void __thiscall initialize_quaternion_from_axis(Quaternion* out, const AxisAngle* axis);",
    ),
    (
        "initialize_axis_from_quaternion",
        "void __thiscall initialize_axis_from_quaternion(AxisAngle* out, const Quaternion* quaternion);",
    ),
    (
        "initialize_quaternion_from_matrix",
        "Quaternion* __thiscall initialize_quaternion_from_matrix(Quaternion* out, const TransformMatrix* matrix);",
    ),
    (
        "initialize_matrix_from_quaternion",
        "TransformMatrix* __thiscall initialize_matrix_from_quaternion(TransformMatrix* out, const Quaternion* quaternion);",
    ),
    (
        "rotate_matrix_local_x",
        "void __thiscall rotate_matrix_local_x(TransformMatrix* transform, float angle);",
    ),
    (
        "rotate_matrix_local_y",
        "void __thiscall rotate_matrix_local_y(TransformMatrix* transform, float angle);",
    ),
    (
        "rotate_matrix_local_z",
        "void __thiscall rotate_matrix_local_z(TransformMatrix* transform, float angle);",
    ),
    (
        "orthogonalize_matrix",
        "void __thiscall orthogonalize_matrix(TransformMatrix* transform);",
    ),
    (
        "invert_matrix_in_place",
        "void __thiscall invert_matrix_in_place(TransformMatrix* transform);",
    ),
    (
        "invert_matrix_from_source",
        "void __thiscall invert_matrix_from_source(TransformMatrix* out, const TransformMatrix* source);",
    ),
    (
        "multiply_matrices",
        "void __thiscall multiply_matrices(TransformMatrix* out, const TransformMatrix* lhs, const TransformMatrix* rhs);",
    ),
    (
        "multiply_matrix",
        "void __thiscall multiply_matrix(TransformMatrix* matrix, const TransformMatrix* rhs);",
    ),
    (
        "multiply_matrix_in_place_forward_thunk",
        "void __thiscall multiply_matrix_in_place_forward_thunk(TransformMatrix* matrix, const TransformMatrix* rhs);",
    ),
    (
        "premultiply_matrix_in_place",
        "void __thiscall premultiply_matrix_in_place(TransformMatrix* matrix, const TransformMatrix* lhs);",
    ),
    (
        "set_matrix_z_direction",
        "void __thiscall set_matrix_z_direction(TransformMatrix* transform, const Vec3* direction);",
    ),
    (
        "look_at_point",
        "void __thiscall look_at_point(TransformMatrix* transform, const Vec3* target);",
    ),
    (
        "interpolate_matrix_rotation",
        "void __thiscall interpolate_matrix_rotation(TransformMatrix* transform, float alpha);",
    ),
    (
        "linear_interpolate_matrix",
        "void __thiscall linear_interpolate_matrix(TransformMatrix* out, const TransformMatrix* from, const TransformMatrix* to, float alpha);",
    ),
    (
        "compute_kind42_attachment_transform",
        "void __thiscall compute_kind42_attachment_transform(Path* self, float radius, float x, float y, TransformMatrix* transform, float* out_angle);",
    ),
    (
        "request_object_vertices",
        "void __thiscall request_object_vertices(Object* object, int32_t vertex_count);",
    ),
    (
        "request_object_vertex_colours",
        "void __fastcall request_object_vertex_colours(Object* object);",
    ),
    (
        "request_object_facequads",
        "void __thiscall request_object_facequads(Object* object, int32_t facequad_count);",
    ),
    (
        "set_color_rgba",
        "tColour* __thiscall set_color_rgba(tColour* color, float r, float g, float b, float a);",
    ),
    (
        "parse_next_int32",
        "int32_t __cdecl parse_next_int32(char** cursor);",
    ),
    (
        "parse_next_space_delimited_token",
        "char** __cdecl parse_next_space_delimited_token(char** cursor, char* out);",
    ),
    (
        "parse_next_float32",
        "double __cdecl parse_next_float32(char** cursor);",
    ),
    (
        "initialize_track_render_cache_manager",
        "void* __thiscall initialize_track_render_cache_manager(SegmentCache* manager);",
    ),
    (
        "build_track_render_caches",
        "int32_t __thiscall build_track_render_caches(SegmentCache* manager, tColour skirt_color);",
    ),
    (
        "add_track_cache_vertex",
        "int32_t __thiscall add_track_cache_vertex(SegmentCache* manager, Object* source, Vec3* position, int32_t source_index, float u, float v, ObjectRenderVertex* vertices, int32_t* vertex_count, int32_t max_vertices, int32_t max_indices, uint32_t color, uint8_t project_uv);",
    ),
    (
        "append_track_cache_object",
        "int32_t __thiscall append_track_cache_object(SegmentCache* manager, int32_t row_index, Object* source, Vec3* position, ObjectRenderVertex* vertices, int32_t* vertex_count, uint16_t* indices, int32_t* index_count, int32_t max_vertices, int32_t max_indices, uint32_t color, uint8_t project_uv);",
    ),
    (
        "update_track_render_cache_rows",
        "void __thiscall update_track_render_cache_rows(SegmentCache* manager);",
    ),
    (
        "remove_track_render_cache_bods",
        "void __thiscall remove_track_render_cache_bods(SegmentCache* manager);",
    ),
    (
        "is_sub_loc_floor",
        "int32_t __fastcall is_sub_loc_floor(TrackRowCell* cell);",
    ),
    (
        "is_sub_loc_slide",
        "int32_t __fastcall is_sub_loc_slide(TrackRowCell* cell);",
    ),
    (
        "is_sub_loc_ramp",
        "int32_t __fastcall is_sub_loc_ramp(TrackRowCell* cell);",
    ),
    (
        "is_sub_loc_empty",
        "int32_t __fastcall is_sub_loc_empty(TrackRowCell* cell);",
    ),
    (
        "set_color_alpha",
        "void __thiscall set_color_alpha(tColour* color, float alpha);",
    ),
    (
        "set_color_grayscale",
        "void __thiscall set_color_grayscale(tColour* color, float intensity);",
    ),
    (
        "set_color_rgb",
        "void __thiscall set_color_rgb(tColour* color, float r, float g, float b);",
    ),
    (
        "set_color_white",
        "void __thiscall set_color_white(tColour* color);",
    ),
    (
        "set_color_black",
        "void __thiscall set_color_black(tColour* color);",
    ),
    (
        "get_track_skirt_color",
        "tColour* __thiscall get_track_skirt_color(SubgameRuntime* game, tColour* out);",
    ),
    (
        "spawn_track_garbage_hazard",
        "void __thiscall spawn_track_garbage_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* player);",
    ),
    (
        "update_salt_hazard",
        "void __thiscall update_salt_hazard(SaltHazardSlot* slot);",
    ),
    (
        "initialize_score_stats",
        "void __thiscall initialize_score_stats(Squidge* squidge);",
    ),
    (
        "start_squidge_y",
        "void __thiscall start_squidge_y(Squidge* squidge, float value);",
    ),
    (
        "start_squidge_z",
        "void __thiscall start_squidge_z(Squidge* squidge, float value);",
    ),
    (
        "update_squidge",
        "void __thiscall update_squidge(Squidge* squidge);",
    ),
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(SnailSkin* snail_skin);",
    ),
    (
        "update_snail_skin",
        "void __thiscall update_snail_skin(Snail* snail);",
    ),
    (
        "initialize_invincible_shell",
        "void __thiscall initialize_invincible_shell(Invincible* invincible);",
    ),
    (
        "start_invincible_shell",
        "void __thiscall start_invincible_shell(Invincible* invincible);",
    ),
    (
        "update_invincible_shell",
        "void __thiscall update_invincible_shell(Invincible* invincible);",
    ),
    (
        "initialize_anim_manager",
        "void __thiscall initialize_anim_manager(AnimManager* manager);",
    ),
    (
        "update_anim_manager",
        "void __thiscall update_anim_manager(AnimManager* manager);",
    ),
    (
        "set_weapon_animation",
        "void __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "update_snail_skin_transition",
        "void __thiscall update_snail_skin_transition(SnailSkin* snail_skin);",
    ),
    (
        "change_snail_skin",
        "void __thiscall change_snail_skin(SnailSkin* snail_skin, int32_t slot_id, float duration_seconds);",
    ),
    (
        "store_color4f",
        "void __thiscall store_color4f(tColour* color, float r, float g, float b, float a);",
    ),
    (
        "pack_color_rgba_u8",
        "tColourSmall* __thiscall pack_color_rgba_u8(tColourSmall* out, tColour* color);",
    ),
    (
        "kill_tip_widgets",
        "void __thiscall kill_tip_widgets(Tip* tip);",
    ),
    (
        "initialize_tip",
        "void __thiscall initialize_tip(Tip* tip, TipData* definition, int32_t hide_disable_button);",
    ),
    (
        "update_tip",
        "void __thiscall update_tip(Tip* tip);",
    ),
    (
        "initialize_tip_manager",
        "void __thiscall initialize_tip_manager(TipManager* manager);",
    ),
    (
        "uninit_tips",
        "void __thiscall uninit_tips(TipManager* manager);",
    ),
    (
        "enqueue_tip_message",
        "Tip* __thiscall enqueue_tip_message(TipManager* manager, TipData* definition, int32_t hide_disable_button);",
    ),
    (
        "update_tip_manager",
        "void __thiscall update_tip_manager(TipManager* manager);",
    ),
    (
        "initialize_tutorial",
        "void __thiscall initialize_tutorial(Tutorial* tutorial);",
    ),
    (
        "uninit_tutorial",
        "void __thiscall uninit_tutorial(Tutorial* tutorial);",
    ),
    (
        "update_tutorial",
        "TrackRowCell* __thiscall update_tutorial(Tutorial* tutorial);",
    ),
    (
        "initialize_frontend_widget",
        "void __thiscall initialize_frontend_widget(FrontendWidget* widget, uint32_t widget_flags, char* text, int32_t widget_type, float x, float y, tColour* color, int32_t text_alignment, float anchor_x);",
    ),
    (
        "layout_frontend_widget",
        "int32_t __thiscall layout_frontend_widget(FrontendWidget* widget);",
    ),
    (
        "set_frontend_widget_shortcut_key",
        "int32_t __thiscall set_frontend_widget_shortcut_key(FrontendWidget* widget, int32_t shortcut_key_code);",
    ),
    (
        "unhighlight_border",
        "int32_t __thiscall unhighlight_border(FrontendWidget* widget);",
    ),
    (
        "highlight_border",
        "int32_t __thiscall highlight_border(FrontendWidget* widget);",
    ),
    (
        "update_frontend_widget_interaction",
        "void __thiscall update_frontend_widget_interaction(FrontendWidget* widget);",
    ),
    (
        "reset_tooltip",
        "int32_t __fastcall reset_tooltip(FrontendWidgetTooltip* tooltip);",
    ),
    (
        "update_tooltip",
        "int32_t __thiscall update_tooltip(FrontendWidgetTooltip* tooltip);",
    ),
    (
        "initialize_cameraman",
        "void __thiscall initialize_cameraman(Cameraman* cameraman);",
    ),
    (
        "update_cameraman",
        "void __thiscall update_cameraman(Cameraman* cameraman);",
    ),
    (
        "initialize_subgoldy",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot);",
    ),
    (
        "end_jetpack_hover",
        "void __thiscall end_jetpack_hover(SubHover* sub_hover);",
    ),
    (
        "update_jetpack_gauge",
        "void __thiscall update_jetpack_gauge(SubHover* sub_hover);",
    ),
    (
        "uninit_jet_particles",
        "void __thiscall uninit_jet_particles(SubHover* sub_hover);",
    ),
    (
        "initialize_jet_particles",
        "void __thiscall initialize_jet_particles(SubHover* sub_hover);",
    ),
    (
        "update_jet_particles",
        "void __thiscall update_jet_particles(SubHover* sub_hover);",
    ),
    (
        "initialize_jetpack_gauge",
        "void __thiscall initialize_jetpack_gauge(SubHover* sub_hover, int32_t player_slot);",
    ),
    (
        "arm_jetpack_gauge",
        "void __thiscall arm_jetpack_gauge(SubHover* sub_hover);",
    ),
    (
        "update_subgoldy",
        "int32_t __thiscall update_subgoldy(Player* player);",
    ),
    (
        "set_subgoldy_ghost_z",
        "Sprite* __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z);",
    ),
    (
        "firework_shoot",
        "void __thiscall firework_shoot(FireWork* firework, Vec3* position, int32_t owner, int32_t texture_id, int32_t count);",
    ),
    (
        "update_banner",
        "void __thiscall update_banner(Banner* banner);",
    ),
    (
        "initialize_track_speedup_runtime",
        "SubSpeedUp* __thiscall initialize_track_speedup_runtime(SubSpeedUp* speedup);",
    ),
    (
        "update_track_speedup",
        "void __thiscall update_track_speedup(SubSpeedUp* speedup);",
    ),
    (
        "initialize_track_jetpack_pickup_runtime",
        "JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack);",
    ),
    (
        "update_track_jetpack_pickup",
        "void __thiscall update_track_jetpack_pickup(JetPack* jetpack);",
    ),
    (
        "initialize_track_health_pickup_runtime",
        "SubHealth* __thiscall initialize_track_health_pickup_runtime(SubHealth* pickup);",
    ),
    (
        "update_track_health_pickup",
        "void __thiscall update_track_health_pickup(SubHealth* pickup);",
    ),
    (
        "initialize_vapour",
        "void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width);",
    ),
    (
        "reset_vapour",
        "void __thiscall reset_vapour(Vapour* vapour, float* z_floor);",
    ),
    (
        "add_vapour_point",
        "void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point);",
    ),
    (
        "update_vapour",
        "void __thiscall update_vapour(Vapour* vapour);",
    ),
    (
        "handle_subgoldy_collisions",
        "int32_t __thiscall handle_subgoldy_collisions(Player* player);",
    ),
    (
        "set_snail_weapon",
        "void __thiscall set_snail_weapon(Snail* snail, int32_t movement_flags);",
    ),
    (
        "set_snail_jetpack",
        "void __thiscall set_snail_jetpack(Snail* snail, int32_t state);",
    ),
    (
        "initialize_cutscene",
        "void __thiscall initialize_cutscene(Snail* snail);",
    ),
    (
        "dispatch_cutscene_animation",
        "int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "initialize_cutscene_ai",
        "void __thiscall initialize_cutscene_ai(CutScene* cutscene);",
    ),
    (
        "update_cutscene",
        "void __thiscall update_cutscene(CutScene* cutscene);",
    ),
    (
        "update_progress_bar",
        "void __thiscall update_progress_bar(ProgressBar* progress_bar);",
    ),
    (
        "initialize_nuke",
        "void __thiscall initialize_nuke(Nuke* nuke);",
    ),
    (
        "update_nuke",
        "void __thiscall update_nuke(Nuke* nuke);",
    ),
    (
        "uninit_nuke",
        "void __thiscall uninit_nuke(Nuke* nuke);",
    ),
    (
        "get_track_grid_cell_at_world_position",
        "TrackRowCell* __thiscall get_track_grid_cell_at_world_position(SubgameRuntime* game, Vec3* position);",
    ),
    (
        "get_track_runtime_cell_at_world_z",
        "SubRow* __thiscall get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position);",
    ),
    (
        "sample_track_floor_height_at_position",
        "double __thiscall sample_track_floor_height_at_position(SubgameRuntime* game, Vec3* position);",
    ),
    (
        "begin_track_attachment_follow_state",
        "void __thiscall begin_track_attachment_follow_state(FollowState* follow_state, TrackRowCell* source_cell, const Vec3* world_position, Player* player);",
    ),
    (
        "update_track_attachment_follow_state",
        "int32_t __thiscall update_track_attachment_follow_state(FollowState* follow_state, float path_factor, Vec3* out_position, Vec3* motion);",
    ),
    (
        "initialize_loopout_path_template_pair",
        "int32_t __thiscall initialize_loopout_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_cage2_path_template_pair",
        "int32_t __thiscall initialize_cage2_path_template_pair(Path* self, int32_t arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_supertramp_path_template_pair",
        "int32_t __thiscall initialize_supertramp_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b, char* texture_c);",
    ),
    (
        "initialize_halfpipe_path_template_pair",
        "int32_t __thiscall initialize_halfpipe_path_template_pair(Path* self, int32_t arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_hump_path_template_pair",
        "int32_t __thiscall initialize_hump_path_template_pair(Path* self, float arg2, float arg3, int32_t arg4, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_looptheloop_path_template_pair",
        "int32_t __thiscall initialize_looptheloop_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_looptheloopw_path_template_pair",
        "int32_t __thiscall initialize_looptheloopw_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_dump_path_template_pair",
        "int32_t __thiscall initialize_dump_path_template_pair(Path* self, float arg2, float arg3, int32_t arg4, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_dip_path_template_pair",
        "int32_t __thiscall initialize_dip_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_screw_path_template_pair",
        "int32_t __thiscall initialize_screw_path_template_pair(Path* self, int32_t arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_slalom_path_template_pair",
        "int32_t __thiscall initialize_slalom_path_template_pair(Path* self, int32_t arg2, uint32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_worm_path_template_pair",
        "int32_t __thiscall initialize_worm_path_template_pair(Path* self, char* texture_path);",
    ),
    (
        "initialize_slalombig_path_template_pair",
        "int32_t __thiscall initialize_slalombig_path_template_pair(Path* self, int32_t arg2, uint32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_sweep_path_template_pair",
        "int32_t __thiscall initialize_sweep_path_template_pair(Path* self, int32_t arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_snake_path_template_pair",
        "int32_t __thiscall initialize_snake_path_template_pair(Path* self, int32_t arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_slalomdouble_path_template_pair",
        "int32_t __thiscall initialize_slalomdouble_path_template_pair(Path* self, int32_t arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_p_path_template_pair",
        "int32_t __thiscall initialize_p_path_template_pair(Path* self, int32_t arg2, uint32_t arg3, float arg4, float arg5, int32_t arg6, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_start_path_template_pair",
        "int32_t __thiscall initialize_start_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_path);",
    ),
    (
        "initialize_turnover_path_template_pair",
        "int32_t __thiscall initialize_turnover_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_turnoverdouble_path_template_pair",
        "int32_t __thiscall initialize_turnoverdouble_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_turnunder_path_template_pair",
        "int32_t __thiscall initialize_turnunder_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_wibble_path_template_pair",
        "int32_t __thiscall initialize_wibble_path_template_pair(Path* self, int32_t arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_invert_path_template_pair",
        "int32_t __thiscall initialize_invert_path_template_pair(Path* self, int32_t arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_twister_path_template_pair",
        "int32_t __thiscall initialize_twister_path_template_pair(Path* self, float arg2, int32_t arg3, char arg4, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_twister2_path_template_pair",
        "int32_t __thiscall initialize_twister2_path_template_pair(Path* self, float arg2, int32_t arg3, char arg4, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "int32_t __thiscall initialize_loopbow_path_template_pair(Path* self, float arg2, uint32_t arg3, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_toad_path_template_pair",
        "int32_t __thiscall initialize_toad_path_template_pair(Path* self, char arg2, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_hill_valley_path_template_pair",
        "int32_t __thiscall initialize_hill_valley_path_template_pair(Path* self, int32_t arg2, float arg3, float arg4, char arg5, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_sbend_path_template_pair",
        "int32_t __thiscall initialize_sbend_path_template_pair(Path* self, uint32_t arg2, float arg3, float arg4, char arg5, char* texture_a, char* texture_b);",
    ),
    (
        "cache_music_file",
        "char __cdecl cache_music_file(char* path, int32_t unused, char* unused_default_path);",
    ),
    (
        "initialize_subgame",
        "void __thiscall initialize_subgame(SubgameRuntime* game);",
    ),
    (
        "destroy_subgame",
        "void __thiscall destroy_subgame(SubgameRuntime* game);",
    ),
    (
        "update_subgame",
        "void __thiscall update_subgame(SubgameRuntime* game);",
    ),
    (
        "remove_subgame_bods",
        "void __thiscall remove_subgame_bods(SubgameRuntime* game);",
    ),
    (
        "build_subgame_level",
        "void __thiscall build_subgame_level(SubgameRuntime* game, int32_t level_index);",
    ),
    (
        "calc_subgame_rate",
        "void __thiscall calc_subgame_rate(SubgameRuntime* game);",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "void __thiscall populate_runtime_track_cells_from_segments(SubgameRuntime* game);",
    ),
    (
        "rebuild_track_runtime_from_segments",
        "int32_t __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* game, int32_t level_index);",
    ),
    (
        "place_parcels_on_track",
        "int32_t __thiscall place_parcels_on_track(SubgameRuntime* game);",
    ),
    (
        "place_challenge_parcels_on_track",
        "int32_t __thiscall place_challenge_parcels_on_track(SubgameRuntime* game);",
    ),
    (
        "mark_track_warning_zones",
        "void __thiscall mark_track_warning_zones(SubgameRuntime* game);",
    ),
    (
        "select_track_tile_edge_variants",
        "int32_t __thiscall select_track_tile_edge_variants(SubgameRuntime* game);",
    ),
    (
        "merge_track_tile_runs",
        "int32_t __thiscall merge_track_tile_runs(SubgameRuntime* game);",
    ),
    (
        "promote_track_tiles_to_fringe_variants",
        "int32_t __thiscall promote_track_tiles_to_fringe_variants(SubgameRuntime* game);",
    ),
    (
        "harmonize_center_lane_floor_slide_variants",
        "int32_t __thiscall harmonize_center_lane_floor_slide_variants(SubgameRuntime* game);",
    ),
    (
        "build_track_fringe_objects",
        "int32_t __thiscall build_track_fringe_objects(SubgameRuntime* game);",
    ),
    (
        "update_subgame_camera",
        "void __thiscall update_subgame_camera(SubgameRuntime* runtime);",
    ),
]


def _sync_build_track_render_cache_lvar() -> dict[str, object]:
    address = idc.get_name_ea_simple("build_track_render_caches")
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function"}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_stk_var() and lvar.get_stkoff() == 64 and lvar.width == 52
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_local_candidates",
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    if lvar.name == "locals" and "TrackRenderCacheBuildLocals" in str(lvar.type()):
        return {"status": "unchanged", "name": lvar.name, "type": str(lvar.type())}

    local_type = ida_typeinf.tinfo_t()
    if not local_type.get_named_type(
        None,
        "TrackRenderCacheBuildLocals",
        ida_typeinf.BTF_STRUCT,
    ):
        return {"status": "failed", "reason": "missing_local_view_type"}

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = "locals"
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {"status": "failed", "reason": "modify_user_lvar_info_failed"}

    return {"status": "applied", "name": "locals", "type": "TrackRenderCacheBuildLocals"}


def _sync_color_lvars(selector: str) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_stk_var() and "Color4f" in str(lvar.type())
    ]
    if not candidates:
        return {"status": "unchanged", "updated_count": 0, "selector": selector}

    local_type = ida_typeinf.tinfo_t()
    if not local_type.get_named_type(None, "tColour", ida_typeinf.BTF_STRUCT):
        return {
            "status": "failed",
            "reason": "missing_tColour_type",
            "selector": selector,
        }

    updated = []
    for lvar in candidates:
        info = ida_hexrays.lvar_saved_info_t()
        info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
        info.type = local_type
        if not ida_hexrays.modify_user_lvar_info(address, ida_hexrays.MLI_TYPE, info):
            return {
                "status": "failed",
                "reason": "modify_user_lvar_info_failed",
                "local": lvar.name,
                "selector": selector,
            }
        updated.append(lvar.name)

    return {
        "status": "applied",
        "updated_count": len(updated),
        "locals": updated,
        "type": "tColour",
        "selector": selector,
    }


def _sync_subgame_receiver_lvar(selector: str) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [lvar for lvar in cfunc.get_lvars() if lvar.is_arg_var]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_argument_candidates",
            "candidate_count": len(candidates),
            "selector": selector,
        }

    owner_type = ida_typeinf.tinfo_t()
    if not owner_type.get_named_type(
        None,
        "SubgameRuntime",
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_SubgameRuntime_type",
            "selector": selector,
        }

    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(owner_type):
        return {
            "status": "failed",
            "reason": "create_SubgameRuntime_pointer_failed",
            "selector": selector,
        }

    lvar = candidates[0]
    expected_type = (_normalize_type_text(str(pointer_type)) or "").removeprefix(
        "struct "
    )
    observed_type = (_normalize_type_text(str(lvar.type())) or "").removeprefix(
        "struct "
    )
    if lvar.name == "game" and observed_type == expected_type:
        return {
            "status": "unchanged",
            "name": lvar.name,
            "type": str(lvar.type()),
            "selector": selector,
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = "game"
    info.type = pointer_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_user_lvar_info_failed",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified_candidates = [
        candidate for candidate in verified_cfunc.get_lvars() if candidate.is_arg_var
    ]
    if len(verified_candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_verified_argument_candidates",
            "candidate_count": len(verified_candidates),
            "selector": selector,
        }

    verified = verified_candidates[0]
    verified_type = (_normalize_type_text(str(verified.type())) or "").removeprefix(
        "struct "
    )
    if verified.name != "game" or verified_type != expected_type:
        return {
            "status": "failed",
            "reason": "lvar_verification_failed",
            "observed_name": verified.name,
            "observed_type": str(verified.type()),
            "selector": selector,
        }

    return {
        "status": "applied",
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified.name,
        "type": str(verified.type()),
        "selector": selector,
    }


def _resolve_function(selector: str) -> tuple[int | None, str]:
    if selector.startswith("0x"):
        address = int(selector, 16)
        name = idc.get_func_name(address) or selector
        return address, name

    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None, selector
    return address, selector


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=;)", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    data_applied = 0
    data_unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "selector": name, "reason": "rename_failed"})
            continue
        renamed += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected_observed = _data_declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))
        if normalized_current == expected_observed:
            data_unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "data_type_failed",
                }
            )
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected_observed:
            failed.append(
                {
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "data_verification_failed",
                }
            )
            continue
        data_applied += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        current_type = idc.get_type(address)
        normalized_current = _normalize_type_text(current_type)

        if normalized_current == expected_observed:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "set_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        normalized_observed = _normalize_type_text(observed)
        if normalized_observed != expected_observed:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "verification_failed",
                }
            )
            continue

        applied += 1

    lvar_view = _sync_build_track_render_cache_lvar()
    if lvar_view.get("status") == "failed":
        failed.append({"selector": "build_track_render_caches", "lvar_view": lvar_view})
    frontend_color_lvars = _sync_color_lvars("initialize_frontend_widget")
    if frontend_color_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_frontend_widget",
                "color_lvars": frontend_color_lvars,
            }
        )
    update_sub_loc_color_lvars = _sync_color_lvars("update_sub_loc")
    if update_sub_loc_color_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "update_sub_loc",
                "color_lvars": update_sub_loc_color_lvars,
            }
        )
    get_track_skirt_color_lvars = _sync_color_lvars("get_track_skirt_color")
    if get_track_skirt_color_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "get_track_skirt_color",
                "color_lvars": get_track_skirt_color_lvars,
            }
        )
    subgame_receiver_lvars = {
        selector: _sync_subgame_receiver_lvar(selector)
        for selector in (
            "initialize_subgame",
            "destroy_subgame",
            "update_subgame",
            "remove_subgame_bods",
        )
    }
    for selector, receiver_lvar in subgame_receiver_lvars.items():
        if receiver_lvar.get("status") == "failed":
            failed.append({"selector": selector, "receiver_lvar": receiver_lvar})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
                "lvar_view": lvar_view,
                "frontend_color_lvars": frontend_color_lvars,
                "update_sub_loc_color_lvars": update_sub_loc_color_lvars,
                "get_track_skirt_color_lvars": get_track_skirt_color_lvars,
                "subgame_receiver_lvars": subgame_receiver_lvars,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )

    if parse_errors or failed or missing:
        return 1
    return 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_path_template_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    if not header_path.is_file():
        print(f"missing header: {header_path}", file=sys.stderr)
        ida_pro.qexit(2)
        return

    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
