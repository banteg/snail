# recycle_bod_to_free_list @ 0x447290

Exact match: 100.00%, 36/36 instructions.

This is the shared active-list teardown helper for BOD nodes. It verifies the
node is live-list owned (`BOD_FLAG_LINKED`), rejects removal while the node is
the saved successor (`BOD_FLAG_NEXT_UPDATE_GUARD`), patches
neighbor `prev`/`next` links, updates the list head when removing the first
node, pushes the node onto `free_top`, clears the linked flag, and returns the
recycled node to the pool.

The exact scratch is now the emitted wrapper around the owned inline
`BodList::remove_bod` implementation. The same method inlines exactly in the
speedup, health, and JetPack AI state paths, making this 36-instruction helper
the source-of-truth anchor for repeated runtime removal/free-stack blocks.

## 2026-07-27 mobile ABI correction

Android retains the exact authored template member as void
`cLinkedList<cRBod>::Remove(cRBod*)`, including both error guards, neighbor
unlinking, head replacement, free-stack push, and linked-flag clear. Its
successful path leaves the list receiver in `r0`, whereas Windows happens to
leave the node in `eax`; all four Windows calls ignore that residue. The
incompatible cross-port residues prove the result is incidental. The natural
void transcription remains exact at 36/36 and is now the shared inline owner.
