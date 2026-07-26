/*
 * mangled: _ZN9cRObjects3AddEv
 * demangled: cRObjects::Add()
 * address: 00014138
 * size: 140
 */

/* cRObjects::Add() */

int __thiscall cRObjects::Add(cRObjects *this)

{
  int iVar1;
  int iVar2;

  iVar1 = *(int *)this;
  if (iVar1 == *(int *)(this + 4)) {
    RShellError("Too many Objects - Increase ObjectList.Init(MAX) in G0.cpp");
    iVar1 = *(int *)this;
  }
  *(int *)this = iVar1 + 1;
  iVar2 = iVar1 * 0x110 + *(int *)(this + 8);
  *(undefined4 *)(iVar1 * 0x110 + *(int *)(this + 8)) = 0;
  *(undefined4 *)(iVar2 + 8) = 0;
  *(undefined4 *)(iVar2 + 0xa0) = 0;
  *(undefined4 *)(iVar2 + 0xc0) = 0;
  *(undefined4 *)(iVar2 + 0xb0) = 0;
  *(undefined4 *)(iVar2 + 0xac) = 0;
  *(undefined4 *)(iVar2 + 0xd4) = 0;
  _strcpy((char *)(iVar2 + 0x20),"Nao");
  *(undefined4 *)(iVar2 + 0x10c) = 0;
  *(undefined4 *)(iVar2 + 0xcc) = 0;
  *(undefined4 *)(iVar2 + 0xd0) = 0;
  *(undefined4 *)(iVar2 + 0xa4) = 0;
  *(undefined4 *)(iVar2 + 200) = 0;
  return iVar2;
}
