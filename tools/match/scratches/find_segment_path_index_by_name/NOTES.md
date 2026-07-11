# find_segment_path_index_by_name @ 0x429ae0

Exact match under the standard `msvc6.5 /O2 /G5 /W3` profile.

Symbol-preserving iOS builds name the authored member
`cRPathManager::NameCode(char*)`. Windows places the otherwise-empty,
one-byte `PathManager` at `SubgameRuntime +0xff2910`, immediately before the
path-template bank. Recasting this scratch from a standalone stdcall helper to
the unused-receiver thiscall method preserves exact 27/27 proof with all three
masked operands clean; both forms emit `ret 4` because the receiver lives in
ECX and is never read.

This helper linearly searches the hardcoded segment `Path=` name table at
`data_4a3d6c` and returns the matching attachment/path-template index, or `-1`
after the cursor reaches `data_4a3e68` (`"TOADPAIR1"`).

The comparison helper is the uncurated ASCII case-folding routine at
`0x44e6c0`; it is distinct from the earlier curated
`strings_equal_case_insensitive` function at `0x431dc0`.

Source-shape note:

- Spelling the table as `extern char* g_segment_path_name_0` and walking from
  `&g_segment_path_name_0` matches the native cursor model.
- The bounded `while ((int)cursor < end)` form is required. A post-test
  label/while form made VC6 peel the first comparison, and an indexed table
  form kept a separate base temporary.
