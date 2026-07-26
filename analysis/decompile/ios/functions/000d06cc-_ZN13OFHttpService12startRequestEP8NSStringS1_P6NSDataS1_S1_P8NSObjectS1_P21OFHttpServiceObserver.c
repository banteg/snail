/*
 * mangled: _ZN13OFHttpService12startRequestEP8NSStringS1_P6NSDataS1_S1_P8NSObjectS1_P21OFHttpServiceObserver
 * demangled: OFHttpService::startRequest(NSString*, NSString*, NSData*, NSString*, NSString*, NSObject*, NSString*, OFHttpServiceObserver*)
 * address: 000d06cc
 * size: 1132
 */

/* OFHttpService::startRequest(NSString*, NSString*, NSData*, NSString*, NSString*, NSObject*,
   NSString*, OFHttpServiceObserver*) */

void OFHttpService::startRequest
               (NSString *param_1,NSString *param_2,NSData *param_3,NSString *param_4,
               NSString *param_5,NSObject *param_6,NSString *param_7,OFHttpServiceObserver *param_8)

{
  ID self;
  undefined4 *puVar1;
  OFSmartObject *in_stack_00000010;
  undefined1 auStack_b8 [4];
  undefined4 local_b4;
  undefined *local_a0;
  undefined *local_9c;
  undefined1 *local_98;
  undefined1 *local_94;
  undefined1 *local_90;
  undefined **local_84;
  undefined4 local_80;
  ID local_7c;
  ID local_78;
  ID local_74;
  ID local_70;
  ID local_6c;
  NSString *local_68;
  OFSmartObject *local_64;

  local_98 = &stack0xfffffff8;
  local_90 = &stack0xffffff14;
  local_a0 = PTR_001b615c;
  local_9c = &GCC_except_table9;
  local_94 = &LAB_000d0b38;
  __Unwind_SjLj_Register(auStack_b8);
  local_b4 = 0xffffffff;
  self = OFHttpRequest::httpRequestWithBase_withObserver_withCookies_
                   ((ID)&objc::class_t::OFHttpRequest,
                    "httpRequestWithBase:withObserver:withCookies:",*(ID *)(param_1 + 0xc),
                    (OFHttpRequestObserver *)(param_1 + 8),(uint)(byte)param_1[0x10]);
  if (self != 0) {
    _objc_msgSend(self,"retain");
  }
  local_b4 = 0x1a;
  OFSmartObject::OFSmartObject((OFSmartObject *)&local_84);
  local_84 = &PTR_GetRTTI_001b7590;
  local_7c = self;
  if (self != 0) {
    local_b4 = 0x18;
    _objc_msgSend(self,"retain");
  }
  local_78 = 0;
  local_74 = 0;
  local_b4 = 0x17;
  local_70 = _objc_msgSend(self,"urlPath");
  if (local_70 != 0) {
    _objc_msgSend(local_70,"retain");
  }
  local_b4 = 0x16;
  local_6c = _objc_msgSend(self,"httpMethod");
  if (local_6c != 0) {
    _objc_msgSend(local_6c,"retain");
  }
  local_68 = param_7;
  if (param_7 != (NSString *)0x0) {
    local_b4 = 0x15;
    _objc_msgSend((ID)param_7,"retain");
  }
  local_64 = in_stack_00000010;
  if (in_stack_00000010 != (OFSmartObject *)0x0) {
    *(int *)(in_stack_00000010 + 4) = *(int *)(in_stack_00000010 + 4) + 1;
  }
  puVar1 = *(undefined4 **)(param_1 + 0x18);
  if (puVar1 == *(undefined4 **)(param_1 + 0x1c)) {
    local_b4 = 0x19;
    std::vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>::
    _M_insert_aux((vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>
                   *)(param_1 + 0x14),puVar1,&local_84);
  }
  else {
    if (puVar1 != (undefined4 *)0x0) {
      puVar1[1] = local_80;
      *puVar1 = &PTR_GetRTTI_001b7590;
      puVar1[2] = local_7c;
      if (local_7c != 0) {
        local_b4 = 0x14;
        _objc_msgSend(local_7c,"retain");
      }
      puVar1[3] = local_78;
      if (local_78 != 0) {
        local_b4 = 0x13;
        _objc_msgSend(local_78,"retain");
      }
      puVar1[4] = local_74;
      if (local_74 != 0) {
        local_b4 = 0x12;
        _objc_msgSend(local_74,"retain");
      }
      puVar1[5] = local_70;
      if (local_70 != 0) {
        local_b4 = 0x11;
        _objc_msgSend(local_70,"retain");
      }
      puVar1[6] = local_6c;
      if (local_6c != 0) {
        local_b4 = 0x10;
        _objc_msgSend(local_6c,"retain");
      }
      puVar1[7] = local_68;
      if (local_68 != (NSString *)0x0) {
        local_b4 = 0xf;
        _objc_msgSend((ID)local_68,"retain");
      }
      puVar1[8] = local_64;
      if (local_64 != (OFSmartObject *)0x0) {
        *(int *)(local_64 + 4) = *(int *)(local_64 + 4) + 1;
      }
    }
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 0x24;
  }
  local_b4 = 0x19;
  _objc_msgSend(self,
                "startRequestWithPath:withMethod:withBody:withEmail:withPassword:multiPartBoundary:"
                ,param_2,param_3);
  local_84 = &PTR_GetRTTI_001b7590;
  if (local_64 != (OFSmartObject *)0x0) {
    local_b4 = 1;
    OFSmartObject::Release(local_64);
  }
  if (local_68 != (NSString *)0x0) {
    local_b4 = 2;
    _objc_msgSend((ID)local_68,"release");
  }
  if (local_6c != 0) {
    local_b4 = 3;
    _objc_msgSend(local_6c,"release");
  }
  if (local_70 != 0) {
    local_b4 = 4;
    _objc_msgSend(local_70,"release");
  }
  if (local_74 != 0) {
    local_b4 = 5;
    _objc_msgSend(local_74,"release");
  }
  if (local_78 != 0) {
    local_b4 = 6;
    _objc_msgSend(local_78,"release");
  }
  if (local_7c != 0) {
    local_b4 = 7;
    _objc_msgSend(local_7c,"release");
  }
  local_b4 = 0x1a;
  OFSmartObject::~OFSmartObject((OFSmartObject *)&local_84);
  if (self != 0) {
    local_b4 = 0xffffffff;
    _objc_msgSend(self,"release");
  }
  __Unwind_SjLj_Unregister(auStack_b8);
  return;
}
