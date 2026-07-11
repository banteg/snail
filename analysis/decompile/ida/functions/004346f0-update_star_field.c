/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_star_field @ 0x4346f0 */
/* selector: update_star_field */

// Runs the four-state star-field controller, fading the streak sprites in or out around the global star-pass flag and dispatching the per-frame camera-relative position update.
void __thiscall update_star_field(StarManager *manager)
{
  double v2; // st7
  double v3; // st7

  switch ( manager->state )
  {
    case 0:
      if ( (g_render_flags & 4) != 0 )
      {
        manager->state = 2;
        initialize_star_field(manager);
        manager->state = 2;
        manager->fade = 0.0;
        manager->fade_step = 0.020833334;
        update_star_positions(manager, 0.0);
      }
      break;
    case 1:
      update_star_positions(manager, 1.0);
      if ( (g_render_flags & 4) == 0 )
      {
        manager->fade = 1.0;
        manager->fade_step = 0.020833334;
        goto LABEL_13;
      }
      break;
    case 2:
      update_star_positions(manager, manager->fade);
      if ( (g_render_flags & 4) != 0 )
      {
        v2 = manager->fade_step + manager->fade;
        manager->fade = v2;
        if ( v2 > 1.0 )
          manager->state = 1;
      }
      else
      {
LABEL_13:
        manager->state = 3;
      }
      break;
    case 3:
      update_star_positions(manager, manager->fade);
      if ( (g_render_flags & 4) != 0 )
      {
        manager->state = 2;
      }
      else
      {
        v3 = manager->fade - manager->fade_step;
        manager->fade = v3;
        if ( v3 < 0.0 )
        {
          destroy_star_field(manager);
          manager->state = 0;
        }
      }
      break;
    default:
      return;
  }
}

