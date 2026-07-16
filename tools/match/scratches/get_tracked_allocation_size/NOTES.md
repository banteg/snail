# get_tracked_allocation_size

Tracked-allocation lookup helper at 0x431ab0. It scans the active prefix of the
`TrackedAllocationStack::records` array for the requested backing pointer and
returns that record's guarded byte size, reporting an error and returning zero
when the pointer is absent.

The 2026-07-16 paired replay recovers the `TrackedAllocationStack*` receiver and
the 12-byte `TrackedAllocationRecord` layout in both analysis databases. The
matching source retains the first-record union view because that natural VC6
expression preserves the native register allocation; the shared owner still
exposes the real record array to analysis and callers.

Focused matching is exact at 26/26 instructions with both masked operands
resolved.
