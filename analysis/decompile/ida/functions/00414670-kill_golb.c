/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_golb @ 0x414670 */
/* selector: kill_golb */

void __thiscall sub_414670(int *this)
{
  char *v2; // ecx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  char *v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // esi
  int v15; // eax
  int v16; // ecx
  char *v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx

  v2 = (char *)MEMORY[0x4DF904] + 1448;
  v3 = *(this + 1);
  if ( (v3 & 0x200) != 0 )
  {
    if ( (v3 & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      v4 = *(this + 3);
      if ( v4 )
        *(_DWORD *)(v4 + 8) = *(this + 2);
      v5 = *(this + 2);
      if ( v5 )
        *(_DWORD *)(v5 + 12) = *(this + 3);
      else
        *((_DWORD *)v2 + 1) = *(this + 3);
      *(this + 3) = *((_DWORD *)v2 + 2);
      *((_DWORD *)v2 + 2) = this;
      v6 = *(this + 1);
      BYTE1(v6) &= ~2u;
      *(this + 1) = v6;
    }
  }
  else
  {
    report_errorf(aListRemove);
  }
  v7 = *(this + 112);
  *(this + 145) = 0;
  if ( v7 )
  {
    v8 = v7 - 1;
    if ( v8 )
    {
      if ( v8 == 1 )
      {
        v9 = (char *)MEMORY[0x4DF904] + 1448;
        v10 = *(this + 71);
        if ( (v10 & 0x200) != 0 )
        {
          if ( (v10 & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
          }
          else
          {
            v11 = *(this + 73);
            if ( v11 )
              *(_DWORD *)(v11 + 8) = *(this + 72);
            v12 = *(this + 72);
            if ( v12 )
              *(_DWORD *)(v12 + 12) = *(this + 73);
            else
              *((_DWORD *)v9 + 1) = *(this + 73);
            *(this + 73) = *((_DWORD *)v9 + 2);
            *((_DWORD *)v9 + 2) = this + 70;
            v13 = *(this + 71);
            BYTE1(v13) &= ~2u;
            *(this + 71) = v13;
          }
        }
        else
        {
          report_errorf(aListRemove);
        }
        v14 = *(this + 102);
        if ( v14 )
        {
          v15 = *(_DWORD *)(v14 + 4);
          BYTE1(v15) &= ~0x10u;
          *(_DWORD *)(v14 + 4) = v15;
        }
      }
    }
    else
    {
      v16 = *(this + 33);
      v17 = (char *)MEMORY[0x4DF904] + 1448;
      if ( (v16 & 0x200) != 0 )
      {
        if ( (v16 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          v18 = *(this + 35);
          if ( v18 )
            *(_DWORD *)(v18 + 8) = *(this + 34);
          v19 = *(this + 34);
          if ( v19 )
            *(_DWORD *)(v19 + 12) = *(this + 35);
          else
            *((_DWORD *)v17 + 1) = *(this + 35);
          *(this + 35) = *((_DWORD *)v17 + 2);
          *((_DWORD *)v17 + 2) = this + 32;
          v20 = *(this + 33);
          BYTE1(v20) &= ~2u;
          *(this + 33) = v20;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
  }
  else
  {
    kill_sprite(*(this + 146));
  }
}

