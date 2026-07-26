/*
 * mangled: _ZN10cRSubGoldy4InitEi
 * demangled: cRSubGoldy::Init(int)
 * address: 00079da8
 * size: 1616
 */

/* cRSubGoldy::Init(int) */

void __thiscall cRSubGoldy::Init(cRSubGoldy *this,int param_1)

{
  int iVar1;
  int iVar2;
  cRSubGoldy *pcVar3;
  uint uVar4;

  *(int *)(this + 0x370) = param_1;
  *(undefined4 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x138) = 0;
  iVar2 = Game;
  *(undefined4 *)(this + 0x360) = 0;
  *(undefined4 *)(this + 0x324) = 0;
  *(undefined4 *)(this + 0x80) = 0;
  iVar1 = *(int *)(this + 0x2824);
  *(int *)(this + 0x400) = iVar2 + 0x718a0;
  *(undefined4 *)(this + 0x328) = 0xffffffff;
  *(undefined4 *)(&DAT_003a5e5c + iVar2) = 0;
  this[0x3f6c] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x397c) = 0;
  *(undefined4 *)(this + 0x43c) = 0;
  *(undefined4 *)(this + 0x2ec0) = 0;
  this[0x2c0] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x2c4) = 0;
  *(undefined4 *)(this + 0x3254) = 0;
  *(cRSubGoldy **)(this + 0x13c) = this;
  *(undefined4 *)(this + 0x2c8) = 0;
  *(undefined4 *)(this + 0x35e8) = 0;
  this[0x134] = (cRSubGoldy)0x0;
  this[0x1cc] = (cRSubGoldy)0x0;
  cRDistort::Init((cRDistort *)(iVar1 + 0xf0));
  *(undefined4 *)(this + 0x3f64) = 0;
  *(undefined4 *)(this + 0x3f68) = 0x3c888889;
  *(undefined4 *)(this + 0x1b4) = 0;
  *(undefined4 *)(this + 0x4010) = 0;
  *(undefined4 *)(this + 0x27fc) = 0xc0400000;
  *(undefined4 *)(this + 0x4014) = 0x3c888889;
  cRSquidge::Init((cRSquidge *)(this + 0x3ff8));
  cRInvincible::Init();
  *(undefined4 *)(this + 0x42c) = 0;
  uVar4 = **(uint **)(this + 0x2824);
  *(undefined4 *)(this + 0x31c) = 0x3d638e39;
  *(undefined4 *)(this + 0x430) = 0x3c888889;
  *(undefined4 *)(this + 800) = 0x3d638e39;
  if ((uVar4 & 0x200000) == 0) {
    cRAnimManager::Init((cRAnimManager *)(this + 0x28f8));
    *(undefined4 *)(this + 0x28f8) = 0;
  }
  else {
    *(cRAnimManager **)(this + 0x286c) = (cRAnimManager *)(this + 0x28f8);
    *(uint *)(this + 0x2804) = *(uint *)(this + 0x2804) | 0x800;
    cRAnimManager::Init((cRAnimManager *)(this + 0x28f8));
    *(undefined4 *)(this + 0x28f8) = 1;
    *(undefined4 *)(this + 0x2934) = 0;
    *(cRSubGoldy **)(this + 0x293c) = this + 0x2940;
    *(cRSubGoldy **)(this + 0x2938) = this + 0x2800;
  }
  if ((**(uint **)(this + 0x38a8) & 0x200000) == 0) {
    cRAnimManager::Init((cRAnimManager *)(this + 0x3980));
    *(undefined4 *)(this + 0x3980) = 0;
  }
  else {
    *(cRAnimManager **)(this + 0x38f0) = (cRAnimManager *)(this + 0x3980);
    *(uint *)(this + 0x3888) = *(uint *)(this + 0x3888) & 0xffffffdf | 0x800;
    *(undefined4 *)(this + 0x397c) = 0;
    cRAnimManager::Init((cRAnimManager *)(this + 0x3980));
    *(undefined4 *)(this + 0x39bc) = 0;
    *(cRSubGoldy **)(this + 0x39c0) = this + 0x3884;
    *(cRSubGoldy **)(this + 0x39c4) = this + 0x39c8;
    *(undefined4 *)(this + 0x3980) = 1;
  }
  if ((**(uint **)(this + 0x2dec) & 0x200000) == 0) {
    cRAnimManager::Init((cRAnimManager *)(this + 0x2ec4));
    *(undefined4 *)(this + 0x2ec4) = 0;
  }
  else {
    *(cRAnimManager **)(this + 0x2e34) = (cRAnimManager *)(this + 0x2ec4);
    *(undefined4 *)(this + 0x2ec0) = 0;
    *(uint *)(this + 0x2dcc) = *(uint *)(this + 0x2dcc) & 0xffffffdf | 0x800;
    cRAnimManager::Init((cRAnimManager *)(this + 0x2ec4));
    *(undefined4 *)(this + 0x2f00) = 0;
    *(cRSubGoldy **)(this + 0x2f04) = this + 0x2dc8;
    *(cRSubGoldy **)(this + 0x2f08) = this + 0x2f0c;
    *(undefined4 *)(this + 0x2ec4) = 1;
  }
  if ((**(uint **)(this + 0x3180) & 0x200000) == 0) {
    cRAnimManager::Init((cRAnimManager *)(this + 0x3258));
    *(undefined4 *)(this + 0x3258) = 0;
  }
  else {
    *(cRAnimManager **)(this + 0x31c8) = (cRAnimManager *)(this + 0x3258);
    *(undefined4 *)(this + 0x3254) = 0;
    *(uint *)(this + 0x3160) = *(uint *)(this + 0x3160) & 0xffffffdf | 0x800;
    cRAnimManager::Init((cRAnimManager *)(this + 0x3258));
    *(undefined4 *)(this + 0x3294) = 0;
    *(cRSubGoldy **)(this + 0x3298) = this + 0x315c;
    *(cRSubGoldy **)(this + 0x329c) = this + 0x32a0;
    *(undefined4 *)(this + 0x3258) = 1;
  }
  if ((**(uint **)(this + 0x3514) & 0x200000) == 0) {
    cRAnimManager::Init((cRAnimManager *)(this + 0x35ec));
    *(undefined4 *)(this + 0x35ec) = 0;
  }
  else {
    *(cRAnimManager **)(this + 0x355c) = (cRAnimManager *)(this + 0x35ec);
    *(undefined4 *)(this + 0x35e8) = 0;
    *(uint *)(this + 0x34f4) = *(uint *)(this + 0x34f4) & 0xffffffdf | 0x800;
    cRAnimManager::Init((cRAnimManager *)(this + 0x35ec));
    *(undefined4 *)(this + 0x3628) = 0;
    *(cRSubGoldy **)(this + 0x362c) = this + 0x34f0;
    *(cRSubGoldy **)(this + 0x3630) = this + 0x3634;
    *(undefined4 *)(this + 0x35ec) = 1;
  }
  cRSnailSkin::Init((cRSnailSkin *)(this + 0x3f70));
  cRCutScene::Init((cRCutScene *)(this + 0x3f90));
  if (gGroup0[*(int *)(this + 0x400) + 0x9d618] == '\0') {
    *(undefined4 *)(this + 0x3f9c) = 1;
  }
  *(cRSubGoldy **)(this + 0x28f4) = this;
  tMatrix::Identity((tMatrix *)(this + 0x282c));
  tMatrix::Identity((tMatrix *)(this + 0x28b4));
  tMatrix::Identity((tMatrix *)(this + 0x2874));
  *(undefined4 *)(this + 0x3fec) = 0;
  cRClickStart::Init((cRClickStart *)(this + 0x94),this);
  cRCameraman::Init((cRCameraman *)(this + 0x1e8));
  GhostInit(this,*(int *)(this + 0x370));
  *(undefined4 *)(this + 0x5c) = 0;
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 100) = 0x40800000;
  *(undefined4 *)(this + 0x36c) = 0;
  *(undefined4 *)(this + 0x314) = 0;
  *(undefined4 *)(this + 0x1bc) = 0;
  *(undefined4 *)(this + 0x27e0) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0x27e4) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0x27e8) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0x1c4) = 0;
  *(undefined4 *)(this + 0x3c20) = 0;
  *(undefined4 *)(this + 0x3c18) = 0;
  *(undefined4 *)(this + 0x3c1c) = 0x3bbc5264;
  *(undefined4 *)(this + 0x408) = 0;
  *(undefined4 *)(this + 0x1c8) = 0x3d4ede61;
  *(undefined4 *)(this + 0x1c0) = 0x3d4ede61;
  *(undefined4 *)(this + 0x410) = 0;
  *(undefined4 *)(this + 0x40c) = 0;
  this[0x78] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x318) = 0x3c888889;
  *(undefined4 *)(this + 0x3c24) = 0x3bde0163;
  if (*(int *)(this + 0x370) == 1) {
    if (Game != -0x68) {
      iVar2 = Game + 0x94;
      goto LAB_0007a294;
    }
  }
  else if (Game != -0xd4) {
    iVar2 = Game + 0x100;
    goto LAB_0007a294;
  }
  iVar2 = 0;
