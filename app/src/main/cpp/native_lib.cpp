#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring  extern "C" JNICALL
Java_com_example_mathcalculator_MainActivity_stringFromJNI (
        JNIEnv* env,
        jobject) {
    std::string hello = "Hello from";
    return env->NewStringUTF(hello.c_str());
}
