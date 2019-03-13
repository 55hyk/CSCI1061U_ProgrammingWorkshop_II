#ifndef __Mat_h__
#define __Mat_h__
#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdlib>
using namespace std;

class Mat
{
protected:
  double* *entry;
  int row, col;

public:
  // constructors of various forms
  Mat();
  Mat(int r, int c);
  Mat(const Mat& o);

  ~Mat();

  void ones();
  void zeros();
  void rand();


  // index operators
  double* operator[](const int& i) {
    return entry[i];
  }

  Mat& operator=(const Mat& m);
  // Scalar arithmatic
  friend Mat operator+(const Mat& m, double k);
  friend Mat operator-(const Mat& m, double k);
  friend Mat operator*(const Mat& m, double k);
  friend Mat operator/(const Mat& m, double k);
  void operator+=(double k);
  void operator-=(double k);
  void operator*=(double k);
  void operator/=(double k);
  // Matrix arithmatic
  friend Mat operator+(const Mat& a, const Mat& b);
  friend Mat operator-(const Mat& a, const Mat& b);
  friend Mat operator*(const Mat& a, const Mat& b);
  void operator+=(const Mat& m);
  void operator-=(const Mat& m);
  void operator*=(const Mat& m);

  friend istream& operator>>(istream& is, Mat& m);
  friend ostream& operator<<(ostream& os, const Mat& m);
};

#endif
