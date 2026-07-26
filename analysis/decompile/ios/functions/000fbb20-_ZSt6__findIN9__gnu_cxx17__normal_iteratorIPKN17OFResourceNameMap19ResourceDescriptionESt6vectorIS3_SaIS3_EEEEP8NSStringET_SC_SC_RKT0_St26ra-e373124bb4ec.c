/*
 * mangled: _ZSt6__findIN9__gnu_cxx17__normal_iteratorIPKN17OFResourceNameMap19ResourceDescriptionESt6vectorIS3_SaIS3_EEEEP8NSStringET_SC_SC_RKT0_St26random_access_iterator_tag
 * demangled: __gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*, std::vector<OFResourceNameMap::ResourceDescription, std::allocator<OFResourceNameMap::ResourceDescription>>> std::__find<__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*, std::vector<OFResourceNameMap::ResourceDescription, std::allocator<OFResourceNameMap::ResourceDescription>>>, NSString*>(__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*, std::vector<OFResourceNameMap::ResourceDescription, std::allocator<OFResourceNameMap::ResourceDescription>>>, __gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*, std::vector<OFResourceNameMap::ResourceDescription, std::allocator<OFResourceNameMap::ResourceDescription>>>, NSString* const&, std::random_access_iterator_tag)
 * address: 000fbb20
 * size: 340
 */

/* __gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*,
   std::vector<OFResourceNameMap::ResourceDescription,
   std::allocator<OFResourceNameMap::ResourceDescription> > >
   std::__find<__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*,
   std::vector<OFResourceNameMap::ResourceDescription,
   std::allocator<OFResourceNameMap::ResourceDescription> > >,
   NSString*>(__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*,
   std::vector<OFResourceNameMap::ResourceDescription,
   std::allocator<OFResourceNameMap::ResourceDescription> > >,
   __gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription const*,
   std::vector<OFResourceNameMap::ResourceDescription,
   std::allocator<OFResourceNameMap::ResourceDescription> > >, NSString* const&,
   std::random_access_iterator_tag) */

ID * std::
     __find<__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription_const*,std::vector<OFResourceNameMap::ResourceDescription,std::allocator<OFResourceNameMap::ResourceDescription>>>,NSString*>
               (ID *param_1,ID *param_2,undefined4 *param_3)

{
  ID IVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)param_2 - (int)param_1;
  iVar3 = iVar2 >> 5;
  if (0 < iVar3) {
    do {
      IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1;
      }
      IVar1 = _objc_msgSend(param_1[2],"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1 + 2;
      }
      IVar1 = _objc_msgSend(param_1[4],"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1 + 4;
      }
      IVar1 = _objc_msgSend(param_1[6],"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1 + 6;
      }
      iVar3 = iVar3 + -1;
      param_1 = param_1 + 8;
    } while (iVar3 != 0);
    iVar2 = (int)param_2 - (int)param_1;
  }
  iVar2 = iVar2 >> 3;
  if (iVar2 != 2) {
    if (iVar2 != 3) {
      if (iVar2 != 1) {
        return param_2;
      }
      goto LAB_000fbc2c;
    }
    IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
    if ((IVar1 & 0xff) != 0) {
      return param_1;
    }
    param_1 = param_1 + 2;
  }
  IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
  if ((IVar1 & 0xff) != 0) {
    return param_1;
  }
  param_1 = param_1 + 2;
LAB_000fbc2c:
  IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
  if ((IVar1 & 0xff) == 0) {
    return param_2;
  }
  return param_1;
}
