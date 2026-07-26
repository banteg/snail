/*
 * mangled: _ZN12cRInvincible5StartEv
 * demangled: cRInvincible::Start()
 * address: 0006d1fc
 * size: 104
 */

/* cRInvincible::Start() */

void __thiscall cRInvincible::Start(cRInvincible *this)

{
  if (*(int *)(this + 0x74) != 0) {
    if (*(int *)(this + 0x74) == 3) {
      *(undefined4 *)(this + 0x74) = 1;
    }
    return;
  }
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0x74) = 1;
  *(undefined4 *)(this + 0x84) = 0x3d088889;
  *(undefined4 *)(this + 0x7c) = 0x3d088889;
  *(uint *)(Game + 0x85240) = *(uint *)(Game + 0x85240) | 0x20;
  return;
}
