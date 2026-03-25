/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sample_track_floor_height_at_position @ 0x43d4d0 */
/* selector: sample_track_floor_height_at_position */

// Evaluates the runtime floor-height sampler for the current gameplay-grid cell, including ramp tiles and the special cell-stored height used by tile 0x16.
double __thiscall sub_43D4D0(char *this, float *a2)
{
  char *v2; // eax
  char v3; // cl

  v2 = get_track_grid_cell_at_world_position(this, a2);
  v3 = v2[60];
  switch ( v3 )
  {
    case 1:
    case 15:
    case 14:
      return 0.0;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
    case 12:
    case 13:
      return (a2[2] - (double)(int)(__int64)a2[2]) * 0.40000001;
    case 8:
    case 9:
    case 10:
      return (a2[2] - (double)(int)(__int64)a2[2]) * 0.40000001 + 0.5;
    case 22:
      return *((float *)v2 + 5);
  }
  return -100.0;
}

