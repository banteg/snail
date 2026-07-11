/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: append_subgame_contact_target @ 0x415ef0 */
/* selector: append_subgame_contact_target */

// Appends one garbage or slug contact target to the per-frame subgame contact registry unless the target object's flags include 0x1000.
void __thiscall append_subgame_contact_target(
        ContactTargetRegistry *registry,
        const Vec3 *position,
        float radius,
        int kind,
        ContactTargetObject *object)
{
  Vec3 *p_position; // eax

  if ( (object->list_flags & 0x1000) == 0 )
  {
    registry->entries[registry->count].kind = kind;
    p_position = &registry->entries[registry->count].position;
    p_position->x = position->x;
    p_position->y = position->y;
    p_position->z = position->z;
    registry->entries[registry->count].radius = radius;
    *(&registry->count + 6 * ++registry->count) = (int32_t)object;
  }
}
