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

  iVar2 = 0;
  if (param_1 != 0) {
    if (param_1 == 1) {
      iVar2 = 4;
    }
    else {
      iVar2 = 0;
    }
  }
  iVar1 = *(int *)(this + 0x117c);
  if (iVar1 == iVar2) {
    return;
  }
  if (iVar1 == 4) {
    cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),1,true,8);
    cRSound::Play((int)&gRSound);
  }
  if (iVar2 != 0) {
    if (iVar2 == 4) {
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),1,iVar1 != 4,4);
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),0,false,-1);
      cRSound::Play((int)&gRSound);
    }
    *(int *)(this + 0x117c) = iVar2;
    return;
  }
  cRWeapon::SetAnimation((cRWeapon *)(this + 0x1084),-1,false,-1);
  *(undefined4 *)(this + 0x117c) = 0;
  return;
}
