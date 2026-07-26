/*
 * mangled: _ZN7_JNIEnv14CallVoidMethodEP8_jobjectP10_jmethodIDz
 * demangled: _JNIEnv::CallVoidMethod(_jobject*, _jmethodID*, ...)
 * address: 00023e84
 * size: 52
 */

/* _JNIEnv::CallVoidMethod(_jobject*, _jmethodID*, ...) */

void __thiscall _JNIEnv::CallVoidMethod(_JNIEnv *this,_jobject *param_1,_jmethodID *param_2,...)

{
  (**(code **)(*(int *)this + 0xf8))(this,param_1,param_2);
  return;
}
