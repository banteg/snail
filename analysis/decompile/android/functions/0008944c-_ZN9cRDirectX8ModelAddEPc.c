/*
 * mangled: _ZN9cRDirectX8ModelAddEPc
 * demangled: cRDirectX::ModelAdd(char*)
 * address: 0008944c
 * size: 228
 */

/* cRDirectX::ModelAdd(char*) */

int __thiscall cRDirectX::ModelAdd(cRDirectX *this,char *param_1)

{
  cRObject *pcVar1;
  int iVar2;
  int iVar3;

  iVar2 = *(int *)(this + 4);
  if (iVar2 < 1) {
    iVar3 = 0;
  }
  else {
    iVar3 = 0;
    do {
      iVar2 = Rstrcmp(param_1,(char *)(this + iVar3 * 0xb0 + 0x38));
      if (iVar2 != 0) {
        return iVar3;
      }
      iVar2 = *(int *)(this + 4);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar2);
  }
  Rstrcpy((char *)(this + iVar2 * 0xb0 + 0x38),param_1);
  iVar2 = *(int *)(this + 4);
  pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + (iVar2 * 0x16 + 1) * 8),pcVar1);
  pcVar1 = *(cRObject **)(this + iVar3 * 0xb0 + 0x2c);
  *(uint *)pcVar1 = *(uint *)pcVar1 | 0x1000;
  Load(this,param_1,pcVar1,1);
  iVar2 = *(int *)(this + 4);
  *(int *)(this + 4) = iVar2 + 1;
  return iVar2;
}
