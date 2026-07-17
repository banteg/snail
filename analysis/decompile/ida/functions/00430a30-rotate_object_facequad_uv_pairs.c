/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_object_facequad_uv_pairs @ 0x430a30 */
/* selector: rotate_object_facequad_uv_pairs */

// Rotates one ObjectFaceQuad's four UV pairs forward by one slot; used by backdrop tile orientation cases before writing the matching quad vertices.
void __fastcall rotate_object_facequad_uv_pairs(ObjectFaceQuad *quad)
{
  float u; // edx
  double v2; // st7
  float v3; // eax
  double v; // st7
  float v5; // edx
  float v6; // eax
  float v7; // edx

  u = quad->uv[2].u;
  v2 = quad->uv[0].u;
  quad->uv[0].u = quad->uv[1].u;
  v3 = quad->uv[3].u;
  quad->uv[3].u = v2;
  v = quad->uv[0].v;
  quad->uv[1].u = u;
  v5 = quad->uv[1].v;
  quad->uv[2].u = v3;
  v6 = quad->uv[2].v;
  quad->uv[0].v = v5;
  v7 = quad->uv[3].v;
  quad->uv[3].v = v;
  quad->uv[1].v = v6;
  quad->uv[2].v = v7;
}
