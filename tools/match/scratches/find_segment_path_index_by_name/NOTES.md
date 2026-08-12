# Exact cRPathManager::NameCode

`0x429ae0` is the authored `cRPathManager::NameCode(char*)` method.

Android and iOS both preserve the exact authored member
`cRPathManager::NameCode(char*)`. Windows independently places the
otherwise-empty, one-byte `cRPathManager` at `cRSubGame +0xff2910`,
immediately before the path-template bank. `PathManager` remains only a
compatibility alias. The natural VC6 method emits
`?NameCode@cRPathManager@@QAEHPAD@Z` and matches all 27 instructions with
three clean operands. Its unused receiver remains in ECX and the method emits
`ret 4`.

The Windows storage from `0x4a3d6c` to the exclusive bound `0x4a3e68` spans
63 pointer slots, but only indices 0 through 50 are populated. The remaining
12 slots are zero. Valid names return their attachment/path-template index;
an unknown name reaches slot 51 and the case-insensitive comparator dereferences
its null pointer before the nominal `-1` exit can execute. Shipped segment
content uses the 51 populated names.

The comparison helper is the uncurated ASCII case-folding routine at
`0x44e6c0`; it is distinct from the earlier curated
`strings_equal_case_insensitive` function at `0x431dc0`.

Source-shape constraints:

- Spelling the table as `extern char* g_segment_path_name_0` and walking from
  `&g_segment_path_name_0` matches the native cursor model.
- The bounded `while ((int)cursor < end)` form is required. A post-test
  label/while form made VC6 peel the first comparison, and an indexed table
  form kept a separate base temporary.
