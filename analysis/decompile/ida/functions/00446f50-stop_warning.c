/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_warning @ 0x446f50 */
/* selector: stop_warning */

// Stops the embedded cRWarning state machine and hides its border. Android and iOS retain this method as cRWarning::Stop().
void __thiscall stop_warning(Warning *warning)
{
  warning->state = WARNING_STATE_INACTIVE;
  hide_border_init(warning->border);
}
