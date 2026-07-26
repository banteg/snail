/*
 * mangled: _ZN12OFViewHelper17sizeThatFitsTightEP6UIView
 * demangled: OFViewHelper::sizeThatFitsTight(UIView*)
 * address: 000db8b0
 * size: 444
 */

/* OFViewHelper::sizeThatFitsTight(UIView*) */

OFViewHelper * __thiscall OFViewHelper::sizeThatFitsTight(OFViewHelper *this,UIView *param_1)

{
  ID self;
  ID IVar1;
  undefined4 uVar2;
  int iVar3;
  ID self_00;
  uint uVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined8 uVar8;
  undefined1 local_d0 [64];
  undefined4 local_90;
  int local_8c;
  int *local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined auStack_70 [12];
  float local_64;
  undefined auStack_60 [4];
  float local_5c;
  undefined auStack_50 [8];
  float local_48;
  float local_40 [8];

  uVar2 = *(undefined4 *)(PTR_001b6240 + 4);
  *(undefined4 *)this = *(undefined4 *)PTR_001b6240;
  *(undefined4 *)(this + 4) = uVar2;
  if (param_1 != (UIView *)0x0) {
    local_90 = 0;
    local_8c = 0;
    local_88 = (int *)0x0;
    local_84 = 0;
    local_80 = 0;
    local_7c = 0;
    local_78 = 0;
    local_74 = 0;
    self = _objc_msgSend((ID)param_1,"subviews");
    IVar1 = _objc_msgSend(self,"countByEnumeratingWithState:objects:count:",&local_90,local_d0,0x10)
    ;
    if (IVar1 != 0) {
      iVar5 = *local_88;
      uVar8 = *(undefined8 *)this;
      iVar3 = iVar5;
      while( true ) {
        uVar4 = 0;
        while( true ) {
          if (iVar5 != iVar3) {
            _objc_msgSend((ID)param_1,"subviews");
            _objc_enumerationMutation();
          }
          self_00 = *(ID *)(local_8c + uVar4 * 4);
          uVar4 = uVar4 + 1;
          _objc_msgSend_stret((undefined *)local_40,self_00,"frame");
          fVar7 = local_40[0];
          _objc_msgSend_stret(auStack_50,self_00,"frame");
          fVar7 = fVar7 + local_48;
          _objc_msgSend_stret(auStack_60,self_00,"frame");
          fVar6 = local_5c;
          _objc_msgSend_stret(auStack_70,self_00,"frame");
          if ((float)uVar8 < fVar7) {
            uVar8 = CONCAT44((int)((ulonglong)uVar8 >> 0x20),fVar7);
          }
          if ((float)((ulonglong)uVar8 >> 0x20) < fVar6 + local_64) {
            uVar8 = CONCAT44(fVar6 + local_64,(int)uVar8);
          }
          if (IVar1 <= uVar4) break;
          iVar3 = *local_88;
        }
        IVar1 = _objc_msgSend(self,"countByEnumeratingWithState:objects:count:",&local_90,local_d0,
                              0x10);
        if (IVar1 == 0) break;
        iVar3 = *local_88;
      }
      *(int *)this = (int)uVar8;
      *(int *)(this + 4) = (int)((ulonglong)uVar8 >> 0x20);
    }
  }
  return this;
}
