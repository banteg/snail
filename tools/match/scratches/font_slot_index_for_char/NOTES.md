# font_slot_index_for_char

Initial scratch for the FONT-MENU-HOVER byte-to-slot mapper at `0x449d20`.

Wibo result: exact 100%, 145/145 instructions, no masked operands.

Recovered relationships:

- `A..Z`, `a..z`, and `0..9` map into contiguous atlas ranges.
- Several punctuation bytes map to icon/symbol slots used by shipped tutorial
  and front-end strings.
- Native contains an impossible signed-char compare against the multi-character
  constant `'""'` (`0x2222`), so a plain double-quote falls through to the
  fallback slot. The scratch preserves that source-level oddity.
