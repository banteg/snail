# `initialize_runtime_pools_and_path_template_bank` notes

- This scratch intentionally uses byte offsets into the subgame runtime blob.
  The function is a constructor pass over many unrelated pools; promoting a
  monolithic shared type would obscure more than it clarifies.
- The call at +0x10013dc targets the small object-constructor thunk at
  0x42f6e0, not `initialize_object` directly.
