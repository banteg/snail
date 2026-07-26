/*
 * mangled: _ZN10cRSubGoldy4InitEi
 * demangled: cRSubGoldy::Init(int)
 * address: 0001e158
 * size: 2216
 */

/* cRSubGoldy::Init(int) */

void __thiscall cRSubGoldy::Init(cRSubGoldy *this,int param_1)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;

  *(int *)(this + 0x370) = param_1;
  puVar2 = PTR__Game_001b60b8;
  iVar3 = *(int *)PTR__Game_001b60b8;
  *(undefined4 *)(this + 0x360) = 0;
  *(int *)(this + 0x3f8) = iVar3 + 0x72b78;
  *(undefined4 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x434) = 0;
  *(undefined4 *)(this + 0x328) = 0xffffffff;
  this[0x2c0] = (cRSubGoldy)0x0;
  this[0x3f64] = (cRSubGoldy)0x0;
  *(cRSubGoldy **)(this + 0x13c) = this;
  *(undefined4 *)(this + 0x138) = 0;
  this[0x134] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x324) = 0;
  this[0x1cc] = (cRSubGoldy)0x0;
  *(undefined4 *)(&DAT_00377e40 + iVar3) = 0;
  *(undefined4 *)(this + 0x2c4) = 0;
  *(undefined4 *)(this + 0x2c8) = 0;
  *(undefined4 *)(this + 0x3974) = 0;
  *(undefined4 *)(this + 0x2eb8) = 0;
  *(undefined4 *)(this + 0x324c) = 0;
  *(undefined4 *)(this + 0x35e0) = 0;
  cRDistort::Init((cRDistort *)(*(int *)(this + 0x281c) + 0xf0));
  *(undefined4 *)(this + 0x27f4) = 0xc0400000;
  *(undefined4 *)(this + 0x3f5c) = 0;
  *(undefined4 *)(this + 0x4008) = 0;
  *(undefined4 *)(this + 0x3f60) = 0x3c888889;
  *(undefined4 *)(this + 0x400c) = 0x3c888889;
  *(undefined4 *)(this + 0x3ff4) = 0;
  *(undefined4 *)(this + 0x4000) = 0;
  *(undefined4 *)(this + 0x3ff8) = 0;
  *(undefined4 *)(this + 0x4004) = 0;
  *(undefined4 *)(this + 0x3ff0) = 0;
  *(undefined4 *)(this + 0x1b4) = 0;
  *(undefined4 *)(this + 0x3ffc) = 0;
  *(undefined4 *)(this + 0x3f44) = 0;
  iVar3 = *(int *)puVar2;
  *(undefined4 *)(iVar3 + 0x85f3c) = 1;
  *(undefined4 *)(iVar3 + 0x85f40) = 0;
  *(undefined4 *)(iVar3 + 0x85f28) = 0;
  *(undefined4 *)(iVar3 + 0x85f44) = 0;
  *(undefined4 *)(this + 800) = 0x3d638e39;
  *(undefined4 *)(this + 0x31c) = 0x3d638e39;
  *(undefined4 *)(this + 0x424) = 0;
  *(undefined4 *)(this + 0x428) = 0x3c888889;
  if ((**(uint **)(this + 0x281c) & 0x200000) == 0) {
    *(undefined4 *)(this + 0x28f0) = 0;
    *(undefined4 *)(this + 0x28f4) = 0;
    *(undefined4 *)(this + 0x28f8) = 0;
    this[0x2900] = (cRSubGoldy)0x0;
    uVar4 = **(uint **)(this + 0x38a0);
  }
  else {
    *(undefined4 *)(this + 0x28f0) = 1;
    *(undefined4 *)(this + 0x292c) = 0;
    *(uint *)(this + 0x27fc) = *(uint *)(this + 0x27fc) | 0x800;
    *(cRSubGoldy **)(this + 0x2864) = this + 0x28f0;
    *(undefined4 *)(this + 0x28f4) = 0;
    *(undefined4 *)(this + 0x28f8) = 0;
    this[0x2900] = (cRSubGoldy)0x0;
    *(cRSubGoldy **)(this + 0x2930) = this + 0x27f8;
    *(cRSubGoldy **)(this + 0x2934) = this + 0x2938;
    uVar4 = **(uint **)(this + 0x38a0);
  }
  if ((uVar4 & 0x200000) == 0) {
    *(undefined4 *)(this + 0x397c) = 0;
    *(undefined4 *)(this + 0x3978) = 0;
    *(undefined4 *)(this + 0x3980) = 0;
    this[0x3988] = (cRSubGoldy)0x0;
    uVar4 = **(uint **)(this + 0x2de4);
  }
  else {
    *(uint *)(this + 0x3880) = *(uint *)(this + 0x3880) & 0xffffffdf | 0x800;
    *(cRSubGoldy **)(this + 0x38e8) = this + 0x3978;
    *(undefined4 *)(this + 0x3974) = 0;
    *(undefined4 *)(this + 0x397c) = 0;
    *(undefined4 *)(this + 0x39b4) = 0;
    *(undefined4 *)(this + 0x3980) = 0;
    this[0x3988] = (cRSubGoldy)0x0;
    *(undefined4 *)(this + 0x3978) = 1;
    *(cRSubGoldy **)(this + 0x39b8) = this + 0x387c;
    *(cRSubGoldy **)(this + 0x39bc) = this + 0x39c0;
    uVar4 = **(uint **)(this + 0x2de4);
  }
  if ((uVar4 & 0x200000) == 0) {
    *(undefined4 *)(this + 0x2ec0) = 0;
    *(undefined4 *)(this + 0x2ebc) = 0;
    *(undefined4 *)(this + 0x2ec4) = 0;
    this[0x2ecc] = (cRSubGoldy)0x0;
    uVar4 = **(uint **)(this + 0x3178);
  }
  else {
    *(uint *)(this + 0x2dc4) = *(uint *)(this + 0x2dc4) & 0xffffffdf | 0x800;
    *(cRSubGoldy **)(this + 0x2e2c) = this + 0x2ebc;
    *(undefined4 *)(this + 0x2eb8) = 0;
    *(undefined4 *)(this + 0x2ec0) = 0;
    *(undefined4 *)(this + 0x2ef8) = 0;
    *(undefined4 *)(this + 0x2ec4) = 0;
    this[0x2ecc] = (cRSubGoldy)0x0;
    *(undefined4 *)(this + 0x2ebc) = 1;
    *(cRSubGoldy **)(this + 0x2efc) = this + 0x2dc0;
    *(cRSubGoldy **)(this + 0x2f00) = this + 0x2f04;
    uVar4 = **(uint **)(this + 0x3178);
  }
  if ((uVar4 & 0x200000) == 0) {
    *(undefined4 *)(this + 0x3254) = 0;
    *(undefined4 *)(this + 0x3258) = 0;
    *(undefined4 *)(this + 0x3250) = 0;
    this[0x3260] = (cRSubGoldy)0x0;
    uVar4 = **(uint **)(this + 0x350c);
  }
  else {
    *(undefined4 *)(this + 0x324c) = 0;
    *(uint *)(this + 0x3158) = *(uint *)(this + 0x3158) & 0xffffffdf | 0x800;
    *(cRSubGoldy **)(this + 0x31c0) = this + 0x3250;
    *(undefined4 *)(this + 0x3254) = 0;
    *(undefined4 *)(this + 0x3258) = 0;
    *(undefined4 *)(this + 0x328c) = 0;
    this[0x3260] = (cRSubGoldy)0x0;
    *(undefined4 *)(this + 0x3250) = 1;
    *(cRSubGoldy **)(this + 0x3290) = this + 0x3154;
    *(cRSubGoldy **)(this + 0x3294) = this + 0x3298;
    uVar4 = **(uint **)(this + 0x350c);
  }
  if ((uVar4 & 0x200000) == 0) {
    *(undefined4 *)(this + 0x35e8) = 0;
    *(undefined4 *)(this + 0x35e4) = 0;
    *(undefined4 *)(this + 0x35ec) = 0;
    this[0x35f4] = (cRSubGoldy)0x0;
  }
  else {
    *(uint *)(this + 0x34ec) = *(uint *)(this + 0x34ec) & 0xffffffdf | 0x800;
    *(cRSubGoldy **)(this + 0x3554) = this + 0x35e4;
    *(undefined4 *)(this + 0x35e0) = 0;
    *(undefined4 *)(this + 0x35e8) = 0;
    *(undefined4 *)(this + 0x3620) = 0;
    *(undefined4 *)(this + 0x35ec) = 0;
    this[0x35f4] = (cRSubGoldy)0x0;
    *(undefined4 *)(this + 0x35e4) = 1;
    *(cRSubGoldy **)(this + 0x3624) = this + 0x34e8;
    *(cRSubGoldy **)(this + 0x3628) = this + 0x362c;
  }
  puVar2 = PTR__Game_001b60b8;
  iVar3 = *(int *)PTR__Game_001b60b8;
  *(undefined4 *)(this + 0x3f68) = 0;
  *(undefined4 *)(this + 0x3f7c) = 0;
  *(int *)(this + 0x3f78) = iVar3 + 0x847b8;
  *(int *)(this + 0x3f88) = *(int *)puVar2 + 0x847b8;
  iVar3 = *(int *)puVar2;
  *(undefined4 *)(this + 0x3f94) = 0;
  *(int *)(this + 0x3f8c) = iVar3 + 0x81fc0;
  cVar1 = (&DAT_002e09cc)[*(int *)(this + 0x3f8)];
  *(cRSubGoldy **)(this + 0x28ec) = this;
  if (cVar1 == '\0') {
    *(undefined4 *)(this + 0x3f94) = 1;
  }
  tMatrix::Identity((tMatrix *)(this + 0x2824));
  tMatrix::Identity((tMatrix *)(this + 0x28ac));
  tMatrix::Identity((tMatrix *)(this + 0x286c));
  *(undefined4 *)(this + 0x3fe4) = 0;
  cRClickStart::Init((cRClickStart *)(this + 0x94),this);
  *(int *)(this + 0x2a8) = *(int *)puVar2 + 0x81fc0;
  iVar3 = *(int *)puVar2;
  this[0x2b4] = (cRSubGoldy)0x0;
  *(int *)(this + 0x2ac) = iVar3 + 0x72b78;
  tMatrix::Identity((tMatrix *)(this + 0x268));
  tMatrix::Identity((tMatrix *)(this + 0x228));
  tMatrix::Identity((tMatrix *)(this + 0x1e8));
  *(undefined4 *)(this + 0x2b0) = 0x42f00000;
  *(undefined4 *)(this + 0x2b8) = 0;
  *(undefined4 *)(this + 700) = 0;
  GhostInit(this,*(int *)(this + 0x370));
  *(undefined4 *)(this + 0x318) = 0x3c888889;
  *(undefined4 *)(this + 0x5c) = 0;
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x1c0) = 0x3d4ede61;
  *(undefined4 *)(this + 0x1c8) = 0x3d4ede61;
  *(undefined4 *)(this + 0x36c) = 0;
  *(undefined4 *)(this + 0x3c10) = 0;
  *(undefined4 *)(this + 0x314) = 0;
  *(undefined4 *)(this + 0x3c14) = 0x3bbc5264;
  *(undefined4 *)(this + 0x3c18) = 0;
  *(undefined4 *)(this + 0x1bc) = 0;
  *(undefined4 *)(this + 0x3c1c) = 0x3bde0163;
  *(undefined4 *)(this + 0x1c4) = 0;
  this[0x78] = (cRSubGoldy)0x0;
  *(undefined1 **)(this + 100) = &DAT_40800000;
  *(undefined4 *)(this + 0x27d8) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0x27dc) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0x27e0) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0x408) = 0;
  *(undefined4 *)(this + 0x404) = 0;
  *(undefined4 *)(this + 0x400) = 0;
  if (*(int *)(this + 0x370) == 1) {
    iVar3 = 0;
    if (*(int *)puVar2 != -0x68) {
      iVar3 = *(int *)puVar2 + 0x94;
    }
  }
  else {
    iVar3 = 0;
    if (*(int *)puVar2 != -0xd4) {
      iVar3 = *(int *)puVar2 + 0x100;
    }
  }
  *(undefined4 *)(this + 0x25a4) = 0;
  *(undefined4 *)(this + 0x25ac) = 0;
  *(undefined4 *)(this + 0x3bc) = 0x3caaaaab;
  *(int *)(this + 0x42c) = iVar3;
  this[0x430] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x3dc) = 0x3d088889;
  *(undefined4 *)(this + 0x3d0) = 0;
  *(undefined4 *)(this + 0x3d4) = 0;
  *(undefined4 *)(this + 0x3cc) = 0;
  *(undefined4 *)(this + 0x3b4) = 0;
  *(undefined4 *)(this + 0x3c4) = 0;
  this[0x3c0] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x3b8) = 0;
  *(undefined4 *)(this + 0x3d8) = 0;
  this[0x374] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x668) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x5e8));
  *(undefined4 *)(this + 0x930) = 0;
  *(undefined4 *)(this + 0x694) = *(undefined4 *)(this + 0x3f8);
  tMatrix::Identity((tMatrix *)(this + 0x8b0));
  *(undefined4 *)(this + 0x95c) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0xbf8) = 0;
  tMatrix::Identity((tMatrix *)(this + 0xb78));
  *(undefined4 *)(this + 0xec0) = 0;
  *(undefined4 *)(this + 0xc24) = *(undefined4 *)(this + 0x3f8);
  tMatrix::Identity((tMatrix *)(this + 0xe40));
  *(undefined4 *)(this + 0xeec) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0x1188) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x1108));
  *(undefined4 *)(this + 0x11b4) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0x1450) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x13d0));
  *(undefined4 *)(this + 0x147c) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0x1718) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x1698));
  *(undefined4 *)(this + 0x1744) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0x19e0) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x1960));
  *(undefined4 *)(this + 0x1a0c) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0x1ca8) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x1c28));
  *(undefined4 *)(this + 0x1cd4) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0x1f70) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x1ef0));
  *(undefined4 *)(this + 0x1f9c) = *(undefined4 *)(this + 0x3f8);
  *(undefined4 *)(this + 0x2238) = 0;
  tMatrix::Identity((tMatrix *)(this + 0x21b8));
  *(undefined4 *)(this + 0x2500) = 0;
  *(undefined4 *)(this + 0x2264) = *(undefined4 *)(this + 0x3f8);
  tMatrix::Identity((tMatrix *)(this + 0x2480));
  *(undefined4 *)(this + 0x252c) = *(undefined4 *)(this + 0x3f8);
  *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
  *(undefined4 *)(this + 0x25b8) = 0;
  *(undefined4 *)(this + 0x25bc) = 0x3e555556;
  *(undefined4 *)(this + 0x25c0) = 0;
  *(undefined4 *)(this + 0x25c4) = 0;
  puVar2 = PTR__Game_001b60b8;
  *(int *)(this + 0x27c4) = *(int *)PTR__Game_001b60b8 + 0x72b78;
  *(undefined4 *)(this + 0x25c8) = 0x3ada740e;
  iVar3 = *(int *)puVar2;
  *(undefined4 *)(this + 0x25d0) = 0;
  *(undefined4 *)(this + 0x33c) = 0;
  *(int *)(this + 0x25d4) = iVar3 + 0x81fc0;
  *(undefined4 *)(this + 0x340) = 0;
  *(undefined4 *)(this + 0x25e0) = 0;
  *(undefined4 *)(this + 0x344) = 0;
  *(undefined4 *)(this + 0x25dc) = 0;
  *(undefined4 *)(this + 0x348) = 0;
  *(undefined4 *)(this + 0x25d8) = 0;
  *(undefined4 *)(this + 0x350) = 0;
  *(undefined4 *)(this + 0x27d0) = 0;
  *(undefined4 *)(this + 0x354) = 0;
  *(undefined4 *)(this + 0x358) = 0;
  *(undefined4 *)(this + 0x35c) = 0;
  *(undefined4 *)(this + 0x364) = 0;
  *(undefined4 *)(this + 0x368) = 0;
  this[0x40d] = (cRSubGoldy)0x0;
  this[0x40c] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x3f4) = 0;
  *(undefined1 *)(*(int *)(this + 0x3f8) + 1) = 1;
  return;
}
