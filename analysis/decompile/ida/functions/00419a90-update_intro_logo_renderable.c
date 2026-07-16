/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_intro_logo_renderable @ 0x419a90 */
/* selector: update_intro_logo_renderable */

// Exact Windows `cRLogoLetter::AI()`: advances one LogoLetter by applying its velocity to the shared BOD position, fades alpha across the z-window, marks the backing object dirty, and toggles visibility. The stable harness alias `update_logo_row` predates the recovered authored owner.
void __thiscall update_intro_logo_renderable(LogoLetter *letter)
{
  uint32_t v1; // eax
  uint32_t list_flags; // eax

  letter->renderable.transform.position.x = letter->velocity.x + letter->renderable.transform.position.x;
  letter->renderable.transform.position.y = letter->velocity.y + letter->renderable.transform.position.y;
  letter->renderable.transform.position.z = letter->velocity.z + letter->renderable.transform.position.z;
  if ( letter->renderable.transform.position.z <= 8.0 )
    letter->renderable.bod.color.a = 0.99900001;
  else
    letter->renderable.bod.color.a = (1.0 - (letter->renderable.transform.position.z - 8.0) * 0.125) * 0.99900001;
  letter->renderable.bod.object->flags |= 0x10u;
  if ( letter->renderable.transform.position.z > 16.0 || letter->renderable.transform.position.z < -4.0 )
  {
    list_flags = letter->renderable.bod.bod.list_flags;
    LOBYTE(list_flags) = list_flags & 0xDF;
    letter->renderable.bod.bod.list_flags = list_flags;
  }
  else
  {
    v1 = letter->renderable.bod.bod.list_flags;
    LOBYTE(v1) = v1 | 0x20;
    letter->renderable.bod.bod.list_flags = v1;
  }
}
