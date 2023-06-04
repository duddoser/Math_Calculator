#include "nativelib_NdkManager.h"

extern "C" {
    JNIEXPORT jdouble JNICALL Java_com_example_mathcalculator_NdkManager_determinantOfMatrix
            (JNIEnv * env, jobject obj, jint n, jdoubleArray array) {
        double* mat = new double[n * n];
        mat = env->GetDoubleArrayElements(array, 0);
        return n;
    }
}
