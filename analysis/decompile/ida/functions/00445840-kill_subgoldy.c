/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_subgoldy @ 0x445840 */
/* selector: kill_subgoldy */

// Void `Player` member that hides both cached ghost sprites and clears Goldy's active render flag. Its sole `update_times_up` caller discards the final flag-clear residue.
void __thiscall kill_subgoldy(Player *player)
{
  begin_post_follow_carryover((int)player);
  player->body.transform.position.y = -8.0;
}
