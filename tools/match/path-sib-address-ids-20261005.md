# Path builder SIB residuals under msvc6.3

Date: 2026-10-05. Tools: [`c2/addrorder.py`](c2/addrorder.py),
[`c2/address_ids.py`](c2/address_ids.py), on the vendored msvc6.3 observer.

Five path builders match every normalized instruction under msvc6.3 and differ
in one SIB byte at a `+0x90` (`center_x`) access: native and candidate swap
base and index. C2 sorts each commutative address sum by operand cost,
descending, and the first operand becomes the base. The tracer validates every
observed cost against the msvc6.5 hash rule, which also holds in msvc6.3:
temporaries hash `(slot mod 0x400) << 6`, locals and parameters below `0x800`
hash `slot << 5`.

| function | offset | C0 | first (candidate base) | second |
|---|---|---|---|---|
| Turnover | `+0x28b` store | `0x4c0` | temp `0x531` (`0x14c40`) | local `0x15` (`0x102a0`) |
| TurnoverDouble | `+0x2b1` store | `0x4c0` | temp `0x4dc` (`0x13700`) | local `0x13` (`0x10260`) |
| HalfPipe | `+0x2f9` store | `0x4c0` | temp `0x51c` (`0x14700`) | local `0x17` (`0x102e0`) |
| LoopBow | `+0x327` store | `0x580` | temp `0x5fd` (`0x17f40`) | iv-temp `0x969` (`0x15a40`) |
| LoopOut | `+0x2e7` load | `0x540` | (load operand) | |

Native puts the second operand first. For the first three that needs the
offset local's hash above the bank-pointer temporary's: `local slot >
2 × (temp slot mod 0x400)`, or a temporary slot at `0x400`-`0x40b`.

## Locals

The first 31 locals and parameters take slots 1-31 in the order they are
encountered; later ones take a block opened at the current counter. HalfPipe's
`middle_offset` is exactly the 23rd local or parameter in the source. Named
intermediates that leave code unchanged move it by one each: nine (radian
angle, sine, wave, half width and special scalar in the lead and tail loops)
put it in the second block at slot `0x120`. That block opens at the counter's
value when the middle loop starts, so it cannot exceed about `0x120`; the
temporary still wins (`0x14840` against `0x12400`). Unused locals never reach
the IL and change nothing.

## Temporaries

With the local at `0x120`, the temporary needs `slot mod 0x400 < 0x90`: C0
about five 32-slot blocks lower (`0x4c0` to `0x420`) with the same creation
index. C0 is the count of frontend temporaries for the whole function, so the
original statements must produce about 160 fewer than the current byte-offset
casts while compiling to the same code.

## Controls that change code

- Natural `bank[i]` indexing in any loop (75-86%). Indexing the middle loop from
  16 reaches 94.9% and fixes the SIB order through an induction temporary, but
  C2 merges that index with `middle`, while native keeps two induction
  variables (the offset register tested against `0x20d0`, and `middle` in
  memory). Five loop shapes compile identically.
- Per-loop sample pointer locals (68-85%); using `primary_samples` instead of
  the `primary_bank` alias in the middle loop (90-96%).
- `__forceinline` helpers taking the offset: the inline copy propagates back to
  the original local.

## LoopBow

The second operand is an induction temporary, so the lever is CSE creation
order: the temporary needs `slot mod 0x400 < 0x169`, or the induction
temporary must be created about `0x95` slots later.
