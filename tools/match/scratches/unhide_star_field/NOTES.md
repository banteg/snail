# unhide_star_field

Star-field presentation helper at 0x4346b0. When the controller is active, it
iterates the live star entry array and sets sprite flag `0x40` on each entry
sprite, re-enabling the background star pass.

Exact match: 100.00%, 23/23 instructions, no masked operands.

The authored `cRStarManager::UnHide()` member is `void`. Both Windows callers
discard EAX; the observed state or count at return is only residue from the
loop condition. Keeping that loop variable while removing the synthetic return
preserves the exact instruction stream.
