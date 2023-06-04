package com.example.mathcalculator;

public class NdkManager {

    static {
        System.loadLibrary("mathcalculator");
    }

//    public native double determinantOfMatrix(int n, double[] array);
}
