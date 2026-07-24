/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_frontend_fade_in @ 0x40abe0 */
/* selector: begin_frontend_fade_in */

// Exact void Windows cRFade::StartOn() projection: seeds alpha to one and state 1 so cRFade::AI fades the black overlay away over 18 updates. Both iOS and Android retain the authored StartOn name.
void __thiscall begin_frontend_fade_in(FrontendFade *fade)
{
  fade->state = 1;
  fade->alpha = 1.0;
}
