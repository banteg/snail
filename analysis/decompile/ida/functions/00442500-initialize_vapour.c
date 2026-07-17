/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_vapour @ 0x442500 */
/* selector: initialize_vapour */

// Exact void Windows `cRVapour::Init(cRObject*, float)`: stores the authored half-width, derives point capacity from the retained output `Object::facequad_count`, allocates the transform history, and resets the exact 0x94-byte Vapour owner. Android preserves the void contract and the same retained `cRObject*`; the explicit object argument is unused on both ports.
void __thiscall initialize_vapour(Vapour *vapour, Object *unused, float half_width)
{
  Object *object; // ecx
  int32_t v5; // eax

  object = vapour->body.bod.object;
  vapour->half_width = half_width;
  v5 = object->facequad_count + 1;
  vapour->capacity = v5;
  vapour->points = (TransformMatrix *)allocate_tracked_memory(v5 << 6, aVapourTrail);
  reset_vapour(vapour, nullptr);
}
