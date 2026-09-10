# dtk and m2c spike — 2026-09-10

**Use dtk now; add m2c as a checked first pass for scalar Wii functions.**
The combination improves our earlier five-function comparison, especially on
Metrowerks save/restore helpers. m2c is not safe as a general paired-single
semantic reference. No Wii compiler matching, runtime equivalence, relinking,
or new Windows matching credit is claimed.

## Pinned experiment

- DOL SHA-256: `523f848f2a0b8ef8c9dfe2714744bf0479a4feec79b25f0d1f5e035a6487c096`.
- dtk **1.8.4**, commit `a0c455e46cab58e1d2e0885623f85089ff0499db`.
  Official macOS arm64 release SHA-256:
  `5ba1fd76adf937847277a1ebe2238b698df0020c3dbbde23ecb126f00fb10353`,
  also checked against GitHub's published asset digest.
- m2c commit `1d1c4454a445326541305f83f2b0cb680a9ecb2d`, target
  `ppc-mwcc-c++`. Archive SHA-256:
  `dee566508729227925c0941cfcc6139ae8a0900640793f4706388946b7d76340`.
  Every extracted source file was checked against the pinned archive before replay.
- Tools were staged under ignored `artifacts/wii/spike-20260910/tools`.
  No project dependencies, global installations, or GUI databases were changed.

The [runner](../../../tools/wii/spike.py) generated a fresh replay directory,
ran `dtk dol info` and `dtk dol split`, then ran m2c on each emitted sample.
The [receipt](report.json) includes commands, input/output hashes, error counts,
and the two controls. Existing Ghidra/BN/IDA outputs remain in
[the prior comparison](../tool-comparison-20260910/README.md).

## dtk results

`dol info` successfully identified semantic sections, SDK routines, `main`, and
Metrowerks runtime helpers. For example:

| Address | dtk identity |
|---|---|
| `80004210` | `__init_registers` |
| `80081034` | `main` |
| `800BBE64` | `_savegpr_18` |
| `800BBE84` | `_savegpr_26` |
| `800C384C` | `sprintf` |

[Full initial findings](dtk-info.stdout) are tool-generated signature results,
not recovered original debug symbols. The register-save identities were also
corroborated by m2c's helper interpretation and a name-removal control below.

`dol split` completed with no stderr, emitted relocatable ELF objects, assembly,
and a linker script, and recorded 3,834 function symbols and 9,282 total symbol
rows. These are analysis counts, **not verified coverage**. dtk trims section
padding when deriving semantic section sizes; these are not a replacement for
the raw DOL header lengths used by our byte-preserving loaders.

All five function sizes agree with the prior comparison. Every emitted
instruction's byte annotation was compared to the DOL at its native address:
**1,148 instructions checked**. This validates the sampled input provenance;
it does not validate all reconstructed relocations or prove that the generated
objects relink to an identical executable.

## m2c results

| Function | Size | Direct input | Adapted input |
|---|---:|---|---|
| `800092e0`, float conversion | 36 | No explicit errors | Clear scalar expression with a named constant |
| `8000a968`, quaternion | 768 | Two `M2C_ERROR` markers and wrong comparison | Correct `>=` axis tree after alias conversion |
| `800444e8`, Galaxy-related | 1,456 | No explicit errors | One receiver argument, save helpers removed |
| `80052a00`, Hotspot-related | 864 | No explicit errors | One receiver argument, save helpers removed |
| `80075cc8`, IntroText-related | 1,468 | No explicit errors | Two ordinary arguments, save helpers removed |

“No explicit errors” is a diagnostic, not a semantic certification. Outputs
still contain unknown types/fields and inferred call signatures. For example,
the raw quaternion output omits the sqrt argument on the positive-trace path.
A separate exploratory context-file trial restored that argument but inferred
excess floating-point varargs; it did not establish complete prototypes and is
not part of the accepted baseline.

The accepted adapted runs use `--no-switches`: the known Windows recovery needs
ordinary axis equality bodies, and automatic switch reconstruction would hide
that useful structure. Both original and adapted assembly byte annotations
remain unchanged. Each `*-adapted.s` is paired with its `*-adapted.c` here.

### Condition-register spelling mismatch

At `8000aa0c` and `8000aa40`, dtk prints `cror eq, gt, eq`. m2c's
`FcmpoCrorPattern` expects numeric operands: `cror 2, 1, 2`.
Direct input exits zero but inserts `M2C_ERROR` and incorrectly retains an
**equality** test where the actual operation combines greater-than and equality.

The adapter changes only that spelling, requires the native encoded word
`4c411382`, and checks the assembly annotations against the original DOL first.
The result recovers the same greater-than-or-equal-first branch structure that
previously enabled the Windows exact match. It does not patch any binary bytes.

### Helper-name control

With dtk's `_savegpr_26` and `_restgpr_26` names, m2c emits:

```c
void fn_80052A00(void *arg0)
```

Renaming only those two symbols to unrecognized names makes m2c treat the
save/restore helpers as ordinary calls and lose the receiver:

```c
void fn_80052A00(void)
```

The [control input](helper-control.s) and [output](helper-control.c) preserve the
experiment. This explains a concrete benefit over the previous decompiler
outputs, rather than relying on pseudocode length or function counts.

### Paired-single control: material limitation

The [synthetic control](paired-body-control.s) places paired-single operations
in the function body, where they have observable effects:

- `psq_l` followed by `stfs` produces `M2C_ERROR(/* psq_l unimplemented */)`.
- `psq_st` followed by `blr` produces an **empty function**, silently losing the
  memory store.

Both functions are visible in [the output](paired-body-control.c). The pinned
m2c source confirms `psq_st` maps to no store and `psq_l` to an error expression.
Thus a zero exit code, or even no error marker, is insufficient. Use native
assembly and Ghidra/BN to check any actual paired-single computation. Removal
of register-preservation boilerplate is useful, but does not imply complete
paired-single support.

## Reproduce

From the repository root, stage the pinned tools if they are absent:

```sh
mkdir -p artifacts/wii/spike-20260910/tools
curl -fL https://github.com/encounter/decomp-toolkit/releases/download/v1.8.4/dtk-macos-arm64 -o artifacts/wii/spike-20260910/tools/dtk
curl -fL https://codeload.github.com/matt-kempster/m2c/tar.gz/1d1c4454a445326541305f83f2b0cb680a9ecb2d -o artifacts/wii/spike-20260910/tools/m2c.tar.gz
chmod +x artifacts/wii/spike-20260910/tools/dtk
tar -xzf artifacts/wii/spike-20260910/tools/m2c.tar.gz -C artifacts/wii/spike-20260910/tools
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run tools/wii/spike.py --out artifacts/wii/spike-new-run
```

The runner verifies hashes before running either tool and refuses to overwrite
an existing output directory. Its assembly byte checks and both controls passed
in the replay. Ruff passed; the alias-adapter and DOL-parser tests passed
**40 tests**. No full matching suite was needed because this spike does not
change matching source, compiler profiles, or the matcher.

The next useful integration would import verified dtk helper identities into
the Wii analysis databases and use dtk-emitted assembly as m2c input. Keep
library signature matches, inferred structures, and compiler exactness as
separate evidence categories.
