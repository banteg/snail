/*
 * mangled: _Z10EndElementPvPKhS1_S1_
 * demangled: EndElement(void*, unsigned char const*, unsigned char const*, unsigned char const*)
 * address: 000d5190
 * size: 28
 */

/* EndElement(void*, unsigned char const*, unsigned char const*, unsigned char const*) */

undefined4 EndElement(void *param_1,uchar *param_2,uchar *param_3,uchar *param_4)

{
  _objc_msgSend((ID)param_1,"elementEnded");
  return 0;
}
