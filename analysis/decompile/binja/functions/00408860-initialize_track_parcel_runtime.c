/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_parcel_runtime @ 0x408860 */

00408863        initialize_bod_base(slot)
00408868        slot->vtable = &track_parcel_runtime_vtable
00408871        return slot
