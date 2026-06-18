# initialize_high_score_tables

Seeds the persistent high-score banks after startup/default-table load:

- postal/top-ten storage records: mode tag `0`, route/rank index `0..10`
- survival/challenge storage records: mode tag `1`, route/rank index `0..10`
- time-trial route records: mode tag `2`, route index `0..50`
- current result scratch record: mode tag/index `0`

This scratch depends on the promoted `HighScoreRecord` stride and confirms the
three bank windows and the `current_result_record` offset in `HighScoreBank`.

Focused Wibo matches 100.00%, 58/58 instructions, with four clean masked
operands.