LAB_0007a294:
  *(int *)(this + 0x434) = iVar2;
  *(undefined4 *)(this + 0x25b4) = 0;
  *(undefined4 *)(this + 0x25ac) = 0;
  iVar2 = 0;
  this[0x438] = (cRSubGoldy)0x0;
  cRDamageGuage::Init((cRDamageGuage *)(this + 0x3b4));
  cRProgressBar::Init();
  this[0x374] = (cRSubGoldy)0x0;
  pcVar3 = this;
  do {
    iVar1 = iVar2 * 0x2c8;
    *(undefined4 *)(pcVar3 + 0x670) = 0;
    iVar2 = iVar2 + 1;
    tMatrix::Identity((tMatrix *)(this + iVar1 + 0x5f0));
    *(undefined4 *)(pcVar3 + 0x69c) = *(undefined4 *)(this + 0x400);
    pcVar3 = pcVar3 + 0x2c8;
  } while (iVar2 != 0xc);
  *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
  *(undefined4 *)(this + 0x25c0) = 0;
  *(undefined4 *)(this + 0x25c8) = 0;
  *(undefined4 *)(this + 0x25c4) = 0x3e555556;
  cRSubHover::Init((int)(this + 0x25cc));
  this[0x415] = (cRSubGoldy)0x0;
  this[0x414] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x368) = 0;
  *(undefined4 *)(this + 0x3fc) = 0;
  *(undefined4 *)(this + 0x340) = 0;
  *(undefined4 *)(this + 0x344) = 0;
  *(undefined4 *)(this + 0x33c) = 0;
  *(undefined4 *)(this + 0x348) = 0;
  *(undefined4 *)(this + 0x350) = 0;
  *(undefined4 *)(this + 0x354) = 0;
  *(undefined4 *)(this + 0x358) = 0;
  *(undefined4 *)(this + 0x35c) = 0;
  *(undefined4 *)(this + 0x364) = 0;
  *(undefined1 *)(*(int *)(this + 0x400) + 1) = 1;
  return;
}
