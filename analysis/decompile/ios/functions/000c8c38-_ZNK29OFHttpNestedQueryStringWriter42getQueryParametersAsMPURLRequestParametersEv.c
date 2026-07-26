/*
 * mangled: _ZNK29OFHttpNestedQueryStringWriter42getQueryParametersAsMPURLRequestParametersEv
 * demangled: OFHttpNestedQueryStringWriter::getQueryParametersAsMPURLRequestParameters() const
 * address: 000c8c38
 * size: 132
 */

/* OFHttpNestedQueryStringWriter::getQueryParametersAsMPURLRequestParameters() const */

ID __thiscall
OFHttpNestedQueryStringWriter::getQueryParametersAsMPURLRequestParameters
          (OFHttpNestedQueryStringWriter *this)

{
  ID self;
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;

  self = NSMutableArray::arrayWithCapacity_
                   ((ID)&_OBJC_CLASS___NSMutableArray,"arrayWithCapacity:",
                    *(int *)(this + 0x1c) - *(int *)(this + 0x18) >> 2);
  puVar3 = *(undefined4 **)(this + 0x1c);
  for (puVar2 = *(undefined4 **)(this + 0x18); puVar3 != puVar2; puVar2 = puVar2 + 1) {
    uVar1 = (**(code **)(*(int *)*puVar2 + 0x14))();
    NSMutableArray::addObject_(self,"addObject:",uVar1);
  }
  return self;
}
