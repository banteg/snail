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
    (0x497354, "g_player_presentation_noop_vtable"),
    (0x497358, "g_invincible_shell_update_vtable"),
    (0x49735C, "g_presentation_animation_channel_noop_vtable"),
]


TRUSTED_DECLARATIONS = [
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
        "PlayerPresentationController* __thiscall initialize_player_presentation_controller(PlayerPresentationController* presentation);",
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
        "void __fastcall set_matrix_identity(TransformMatrix* transform);",
    ),
    (
        "set_matrix_rotation_identity",
        "void __fastcall set_matrix_rotation_identity(TransformMatrix* transform);",
    ),
    (
        "initialize_matrix_from_values",
        "TransformMatrix* __thiscall initialize_matrix_from_values(TransformMatrix* transform, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);",
    ),
    (
        "rotate_matrix_world_x",
        "void __thiscall rotate_matrix_world_x(TransformMatrix* transform, float angle);",
    ),
    (
        "rotate_matrix_world_y",
        "void __thiscall rotate_matrix_world_y(TransformMatrix* transform, float angle);",
    ),
    (
        "rotate_matrix_world_z",
        "void __thiscall rotate_matrix_world_z(TransformMatrix* transform, float angle);",
    ),
    (
        "normalize_vector",
        "double __fastcall normalize_vector(Vec3* vector);",
    ),
    (
        "normalize_vector_from_source",
        "float __thiscall normalize_vector_from_source(Vec3* out, const Vec3* src);",
    ),
    (
        "cross_vectors",
        "int32_t __thiscall cross_vectors(Vec3* out, Vec3* lhs, Vec3* rhs);",
    ),
    (
        "orthogonalize_matrix",
        "int32_t __fastcall orthogonalize_matrix(TransformMatrix* transform);",
    ),
    (
        "invert_matrix_from_source",
        "TransformMatrix* __fastcall invert_matrix_from_source(TransformMatrix* out, TransformMatrix* source);",
    ),
    (
        "multiply_matrix_in_place",
        "TransformMatrix* __thiscall multiply_matrix_in_place(TransformMatrix* lhs, TransformMatrix* rhs);",
    ),
    (
        "premultiply_matrix_in_place",
        "TransformMatrix* __thiscall premultiply_matrix_in_place(TransformMatrix* lhs, TransformMatrix* rhs);",
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
        "TransformMatrix* __thiscall interpolate_matrix_rotation(TransformMatrix* transform, float alpha);",
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
        "load_x_mesh",
        "int32_t __stdcall load_x_mesh(char* mesh_path, Object* object, uint8_t options_flags);",
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
        "Color4f* __thiscall set_color_rgba(Color4f* color, float r, float g, float b, float a);",
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
        "int32_t __thiscall build_track_render_caches(SegmentCache* manager, Color4f skirt_color);",
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
        "is_slide_cache_tile_family",
        "int32_t __fastcall is_slide_cache_tile_family(TrackRowCell* cell);",
    ),
    (
        "is_floor_cache_tile_family",
        "int32_t __fastcall is_floor_cache_tile_family(TrackRowCell* cell);",
    ),
    (
        "is_ramp_cache_tile_family",
        "int32_t __fastcall is_ramp_cache_tile_family(TrackRowCell* cell);",
    ),
    (
        "set_color_alpha",
        "float __thiscall set_color_alpha(Color4f* color, float alpha);",
    ),
    (
        "set_color_grayscale",
        "float __thiscall set_color_grayscale(Color4f* color, float intensity);",
    ),
    (
        "start_squidge_y",
        "void __thiscall start_squidge_y(SquidgeState* squidge, float value);",
    ),
    (
        "start_squidge_z",
        "void __thiscall start_squidge_z(SquidgeState* squidge, float value);",
    ),
    (
        "update_squidge",
        "void __thiscall update_squidge(SquidgeState* squidge);",
    ),
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(SnailSkinTransitionState* state);",
    ),
    (
        "update_snail_skin",
        "void __thiscall update_snail_skin(PlayerPresentationController* presentation);",
    ),
    (
        "initialize_invincible_shell",
        "void __thiscall initialize_invincible_shell(InvincibleShellController* shell);",
    ),
    (
        "start_invincible_shell",
        "void __thiscall start_invincible_shell(InvincibleShellController* shell);",
    ),
    (
        "update_invincible_shell",
        "void __thiscall update_invincible_shell(InvincibleShellController* shell);",
    ),
    (
        "initialize_anim_manager",
        "void __thiscall initialize_anim_manager(AnimationDispatchState* manager);",
    ),
    (
        "update_anim_manager",
        "void __thiscall update_anim_manager(AnimationDispatchState* manager);",
    ),
    (
        "set_weapon_animation",
        "int32_t __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t initial_frame);",
    ),
    (
        "update_snail_skin_transition",
        "void __thiscall update_snail_skin_transition(SnailSkinTransitionState* state);",
    ),
    (
        "store_color4f",
        "float __thiscall store_color4f(Color4f* color, float r, float g, float b, float a);",
    ),
    (
        "pack_color_rgba_u8",
        "ColorBGRA8* __thiscall pack_color_rgba_u8(ColorBGRA8* out, Color4f* color);",
    ),
    (
        "enqueue_tip_message",
        "TipSlot* __thiscall enqueue_tip_message(TipManager* manager, TipMessageDefinition* definition, int32_t show_disable_button);",
    ),
    (
        "initialize_tip",
        "void __thiscall initialize_tip(TipSlot* slot, TipMessageDefinition* definition, int32_t show_disable_button);",
    ),
    (
        "update_tip",
        "void* __fastcall update_tip(TipSlot* slot);",
    ),
    (
        "update_tip_manager",
        "void __fastcall update_tip_manager(TipManager* manager);",
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
        "flush_row_event_display",
        "void __thiscall flush_row_event_display(Completion* completion);",
    ),
    (
        "register_parcel_delivery",
        "void __thiscall register_parcel_delivery(Completion* completion);",
    ),
    (
        "update_row_event_display",
        "void __thiscall update_row_event_display(Completion* completion);",
    ),
    (
        "initialize_frontend_widget",
        "int32_t __thiscall initialize_frontend_widget(FrontendWidget* widget, uint32_t widget_flags, char* text, int32_t widget_type, float x, float y, Color4f* color, int32_t text_alignment, float anchor_x);",
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
        "int32_t __thiscall initialize_cameraman(CameramanState* cameraman);",
    ),
    (
        "update_cameraman",
        "int32_t __thiscall update_cameraman(CameramanState* cameraman);",
    ),
    (
        "initialize_subgoldy",
        "int32_t __thiscall initialize_subgoldy(Player* player, int32_t player_slot);",
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
        "handle_subgoldy_collisions",
        "int32_t __thiscall handle_subgoldy_collisions(Player* player);",
    ),
    (
        "set_snail_weapon",
        "void __thiscall set_snail_weapon(PlayerPresentationController* presentation, int32_t movement_flags);",
    ),
    (
        "set_snail_jetpack",
        "void __thiscall set_snail_jetpack(GlobalJetpackPresentationController* controller, int32_t state);",
    ),
    (
        "initialize_cutscene",
        "int32_t __thiscall initialize_cutscene(PlayerPresentationController* presentation);",
    ),
    (
        "dispatch_cutscene_animation",
        "int32_t __thiscall dispatch_cutscene_animation(PlayerPresentationController* presentation, int32_t animation_id, uint8_t immediate, int32_t initial_frame);",
    ),
    (
        "initialize_cutscene_ai",
        "int32_t __fastcall initialize_cutscene_ai(CutsceneAI* cutscene_ai);",
    ),
    (
        "update_cutscene",
        "int32_t __thiscall update_cutscene(CutsceneAI* cutscene_ai);",
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
        "TrackRowCell* __thiscall get_track_grid_cell_at_world_position(Game* game, Vec3* position);",
    ),
    (
        "get_track_runtime_cell_at_world_z",
        "TrackAttachmentRuntimeRow* __thiscall get_track_runtime_cell_at_world_z(Game* game, Vec3* position);",
    ),
    (
        "sample_track_floor_height_at_position",
        "double __thiscall sample_track_floor_height_at_position(Game* game, Vec3* position);",
    ),
    (
        "begin_track_attachment_follow_state",
        "Path* __thiscall begin_track_attachment_follow_state(FollowState* follow_state, TrackRowCell* source_cell, Vec3* world_position, Player* player);",
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
        "build_subgame_level",
        "void __thiscall build_subgame_level(Game* game, int32_t level_index);",
    ),
    (
        "calc_subgame_rate",
        "void __thiscall calc_subgame_rate(Game* game);",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "void __thiscall populate_runtime_track_cells_from_segments(Game* game);",
    ),
    (
        "rebuild_track_runtime_from_segments",
        "int32_t __thiscall rebuild_track_runtime_from_segments(Game* game, int32_t level_index);",
    ),
    (
        "place_parcels_on_track",
        "int32_t __thiscall place_parcels_on_track(Game* game);",
    ),
    (
        "mark_track_warning_zones",
        "int32_t __thiscall mark_track_warning_zones(Game* game);",
    ),
    (
        "select_track_tile_edge_variants",
        "int32_t __thiscall select_track_tile_edge_variants(Game* game);",
    ),
    (
        "merge_track_tile_runs",
        "int32_t __thiscall merge_track_tile_runs(Game* game);",
    ),
    (
        "promote_track_tiles_to_fringe_variants",
        "int32_t __thiscall promote_track_tiles_to_fringe_variants(Game* game);",
    ),
    (
        "harmonize_center_lane_floor_slide_variants",
        "int32_t __thiscall harmonize_center_lane_floor_slide_variants(Game* game);",
    ),
    (
        "build_track_fringe_objects",
        "int32_t __thiscall build_track_fringe_objects(Game* game);",
    ),
    (
        "update_subgame_camera",
        "char __thiscall update_subgame_camera(Game* game);",
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


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
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
                "lvar_view": lvar_view,
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
