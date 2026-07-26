/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_add_text_number @ 0x401030 */
/* selector: border_add_text_number */

// Exact authored `cRBorder::AddTextNumber(int)` member: appends a positive decimal value to the border's text buffer, inserts comma separators at the million and thousand boundaries, and handles zero as `0`. Android and iOS preserve the owner and algorithm while using their own cRBorder layout.
void __thiscall border_add_text_number(FrontendWidget *border, int32_t value)
{
  uint8_t v2; // al
  FrontendWidgetTextBuffer *p_text_buffer; // ecx
  uint8_t v4; // al
  int32_t v5; // ebx
  char v6; // al
  int v7; // esi
  int v8; // eax
  char valuea; // [esp+4h] [ebp+4h]

  v2 = border->text_buffer.raw[0];
  p_text_buffer = &border->text_buffer;
  if ( v2 != 0 )
  {
    do
    {
      v4 = p_text_buffer->raw[1];
      p_text_buffer = (FrontendWidgetTextBuffer *)((char *)p_text_buffer + 1);
    }
    while ( v4 != 0 );
  }
  v5 = value;
  if ( value == 0 )
  {
    p_text_buffer->raw[0] = 48;
    p_text_buffer->raw[1] = 0;
    return;
  }
  v6 = 0;
  v7 = 10000000;
  for ( valuea = 0; ; v6 = valuea )
  {
    if ( v6 != 0 && (v7 == 100 || v7 == 100000) )
    {
      p_text_buffer->raw[0] = 44;
      p_text_buffer = (FrontendWidgetTextBuffer *)((char *)p_text_buffer + 1);
    }
    if ( v5 >= v7 || v6 != 0 )
    {
      if ( v7 == 1 )
      {
        LOBYTE(v8) = v5;
      }
      else
      {
        v8 = v5 / v7;
        if ( v5 / v7 == 0 )
        {
          if ( valuea == 0 )
            goto LABEL_21;
          p_text_buffer->raw[0] = 48;
          goto LABEL_20;
        }
        valuea = 1;
      }
      p_text_buffer->raw[0] = v8 + 48;
LABEL_20:
      p_text_buffer = (FrontendWidgetTextBuffer *)((char *)p_text_buffer + 1);
    }
LABEL_21:
    v5 %= v7;
    v7 /= 10;
    if ( v7 == 0 )
      break;
  }
  p_text_buffer->raw[0] = 0;
}
