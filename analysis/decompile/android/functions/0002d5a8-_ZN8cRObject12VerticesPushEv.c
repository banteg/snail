/*
 * mangled: _ZN8cRObject12VerticesPushEv
 * demangled: cRObject::VerticesPush()
 * address: 0002d5a8
 * size: 84
 */

/* cRObject::VerticesPush() */

void __thiscall cRObject::VerticesPush(cRObject *this)

{
  void *__dest;

  __dest = *(void **)(this + 0xac);
  if (__dest == (void *)0x0) {
    __dest = (void *)RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,
                                        (char *)(DAT_0002d5fc + 0x2d5c4 + DAT_0002d600));
    *(void **)(this + 0xac) = __dest;
  }
  memcpy(__dest,*(void **)(this + 0xa4),*(int *)(this + 0xa0) * 0xc);
  return;
}
