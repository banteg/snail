/*
 * mangled: _ZL8_getTimev
 * demangled: _getTime()
 * address: 000254c0
 * size: 64
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* _getTime() */

int _getTime(void)

{
  timeval local_10;

  gettimeofday(&local_10,(__timezone_ptr_t)0x0);
  return local_10.tv_sec * 1000 + local_10.tv_usec / 1000;
}
