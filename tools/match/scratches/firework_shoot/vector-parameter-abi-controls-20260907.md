# 2026-09-07 vector parameter ABI controls

The mobile firework method is `cRFireWork::Shoot(tVector, int, int, int)`,
whereas Windows ends with `ret 0x10` and its final copy reads a vector through
one pointer-sized argument. A possible invisible-reference convention for
nontrivial by-value objects was checked with the project-standard VC6 compiler.

Each fixture defines a 12-byte `struct V { float x, y, z; }`, then compiles:

```cpp
extern void sink(const V*, int, int, int);
struct Receiver { void F(V, int, int, int); };
void Receiver::F(V value, int a, int b, int c) {
    sink(&value, a, b, c);
}
```

The copy-constructor controls add `V(const V& other) : x(other.x),
y(other.y), z(other.z) {}`; destructor controls add an out-of-line `~V();`.
The reference control changes both formal declarations to `const V&`. All
fixtures use `msvc6.5 /O2 /G5 /W3`, and the emitted member was selected by its
actual COFF symbol. These are ABI fixtures, not matching candidates or new
proof-grade functions.

| Parameter form | Return cleanup | Function/relocation fingerprint |
| --- | --- | --- |
| trivial-value | `0x18` | `22a57dea114c9f2e45988faf8cb6615799817ec8f0b782cb851d43153b41756b` |
| copy-value | `0x18` | `22a57dea114c9f2e45988faf8cb6615799817ec8f0b782cb851d43153b41756b` |
| destructor-value | `0x18` | `e045230af1e300238abdb4a7fad0c15fba245b471cea66ddf821d1febad5824b` |
| copy-destructor-value | `0x18` | `e045230af1e300238abdb4a7fad0c15fba245b471cea66ddf821d1febad5824b` |
| const-reference | `0x10` | `deceae148dbd896f705cd814840cabe1aae6ee33a7fca314b65d57877bd067f8` |

A by-value vector consumes 24 argument bytes in all four controls, including
nontrivial copy construction and destruction. The const-reference control
consumes 16 bytes. This independently rejects adopting the mobile by-value
formal in the Windows scratch via an assumed invisible-reference ABI. It does
not distinguish a Windows pointer from a reference, nor change any callsite,
shared header, symbol alias, or current scratch contract.
