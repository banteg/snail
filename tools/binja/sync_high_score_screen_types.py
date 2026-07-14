#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    current_prototypes,
    emit_summary,
    types_declare,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_high_score_screen_types.h"
FRONTEND_WIDGET_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frontend_widget_types.h"
TARGET = DEFAULT_TARGET

DEFERRED_PROTO_UPDATES = (
    (
        "initialize_high_score_screen",
        "void __thiscall initialize_high_score_screen(HighScore* high_score, int32_t selected_bank, int32_t selected_rank)",
    ),
    (
        "destroy_high_score_screen",
        "void __thiscall destroy_high_score_screen(HighScore* high_score)",
    ),
    (
        "update_high_score_screen",
        "void __thiscall update_high_score_screen(HighScore* high_score)",
    ),
    (
        "exit_high_score_screen",
        "void __thiscall exit_high_score_screen(HighScore* high_score)",
    ),
)


def report_deferred_prototypes(*, target: str) -> list[dict[str, object]]:
    observed_prototypes = current_prototypes(
        REPO_ROOT,
        target=target,
        identifiers=(
            identifier for identifier, _prototype in DEFERRED_PROTO_UPDATES
        ),
    )
    return [
        {
            "op": "proto_owner_deferred",
            "status": "deferred",
            "reason": "Binary Ninja restores the stale scalar prototype during live verification",
            "identifier": identifier,
            "desired_prototype": prototype,
            "observed_prototype": observed_prototypes.get(identifier),
        }
        for identifier, prototype in DEFERRED_PROTO_UPDATES
    ]


def main() -> int:
    operations = [
        types_declare_if_missing(
            REPO_ROOT,
            target=TARGET,
            header_path=FRONTEND_WIDGET_HEADER_PATH,
            required_structs=("FrontendWidget",),
        ),
        types_declare(REPO_ROOT, target=TARGET, header_path=HEADER_PATH),
        *report_deferred_prototypes(target=TARGET),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=TARGET,
        header_path=HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
