#include <iostream>
#include <cmath>
#include <gtest/gtest.h>

using namespace std;

class Complex {
private:
    double re;
    double im;

public:
    Complex(): re(0.0), im(0.0) {}

    Complex(double r, double i): re(r), im(i) {}

    double getre() const {
        return re;
    }
    
    void setre(double r) {
        re = r;
    }

    double getim() const {
        return im;
    }
    
    void setim(double i) { im = i; }

    Complex add(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }

    Complex sub(const Complex& other) const {
        return Complex(re - other.re, im - other.im);
    }

    Complex mul(const Complex& other) const {
        return Complex((re * other.re) - (im * other.im), (re * other.im) + (im * other.re));
    }

    Complex cdiv(const Complex& other) const {
        double d = other.mod() * other.mod();
        return Complex((re * other.re + im * other.im) / d, (im * other.re - re * other.im) / d);
    }

    bool isequal(const Complex& other) const {
        return (re == other.re) && (im == other.im);
    }
    
    bool isequal(double value) const {
        return (re == value) && (im == 0.0);
    }

    Complex power(int n) const {
        double modul = pow(mod(), n);
        double arg = n * atan2(im, re);
        return Complex(modul * cos(arg), modul * sin(arg));
    }

    double mod() const {
        return sqrt(re * re + im * im);
    }

    void display() const {
        cout << "Complex Number: " << re << " + " << im << "i" << endl;
    }
};

TEST(ComplexTest, gsReal) {
    Complex num;
    EXPECT_DOUBLE_EQ(num.getre(), 0.0);

    num.setre(3.5);
    EXPECT_DOUBLE_EQ(num.getre(), 3.5);
}

TEST(ComplexTest, gsImaginary) {
    Complex num;
    EXPECT_DOUBLE_EQ(num.getim(), 0.0);

    num.setim(2.0);
    EXPECT_DOUBLE_EQ(num.getim(), 2.0);
}

TEST(ComplexTest, ArithmeticOperations) {
    Complex num1(2.0, 3.0);
    Complex num2(1.5, 2.5);

    Complex sum = num1.add(num2);
    Complex difference = num1.sub(num2);
    Complex product = num1.mul(num2);
    Complex quotient = num1.cdiv(num2);

    EXPECT_DOUBLE_EQ(sum.getre(), 3.5);
    EXPECT_DOUBLE_EQ(sum.getim(), 5.5);

    EXPECT_DOUBLE_EQ(difference.getre(), 0.5);
    EXPECT_DOUBLE_EQ(difference.getim(), 0.5);

    EXPECT_DOUBLE_EQ(product.getre(), -4.5);
    EXPECT_DOUBLE_EQ(product.getim(), 8.5);

    EXPECT_DOUBLE_EQ(quotient.getre(), 1.15);
    EXPECT_DOUBLE_EQ(quotient.getim(), -0.35);
}

TEST(ComplexTest, ComplexEquality) {
    Complex num1(2.0, 3.0);
    Complex num2(2.0, 3.0);
    Complex num3(1.5, 2.5);

    EXPECT_TRUE(num1.isequal(num2));
    EXPECT_FALSE(num1.isequal(num3));
}

TEST(ComplexTest, FloatEquality) {
    Complex num(2.0, 0.0);

    EXPECT_TRUE(num.isequal(2.0));
    EXPECT_FALSE(num.isequal(3.0));
}

TEST(ComplexTest, Power) {
    Complex num(2.0, 3.0);
    Complex powerResult = num.power(2);

    EXPECT_DOUBLE_EQ(powerResult.getre(), -5.0);
    EXPECT_DOUBLE_EQ(powerResult.getim(), 12.0);
}

TEST(ComplexTest, Modulus) {
    Complex num(3.0, 4.0);

    EXPECT_TRUE(num.mod() == 5.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
