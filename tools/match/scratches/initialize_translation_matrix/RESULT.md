# initialize_translation_matrix match result

Focused matcher result:

| Metric | Result |
|---|---:|
| Match | 7.02% |
| Target instructions | 34 |
| Candidate instructions | 23 |
| Common prefix | 1 / 34 |
| Masked operands | none |

This is a semantic scratch rather than a compiler-shape match. The first
mismatch is the target's `fldz` for the first zero store versus the candidate's
integer constant setup:

```text
target[1]    fldz
candidate[1] mov edx, dword [esp+0x8]
```

The recovered behavior is complete; the open question is whether this helper
came from a different source/compiler configuration than the main VC6.5 game
translation units, or whether there is a non-fake source idiom that forces this
x87 constant-store sequence.
