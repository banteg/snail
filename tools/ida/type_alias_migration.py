from __future__ import annotations

from collections.abc import Iterable

import ida_typeinf

TypeAliasSpec = tuple[str, str, int]


def _named_struct_layout(name: str) -> dict[str, object] | None:
    type_info = ida_typeinf.tinfo_t()
    if not type_info.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None

    members = ida_typeinf.udt_type_data_t()
    if not type_info.get_udt_details(members):
        return None

    return {
        "size": type_info.get_size(),
        "members": tuple(
            (
                int(member.offset) // 8,
                int(member.size) // 8,
                str(member.name),
            )
            for member in members
        ),
    }


def migrate_equivalent_struct_aliases(
    specs: Iterable[TypeAliasSpec],
) -> list[dict[str, object]]:
    """Redirect stale struct ordinals to layout-equivalent canonical owners."""
    results: list[dict[str, object]] = []
    for old_name, new_name, expected_size in specs:
        old_ordinal = ida_typeinf.get_type_ordinal(None, old_name)
        new_ordinal = ida_typeinf.get_type_ordinal(None, new_name)
        if not old_ordinal and new_ordinal:
            new_layout = _named_struct_layout(new_name)
            if new_layout is not None and new_layout["size"] == expected_size:
                results.append(
                    {
                        "status": "unchanged",
                        "reason": "source_type_retired",
                        "old_name": old_name,
                        "new_name": new_name,
                        "old_ordinal": old_ordinal,
                        "new_ordinal": new_ordinal,
                        "layout": new_layout,
                    }
                )
                continue

        if not old_ordinal or not new_ordinal:
            results.append(
                {
                    "status": "failed",
                    "reason": "missing_type_ordinal",
                    "old_name": old_name,
                    "new_name": new_name,
                    "old_ordinal": old_ordinal,
                    "new_ordinal": new_ordinal,
                }
            )
            continue

        old_target = ida_typeinf.get_alias_target(None, old_ordinal)
        new_target = ida_typeinf.get_alias_target(None, new_ordinal)
        if old_target == new_target:
            results.append(
                {
                    "status": "unchanged",
                    "old_name": old_name,
                    "new_name": new_name,
                    "old_ordinal": old_ordinal,
                    "new_ordinal": new_ordinal,
                    "target_ordinal": new_target,
                }
            )
            continue

        old_layout = _named_struct_layout(old_name)
        new_layout = _named_struct_layout(new_name)
        if (
            old_layout is None
            or new_layout is None
            or old_layout != new_layout
            or old_layout["size"] != expected_size
        ):
            results.append(
                {
                    "status": "failed",
                    "reason": "non_equivalent_struct_layouts",
                    "old_name": old_name,
                    "new_name": new_name,
                    "expected_size": expected_size,
                    "old_layout": old_layout,
                    "new_layout": new_layout,
                }
            )
            continue

        if not ida_typeinf.set_type_alias(None, old_ordinal, new_ordinal):
            results.append(
                {
                    "status": "failed",
                    "reason": "set_type_alias_failed",
                    "old_name": old_name,
                    "new_name": new_name,
                    "old_ordinal": old_ordinal,
                    "new_ordinal": new_ordinal,
                }
            )
            continue

        observed_target = ida_typeinf.get_alias_target(None, old_ordinal)
        expected_target = ida_typeinf.get_alias_target(None, new_ordinal)
        if observed_target != expected_target:
            results.append(
                {
                    "status": "failed",
                    "reason": "type_alias_readback_failed",
                    "old_name": old_name,
                    "new_name": new_name,
                    "observed_target": observed_target,
                    "expected_target": expected_target,
                }
            )
            continue

        results.append(
            {
                "status": "applied",
                "old_name": old_name,
                "new_name": new_name,
                "old_ordinal": old_ordinal,
                "new_ordinal": new_ordinal,
                "target_ordinal": observed_target,
                "layout": new_layout,
            }
        )

    return results
