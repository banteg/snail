/*
 * mangled: _ZN7_JNIEnv13CallIntMethodEP8_jobjectP10_jmethodIDz
 * demangled: _JNIEnv::CallIntMethod(_jobject*, _jmethodID*, ...)
 * address: 000240e4
 * size: 52
 */

/* _JNIEnv::CallIntMethod(_jobject*, _jmethodID*, ...) */

void __thiscall _JNIEnv::CallIntMethod(_JNIEnv *this,_jobject *param_1,_jmethodID *param_2,...)

{
  (**(code **)(*(int *)this + 200))(this,param_1,param_2);
  return;
}
