# hide_star_field

Star-field presentation helper at 0x434670. When the controller is active, it
iterates the live star entry array and clears sprite flag `0x40` on each entry
sprite without destroying the controller state.

Exact match: 100.00%, 23/23 instructions, no masked operands.

The authored `cRStarManager::Hide()` member is `void`. All six Windows callers
discard EAX; the observed state or count at return is only residue from the
loop condition. Keeping that loop variable while removing the synthetic return
preserves the exact instruction stream.
