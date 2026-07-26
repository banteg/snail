/*
 * mangled: _ZN13OFISerializer9serializeEPKcS1_RSt6vectorI13OFRetainedPtrI8NSStringESaIS5_EE
 * demangled: OFISerializer::serialize(char const*, char const*, std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString>>>&)
 * address: 000cc4d4
 * size: 16
 */

/* OFISerializer::serialize(char const*, char const*, std::vector<OFRetainedPtr<NSString>,
   std::allocator<OFRetainedPtr<NSString> > >&) */

void __thiscall
OFISerializer::serialize(OFISerializer *this,char *param_1,char *param_2,vector *param_3)

{
  serializePodVector<OFRetainedPtr<NSString>>(this,param_1,param_2,param_3);
  return;
}
