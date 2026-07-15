/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_input_text @ 0x4035b0 */
/* selector: border_input_text */

// Stable Windows harness identity for the authored void cRBorder::InputText() member. The iOS and Android bodies preserve the same autorepeat key dispatch, inline cursor marker, insertion/deletion and separator-aware movement, blink/layout refresh, and optional cRInputOK teardown over the complete editor tail. The sole Windows caller ignores EAX; mobile return values are incidental RePosition/Kill results, not an authored result.
void __thiscall border_input_text(FrontendWidget *widget)
{
  char repeating_text_input_key_code; // bl
  uint32_t input_flags; // eax
  int32_t v4; // eax
  char v5; // bl
  uint8_t v6; // cl
  char *v7; // eax
  char v8; // dl
  int32_t input_cursor; // eax
  uint8_t v10; // dl
  int32_t v11; // eax
  uint8_t v12; // dl
  int32_t v13; // eax
  int i; // edi
  int j; // ecx
  uint8_t *v16; // ecx
  int32_t v18; // eax
  uint8_t v19; // cl
  uint8_t *v20; // eax
  uint8_t v21; // dl
  int32_t v22; // eax
  int k; // ebp
  int32_t v24; // edx
  uint8_t v25; // al
  int v26; // edx
  int v27; // eax
  uint8_t m; // cl
  uint8_t *v29; // ecx
  int32_t v31; // eax
  uint8_t v32; // cl
  uint8_t *v33; // eax
  uint8_t v34; // dl
  int32_t v35; // ecx
  uint8_t v36; // al
  uint8_t *v37; // eax
  int v39; // eax
  uint8_t v40; // cl
  uint8_t *v41; // eax
  uint8_t v42; // dl
  int n; // eax
  int32_t v44; // ecx
  uint8_t v45; // dl
  uint8_t *v46; // ecx
  uint8_t v48; // cl
  uint8_t *v49; // eax
  uint8_t v50; // dl
  int32_t v51; // eax
  int32_t v52; // eax
  uint8_t v53; // cl
  uint8_t *v54; // eax
  int32_t v56; // eax
  int32_t v57; // eax
  uint8_t v58; // cl
  uint8_t *v59; // eax
  int32_t v61; // eax
  char v62; // bl
  uint8_t v63; // cl
  int32_t v64; // ecx
  uint8_t v65; // dl
  uint8_t *v66; // eax
  int32_t v68; // eax
  double v70; // st7
  int32_t input_cursor_visible; // ecx
  int32_t v72; // eax
  uint8_t v73; // cl
  uint8_t *v74; // eax
  FrontendWidgetFlag widget_flags; // edx
  FrontendWidgetFlag v77; // eax
  int32_t v78; // edi

  repeating_text_input_key_code = read_repeating_text_input_key_code();
  if ( (widget->input_flags & 0xC) == 0
    || (update_input_ok((float **)widget->tooltip._pad_1c),
        (*(_BYTE *)(*(_DWORD *)widget->tooltip._pad_3c + 416) & 0x20) == 0) )
  {
    if ( repeating_text_input_key_code != 5 && (widget->widget_flags & 0x8000000) == 0 )
    {
      switch ( repeating_text_input_key_code )
      {
        case 6:
          input_flags = widget->input_flags;
          if ( (input_flags & 1) == 0 )
          {
            if ( (input_flags & 2) != 0 )
              goto LABEL_99;
            widget->text_buffer.raw[widget->input_cursor] = 62;
            v4 = widget->input_cursor + 1;
            widget->input_cursor = v4;
            v5 = 32;
            v6 = widget->text_buffer.raw[v4];
            v7 = (char *)&widget->text_buffer.raw[v4];
            v8 = 32;
            if ( v6 )
            {
              do
              {
                *v7++ = v5;
                v8 = v6;
                v6 = *v7;
                v5 = v8;
              }
              while ( *v7 );
            }
            goto LABEL_97;
          }
          break;
        case 3:
          input_cursor = widget->input_cursor;
          if ( input_cursor > 0 )
          {
            v10 = widget->text_buffer.raw[input_cursor];
            widget->text_buffer.raw[input_cursor] = widget->tooltip._pad_3c[input_cursor + 3];
            widget->tooltip._pad_3c[input_cursor + 3] = v10;
            --widget->input_cursor;
          }
          goto LABEL_99;
        case 4:
          v11 = widget->input_cursor;
          if ( v11 < widget->input_length )
          {
            v12 = widget->text_buffer.raw[v11];
            widget->text_buffer.raw[v11] = widget->text_buffer.raw[v11 + 1];
            widget->text_buffer.raw[v11 + 1] = v12;
            ++widget->input_cursor;
          }
          goto LABEL_99;
        case 7:
          v13 = widget->input_cursor;
          for ( i = -1; v13 > 0; --v13 )
          {
            if ( widget->text_buffer.raw[v13] == 62 )
              break;
            ++i;
          }
          if ( widget->text_buffer.raw[v13] == 62 )
            --v13;
          if ( v13 )
          {
            for ( j = 0; v13 > 0; --v13 )
            {
              if ( widget->text_buffer.raw[v13] == 62 )
                break;
              ++j;
            }
            if ( widget->text_buffer.raw[v13] == 62 )
              ++v13;
            if ( i > j )
              i = j;
            v16 = &widget->text_buffer.raw[widget->input_cursor];
            if ( *v16 )
            {
              do
                *v16 = v16[1];
              while ( *++v16 );
            }
            v18 = i + v13;
            widget->input_cursor = v18;
            v19 = widget->text_buffer.raw[v18];
            v20 = &widget->text_buffer.raw[v18];
            do
            {
              v21 = v20[1];
              *++v20 = v19;
              v19 = v21;
            }
            while ( *v20 );
          }
          goto LABEL_99;
        case 8:
          v22 = widget->input_cursor;
          for ( k = 0; v22 > 0; --v22 )
          {
            if ( widget->text_buffer.raw[v22] == 62 )
              break;
            ++k;
          }
          if ( widget->text_buffer.raw[v22] == 62 )
          {
            ++v22;
            --k;
          }
          v24 = v22;
          if ( widget->text_buffer.raw[v22] )
          {
            v25 = widget->text_buffer.raw[v22];
            do
            {
              if ( v25 == 62 )
                break;
              v25 = widget->text_buffer.raw[++v24];
            }
            while ( v25 );
          }
          if ( widget->text_buffer.raw[v24] == 62 )
          {
            v26 = v24 + 1;
            v27 = 0;
            for ( m = widget->text_buffer.raw[v26]; m; m = widget->text_buffer.raw[v26 + 1 + v27++] )
            {
              if ( m == 62 )
                break;
            }
            if ( k > v27 )
              k = v27;
            v29 = &widget->text_buffer.raw[widget->input_cursor];
            if ( *v29 )
            {
              do
                *v29 = v29[1];
              while ( *++v29 );
            }
            v31 = v26 + k - 1;
            widget->input_cursor = v31;
            v32 = widget->text_buffer.raw[v31];
            v33 = &widget->text_buffer.raw[v31];
            do
            {
              v34 = v33[1];
              *++v33 = v32;
              v32 = v34;
            }
            while ( *v33 );
          }
          goto LABEL_99;
        case 9:
          v35 = widget->input_cursor;
          if ( widget->text_buffer.raw[v35] )
          {
            v36 = widget->text_buffer.raw[v35];
            do
            {
              if ( v36 == 62 )
                break;
              v36 = widget->text_buffer.raw[++v35];
            }
            while ( v36 );
          }
          v37 = &widget->text_buffer.raw[widget->input_cursor];
          if ( *v37 )
          {
            do
              *v37 = v37[1];
            while ( *++v37 );
          }
          v39 = v35 - 1;
          widget->input_cursor = v35 - 1;
          v40 = widget->tooltip._pad_3c[v35 + 3];
          v41 = &widget->text_buffer.raw[v39];
          do
          {
            v42 = v41[1];
            *++v41 = v40;
            v40 = v42;
          }
          while ( *v41 );
          goto LABEL_99;
        case 10:
          for ( n = widget->input_cursor; n > 0; --n )
          {
            if ( widget->text_buffer.raw[n] == 62 )
              break;
          }
          if ( widget->text_buffer.raw[n] == 62 )
            ++n;
          v44 = widget->input_cursor;
          v45 = widget->text_buffer.raw[v44];
          v46 = &widget->text_buffer.raw[v44];
          if ( v45 )
          {
            do
              *v46 = v46[1];
            while ( *++v46 );
          }
          widget->input_cursor = n;
          v48 = widget->text_buffer.raw[n];
          v49 = &widget->text_buffer.raw[n];
          do
          {
            v50 = v49[1];
            *++v49 = v48;
            v48 = v50;
          }
          while ( *v49 );
          goto LABEL_99;
        case 1:
          v51 = widget->input_cursor;
          if ( v51 <= 0 )
            goto LABEL_99;
          v52 = v51 - 1;
          widget->input_cursor = v52;
          v53 = widget->text_buffer.raw[v52];
          v54 = &widget->text_buffer.raw[v52];
          if ( v53 )
          {
            do
              *v54 = v54[1];
            while ( *++v54 );
          }
          v56 = widget->input_length - 1;
          goto LABEL_98;
        case 2:
          v57 = widget->input_cursor;
          if ( v57 >= widget->input_length )
            goto LABEL_99;
          v58 = widget->text_buffer.raw[v57];
          v59 = &widget->text_buffer.raw[v57];
          if ( v58 )
          {
            do
              *v59 = v59[1];
            while ( *++v59 );
          }
          v56 = widget->input_length - 1;
          goto LABEL_98;
        case 0:
          goto LABEL_99;
      }
      if ( widget->input_length >= widget->input_capacity
        || repeating_text_input_key_code == 32 && (widget->input_flags & 1) != 0
        || (widget->input_flags & 2) != 0
        && (repeating_text_input_key_code == 44 || repeating_text_input_key_code == 46) )
      {
        goto LABEL_99;
      }
      widget->text_buffer.raw[widget->input_cursor] = repeating_text_input_key_code;
      v61 = widget->input_cursor + 1;
      widget->input_cursor = v61;
      v62 = 32;
      v63 = widget->text_buffer.raw[v61];
      v7 = (char *)&widget->text_buffer.raw[v61];
      v8 = 32;
      if ( v63 )
      {
        do
        {
          *v7++ = v62;
          v8 = v63;
          v63 = *v7;
          v62 = v8;
        }
        while ( *v7 );
      }
LABEL_97:
      *v7 = v8;
      v7[1] = 0;
      v56 = widget->input_length + 1;
LABEL_98:
      widget->input_length = v56;
LABEL_99:
      if ( (widget->input_flags & 2) != 0 )
      {
        v64 = 0;
        if ( widget->text_buffer.raw[0] )
        {
          do
          {
            v65 = widget->text_buffer.raw[v64];
            v66 = &widget->text_buffer.raw[v64];
            if ( v65 != 32 && v64 != widget->input_cursor )
              break;
            if ( v64 != widget->input_cursor )
            {
              if ( v65 )
              {
                do
                  *v66 = v66[1];
                while ( *++v66 );
              }
              v68 = widget->input_cursor;
              if ( v64 <= v68 )
                widget->input_cursor = v68 - 1;
              --widget->input_length;
            }
          }
          while ( widget->text_buffer.raw[++v64] );
        }
      }
      v70 = widget->input_cursor_blink_step + widget->input_cursor_blink_progress;
      widget->input_cursor_blink_progress = v70;
      if ( v70 > 1.0 )
      {
        input_cursor_visible = widget->input_cursor_visible;
        widget->input_cursor_blink_progress = 0.0;
        widget->input_cursor_visible = input_cursor_visible == 0;
      }
      if ( widget->input_cursor_visible == 1 )
        widget->text_buffer.raw[widget->input_cursor] = 124;
      else
        widget->text_buffer.raw[widget->input_cursor] = 32;
      layout_frontend_widget(widget);
      return;
    }
  }
  v72 = widget->input_cursor;
  v73 = widget->text_buffer.raw[v72];
  v74 = &widget->text_buffer.raw[v72];
  if ( v73 )
  {
    do
      *v74 = v74[1];
    while ( *++v74 );
  }
  widget_flags = widget->widget_flags;
  BYTE1(widget_flags) &= ~0x20u;
  v77 = widget_flags;
  v78 = widget->input_length - 1;
  BYTE1(v77) = BYTE1(widget_flags) | 0x40;
  widget->widget_flags = widget_flags;
  widget->input_length = v78;
  widget->widget_flags = v77;
  layout_frontend_widget(widget);
  if ( (widget->input_flags & 0xC) != 0 )
    kill_border(*(_DWORD **)widget->tooltip._pad_3c);
}
