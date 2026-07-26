/*
 * mangled: _ZN23OFResourceControllerMap11addResourceEP10objc_classP8NSString
 * demangled: OFResourceControllerMap::addResource(objc_class*, NSString*)
 * address: 000fa168
 * size: 304
 */

/* OFResourceControllerMap::addResource(objc_class*, NSString*) */

void __thiscall
OFResourceControllerMap::addResource
          (OFResourceControllerMap *this,objc_class *param_1,NSString *param_2)

{
  NSString *self;
  ResourceDescription *pRVar1;
  undefined1 auStack_ac [4];
  NSString *local_a8;
  objc_class *local_a4;
  OFResourceControllerMap *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  objc_class *local_68;
  NSString *local_64;

  local_7c = &stack0xfffffff8;
  local_74 = auStack_ac;
  local_84 = PTR_001b615c;
  local_80 = &::GCC_except_table1;
  local_78 = &LAB_000fa298;
  local_a8 = param_2;
  local_a4 = param_1;
  local_a0 = this;
  self = (NSString *)__Unwind_SjLj_Register(auStack_9c);
  local_64 = (NSString *)0x0;
  local_68 = local_a4;
  if (local_a8 != (NSString *)0x0) {
    local_64 = local_a8;
    local_98 = 2;
    self = (NSString *)_objc_msgSend((ID)local_a8,"retain");
  }
  pRVar1 = (local_a0->field2_0x8).field0_0x0.field1_0x4;
  if (pRVar1 == (local_a0->field2_0x8).field0_0x0.field2_0x8) {
    local_98 = 2;
    std::
    vector<OFResourceControllerMap::ResourceDescription,std::allocator<OFResourceControllerMap::ResourceDescription>>
    ::_M_insert_aux((vector<OFResourceControllerMap::ResourceDescription,std::allocator<OFResourceControllerMap::ResourceDescription>>
                     *)&local_a0->field2_0x8,pRVar1,&local_68);
  }
  else {
    if (pRVar1 != (ResourceDescription *)0x0) {
      *(objc_class **)pRVar1 = local_68;
      *(NSString **)(pRVar1 + 4) = local_64;
      self = local_64;
    }
    if (pRVar1 != (ResourceDescription *)0x0 && self != (NSString *)0x0) {
      local_98 = 1;
      _objc_msgSend((ID)self,"retain");
    }
    (local_a0->field2_0x8).field0_0x0.field1_0x4 = (local_a0->field2_0x8).field0_0x0.field1_0x4 + 8;
  }
  if (local_64 != (NSString *)0x0) {
    local_98 = 0xffffffff;
    _objc_msgSend((ID)local_64,"release");
  }
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
