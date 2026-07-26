/*
 * mangled: _ZN19OFBinaryKeyedWriter13onScopePushedEP16OFISerializerKey
 * demangled: OFBinaryKeyedWriter::onScopePushed(OFISerializerKey*)
 * address: 000c6df4
 * size: 64
 */

/* OFBinaryKeyedWriter::onScopePushed(OFISerializerKey*) */

void __thiscall
OFBinaryKeyedWriter::onScopePushed(OFBinaryKeyedWriter *this,OFISerializerKey *param_1)

{
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),"$&19OFSdbmSerializerKey",1);
                    /* WARNING: Could not recover jumptable at 0x000c6e30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)this + 0x60))(this,param_1);
  return;
}
