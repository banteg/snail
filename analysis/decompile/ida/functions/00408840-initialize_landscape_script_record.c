/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_landscape_script_record @ 0x408840 */
/* selector: initialize_landscape_script_record */

// Constructs one 0x124-byte parsed landscape-script record by running the no-op `Color4f` constructor for its `fog_color` field at `+0x110`; used for the 128-record landscape-script bank at `game+0xff81a4`.
int __thiscall sub_408840(int this)
{
  Iostream_init::Iostream_init((ObjectVertexBufferVtbl *)(this + 272));
  return this;
}
