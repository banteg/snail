# `initialize_runtime_pools_and_path_template_bank` notes

- This scratch intentionally uses byte offsets into the subgame runtime blob.
  The function is a constructor pass over many unrelated pools; promoting a
  monolithic shared type would obscure more than it clarifies.
- The call at +0x10013dc targets the small object-constructor thunk at
  0x42f6e0, not `initialize_object` directly.

## 2026-07-10 path-bank ownership

- The pass at `SubgameRuntime +0xff2914` initializes exactly `126` records at
  stride `0xa8`: 63 adjacent primary/secondary pairs of stride `0x150`.
- `SubgameRuntime` itself is `GameRoot +0x74618`, so this is the same address as
  the world initializer's constructor base `GameRoot +0x1066f2c`; no install
  copy or transfer exists.
- The `63 * 0x150 = 0x52b0` extent ends exactly at the embedded barrier at
  `SubgameRuntime +0xff7bc4`.
- Despite its retained historical name, `initialize_path_template_record_pair`
  initializes one record's leading `BodBase` and fringe `BodBase` at `+0x60`.
