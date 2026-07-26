/*
 * mangled: _ZNK16OFViewDataGetter9serializeEP18OFOutputSerializer
 * demangled: OFViewDataGetter::serialize(OFOutputSerializer*) const
 * address: 000fc918
 * size: 264
 */

/* OFViewDataGetter::serialize(OFOutputSerializer*) const */

void __thiscall OFViewDataGetter::serialize(OFViewDataGetter *this,OFOutputSerializer *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  ID self;
  ID IVar4;
  int iVar5;
  undefined4 uVar6;
  code *pcVar7;

  puVar2 = (undefined4 *)OFViewDataMap::begin(*(OFViewDataMap **)(this + 4));
  puVar3 = (undefined4 *)OFViewDataMap::end(*(OFViewDataMap **)(this + 4));
  do {
    if (puVar2 == puVar3) {
      return;
    }
    self = OFViewHelper::findViewByTag(*(UIView **)this,puVar2[1]);
    uVar6 = *puVar2;
    IVar4 = _objc_msgSend(self,"class");
    if (IVar4 == sAvailableGetters) {
      iVar5 = 0;
LAB_000fc9d0:
      pcVar7 = (code *)(&DAT_001ee07c)[iVar5 * 3];
      if (pcVar7 != (code *)0x0) {
        iVar1 = (int)(&DAT_001ee080)[iVar5 * 3] >> 1;
        if (((&DAT_001ee080)[iVar5 * 3] & 1) != 0) {
          pcVar7 = *(code **)(pcVar7 + *(int *)(this + iVar1));
        }
        (*pcVar7)(this + iVar1,self,uVar6,param_1);
      }
    }
    else {
      if (IVar4 == DAT_001ee084) {
        iVar5 = 1;
        goto LAB_000fc9d0;
      }
      if (IVar4 == DAT_001ee090) {
        iVar5 = 2;
        goto LAB_000fc9d0;
      }
      if (IVar4 == DAT_001ee09c) {
        iVar5 = 3;
        goto LAB_000fc9d0;
      }
    }
    puVar2 = puVar2 + 3;
  } while( true );
}
