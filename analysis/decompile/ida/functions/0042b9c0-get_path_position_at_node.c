/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_path_position_at_node @ 0x42b9c0 */
/* selector: get_path_position_at_node */

// Projects a path node and row index into a borrowed output vector for attachment-row consumers; iOS Path.o names this `cRPath::GetPos(tVector&, int, int, tVector&)`. Both Windows callers discard EAX, and the byte-identical VC6 candidate naturally leaves the final z bits there when declared void, confirming that the apparent scalar return is compiler residue rather than an owned result.
void __thiscall get_path_position_at_node(Path *self, Vec3 *out, int32_t node, int32_t row_index, Vec3 *local)
{
  double y; // st7
  PathTemplateSample *v6; // eax
  double x; // st6
  float v8; // [esp+4h] [ebp-24h]
  float v9; // [esp+4h] [ebp-24h]
  float v10; // [esp+8h] [ebp-20h]
  float v11; // [esp+8h] [ebp-20h]
  float v12; // [esp+Ch] [ebp-1Ch]
  float v13; // [esp+10h] [ebp-18h]
  float v14; // [esp+14h] [ebp-14h]
  float v15; // [esp+1Ch] [ebp-Ch]
  float v16; // [esp+20h] [ebp-8h]
  float v17; // [esp+24h] [ebp-4h]

  y = local->y;
  v6 = &self->primary_samples[node];
  v15 = y * v6->transform.basis_up.x;
  v16 = y * v6->transform.basis_up.y;
  x = local->x;
  v8 = x * v6->transform.basis_right.x;
  v10 = x * v6->transform.basis_right.y;
  v13 = v8 + v6->transform.position.x;
  v14 = v10 + v6->transform.position.y;
  v9 = v13 + v15;
  v11 = v14 + v16;
  v12 = x * v6->transform.basis_right.z + v6->transform.position.z + y * v6->transform.basis_up.z;
  out->x = v9;
  out->y = v11;
  v17 = (double)row_index + v12;
  out->z = v17;
}
