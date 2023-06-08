package com.example.mathcalculator;


import static java.lang.Math.abs;

public class Fraction {
    private int num, denom;

    public Fraction() {
        num = 0;
        denom = 1;
    }

    Fraction(int n){
        num = n;
        denom = 1;
    }

    Fraction(int n, int d){
        num = n;
        if(d < 0) num *= -1;
        if(d != 0) denom = abs(d);
    }

    int n() {
        return num;
    }

    void set_n(int n){
        num = n;
    }

    int d() {
        return denom;
    }

    void set_d(int d){
        denom = d;
    }

    Fraction minus() {
        Fraction result = new Fraction(0, 1);
        result.num = -1 * num;
        result.denom = denom;
        return result;
    }

    Fraction mult(int m){
        Fraction result = new Fraction(0, 1);
        result.num = num * m;
        result.denom = denom;
        int com_factor = gcd(abs(m), denom);
        result.num /= com_factor;
        result.denom /= com_factor;
        return result;
    }

    Fraction mult(Fraction f) {
        Fraction result = new Fraction(0, 1);
        result.num = num * f.num;
        result.denom = denom * f.denom;
        int com_factor = gcd(abs(result.num), result.denom);
        result.num /= com_factor;
        result.denom /= com_factor;
        return result;
    }

    Fraction del(Fraction f) {
        Fraction result = new Fraction(0, 1);
        if(f.num < 0) result.num = f.denom * (-1);
        else result.num = f.denom;
        result.denom = abs(f.num);
        return this.mult(result);
    }

    Fraction sum(Fraction f) {
        Fraction result = new Fraction(0, 1);
        result.num = num * f.denom + f.num * denom;
        result.denom = denom * f.denom;
        int com_factor = gcd(abs(result.num), result.denom);
        result.num /= com_factor;
        result.denom /= com_factor;
        return result;
    }

    Fraction plus_equal(Fraction f){
        Fraction result = this.sum(f);
        num = result.num;
        denom = result.denom;
        return this;
    }

    Fraction del_equal(Fraction f){
        Fraction result;
        result = this.del(f);
        num = result.num;
        denom = result.denom;
        return this;
    }

    Fraction minus(Fraction f) {
        Fraction result = new Fraction(0, 1);
        result.num = -1 * f.num;
        return this.sum(f);
    }


    boolean equal_equal(Fraction f) {
        return num == f.num && denom == f.denom;
    }

    boolean not_equal(Fraction f) {
        return !(this.equal_equal(f));
    }

    boolean equal_equal(int i) {
        return num == denom * i;
    }

    public int gcd(int a, int b) {
        return b != 0 ? gcd(b, a % b) : a;
    }

    boolean operator_more(Fraction f){
        return num * f.denom > denom * f.num;
    }

    boolean operator_less(Fraction f) {
        return !(this.operator_more(f) || this.equal_equal(f));
    }

    boolean operator_less(double d) {
        return num < d * denom;
    }

    Fraction fabs(Fraction f1){
        Fraction result = new Fraction();
        result.set_n(abs(f1.n()));
        result.set_d(f1.d());
        return result;
    }
}
