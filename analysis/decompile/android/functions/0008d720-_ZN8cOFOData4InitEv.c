/*
 * mangled: _ZN8cOFOData4InitEv
 * demangled: cOFOData::Init()
 * address: 0008d720
 * size: 132
 */

/* cOFOData::Init() */

void __thiscall cOFOData::Init(cOFOData *this)

{
  cOFOData *pcVar1;
  cOFOData *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar3 = 0;
  iVar5 = 0;
  iVar4 = DAT_0008d7a4 + 0x8d748;
  *this = (cOFOData)0x0;
  this[1] = (cOFOData)0x0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 0;
  pcVar1 = this;
  pcVar2 = this;
  do {
    iVar3 = iVar3 + 1;
    *(undefined4 *)(pcVar2 + 0x2c) = 0;
    pcVar1[0x10c] = (cOFOData)0x0;
    pcVar2 = pcVar2 + 4;
    pcVar1 = pcVar1 + 1;
  } while (iVar3 != 0x38);
  do {
    iVar5 = iVar5 + 1;
    this[0x144] = (cOFOData)0x0;
    this = this + 1;
  } while (iVar5 != 0x23);
  strcpy(*(char **)(iVar4 + DAT_0008d7ac),(char *)(*(int *)(iVar4 + DAT_0008d7a8) + 0xf0));
  return;
}
