#include "Mat.h"

Mat::Mat() : entry(0), row(0), col(0) {
  cout << "An empty matrix has constructed." << endl;
}

Mat::Mat(int r, int c) : row(r), col(c) {
  if (row == 0 || col == 0) {
    cout << "Number of row or column can not be 0." << endl;
    row = 0;
    col = 0;
  } else {
    entry = new double* [row];
    for (int i = 0; i < row; i++) {
      entry[i] = new double[col];
    }
    cout << "A(n) " << r << " by " << c << " matrix has constructed." << endl;
  }
}

Mat::Mat(const Mat& o) {
  if (row && col) {
    if (o.row && o.col) {
      row = o.row;
      col = o.col;

      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          entry[i][j] = o.entry[i][j];
        }
      }
    } else {
      this->~Mat();
    }
  } else {
    if (o.row && o.col) {
      row = o.row;
      col = o.col;
      entry = new double* [row];
      for (int i = 0; i < row; i++) {
        entry[row] = new double[col];
      }
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          entry[i][j] = o.entry[i][j];
        }
      }
    }
  }
  cout << "A copy is made." << endl;
}

Mat::~Mat() {
  row = 0;
  col = 0;
  for (int i = 0; i < row; i++) {
    delete[] entry[i];
  }
  delete[] entry;
  cout << "A matrix is destroyed." << endl;
}

void Mat::ones() {
  if (row && col) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        entry[i][j] = 1;
      }
    }
  } else {
    cout << "The matrix is empty." << endl;
  }
}

void Mat::zeros() {
  if (row && col) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        entry[i][j] = 0;
      }
    }
  } else {
    cout << "The matrix is empty." << endl;
  }
}

void Mat::rand() {
  if (row && col) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        entry[i][j] = std::rand()/(double)RAND_MAX;
      }
    }
  } else {
    cout << "The matrix is empty." << endl;
  }
}

istream& operator>>(istream& is, Mat& m) {
  if (!(m.row || m.col)) {
    cout << "Example: 2 2 4 6 8 45 (end with a space)" << endl
         << "The first number that you enter is the number of rows;" << endl
         << "the second number is the number of columns;" << endl
         << "the third, fourth, fifth and sixth are"
         << "the 11, 12, 21, 22 entry of the matrix." << endl;

    is >> m.row >> m.col;
    m.entry = new double* [m.row];
    for (int i = 0; i < m.row; i++) {
      m.entry[i] = new double[m.col];
    }
    for (int i = 0; i < m.row; i++) {
      for (int j = 0; j < m.col; j++) {
        is >> m.entry[i][j];
      }
    }
  } else {
    cout << "This is not a null matrix." << endl;
  }

  return is;
}

ostream& operator<<(ostream& os, const Mat& m) {
  if (m.row || m.col) {
    os << m.row << " by " << m.col << " Matrix" << endl;
    for (int i = 0; i < m.row; i++) {
      for (int j = 0; j < m.col; j++) {
        os << m.entry[i][j] << "\t";
      }
      os << endl;
    }
  }
  return os;
}

Mat& Mat::operator=(const Mat& m) {
  if (row == 0 && col == 0) {
    row = m.row;
    col = m.col;
    entry = new double* [row];
    for (int i = 0; i < row; i++) {
      entry[i] = new double[col];
    }
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        entry[i][j] = m.entry[i][j];
      }
    }
  } else if (row == m.row && col == m.col) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        entry[i][j] = m.entry[i][j];
      }
    }
  } else {
    cout << "The size does not match." << endl;
  }

  return *this;
}

//Scalar arithmatic
Mat operator+(const Mat& m, double k) {
  int r = m.row, c = m.col;
  Mat temp(r, c);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      temp.entry[i][j] = m.entry[i][j] + k;
    }
  }
  return temp;
}
Mat operator-(const Mat& m, double k) {
  Mat temp(m.row, m.col);
  for (int i = 0; i < m.row; i++) {
    for (int j = 0; j < m.col; j++) {
      temp.entry[i][j] = m.entry[i][j] - k;
    }
  }
  return temp;
}
Mat operator*(const Mat& m, double k) {
  Mat temp(m.row, m.col);
  for (int i = 0; i < m.row; i++) {
    for (int j = 0; j < m.col; j++) {
      temp.entry[i][j] = m.entry[i][j] * k;
    }
  }
  return temp;
}
Mat operator/(const Mat& m, double k) {
  Mat temp(m.row, m.col);
  for (int i = 0; i < m.row; i++) {
    for (int j = 0; j < m.col; j++) {
      temp.entry[i][j] = m.entry[i][j] / k;
    }
  }
  return temp;
}

void Mat::operator+=(double k) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      entry[i][j] += k;
    }
  }
}
void Mat::operator-=(double k) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      entry[i][j] -= k;
    }
  }
}
void Mat::operator*=(double k) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      entry[i][j] *= k;
    }
  }
}
void Mat::operator/=(double k) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      entry[i][j] /= k;
    }
  }
}

Mat operator+(const Mat& a, const Mat& b) {
  int r = a.row;
  int c = a.col;
  Mat temp(r, c);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      temp.entry[i][j] = a.entry[i][j] + b.entry[i][j];
    }
  }
  return temp;
}
Mat operator-(const Mat& a, const Mat& b) {
  int r = a.row;
  int c = a.col;
  Mat temp(r, c);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      temp.entry[i][j] = a.entry[i][j] - b.entry[i][j];
    }
  }
  return temp;
}
Mat operator*(const Mat& a, const Mat& b) {
  int r = a.row;
  int c = b.col, count;
  double e;
  Mat temp(r, c);
  for (int m = 0; m < r; m++) {
    for (int n = 0; n < c; n++) {
      for (int i = 0; i < a.col; i++) {
        temp.entry[m][n] += (a.entry[m][i] * b.entry[i][n]);
      }
    }
  }
  return temp;
}

void Mat::operator+=(const Mat& m) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      entry[i][j] += m.entry[i][j];
    }
  }
}
void Mat::operator-=(const Mat& m) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      entry[i][j] -= m.entry[i][j];
    }
  }
}
void Mat::operator*=(const Mat& m) {
  Mat temp(*this * m);
  this->~Mat();
  row = temp.row;
  col = temp.col;
  entry = new double* [row];
  for (int i = 0; i < row; i++) {
    entry[i] = new double[col];
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      entry[i][j] = temp.entry[i][j];
    }
  }
}









//
