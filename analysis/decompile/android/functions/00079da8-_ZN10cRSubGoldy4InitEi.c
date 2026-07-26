/*
 * mangled: _ZN10cRSubGoldy4InitEi
 * demangled: cRSubGoldy::Init(int)
 * address: 00079da8
 * size: 1616
 */

/* cRSubGoldy::Init(int) */

void __thiscall cRSubGoldy::Init(cRSubGoldy *this,int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  cRSubGoldy *pcVar9;
  uint uVar10;

  uVar3 = DAT_0007a150;
  iVar7 = DAT_0007a138;
  iVar8 = DAT_0007a134 + 0x79dc8;
  *(int *)(this + 0x370) = param_1;
  piVar5 = *(int **)(iVar8 + iVar7);
  *(undefined4 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x138) = 0;
  iVar6 = *piVar5;
  *(undefined4 *)(this + 0x360) = uVar3;
  *(undefined4 *)(this + 0x324) = 0;
  *(undefined4 *)(this + 0x80) = uVar3;
  iVar4 = *(int *)(this + 0x2824);
  *(int *)(this + 0x400) = iVar6 + 0x718a0;
  *(undefined4 *)(this + 0x328) = 0xffffffff;
  *(undefined4 *)(&DAT_003a5e5c + iVar6) = 0;
  this[0x3f6c] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x397c) = 0;
  *(undefined4 *)(this + 0x43c) = uVar3;
  *(undefined4 *)(this + 0x2ec0) = 0;
  this[0x2c0] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x2c4) = uVar3;
  *(undefined4 *)(this + 0x3254) = 0;
  *(cRSubGoldy **)(this + 0x13c) = this;
  *(undefined4 *)(this + 0x2c8) = uVar3;
  *(undefined4 *)(this + 0x35e8) = 0;
  uVar2 = DAT_0007a148;
  this[0x134] = (cRSubGoldy)0x0;
  this[0x1cc] = (cRSubGoldy)0x0;
  cRDistort::Init((cRDistort *)(iVar4 + 0xf0));
  *(undefined4 *)(this + 0x3f64) = uVar3;
  uVar1 = DAT_0007a12c;
  *(undefined4 *)(this + 0x3f68) = uVar2;
  *(undefined4 *)(this + 0x1b4) = 0;
  *(undefined4 *)(this + 0x4010) = uVar3;
  *(undefined4 *)(this + 0x27fc) = uVar1;
  *(undefined4 *)(this + 0x4014) = uVar2;
  cRSquidge::Init((cRSquidge *)(this + 0x3ff8));
  cRInvincible::Init();
  uVar1 = DAT_0007a130;
  *(undefined4 *)(this + 0x42c) = uVar3;
  uVar10 = **(uint **)(this + 0x2824);
  *(undefined4 *)(this + 0x31c) = uVar1;
  *(undefined4 *)(this + 0x430) = uVar2;
  *(undefined4 *)(this + 800) = uVar1;
  if ((uVar10 & 0x200000) == 0) {
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
  uVar3 = DAT_0007a150;
  uVar1 = DAT_0007a13c;
  *(undefined4 *)(this + 0x5c) = DAT_0007a150;
  *(undefined4 *)(this + 0x60) = uVar3;
  *(undefined4 *)(this + 100) = uVar1;
  *(undefined4 *)(this + 0x36c) = uVar3;
  *(undefined4 *)(this + 0x314) = uVar3;
  *(undefined4 *)(this + 0x1bc) = uVar3;
  *(undefined4 *)(this + 0x27e0) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0x27e4) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0x27e8) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0x1c4) = uVar3;
  uVar1 = DAT_0007a140;
  *(undefined4 *)(this + 0x3c20) = uVar3;
  uVar2 = DAT_0007a144;
  *(undefined4 *)(this + 0x3c18) = uVar3;
  *(undefined4 *)(this + 0x3c1c) = uVar1;
  *(undefined4 *)(this + 0x408) = uVar3;
  *(undefined4 *)(this + 0x1c8) = uVar2;
  *(undefined4 *)(this + 0x1c0) = uVar2;
  *(undefined4 *)(this + 0x410) = uVar3;
  uVar1 = DAT_0007a148;
  *(undefined4 *)(this + 0x40c) = uVar3;
  uVar2 = DAT_0007a14c;
  this[0x78] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x318) = uVar1;
  *(undefined4 *)(this + 0x3c24) = uVar2;
  if (*(int *)(this + 0x370) == 1) {
    if (**(int **)(iVar8 + iVar7) != -0x68) {
      iVar7 = **(int **)(iVar8 + iVar7) + 0x94;
      goto LAB_0007a294;
    }
  }
  else if (**(int **)(iVar8 + iVar7) != -0xd4) {
    iVar7 = **(int **)(iVar8 + iVar7) + 0x100;
    goto LAB_0007a294;
  }
  iVar7 = 0;
LAB_0007a294:
  *(int *)(this + 0x434) = iVar7;
  uVar1 = DAT_0007a150;
  *(undefined4 *)(this + 0x25b4) = DAT_0007a150;
  *(undefined4 *)(this + 0x25ac) = uVar1;
  iVar7 = 0;
  this[0x438] = (cRSubGoldy)0x0;
  cRDamageGuage::Init((cRDamageGuage *)(this + 0x3b4));
  cRProgressBar::Init();
  this[0x374] = (cRSubGoldy)0x0;
  pcVar9 = this;
  do {
    iVar4 = iVar7 * 0x2c8;
    *(undefined4 *)(pcVar9 + 0x670) = 0;
    iVar7 = iVar7 + 1;
    tMatrix::Identity((tMatrix *)(this + iVar4 + 0x5f0));
    *(undefined4 *)(pcVar9 + 0x69c) = *(undefined4 *)(this + 0x400);
    uVar1 = DAT_0007a150;
    pcVar9 = pcVar9 + 0x2c8;
  } while (iVar7 != 0xc);
  *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
  uVar2 = DAT_0007a154;
  *(undefined4 *)(this + 0x25c0) = uVar1;
  *(undefined4 *)(this + 0x25c8) = uVar1;
  *(undefined4 *)(this + 0x25c4) = uVar2;
  cRSubHover::Init((int)(this + 0x25cc));
  this[0x415] = (cRSubGoldy)0x0;
  this[0x414] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x368) = uVar1;
  *(undefined4 *)(this + 0x3fc) = 0;
  *(undefined4 *)(this + 0x340) = uVar1;
  *(undefined4 *)(this + 0x344) = uVar1;
  *(undefined4 *)(this + 0x33c) = 0;
  *(undefined4 *)(this + 0x348) = uVar1;
  *(undefined4 *)(this + 0x350) = 0;
  *(undefined4 *)(this + 0x354) = uVar1;
  *(undefined4 *)(this + 0x358) = uVar1;
  *(undefined4 *)(this + 0x35c) = uVar1;
  *(undefined4 *)(this + 0x364) = uVar1;
  *(undefined1 *)(*(int *)(this + 0x400) + 1) = 1;
  return;
}
