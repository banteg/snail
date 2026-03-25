/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: font_slot_index_for_char @ 0x449d20 */
/* selector: font_slot_index_for_char */

// Maps front-end text bytes onto FONT-MENU-HOVER atlas slot indices; shipped tutorial strings reuse bytes like `{`, `}`, `[`, `]`, `~`, `_`, `^`, and `;` as icon tokens.
int __cdecl sub_449D20(char a1)
{
  int v2; // eax

  if ( a1 >= 65 && a1 <= 90 )
    return a1 - 38;
  if ( a1 >= 97 && a1 <= 122 )
    return a1 - 96;
  if ( a1 >= 48 && a1 <= 57 )
    return a1 + 6;
  switch ( a1 )
  {
    case 32:
      return 53;
    case 34:
      return 64;
    case 58:
      return 66;
    case 40:
      return 67;
    case 41:
      return 68;
    case 33:
      return 69;
    case 64:
      return 70;
    case 35:
      return 71;
    case 36:
      return 72;
    case 37:
      return 73;
    case 63:
      return 74;
    case 38:
      return 75;
    case 42:
      return 76;
    case 43:
      return 77;
    case 45:
      return 79;
    case 47:
      return 80;
    case 92:
      return 81;
    case 44:
      return 82;
    case 46:
      return 83;
    case 39:
      return 84;
    case 124:
      return 85;
    case 123:
      return 86;
    case 125:
      return 87;
    case 91:
      return 88;
    case 93:
      return 89;
    case 126:
      return 90;
    case 59:
      return 91;
    case 95:
      return 92;
    case 94:
      return 93;
  }
  v2 = -(a1 != 61);
  LOBYTE(v2) = v2 & 0xD7;
  return v2 + 94;
}

