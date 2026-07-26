/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter12formatScopedEP16OFISerializerKey
 * demangled: OFHttpNestedQueryStringWriter::formatScoped(OFISerializerKey*)
 * address: 000c8b68
 * size: 192
 */

/* OFHttpNestedQueryStringWriter::formatScoped(OFISerializerKey*) */

ID __thiscall
OFHttpNestedQueryStringWriter::formatScoped
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1)

{
  ID self;
  int *piVar1;
  undefined4 uVar2;
  int iVar3;

  self = getCurrentScope(this);
  piVar1 = (int *)OFISerializer::getActiveScopes((OFISerializer *)this);
  if (*piVar1 == piVar1[1]) {
    uVar2 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
    _objc_msgSend(self,"appendFormat:",&cf__s,uVar2);
    return self;
  }
  iVar3 = OFISerializer::isCurrentScopeASeries((OFISerializer *)this);
  if (iVar3 == 0) {
    uVar2 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
    _objc_msgSend(self,"appendFormat:",&cf___s_,uVar2);
    return self;
  }
  _objc_msgSend(self,"appendFormat:",&cf___);
  return self;
}
