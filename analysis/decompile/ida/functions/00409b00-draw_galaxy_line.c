/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_galaxy_line @ 0x409b00 */
/* selector: draw_galaxy_line */

int32_t __thiscall draw_galaxy_line(
        Galaxy *galaxy,
        int32_t texture_id,
        float x0,
        float y0,
        float x1,
        float y1,
        float width,
        tColour *color)
{
  double v8; // st7
  double v9; // st6
  float x0a; // [esp+0h] [ebp-54h]
  float y0a; // [esp+4h] [ebp-50h]
  float x1a; // [esp+8h] [ebp-4Ch]
  float y1a; // [esp+Ch] [ebp-48h]
  float x2; // [esp+10h] [ebp-44h]
  float y2; // [esp+14h] [ebp-40h]
  float x3; // [esp+18h] [ebp-3Ch]
  float y3; // [esp+1Ch] [ebp-38h]
  Vec3 vector; // [esp+48h] [ebp-Ch] BYREF

  vector.z = 0.0;
  vector.x = x1 - x0;
  vector.y = y1 - y0;
  normalize_vector(&vector);
  v8 = vector.y * width * -0.5;
  v9 = vector.x * width * 0.5;
  y3 = v9 + y0;
  x3 = v8 + x0;
  y2 = v9 + y1;
  x2 = v8 + x1;
  y1a = y1 - v9;
  x1a = x1 - v8;
  y0a = y0 - v9;
  x0a = x0 - v8;
  return queue_textured_quad_corners(
           texture_id,
           x0a,
           y0a,
           x1a,
           y1a,
           x2,
           y2,
           x3,
           y3,
           0,
           0,
           0x1000000u,
           color,
           0.0,
           0.0,
           1.0,
           1.0,
           15,
           0.0);
}
