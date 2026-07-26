/*
 * mangled: _ZNK16OFRTTIRepository7getTypeEPKc
 * demangled: OFRTTIRepository::getType(char const*) const
 * address: 000c6898
 * size: 144
 */

/* OFRTTIRepository::getType(char const*) const */

undefined4 __thiscall OFRTTIRepository::getType(OFRTTIRepository *this,char *param_1)

{
  OFRTTIRepository *pOVar1;
  int iVar2;
  OFRTTIRepository *pOVar3;
  undefined4 uVar4;
  OFRTTIRepository *pOVar5;
  OFSdbmHashedString aOStack_18 [4];

  OFSdbmHashedString::OFSdbmHashedString(aOStack_18,param_1);
  pOVar5 = this + 4;
  pOVar1 = *(OFRTTIRepository **)(this + 8);
  pOVar3 = this + 4;
  while (pOVar1 != (OFRTTIRepository *)0x0) {
    iVar2 = OFSdbmHashedString::operator<((OFSdbmHashedString *)(pOVar1 + 0x10),aOStack_18);
    if (iVar2 == 0) {
      pOVar1 = *(OFRTTIRepository **)(pOVar1 + 8);
      pOVar3 = pOVar1;
    }
    else {
      pOVar1 = *(OFRTTIRepository **)(pOVar1 + 0xc);
    }
  }
  if ((pOVar3 == pOVar5) ||
     (iVar2 = OFSdbmHashedString::operator<(aOStack_18,(OFSdbmHashedString *)(pOVar3 + 0x10)),
     iVar2 != 0)) {
    pOVar3 = pOVar5;
  }
  if (pOVar5 == pOVar3) {
    uVar4 = 0;
  }
  else {
    uVar4 = *(undefined4 *)(pOVar3 + 0x14);
  }
  return uVar4;
}
