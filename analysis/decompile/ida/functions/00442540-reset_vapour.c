/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_vapour @ 0x442540 */
/* selector: reset_vapour */

// Exact void Windows `cRVapour::ReSet(float*)`: clears the point count and visible flag and retains an optional borrowed z-floor clamp. Android returns directly after the same stores, proving that Windows' final flags value is incidental.
void __thiscall reset_vapour(Vapour *vapour, float *z_floor)
{
  uint32_t list_flags; // eax

  vapour->point_count = 0;
  vapour->z_floor = z_floor;
  list_flags = vapour->body.bod.bod.list_flags;
  LOBYTE(list_flags) = list_flags & 0xDF;
  vapour->body.bod.bod.list_flags = list_flags;
}
