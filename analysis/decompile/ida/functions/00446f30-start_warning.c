/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_warning @ 0x446f30 */
/* selector: start_warning */

// Starts the embedded cRWarning fade cycle and unhides its border. Android cRDamageGuage::AI() calls cRWarning::Start() through the same owner relationship.
void __thiscall start_warning(Warning *warning)
{
  warning->phase = 1.0;
  warning->state = WARNING_STATE_FADING;
  unhide_border_init(warning->border);
}
