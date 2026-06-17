/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_vapour @ 0x442500 */
/* selector: initialize_vapour */

int32_t __thiscall initialize_vapour(VapourTrail *trail, int32_t unused, int32_t half_width_bits)
{
  VapourTrailOwner *owner; // ecx
  int32_t v5; // eax

  owner = trail->owner;
  LODWORD(trail->half_width) = half_width_bits;
  v5 = owner->max_points + 1;
  trail->capacity = v5;
  trail->points = (TransformMatrix *)allocate_tracked_memory(v5 << 6, (int)aVapourTrail);
  return reset_vapour(trail, 0);
}

