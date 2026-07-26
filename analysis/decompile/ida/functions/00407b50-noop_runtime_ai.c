/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: noop_runtime_ai @ 0x407b50 */
/* selector: noop_runtime_ai */

// Shared one-byte empty method body folded across runtime owners. Receiver-typed calls at Player +0x3f0 and SubgameRuntime +0x3bbb54 recover `cRProgressBar::Init()` specifically; the Player receiver at collision callsite 0x445536 recovers mobile-authored `cRSubGoldy::SpeedUpCollect()`. The dedicated table at 0x49735c points here and is installed on all four embedded Weapon owners, while Android and iOS independently retain empty `cRWeapon::AI()` bodies. Other callsites remain distinct no-op AI or lifecycle methods.
void noop_runtime_ai()
{
  ;
}
