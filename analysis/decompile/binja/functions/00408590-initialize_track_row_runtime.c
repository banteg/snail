/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_row_runtime @ 0x408590 */

00408599        initialize_renderable_bod(&row->row_model)
004085a4        row->row_model.body.bod.bod.vtable = &g_row_model_vtable
004085aa        initialize_bod_base(&row->attachment_body)
004085b3        return row
