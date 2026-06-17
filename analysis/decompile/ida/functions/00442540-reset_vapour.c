/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_vapour @ 0x442540 */
/* selector: reset_vapour */

int32_t __thiscall reset_vapour(VapourTrail *trail, int32_t z_floor)
{
  int32_t result; // eax

  trail->point_count = 0;
  trail->z_floor = z_floor;
  result = trail->flags;
  LOBYTE(result) = result & 0xDF;
  trail->flags = result;
  return result;
}

