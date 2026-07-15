/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_sprite_extend @ 0x404540 */
/* selector: border_sprite_extend */

// Stable Windows harness identity for the authored void cRBorder::SpriteExtend(int, int, int, bool) member. It owns the three-texture contextual sprite lane, wobble direction, and zeroed padding targets.
void __thiscall border_sprite_extend(
        FrontendWidget *widget,
        int32_t sprite_a,
        int32_t sprite_c,
        int32_t sprite_b,
        uint8_t wobble_positive)
{
  widget->background_texture_id = sprite_a;
  widget->texture_hit_test_sprite = sprite_b;
  widget->sprite_extend_texture_c = sprite_c;
  widget->texture_hit_test_enabled = 1;
  widget->sprite_wobble_positive = wobble_positive;
  widget->target_padding = 0.0;
  widget->idle_padding = 0.0;
  widget->hot_padding = 0.0;
}
