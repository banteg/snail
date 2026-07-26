/*
 * mangled: _ZN21OFHighScoreBatchEntry9serializeEP13OFISerializer
 * demangled: OFHighScoreBatchEntry::serialize(OFISerializer*)
 * address: 0008c820
 * size: 152
 */

/* OFHighScoreBatchEntry::serialize(OFISerializer*) */

void __thiscall OFHighScoreBatchEntry::serialize(OFHighScoreBatchEntry *this,OFISerializer *param_1)

{
  bool local_11;

  OFISerializer::io(param_1,"leaderboard_id",(OFRetainedPtr *)(this + 8));
  OFISerializer::io(param_1,"score",(longlong *)(this + 0x18));
  if (*(int *)(this + 0xc) != 0) {
    OFISerializer::io(param_1,"display_text",(OFRetainedPtr *)(this + 0xc));
  }
  if (*(int *)(this + 0x10) != 0) {
    OFISerializer::io(param_1,"custom_data",(OFRetainedPtr *)(this + 0x10));
  }
  local_11 = *(int *)(this + 0x14) != 0;
  OFISerializer::io(param_1,"has_blob",&local_11);
  return;
}
