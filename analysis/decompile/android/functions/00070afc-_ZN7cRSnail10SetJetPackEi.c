/*
 * mangled: _ZN7cRSnail10SetJetPackEi
 * demangled: cRSnail::SetJetPack(int)
 * address: 00070afc
 * size: 236
 */

/* cRSnail::SetJetPack(int) */

void __thiscall cRSnail::SetJetPack(cRSnail *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar2 = DAT_00070be8 + 0x70b14;
  iVar3 = 0;
  if (param_1 != 0) {
    if (param_1 == 1) {
      iVar3 = 4;
    }
    else {
      iVar3 = 0;
    }
  }
  iVar1 = *(int *)(this + 0x117c);
  if (iVar1 == iVar3) {
    return;
  }
  if (iVar1 == 4) {
    cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),1,true,8);
    cRSound::Play(*(int *)(iVar2 + DAT_00070bec));
  }
  if (iVar3 != 0) {
    if (iVar3 == 4) {
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),1,iVar1 != 4,4);
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),0,false,-1);
      cRSound::Play(*(int *)(iVar2 + DAT_00070bec));
    }
    *(int *)(this + 0x117c) = iVar3;
    return;
  }
  cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),-1,false,-1);
  *(undefined4 *)(this + 0x117c) = 0;
  return;
}
