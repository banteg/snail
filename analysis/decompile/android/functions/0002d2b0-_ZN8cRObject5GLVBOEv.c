/*
 * mangled: _ZN8cRObject5GLVBOEv
 * demangled: cRObject::GLVBO()
 * address: 0002d2b0
 * size: 16
 */

/* cRObject::GLVBO() */

void __thiscall cRObject::GLVBO(cRObject *this)

{
  if ((*(uint *)this & 0x200) != 0) {
    return;
  }
  GLObjectVBO(this);
  return;
}
