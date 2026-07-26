/*
 * mangled: _ZSt6__findIN9__gnu_cxx17__normal_iteratorIPKN17OFResourceDataMap16FieldDescriptionESt6vectorIS3_SaIS3_EEEEP8NSStringET_SC_SC_RKT0_St26random_access_iterator_tag
 * demangled: __gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*, std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>>> std::__find<__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*, std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>>>, NSString*>(__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*, std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>>>, __gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*, std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>>>, NSString* const&, std::random_access_iterator_tag)
 * address: 000faf84
 * size: 356
 */

/* __gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*,
   std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription> > >
   std::__find<__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*,
   std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription> > >,
   NSString*>(__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*,
   std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription> > >,
   __gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription const*,
   std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription> > >, NSString* const&,
   std::random_access_iterator_tag) */

ID * std::
     __find<__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription_const*,std::vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>>,NSString*>
               (ID *param_1,ID *param_2,undefined4 *param_3)

{
  ID IVar1;
  int iVar2;
  int iVar3;

  iVar2 = ((int)param_2 - (int)param_1 >> 2) * -0x33333333;
  iVar3 = iVar2 >> 2;
  if (0 < iVar3) {
    do {
      IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1;
      }
      IVar1 = _objc_msgSend(param_1[5],"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1 + 5;
      }
      IVar1 = _objc_msgSend(param_1[10],"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1 + 10;
      }
      IVar1 = _objc_msgSend(param_1[0xf],"isEqualToString:",*param_3);
      if ((IVar1 & 0xff) != 0) {
        return param_1 + 0xf;
      }
      iVar3 = iVar3 + -1;
      param_1 = param_1 + 0x14;
    } while (iVar3 != 0);
    iVar2 = ((int)param_2 - (int)param_1 >> 2) * -0x33333333;
  }
  if (iVar2 != 2) {
    if (iVar2 != 3) {
      if (iVar2 != 1) {
        return param_2;
      }
      goto LAB_000fb0a0;
    }
    IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
    if ((IVar1 & 0xff) != 0) {
      return param_1;
    }
    param_1 = param_1 + 5;
  }
  IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
  if ((IVar1 & 0xff) != 0) {
    return param_1;
  }
  param_1 = param_1 + 5;
LAB_000fb0a0:
  IVar1 = _objc_msgSend(*param_1,"isEqualToString:",*param_3);
  if ((IVar1 & 0xff) == 0) {
    return param_2;
  }
  return param_1;
}
