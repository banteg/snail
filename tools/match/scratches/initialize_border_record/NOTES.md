# initialize_border_record @ 0x408410

Constructs one exact `0x724`-byte `BorderRecord` backing slot, initializes its
shared BOD prefix and seven constructor-proven color blocks, then installs the
front-end widget callback table. `BorderManager` owns 150 of these slots;
allocators return a slot through the separate `FrontendWidget*` semantic view.

2026-07-15 live replay: BN and IDA now retain the `BorderRecord*` receiver and
the named color fields instead of raw dword arithmetic. The matching source is
unchanged and exact at 21/21 instructions with nine clean operands.
