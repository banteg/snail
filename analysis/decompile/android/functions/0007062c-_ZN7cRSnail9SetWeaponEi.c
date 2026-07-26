/*
 * mangled: _ZN7cRSnail9SetWeaponEi
 * demangled: cRSnail::SetWeapon(int)
 * address: 0007062c
 * size: 936
 */

/* cRSnail::SetWeapon(int) */

void __thiscall cRSnail::SetWeapon(cRSnail *this,int param_1)

{
  int iVar1;
  int unaff_r5;
  int unaff_r6;
  int unaff_r8;
  bool bVar2;
  bool bVar3;

  if (param_1 == 0x10) {
LAB_000708d4:
    unaff_r5 = 2;
    unaff_r6 = 0;
    unaff_r8 = 2;
  }
  else if (param_1 < 0x11) {
    if (param_1 == 2) {
      unaff_r5 = 1;
      unaff_r6 = 0;
      unaff_r8 = unaff_r5;
    }
    else if (param_1 < 3) {
      if (param_1 == 1) {
        unaff_r5 = 0;
        unaff_r6 = 1;
        unaff_r8 = unaff_r5;
      }
    }
    else if (param_1 == 4) {
      unaff_r5 = 1;
      unaff_r6 = unaff_r5;
      unaff_r8 = unaff_r5;
    }
    else if (param_1 == 8) {
      unaff_r6 = 0;
      unaff_r5 = 2;
      unaff_r8 = unaff_r6;
    }
  }
  else if (param_1 == 0x40) {
LAB_000707d0:
    unaff_r5 = 0;
    unaff_r6 = 3;
    unaff_r8 = unaff_r5;
  }
  else if (param_1 < 0x41) {
    if (param_1 == 0x20) goto LAB_000707d0;
  }
  else {
    if (param_1 == 0x90) goto LAB_000708d4;
    if (param_1 == 0xc0) goto LAB_000707d0;
  }
  iVar1 = *(int *)(this + 0x6c0);
  if (iVar1 == unaff_r8) {
    bVar3 = false;
  }
  else {
    if (iVar1 == 1) {
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x5c8),1,true,8);
      bVar3 = false;
      bVar2 = false;
      if (unaff_r8 == 1) goto LAB_0007085c;
LAB_000706ac:
      if (unaff_r8 == 2) {
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x5c8),4,bVar3,4);
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x5c8),3,false,-1);
      }
      else if (unaff_r8 == 0) {
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x5c8),-1,false,-1);
      }
    }
    else {
      bVar2 = iVar1 != 2;
      if (!bVar2) {
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x5c8),4,true,8);
      }
      bVar3 = bVar2;
      if (unaff_r8 != 1) goto LAB_000706ac;
LAB_0007085c:
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x5c8),unaff_r8,bVar2,4);
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x5c8),0,false,-1);
    }
    bVar3 = true;
    *(int *)(this + 0x6c0) = unaff_r8;
  }
  iVar1 = *(int *)(this + 0xa54);
  if (iVar1 != unaff_r5) {
    if (iVar1 == 1) {
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x95c),1,true,8);
      bVar3 = false;
      bVar2 = false;
      if (unaff_r5 == 1) goto LAB_0007080c;
LAB_00070708:
      if (unaff_r5 == 2) {
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x95c),4,bVar3,4);
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x95c),3,false,-1);
      }
      else if (unaff_r5 == 0) {
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x95c),-1,false,-1);
      }
    }
    else {
      bVar2 = iVar1 != 2;
      if (!bVar2) {
        cRWeapon::SetAnimation((cRWeapon *)(this + 0x95c),4,true,8);
      }
      bVar3 = bVar2;
      if (unaff_r5 != 1) goto LAB_00070708;
LAB_0007080c:
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x95c),unaff_r5,bVar2,4);
      cRWeapon::SetAnimation((cRWeapon *)(this + 0x95c),0,false,-1);
    }
    bVar3 = true;
    *(int *)(this + 0xa54) = unaff_r5;
  }
  iVar1 = *(int *)(this + 0xde8);
  if (iVar1 == unaff_r6) {
    if (!bVar3) {
      return;
    }
    goto LAB_00070774;
  }
  if (iVar1 == 1) {
    cRWeapon::SetAnimation((cRWeapon *)(this + 0xcf0),1,true,8);
    bVar3 = false;
    if (unaff_r6 == 1) goto LAB_000708a8;
LAB_00070760:
    if (unaff_r6 == 3) {
      cRWeapon::SetAnimation((cRWeapon *)(this + 0xcf0),4,bVar3,4);
      cRWeapon::SetAnimation((cRWeapon *)(this + 0xcf0),3,false,-1);
    }
    else if (unaff_r6 == 0) {
      cRWeapon::SetAnimation((cRWeapon *)(this + 0xcf0),-1,false,-1);
    }
  }
  else {
    bVar3 = iVar1 != 3;
    if (!bVar3) {
      cRWeapon::SetAnimation((cRWeapon *)(this + 0xcf0),4,true,8);
    }
    if (unaff_r6 != 1) goto LAB_00070760;
LAB_000708a8:
    cRWeapon::SetAnimation((cRWeapon *)(this + 0xcf0),unaff_r6,bVar3,4);
    cRWeapon::SetAnimation((cRWeapon *)(this + 0xcf0),0,false,-1);
  }
  *(int *)(this + 0xde8) = unaff_r6;
LAB_00070774:
  cRSound::Play((int)&gRSound);
  return;
}
