/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_bounding_box @ 0x42fb10 */
/* selector: calc_object_bounding_box */

int __thiscall sub_42FB10(_DWORD *this)
{
  float *v2; // edi
  float *v3; // ebx
  int v4; // ebp
  int result; // eax
  float *v6; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  int v13; // [esp+10h] [ebp-10h]

  v2 = (float *)(this + 44);
  *(this + 44) = -803929351;
  v3 = (float *)(this + 41);
  *(this + 45) = -803929351;
  *(this + 46) = -803929351;
  *(this + 41) = 1343554297;
  v4 = 0;
  *(this + 42) = 1343554297;
  *(this + 37) = 0;
  v13 = 0;
  *(this + 43) = 1343554297;
  result = *(this + 11);
  if ( result > 0 )
  {
    do
    {
      v6 = (float *)(v4 + *(this + 14));
      if ( *v2 <= (double)*v6 )
      {
        v7 = *v6;
      }
      else
      {
        v7 = *((float *)this + 44);
        v2 = (float *)(this + 44);
      }
      *v2 = v7;
      if ( *v6 <= (double)*v3 )
      {
        v8 = *v6;
      }
      else
      {
        v8 = *((float *)this + 41);
        v3 = (float *)(this + 41);
      }
      *v3 = v8;
      if ( *((float *)this + 45) <= (double)v6[1] )
        v9 = v6[1];
      else
        v9 = *((float *)this + 45);
      *((float *)this + 45) = v9;
      if ( v6[1] <= (double)*((float *)this + 42) )
        v10 = v6[1];
      else
        v10 = *((float *)this + 42);
      *((float *)this + 42) = v10;
      if ( *((float *)this + 46) <= (double)v6[2] )
        v11 = v6[2];
      else
        v11 = *((float *)this + 46);
      *((float *)this + 46) = v11;
      if ( v6[2] <= (double)*((float *)this + 43) )
        v12 = v6[2];
      else
        v12 = *((float *)this + 43);
      *((float *)this + 43) = v12;
      vector_magnitude(v6);
      if ( v12 > *((float *)this + 37) )
        *((float *)this + 37) = v12;
      result = v13 + 1;
      v4 += 12;
      ++v13;
    }
    while ( v13 < *(this + 11) );
  }
  return result;
}

