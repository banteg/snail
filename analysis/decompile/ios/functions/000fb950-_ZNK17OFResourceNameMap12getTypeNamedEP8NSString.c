/*
 * mangled: _ZNK17OFResourceNameMap12getTypeNamedEP8NSString
 * demangled: OFResourceNameMap::getTypeNamed(NSString*) const
 * address: 000fb950
 * size: 64
 */

/* OFResourceNameMap::getTypeNamed(NSString*) const */

undefined4 OFResourceNameMap::getTypeNamed(NSString *param_1)

{
  int iVar1;
  undefined4 uVar2;

  iVar1 = std::
          __find<__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription_const*,std::vector<OFResourceNameMap::ResourceDescription,std::allocator<OFResourceNameMap::ResourceDescription>>>,NSString*>
                    (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  if (iVar1 == *(int *)(param_1 + 0xc)) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 4);
  }
  return uVar2;
}
