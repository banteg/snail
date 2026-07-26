/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter15getCurrentScopeEv
 * demangled: OFHttpNestedQueryStringWriter::getCurrentScope()
 * address: 000c8a4c
 * size: 252
 */

/* OFHttpNestedQueryStringWriter::getCurrentScope() */

ID __thiscall OFHttpNestedQueryStringWriter::getCurrentScope(OFHttpNestedQueryStringWriter *this)

{
  undefined4 *puVar1;
  ID IVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;

  IVar2 = NSMutableString::alloc((ID)&_OBJC_CLASS___NSMutableString,"alloc");
  IVar2 = NSMutableString::init(IVar2,"init");
  IVar2 = NSMutableString::autorelease(IVar2,"autorelease");
  puVar3 = (undefined4 *)OFISerializer::getActiveScopes((OFISerializer *)this);
  puVar5 = (undefined4 *)*puVar3;
  puVar3 = (undefined4 *)puVar3[1];
  if (puVar5 != puVar3) {
    uVar4 = (**(code **)(*(int *)*puVar5 + 0x14))();
    NSMutableString::appendFormat_(IVar2,"appendFormat:",&cf__s,uVar4);
    while (puVar1 = puVar5 + 2, puVar3 != puVar1) {
      if (*(char *)(puVar5 + 1) == '\0') {
        uVar4 = (**(code **)(*(int *)*puVar1 + 0x14))();
        NSMutableString::appendFormat_(IVar2,"appendFormat:",&cf___s_,uVar4);
        puVar5 = puVar1;
      }
      else {
        NSMutableString::appendFormat_(IVar2,"appendFormat:",&cf___);
        puVar5 = puVar1;
      }
    }
  }
  return IVar2;
}
