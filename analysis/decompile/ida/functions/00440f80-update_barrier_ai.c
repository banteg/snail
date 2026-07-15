/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_barrier_ai @ 0x440f80 */
/* selector: update_barrier_ai */

// Exact void cRBarrier::AI() callback for the embedded 0x3c-byte BarrierActor at SubgameRuntime +0xff7bc4. It borrows Player* at +0x38, follows the player's live z position, and is installed in g_barrier_actor_callback_table; the residual EAX value is not an authored return.
void __thiscall update_barrier_ai(BarrierActor *barrier)
{
  float z; // edx

  z = barrier->owner_player->body.transform.position.z;
  barrier->bod.position.y = 0.40000001;
  barrier->bod.position.z = z;
}
