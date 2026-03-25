/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stack_widget_below @ 0x4027b0 */
/* selector: stack_widget_below */

// Chains one shell-font front-end widget below another by copying the previous widget x anchor and adding the current gap plus the previous measured height.
float *__thiscall sub_4027B0(int this, int a2)
{
  *(_DWORD *)(this + 1780) = *(_DWORD *)(a2 + 1780);
  *(float *)(this + 1784) = *(float *)(a2 + 1784) + *(float *)(this + 620) + *(float *)(a2 + 588);
  return layout_frontend_widget(this);
}

