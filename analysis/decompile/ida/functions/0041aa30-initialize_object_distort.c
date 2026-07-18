/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_object_distort @ 0x41aa30 */
/* selector: initialize_object_distort */

// Initializes the five-float cRDistort subobject embedded at Object +0x80. Android independently exports cRDistort::Init and calls it from cRSubGoldy::Init on the same presentation object.
void __thiscall initialize_object_distort(ObjectDistort *distort)
{
  distort->z_wave = 0.0;
  distort->unknown_10 = 0.0;
  distort->unknown_0c = 0.0;
  distort->y_squash = 0.0;
  distort->xyz_scale = 0.0;
}
