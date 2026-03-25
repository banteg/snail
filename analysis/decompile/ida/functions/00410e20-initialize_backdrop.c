/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop @ 0x410e20 */
/* selector: initialize_backdrop */

// Initializes the shared backdrop renderer, seeds its texture-transition state, and primes its distortion grid. Cross-port Android and iOS symbols match this helper to `cRBackdrop::Init(int)`.
float *__thiscall sub_410E20(int this, int a2)
{
  *(_DWORD *)(this + 1628) = 1;
  *(_BYTE *)(this + 1632) = 0;
  *(_DWORD *)(this + 60) = -1;
  *(_BYTE *)(this + 76) = 0;
  *(_DWORD *)(this + 1736) = 0;
  *(_DWORD *)(this + 1732) = 5;
  *(_DWORD *)(this + 1724) = 0;
  *(_DWORD *)(this + 1728) = 995783694;
  set_backdrop_texture_target(this, 5);
  if ( (byte_4DF934 & 1) != 0 )
  {
    *(_DWORD *)(this + 1624) = 1;
    *(_DWORD *)(this + 1636) = 1065353216;
  }
  else
  {
    *(_DWORD *)(this + 1624) = 0;
    *(_DWORD *)(this + 1636) = 0;
  }
  *(_DWORD *)(this + 1640) = 1017817771;
  if ( !a2 )
  {
    *(_DWORD *)(this + 1644) = 0;
    *(_DWORD *)(this + 1648) = 984322726;
    *(_DWORD *)(this + 1652) = 0;
    *(_DWORD *)(this + 1656) = 988070793;
    goto LABEL_8;
  }
  if ( a2 == 1 )
  {
    *(_DWORD *)(this + 1644) = 0;
    *(_DWORD *)(this + 1648) = -1154772314;
    *(_DWORD *)(this + 1652) = 0;
    *(_DWORD *)(this + 1656) = -1151024247;
LABEL_8:
    *(_DWORD *)(this + 1684) = 0;
    *(_DWORD *)(this + 1688) = 0;
    *(_DWORD *)(this + 1676) = 1065353216;
    *(_DWORD *)(this + 1680) = 1001786209;
    *(_DWORD *)(this + 1716) = 0;
    *(_DWORD *)(this + 1720) = 0;
    *(_DWORD *)(this + 1708) = 1065353216;
    *(_DWORD *)(this + 1712) = 998803593;
  }
  set_backdrop_texture_target(this, 0);
  return set_backdrop_distort((float *)this, 0.0);
}

