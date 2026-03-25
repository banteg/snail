/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_subgame @ 0x437b10 */
/* selector: reset_subgame */

int __thiscall sub_437B10(_DWORD *this)
{
  int v2; // ecx
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  int v5; // ecx
  _DWORD *v6; // eax
  int v7; // ecx
  _DWORD *v8; // eax
  int v9; // ecx
  int v10; // edx
  int result; // eax

  v2 = 8;
  v3 = this + 874513;
  do
  {
    *(v3 - 3) = 0;
    *v3 = this;
    v3 += 29;
    --v2;
  }
  while ( v2 );
  *(this + 874380) = 0;
  *(this + 874383) = this;
  *(this + 874407) = 0;
  *(this + 874410) = this;
  v4 = this + 877684;
  v5 = 50;
  do
  {
    *(v4 - 2) = 0;
    *v4 = this;
    *(v4 - 3) = 0;
    v4 += 49;
    --v5;
  }
  while ( v5 );
  v6 = this + 874762;
  v7 = 8;
  do
  {
    *(v6 - 2) = 0;
    *v6 = this;
    v6 += 59;
    --v7;
  }
  while ( v7 );
  v8 = this + 880215;
  v9 = 2;
  do
  {
    *(v8 - 84) = 0;
    *v8 = this;
    v8 += 126;
    --v9;
  }
  while ( v9 );
  if ( *((_BYTE *)this + 16721360) == 1 && *(this + 16) == *(this + 4147919) )
  {
    v10 = *(this + 4147916);
    result = *(this + 4147917);
    *(this + 978578) = *(this + 4147909);
    *(this + 978585) = v10;
    qmemcpy(this + 978579, this + 4147910, 0x18u);
    *(this + 978586) = result;
  }
  else
  {
    if ( *(this + 4834290) == 2 )
    {
      *(this + 978578) = 0;
      clear_subgoldy_score_buckets((int)(this + 978393));
    }
    result = zero_timer_counters(this + 978579);
    *(this + 978585) = 0;
    *(this + 978586) = 0;
  }
  *(this + 978616) = 0;
  *(_BYTE *)this = 1;
  *((_BYTE *)this + 1) = 1;
  *((_BYTE *)this + 16721360) = 0;
  *(this + 877648) = 0;
  return result;
}

