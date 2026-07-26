/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_all_border_visibility_mode @ 0x404360 */
/* selector: apply_all_border_visibility_mode */

// Exact authored `cRBorderStack::Perform(int)` member: applies one of four nested hidden/disabled transitions to the BorderManager-owned 150-record pool, recording borrowed cRBorder handles by generation so only the newest batch is unwound. Android confirms the owner, four-mode contract, and non-owning handle stack.
void __thiscall apply_all_border_visibility_mode(BorderStack *stack, int32_t mode)
{
  int i; // edx
  int32_t *p_flags; // esi
  int32_t v4; // eax
  int32_t entry_count; // eax
  int32_t v6; // eax
  FrontendWidget *widget; // eax
  FrontendWidget *v8; // eax
  int j; // edx
  int32_t *v10; // esi
  int32_t v11; // eax
  int32_t v12; // eax
  int32_t v13; // eax

  switch ( mode )
  {
    case 0:
      for ( i = 0; i < 150; ++i )
      {
        p_flags = &stack->owner->borders[i].flags;
        v4 = *p_flags;
        if ( *p_flags != 0 && (v4 & 0x10001400) == 0 )
        {
          BYTE1(v4) |= 0x10u;
          *p_flags = v4;
          stack->entries[stack->entry_count].widget = (FrontendWidget *)&stack->owner->borders[i];
          stack->entries[stack->entry_count++].generation = stack->generation;
        }
      }
      ++stack->generation;
      break;
    case 1:
      if ( stack->generation > 0 )
      {
        --stack->generation;
        entry_count = stack->entry_count;
        if ( entry_count > 0 )
        {
          v6 = entry_count - 1;
          stack->entry_count = v6;
          if ( v6 < 0 )
            goto LABEL_25;
          do
          {
            if ( stack->entries[v6].generation != stack->generation )
              goto LABEL_25;
            stack->entries[v6].widget->widget_flags &= ~0x1000u;
            widget = stack->entries[stack->entry_count].widget;
            widget->target_padding = widget->idle_padding;
            v8 = stack->entries[stack->entry_count].widget;
            v8->current_padding = v8->idle_padding;
            stack->entries[stack->entry_count].widget->hover_blend_target = 0.0;
            stack->entries[stack->entry_count].widget->hover_blend_current = 0.0;
            v6 = stack->entry_count - 1;
            stack->entry_count = v6;
          }
          while ( v6 >= 0 );
          stack->entry_count = v6 + 1;
        }
      }
      break;
    case 2:
      if ( stack->generation > 0 )
      {
        --stack->generation;
        v12 = stack->entry_count;
        if ( v12 > 0 )
        {
          v13 = v12 - 1;
          for ( stack->entry_count = v13; v13 >= 0; stack->entry_count = v13 )
          {
            if ( stack->entries[v13].generation != stack->generation )
              break;
            stack->entries[v13].widget->widget_flags &= ~0x8000u;
            v13 = stack->entry_count - 1;
          }
LABEL_25:
          ++stack->entry_count;
        }
      }
      break;
    case 3:
      for ( j = 0; j < 150; ++j )
      {
        v10 = &stack->owner->borders[j].flags;
        v11 = *v10;
        if ( *v10 != 0 && (v11 & 0x10009400) == 0 )
        {
          BYTE1(v11) |= 0x80u;
          *v10 = v11;
          stack->entries[stack->entry_count].widget = (FrontendWidget *)&stack->owner->borders[j];
          stack->entries[stack->entry_count++].generation = stack->generation;
        }
      }
      ++stack->generation;
      break;
    default:
      return;
  }
}
