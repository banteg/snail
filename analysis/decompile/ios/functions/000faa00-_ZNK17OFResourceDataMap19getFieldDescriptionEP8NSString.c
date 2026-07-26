/*
 * mangled: _ZNK17OFResourceDataMap19getFieldDescriptionEP8NSString
 * demangled: OFResourceDataMap::getFieldDescription(NSString*) const
 * address: 000faa00
 * size: 56
 */

/* OFResourceDataMap::getFieldDescription(NSString*) const */

int OFResourceDataMap::getFieldDescription(NSString *param_1)

{
  int iVar1;

  iVar1 = std::
          __find<__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription_const*,std::vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>>,NSString*>
                    (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  if (*(int *)(param_1 + 0xc) == iVar1) {
    iVar1 = 0;
  }
  return iVar1;
}
