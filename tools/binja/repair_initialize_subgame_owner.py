#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

from _narrow_sync import run_bn
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
SUBGAME_RUNTIME_SIZE = 0x1272838
PATH_SIZE = 0xA8

FUNCTION_SPECS = {
    "initialize_subgame": {
        "address": 0x4374B0,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall initialize_subgame(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": -24,
                "name": "color",
                "type": "struct tColour",
            },
        ),
    },
    "build_subgame_level": {
        "address": 0x437EB0,
        "expected_prototype": (
            "void __thiscall(struct SubgameRuntime* game, int32_t level_index)"
        ),
        "stale_prototype": "void __thiscall(struct Game* game, int32_t level_index)",
        "declaration": (
            "void __thiscall build_subgame_level(SubgameRuntime* game, "
            "int32_t level_index)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "level_index",
                "type": "int32_t",
            },
        ),
    },
    "destroy_subgame": {
        "address": 0x438850,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall destroy_subgame(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "update_subgame": {
        "address": 0x438B90,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall update_subgame(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "remove_subgame_bods": {
        "address": 0x440910,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall remove_subgame_bods(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "merge_track_tile_runs": {
        "address": 0x435180,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall merge_track_tile_runs(SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "build_track_fringe_objects": {
        "address": 0x434BE0,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        # Binary Ninja derives this address tag from the function's mismatched
        # incoming stack states. It is analyzer-owned evidence, not a user
        # annotation. The guarded recreation preserves it through mutation so
        # fresh analysis, rather than the repair itself, decides whether it remains.
        "allowed_auto_tag_types": ("Unresolved Stack Pointer Value",),
        "declaration": (
            "int32_t __thiscall build_track_fringe_objects(SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "promote_track_tiles_to_fringe_variants": {
        "address": 0x4355F0,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall promote_track_tiles_to_fringe_variants("
            "SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "harmonize_center_lane_floor_slide_variants": {
        "address": 0x4356F0,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall harmonize_center_lane_floor_slide_variants("
            "SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "select_track_tile_edge_variants": {
        "address": 0x435A80,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall select_track_tile_edge_variants("
            "SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "get_track_grid_cell_at_world_position": {
        "address": 0x43D410,
        "expected_prototype": (
            "struct TrackRowCell* __thiscall("
            "struct SubgameRuntime* game, struct Vec3* position)"
        ),
        "stale_prototype": (
            "struct TrackRowCell* __thiscall("
            "struct Game* game, struct Vec3* position)"
        ),
        "declaration": (
            "TrackRowCell* __thiscall get_track_grid_cell_at_world_position("
            "SubgameRuntime* game, Vec3* position)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "position",
                "type": "struct Vec3*",
            },
        ),
    },
    "sample_track_floor_height_at_position": {
        "address": 0x43D4D0,
        "expected_prototype": (
            "double __thiscall(struct SubgameRuntime* game, struct Vec3* position)"
        ),
        "stale_prototype": (
            "double __thiscall(struct Game* game, struct Vec3* position)"
        ),
        "declaration": (
            "double __thiscall sample_track_floor_height_at_position("
            "SubgameRuntime* game, Vec3* position)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "position",
                "type": "struct Vec3*",
            },
        ),
    },
    "spawn_track_health_pickup": {
        "address": 0x43D6C0,
        "expected_prototype": (
            "void __thiscall(struct SubgameRuntime* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "stale_prototype": (
            "struct TrackPickupRuntime* __thiscall(struct Game* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "declaration": (
            "void __thiscall spawn_track_health_pickup("
            "SubgameRuntime* game, TrackRowCell* cell, Player* player)"
        ),
        "parameter_count": 3,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "cell",
                "type": "struct TrackRowCell*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 8,
                "name": "player",
                "type": "struct Player*",
            },
        ),
    },
    "spawn_track_jetpack_pickup": {
        "address": 0x43D890,
        "expected_prototype": (
            "void __thiscall(struct SubgameRuntime* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "stale_prototype": (
            "struct TrackPickupRuntime* __thiscall(struct Game* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "declaration": (
            "void __thiscall spawn_track_jetpack_pickup("
            "SubgameRuntime* game, TrackRowCell* cell, Player* player)"
        ),
        "parameter_count": 3,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "cell",
                "type": "struct TrackRowCell*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 8,
                "name": "player",
                "type": "struct Player*",
            },
        ),
    },
    "get_track_runtime_cell_at_world_z": {
        "address": 0x43D480,
        "expected_prototype": (
            "struct SubRow* __thiscall("
            "struct SubgameRuntime* game, struct Vec3* position)"
        ),
        "stale_prototype": (
            "struct TrackAttachmentRuntimeRow* __thiscall("
            "struct Game* game, struct Vec3* position)"
        ),
        "legacy_prototypes": (
            "struct TrackAttachmentRuntimeRow* __thiscall("
            "struct SubgameRuntime* game, struct Vec3* position)",
        ),
        "declaration": (
            "SubRow* __thiscall "
            "get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "position",
                "type": "struct Vec3*",
            },
        ),
    },
}


def _path_function_spec(
    *,
    address: int,
    name: str,
    return_type: str,
    stale_return_type: str,
    calling_convention: str,
    parameters: tuple[tuple[str, str, str], ...] = (),
    stale_parameters: tuple[tuple[str, str], ...] | None = None,
    stale_variable_annotations: tuple[tuple[int, str, str], ...] = (),
    stale_auto_variable_annotations: tuple[tuple[int, str, str], ...] = (),
    missing_stale_variable_storages: tuple[int, ...] = (),
    discard_variables: tuple[dict[str, object], ...] = (),
) -> dict[str, object]:
    expected_parameters = (("self", "struct Path*"),) + tuple(
        (parameter_name, expected_type)
        for parameter_name, expected_type, _stale_type in parameters
    )
    stale_stack_parameters = (
        tuple(
            (parameter_name, stale_type)
            for parameter_name, _expected_type, stale_type in parameters
        )
        if stale_parameters is None
        else stale_parameters
    )
    stale_parameters_with_owner = (
        ("self", "struct PathTemplate*"),
    ) + stale_stack_parameters

    def render_prototype(result_type: str, values: tuple[tuple[str, str], ...]) -> str:
        rendered = ", ".join(
            f"{parameter_type} {parameter_name}"
            for parameter_name, parameter_type in values
        )
        return f"{result_type} {calling_convention}({rendered})"

    def render_declaration(values: tuple[tuple[str, str], ...]) -> str:
        rendered = ", ".join(
            f"{parameter_type} {parameter_name}"
            for parameter_name, parameter_type in values
        )
        return f"{return_type} {calling_convention} {name}({rendered})"

    variables: list[dict[str, object]] = [
        {
            "source_type": "VariableSourceType.RegisterVariableSourceType",
            "index": 0,
            "storage": 67,
            "name": "self",
            "type": "struct Path*",
        }
    ]
    for stack_index, (parameter_name, expected_type, _stale_type) in enumerate(
        parameters,
        start=1,
    ):
        variables.append(
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": stack_index * 4,
                "name": parameter_name,
                "type": expected_type,
            }
        )

    return {
        "address": address,
        "owner_type": "Path",
        "owner_size": PATH_SIZE,
        "expected_prototype": render_prototype(return_type, expected_parameters),
        "stale_prototype": render_prototype(
            stale_return_type,
            stale_parameters_with_owner,
        ),
        "declaration": render_declaration(expected_parameters),
        "parameter_count": len(expected_parameters),
        "stale_parameter_counts": (len(stale_parameters_with_owner),),
        "stale_variable_annotations": tuple(
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": storage,
                "name": variable_name,
                "type": variable_type,
                "user_defined": True,
            }
            for storage, variable_name, variable_type in stale_variable_annotations
        )
        + tuple(
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": storage,
                "name": variable_name,
                "type": variable_type,
                "user_defined": False,
            }
            for storage, variable_name, variable_type in stale_auto_variable_annotations
        ),
        "allowed_missing_stale_variable_keys": tuple(
            (
                "VariableSourceType.StackVariableSourceType",
                0,
                storage,
            )
            for storage in missing_stale_variable_storages
        ),
        "variables": tuple(variables),
        "discard_variables": discard_variables,
    }


FUNCTION_SPECS.update(
    {
        "allocate_path_template_samples": _path_function_spec(
            address=0x41B0A0,
            name="allocate_path_template_samples",
            return_type="void",
            stale_return_type="void",
            calling_convention="__fastcall",
        ),
        "finalize_path_template": _path_function_spec(
            address=0x42C600,
            name="finalize_path_template",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__fastcall",
        ),
        "initialize_worm_path_template_pair": _path_function_spec(
            address=0x420170,
            name="initialize_worm_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(("texture_path", "char*", "char*"),),
            discard_variables=(
                {
                    "source_type": "VariableSourceType.StackVariableSourceType",
                    "index": 0,
                    "storage": 8,
                    "name": "arg2",
                    "type": "char*",
                },
            ),
        ),
        "initialize_looptheloop_path_template_pair": _path_function_spec(
            address=0x41B0F0,
            name="initialize_looptheloop_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "float", "float"),
                ("width_cells_", "int32_t", "int32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "float"),
                ("arg3", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((20, "arg5", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_looptheloopw_path_template_pair": _path_function_spec(
            address=0x41BB40,
            name="initialize_looptheloopw_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "float", "float"),
                ("width_cells_", "int32_t", "int32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "float"),
                ("arg3", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((20, "arg5", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_loopout_path_template_pair": _path_function_spec(
            address=0x41C5F0,
            name="initialize_loopout_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "float", "float"),
                ("width_cells_", "int32_t", "int32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "float"),
                ("arg3", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((20, "arg5", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_hump_path_template_pair": _path_function_spec(
            address=0x41D030,
            name="initialize_hump_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "float", "float"),
                ("height_scale", "float", "float"),
                ("width_cells_", "int32_t", "int32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "float"),
                ("arg3", "float"),
                ("arg4", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            missing_stale_variable_storages=(28,),
        ),
        "initialize_dump_path_template_pair": _path_function_spec(
            address=0x41DA30,
            name="initialize_dump_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "float", "float"),
                ("height_scale", "float", "float"),
                ("width_cells_", "int32_t", "int32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "float"),
                ("arg3", "float"),
                ("arg4", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((24, "arg6", "char*"),),
            missing_stale_variable_storages=(28,),
        ),
        "initialize_dip_path_template_pair": _path_function_spec(
            address=0x41E440,
            name="initialize_dip_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "float", "float"),
                ("width_cells_", "int32_t", "int32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "float"),
                ("arg3", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((20, "arg5", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_screw_path_template_pair": _path_function_spec(
            address=0x41EDA0,
            name="initialize_screw_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "int32_t", "int32_t"),
                ("width_cells_", "int32_t", "int32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "int32_t"),
                ("arg3", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((20, "arg5", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_slalom_path_template_pair": _path_function_spec(
            address=0x41F760,
            name="initialize_slalom_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_source", "int32_t", "int32_t"),
                ("width_cells_", "int32_t", "uint32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "int32_t"),
                ("arg3", "uint32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((20, "arg5", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_slalombig_path_template_pair": _path_function_spec(
            address=0x4221F0,
            name="initialize_slalombig_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_segments", "int32_t", "int32_t"),
                ("width_cells_", "int32_t", "uint32_t"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "int32_t"),
                ("arg3", "uint32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((20, "arg5", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_sweep_path_template_pair": _path_function_spec(
            address=0x422C00,
            name="initialize_sweep_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("scale_arg", "float", "int32_t"),
                ("width_cells_", "int32_t", "char*"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_auto_variable_annotations=(
                (16, "texture_path_2", "char*"),
                (20, "texture_path_3", "char*"),
            ),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_snake_path_template_pair": _path_function_spec(
            address=0x423580,
            name="initialize_snake_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("scale_arg", "float", "int32_t"),
                ("width_cells_", "int32_t", "char*"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((16, "arg4", "char*"),),
            stale_auto_variable_annotations=((20, "texture_path_2", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_slalomdouble_path_template_pair": _path_function_spec(
            address=0x425050,
            name="initialize_slalomdouble_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("curve_segments", "int32_t", "int32_t"),
                ("width_cells_", "int32_t", "char*"),
                ("side_exit", "int32_t", "char*"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("cap_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((16, "arg4", "char*"),),
            stale_auto_variable_annotations=((20, "texture_path_2", "char*"),),
            missing_stale_variable_storages=(24,),
        ),
        "initialize_cage2_path_template_pair": _path_function_spec(
            address=0x42E720,
            name="initialize_cage2_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("width_cells_", "int32_t", "int32_t"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("vertical_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "int32_t"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            missing_stale_variable_storages=(16,),
        ),
        "initialize_toad_path_template_pair": _path_function_spec(
            address=0x42CBF0,
            name="initialize_toad_path_template_pair",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(
                ("turn_left", "char", "char"),
                ("texture_a", "char*", "char*"),
                ("texture_b", "char*", "char*"),
                ("vertical_texture", "char*", "char*"),
            ),
            stale_parameters=(
                ("arg2", "char"),
                ("texture_a", "char*"),
                ("texture_b", "char*"),
            ),
            stale_variable_annotations=((16, "arg4", "char*"),),
        ),
        "mirror_path_template_pair_x": _path_function_spec(
            address=0x421DC0,
            name="mirror_path_template_pair_x",
            return_type="void",
            stale_return_type="int32_t",
            calling_convention="__thiscall",
            parameters=(("source", "struct Path*", "struct PathTemplate*"),),
        ),
    }
)


def _repair_code(
    *, function_name: str, spec: dict[str, object], apply: bool
) -> str:
    template = r'''
SPEC = __SPEC__
ADDRESS = SPEC["address"]
NAME = SPEC["name"]
EXPECTED_PROTOTYPE = SPEC["expected_prototype"]
STALE_PROTOTYPE = SPEC["stale_prototype"]
STALE_PROTOTYPES = {STALE_PROTOTYPE, *SPEC.get("legacy_prototypes", ())}
DECLARATION = SPEC["declaration"]
EXPECTED_PARAMETER_COUNT = SPEC["parameter_count"]
STALE_PARAMETER_COUNTS = set(
    SPEC.get("stale_parameter_counts", (EXPECTED_PARAMETER_COUNT,))
)
EXPECTED_VARIABLES = SPEC["variables"]
DISCARD_VARIABLES = SPEC.get("discard_variables", ())
STALE_VARIABLE_ANNOTATIONS = SPEC.get("stale_variable_annotations", ())
ALLOWED_MISSING_STALE_VARIABLE_KEYS = {
    tuple(value)
    for value in SPEC.get("allowed_missing_stale_variable_keys", ())
}
ALLOWED_AUTO_TAG_TYPES = set(SPEC.get("allowed_auto_tag_types", ()))
OWNER_TYPE_NAME = SPEC.get("owner_type", "SubgameRuntime")
OWNER_SIZE = SPEC.get("owner_size", __SUBGAME_RUNTIME_SIZE__)
APPLY = __APPLY__


def variable_record(fn, var):
    return {
        "name": str(var.name),
        "type": str(var.type),
        "source_type": str(var.source_type),
        "index": int(var.index),
        "storage": int(var.storage),
        "user_defined": bool(fn.is_var_user_defined(var)),
    }


def variable_key(record):
    return (record["source_type"], record["index"], record["storage"])


def tag_record(fn, entry):
    arch, address, tag = entry
    auto_tags = fn.get_tags_at(address, arch, auto=True)
    return {
        "architecture": str(arch.name),
        "address": hex(int(address)),
        "type": str(tag.type.name),
        "data": str(tag.data),
        "auto": any(candidate.id == tag.id for candidate in auto_tags),
    }


def restore_preserved_auto_tags(fn, entries):
    if not entries:
        return

    for arch, address, tag in entries:
        current = fn.get_tags_at(address, arch, auto=True)
        if any(
            str(candidate.type.name) == str(tag.type.name)
            and str(candidate.data) == str(tag.data)
            for candidate in current
        ):
            continue
        fn.add_tag(
            str(tag.type.name),
            str(tag.data),
            int(address),
            auto=True,
            arch=arch,
        )
    bv.update_analysis_and_wait()

    missing = []
    for arch, address, tag in entries:
        current = fn.get_tags_at(address, arch, auto=True)
        if not any(
            str(candidate.type.name) == str(tag.type.name)
            and str(candidate.data) == str(tag.data)
            for candidate in current
        ):
            missing.append(
                {
                    "address": hex(int(address)),
                    "type": str(tag.type.name),
                    "data": str(tag.data),
                }
            )
    if missing:
        raise RuntimeError(f"failed to preserve auto tags: {missing!r}")


def find_variable(fn, record):
    candidates = [
        var
        for var in fn.vars
        if str(var.source_type) == record["source_type"]
        and int(var.index) == record["index"]
        and int(var.storage) == record["storage"]
    ]
    if len(candidates) != 1:
        raise RuntimeError(
            f"expected one variable for {record!r}, found {len(candidates)}"
        )
    return candidates[0]


def annotations(fn):
    parameters = list(fn.parameter_vars)
    variables = []
    for expected in EXPECTED_VARIABLES:
        candidates = [
            var
            for var in fn.vars
            if str(var.source_type) == expected["source_type"]
            and int(var.index) == expected["index"]
            and int(var.storage) == expected["storage"]
        ]
        variables.append(
            {
                "expected": expected,
                "candidate_count": len(candidates),
                "observed": (
                    variable_record(fn, candidates[0]) if len(candidates) == 1 else None
                ),
            }
        )
    return {
        "parameter_count": len(parameters),
        "variables": variables,
    }


def annotations_are_current(value):
    return (
        value["parameter_count"] == EXPECTED_PARAMETER_COUNT
        and all(
            entry["candidate_count"] == 1
            and entry["observed"] is not None
            and entry["observed"]["name"] == entry["expected"]["name"]
            and entry["observed"]["type"] == entry["expected"]["type"]
            for entry in value["variables"]
        )
    )


def apply_annotations(fn):
    value = annotations(fn)
    if value["parameter_count"] != EXPECTED_PARAMETER_COUNT:
        raise RuntimeError(f"unexpected parameter count: {value!r}")
    if any(entry["candidate_count"] != 1 for entry in value["variables"]):
        raise RuntimeError(f"unexpected variable candidates: {value!r}")

    for entry in value["variables"]:
        expected = entry["expected"]
        var = find_variable(fn, expected)
        var_type, _ = bv.parse_type_string(expected["type"])
        fn.create_user_var(var, var_type, expected["name"])
    bv.update_analysis_and_wait()


fn = bv.get_function_at(ADDRESS)
if fn is None:
    result = {
        "status": "conflict",
        "reason": "missing_function",
        "address": hex(ADDRESS),
    }
else:
    owner_type = bv.get_type_by_name(OWNER_TYPE_NAME)
    comments = {hex(int(address)): str(text) for address, text in fn.comments.items()}
    tag_entries = list(fn.tags)
    tags = [tag_record(fn, entry) for entry in tag_entries]
    preserved_auto_tags = [
        entry
        for entry, record in zip(tag_entries, tags)
        if record["auto"] and record["type"] in ALLOWED_AUTO_TAG_TYPES
    ]
    user_vars = [variable_record(fn, var) for var in fn.vars if fn.is_var_user_defined(var)]
    before_annotations = annotations(fn)
    observed_prototype = str(fn.type)
    observed = {
        "address": hex(int(fn.start)),
        "name": str(fn.name),
        "prototype": observed_prototype,
        "comments": comments,
        "tags": tags,
        "user_vars": user_vars,
        "annotations": before_annotations,
    }

    conflicts = []
    if int(fn.start) != ADDRESS:
        conflicts.append("function_start_changed")
    if str(fn.name) != NAME:
        conflicts.append("function_name_changed")
    if owner_type is None or int(owner_type.width) != OWNER_SIZE:
        conflicts.append(f"{OWNER_TYPE_NAME}_layout_changed")
    if observed_prototype != EXPECTED_PROTOTYPE and observed_prototype not in STALE_PROTOTYPES:
        conflicts.append("unexpected_prototype")

    stale = observed_prototype in STALE_PROTOTYPES
    allowed_user_var_keys = {
        (record["source_type"], record["index"], record["storage"])
        for record in (*EXPECTED_VARIABLES, *DISCARD_VARIABLES)
    }
    unexpected_user_vars = [
        record
        for record in user_vars
        if (record["source_type"], record["index"], record["storage"])
        not in allowed_user_var_keys
    ]
    if stale and comments:
        conflicts.append("function_has_comments")
    if stale and tags:
        unexpected_tags = [
            record
            for record in tags
            if not (
                record["auto"] and record["type"] in ALLOWED_AUTO_TAG_TYPES
            )
        ]
        if unexpected_tags:
            conflicts.append("function_has_tags")
    if stale and unexpected_user_vars:
        conflicts.append("function_has_unpreserved_user_vars")
    discard_by_key = {
        (record["source_type"], record["index"], record["storage"]): record
        for record in DISCARD_VARIABLES
    }
    invalid_discard_variables = [
        record
        for record in user_vars
        if (record["source_type"], record["index"], record["storage"])
        in discard_by_key
        and (
            record["name"]
            != discard_by_key[
                (record["source_type"], record["index"], record["storage"])
            ]["name"]
            or record["type"]
            != discard_by_key[
                (record["source_type"], record["index"], record["storage"])
            ]["type"]
        )
    ]
    if stale and invalid_discard_variables:
        conflicts.append("stale_discard_variable_changed")
    annotation_by_key = {
        variable_key(entry["expected"]): entry
        for entry in before_annotations["variables"]
    }
    invalid_stale_variable_annotations = [
        expected
        for expected in STALE_VARIABLE_ANNOTATIONS
        if (
            (entry := annotation_by_key.get(variable_key(expected))) is None
            or entry["candidate_count"] != 1
            or entry["observed"] is None
            or any(
                entry["observed"][field] != expected[field]
                for field in ("name", "type", "user_defined")
            )
        )
    ]
    if stale and invalid_stale_variable_annotations:
        conflicts.append("stale_variable_annotation_changed")
    if not stale and any(
        (record["source_type"], record["index"], record["storage"])
        in discard_by_key
        for record in user_vars
    ):
        conflicts.append("discarded_variable_survived_repair")
    allowed_parameter_counts = (
        STALE_PARAMETER_COUNTS if stale else {EXPECTED_PARAMETER_COUNT}
    )
    if before_annotations["parameter_count"] not in allowed_parameter_counts:
        conflicts.append("unexpected_parameter_count")
    if any(
        entry["candidate_count"] != 1
        and not (
            stale
            and entry["candidate_count"] == 0
            and variable_key(entry["expected"])
            in ALLOWED_MISSING_STALE_VARIABLE_KEYS
        )
        for entry in before_annotations["variables"]
    ):
        conflicts.append("unexpected_variable_candidates")

    if conflicts:
        result = {
            "status": "conflict",
            "reason": "guard_failed",
            "conflicts": conflicts,
            "observed": observed,
        }
    elif not APPLY:
        current = (
            observed_prototype == EXPECTED_PROTOTYPE
            and annotations_are_current(before_annotations)
        )
        result = {
            "status": "current" if current else "planned",
            "operation": (
                "none" if current else "recreate_function" if stale else "repair_annotations"
            ),
            "observed": observed,
            "expected_prototype": EXPECTED_PROTOTYPE,
            "dry_run": True,
            "discard_variables": list(DISCARD_VARIABLES) if stale else [],
        }
    elif observed_prototype == EXPECTED_PROTOTYPE:
        if annotations_are_current(before_annotations):
            result = {
                "status": "current",
                "operation": "none",
                "observed": observed,
                "snapshot_saved": False,
                "dry_run": False,
            }
        else:
            undo = bv.begin_undo_actions()
            undo_closed = False
            try:
                apply_annotations(fn)
                after_annotations = annotations(fn)
                if not annotations_are_current(after_annotations):
                    raise RuntimeError(f"annotation verification failed: {after_annotations!r}")
                bv.commit_undo_actions(undo)
                undo_closed = True
                snapshot_saved = bv.file.save_auto_snapshot()
            except Exception:
                if not undo_closed:
                    bv.revert_undo_actions(undo)
                    bv.update_analysis_and_wait()
                raise
            result = {
                "status": "repaired",
                "operation": "repair_annotations",
                "before": observed,
                "after": {
                    "prototype": str(fn.type),
                    "annotations": after_annotations,
                },
                "snapshot_saved": snapshot_saved,
                "dry_run": False,
            }
    else:
        old_type = fn.type
        old_platform = fn.platform
        old_user_vars = user_vars
        recreated = False

        def restore_old_function():
            current = bv.get_function_at(ADDRESS)
            if current is not None:
                bv.remove_function(current)
            restored = bv.add_function(
                ADDRESS,
                old_platform,
                auto_discovered=False,
                func_type=old_type,
            )
            if restored is None:
                raise RuntimeError("failed to recreate the original function during rollback")
            restored.name = NAME
            restored.set_user_type(old_type)
            bv.update_analysis_and_wait()
            for record in old_user_vars:
                var = find_variable(restored, record)
                var_type, _ = bv.parse_type_string(record["type"])
                restored.create_user_var(var, var_type, record["name"])
            restore_preserved_auto_tags(restored, preserved_auto_tags)
            bv.file.save_auto_snapshot()

        try:
            expected_type, _ = bv.parse_type_string(DECLARATION)
            bv.remove_function(fn)
            recreated = True
            repaired = bv.add_function(
                ADDRESS,
                old_platform,
                auto_discovered=False,
                func_type=expected_type,
            )
            if repaired is None:
                raise RuntimeError(f"failed to recreate {NAME}")
            repaired.name = NAME
            repaired.set_user_type(expected_type)
            bv.update_analysis_and_wait()
            apply_annotations(repaired)
            restore_preserved_auto_tags(repaired, preserved_auto_tags)

            after_annotations = annotations(repaired)
            after_prototype = str(repaired.type)
            if after_prototype != EXPECTED_PROTOTYPE:
                raise RuntimeError(
                    f"prototype verification failed: {after_prototype!r}"
                )
            if not annotations_are_current(after_annotations):
                raise RuntimeError(f"annotation verification failed: {after_annotations!r}")
            snapshot_saved = bv.file.save_auto_snapshot()
        except Exception as repair_error:
            if recreated:
                try:
                    restore_old_function()
                except Exception as rollback_error:
                    raise RuntimeError(
                        f"repair failed ({repair_error}); rollback also failed ({rollback_error})"
                    ) from repair_error
            raise

        result = {
            "status": "repaired",
            "operation": "recreate_function",
            "before": observed,
            "after": {
                "prototype": str(repaired.type),
                "annotations": after_annotations,
            },
            "snapshot_saved": snapshot_saved,
            "dry_run": False,
            "discarded_variables": list(DISCARD_VARIABLES),
        }
'''
    embedded_spec = {
        **spec,
        "name": function_name,
        "variables": list(spec["variables"]),
    }
    return (
        template.replace("__SPEC__", repr(embedded_spec))
        .replace("__SUBGAME_RUNTIME_SIZE__", hex(SUBGAME_RUNTIME_SIZE))
        .replace("__APPLY__", repr(apply))
    )


def _unwrap_result(payload: object) -> dict[str, object]:
    if isinstance(payload, dict) and isinstance(payload.get("result"), dict):
        return payload["result"]
    if isinstance(payload, dict):
        return payload
    raise RuntimeError(f"unexpected Binary Ninja response: {payload!r}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Inspect or narrowly repair a cataloged function when a stale Binary "
            "Ninja named-type identity blocks its proven owner and ABI."
        )
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    parser.add_argument(
        "--function",
        dest="function_name",
        choices=tuple(FUNCTION_SPECS),
        default="initialize_subgame",
        help="Cataloged function to inspect or repair. Defaults to initialize_subgame.",
    )
    parser.add_argument(
        "--apply",
        action="store_true",
        help=(
            "Apply the guarded repair and save a snapshot. Without this flag the tool "
            "is read-only. Function recreation is used only for the exact known stale ABI."
        ),
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    spec = FUNCTION_SPECS[args.function_name]
    payload = run_bn(
        REPO_ROOT,
        "py",
        "exec",
        "--target",
        args.target,
        "--format",
        "json",
        "--code",
        _repair_code(
            function_name=args.function_name,
            spec=spec,
            apply=args.apply,
        ),
    )
    result = _unwrap_result(payload)
    json.dump(
        {
            "tool": "binary_ninja",
            "target": args.target,
            "function": args.function_name,
            "apply": args.apply,
            "result": result,
        },
        sys.stdout,
        indent=2,
        sort_keys=True,
    )
    sys.stdout.write("\n")
    return 1 if result.get("status") == "conflict" else 0


if __name__ == "__main__":
    raise SystemExit(main())
