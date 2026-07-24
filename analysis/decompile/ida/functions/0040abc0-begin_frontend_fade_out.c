/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_frontend_fade_out @ 0x40abc0 */
/* selector: begin_frontend_fade_out */

// Exact void Windows cRFade::Start(void (*)()) projection: enters opaque-bound state 2, clears alpha, and stores the completion callback at +0x10. Every Windows caller passes null and discards EAX; the natural callback-shaped void source remains exact at 5/5 instructions.
void __thiscall begin_frontend_fade_out(FrontendFade *fade, FrontendFadeCallback completion_callback)
{
  fade->state = 2;
  fade->alpha = 0.0;
  fade->completion_callback = completion_callback;
}
