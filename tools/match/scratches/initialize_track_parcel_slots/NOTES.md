# Exact match

`ParcelManager::initialize_track_parcel_slots` initializes all 50 inline
`Parcel` records owned by the manager. Each inactive slot borrows the enclosing
`GameRoot::subgame`; no slot owns or allocates that backlink. Android
independently retains this member as
`cRParcelManager::Init()`. The shared typed version remains 100% (13/13, one
clean operand).

The 2026-07-14 canonical root path is codegen-identical at the same exact
13/13 baseline.

The 2026-07-14 extent pass derives the loop bound from
`ParcelManager::slots`. Its normalized listing remains byte-identical
(`764ab79c9a5d43f9013f4ec2996b4c288e80374c3d7d455e45359d914adc70ac`)
and exact at 13/13 instructions with one clean operand.

## 2026-07-14 parcel lifecycle ownership

The run reset now names each manager-owned slot's terminal value as
`PARCEL_STATE_INACTIVE`. The borrowed `owner_subgame` backlink is unchanged,
and focused matching remains exact at 13/13 instructions with one clean
operand.
