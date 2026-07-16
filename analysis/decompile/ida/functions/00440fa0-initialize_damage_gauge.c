/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_damage_gauge @ 0x440fa0 */
/* selector: initialize_damage_gauge */

// Initializes Goldy's contact-damage gauge controller at player +0x3c4. Cross-port iOS v1.9 symbols match this helper to the intentionally misspelled `cRDamageGuage::Init(cRSubGoldy*)` owner.
void __thiscall initialize_damage_gauge(DamageGuage *damage_guage)
{
  damage_guage->pulse_step = 0.020833334;
  damage_guage->fill = 0.0;
  damage_guage->display_fill = 0.0;
  damage_guage->skin_hold_ticks = 0;
  damage_guage->state = DAMAGE_GUAGE_STATE_MONITORING;
  damage_guage->warning_transition_progress = 0.0;
  damage_guage->unresolved_byte_0c = 0;
  damage_guage->pulse_progress = 0.0;
  damage_guage->hit_flash_progress = 0.0;
  damage_guage->hit_flash_step = 0.033333335;
}
