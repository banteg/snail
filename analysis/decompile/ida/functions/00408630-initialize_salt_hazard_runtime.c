/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_salt_hazard_runtime @ 0x408630 */
/* selector: initialize_salt_hazard_runtime */

// Exact constructor wrapper for one authored `Salt` (`cRSalt` cross-port): constructs the renderable-body prefix, installs the table whose entry is update_salt_hazard, and returns the receiver. SaltManager owns 40 inline 0x98-byte records whose 0x17c0 total matches the native ledger.
Salt *__thiscall initialize_salt_hazard_runtime(Salt *salt)
{
  initialize_renderable_bod(&salt->body);
  salt->body.bod.bod.vtable = &g_salt_vtable;
  return salt;
}
