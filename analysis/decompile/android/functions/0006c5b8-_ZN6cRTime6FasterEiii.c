/*
 * mangled: _ZN6cRTime6FasterEiii
 * demangled: cRTime::Faster(int, int, int)
 * address: 0006c5b8
 * size: 64
 */

/* cRTime::Faster(int, int, int) */

bool cRTime::Faster(int param_1,int param_2,int param_3)

{
  return *(int *)(param_1 + 4) * 6000 + *(int *)(param_1 + 8) * 100 + *(int *)(param_1 + 0xc) <
         param_2 * 6000 + param_3 * 100 + 100;
}
