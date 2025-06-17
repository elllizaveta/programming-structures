#ifndef MATRIX
#define MATRIX
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED
#include <iostream>
#include <stdexcept>
#include <algorithm>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t Rows, size_t Columns>
struct Matrix {
 public:
  T matrix[Rows][Columns];
  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T& operator()(size_t i, size_t j);
  const T& operator()(size_t i, size_t j) const;
  T& At(size_t i, size_t j);
  const T& At(size_t i, size_t j) const;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix<T, Columns, Columns>& other);
  Matrix& operator*=(T x);
  Matrix& operator/=(T x);
  Matrix operator*(T x);
  Matrix operator/(T x);
  bool operator==(const Matrix<T, Rows, Columns>& second) const;
};

template <class T, size_t Rows, size_t Columns>
size_t Matrix<T, Rows, Columns>::RowsNumber() const {
  return Rows;
}

template <class T, size_t Rows, size_t Columns>
size_t Matrix<T, Rows, Columns>::ColumnsNumber() const {
  return Columns;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Columns, Rows> GetTransposed(Matrix<T, Rows, Columns> old) {
  Matrix<T, Columns, Rows> ans;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      ans.matrix[j][i] = old.matrix[i][j];
    }
  }
  return ans;
}

template <class T, size_t Rows, size_t Columns>
T& Matrix<T, Rows, Columns>::operator()(size_t i, size_t j) {
  return matrix[i][j];
}

template <class T, size_t Rows, size_t Columns>
const T& Matrix<T, Rows, Columns>::operator()(size_t i, size_t j) const {
  return matrix[i][j];
}

template <class T, size_t Rows, size_t Columns>
T& Matrix<T, Rows, Columns>::At(size_t i, size_t j) {
  if (i < 0 || i >= Rows || j < 0 || j >= Columns) {
    throw MatrixOutOfRange{};
  }
  return matrix[i][j];
}

template <class T, size_t Rows, size_t Columns>
const T& Matrix<T, Rows, Columns>::At(size_t i, size_t j) const {
  if (i < 0 || i >= Rows || j < 0 || j >= Columns) {
    throw MatrixOutOfRange{};
  }
  return matrix[i][j];
}

// присваивающие версии операций над матрицами(в классе)

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator+=(const Matrix<T, Rows, Columns>& other) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      this->matrix[i][j] += other.matrix[i][j];
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator-=(const Matrix<T, Rows, Columns>& other) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      this->matrix[i][j] -= other.matrix[i][j];
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator*=(const Matrix<T, Columns, Columns>& other) {
  Matrix<T, Rows, Columns> ans;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      ans(i, j) = 0;
      for (size_t r = 0; r < Columns; ++r) {
        ans(i, j) += matrix[i][r] * other(r, j);
      }
    }
    for (size_t j = 0; j < Columns; ++j) {
      matrix[i][j] = ans(i, j);
    }
  }
  return *this;
}

// операции над матрицами(вне класса)

template <class T, size_t N, size_t M, size_t K>
Matrix<T, N, K> operator*(const Matrix<T, N, M>& first, const Matrix<T, M, K>& second) {
  Matrix<T, N, K> ans;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      ans(i, j) = 0;
      for (size_t r = 0; r < M; ++r) {
        ans(i, j) += first(i, r) * second(r, j);
      }
    }
  }
  return ans;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator-(const Matrix<T, Rows, Columns>& first, const Matrix<T, Rows, Columns>& second) {
  Matrix ans = first;
  return ans -= second;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns>& first, const Matrix<T, Rows, Columns>& second) {
  Matrix ans = first;
  return ans += second;
}

// присваивающие версии операций с числами

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator*=(T x) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      this->matrix[i][j] *= x;
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator/=(T x) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      this->matrix[i][j] /= x;
    }
  }
  return *this;
}

// операции с числом справа

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator*(T x) {
  Matrix<T, Rows, Columns> ans;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      ans(i, j) = this->matrix[i][j] * x;
    }
  }
  return ans;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator/(T x) {
  Matrix<T, Rows, Columns> ans;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      ans(i, j) = this->matrix[i][j] / x;
    }
  }
  return ans;
}

// операции с числом слева

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator*(T x, const Matrix<T, Rows, Columns>& old) {
  Matrix<T, Rows, Columns> ans;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      ans(i, j) = old(i, j) * x;
    }
  }
  return ans;
}

// сравнение матриц

template <class T, size_t Rows, size_t Columns>
bool Matrix<T, Rows, Columns>::operator==(const Matrix<T, Rows, Columns>& second) const {
  bool ans = true;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      if (matrix[i][j] != second(i, j)) {
        ans = false;
        break;
      }
    }
  }
  return ans;
}

template <class T, size_t Rows, size_t Columns>
bool operator!=(const Matrix<T, Rows, Columns>& first, const Matrix<T, Rows, Columns>& second) {
  return !(first == second);
}

// ввод в поток и вывод из потока

template <class T, size_t Rows, size_t Columns>
std::istream& operator>>(std::istream& in, Matrix<T, Rows, Columns>& x) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      in >> x(i, j);
    }
  }
  return in;
}

template <class T, size_t Rows, size_t Columns>
std::ostream& operator<<(std::ostream& out, const Matrix<T, Rows, Columns>& x) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      out << x(i, j);
      if (Columns > j + 1) {
        out << " ";
      }
    }
    out << std::endl;
  }
  return out;
}

// доп часть

template <class T, size_t N>
Matrix<T, N, N>& Transpose(Matrix<T, N, N>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      std::swap(matrix(i, j), matrix(j, i));
    }
  }
  return matrix;
}

template <class T, size_t N>
T Trace(Matrix<T, N, N>& matrix) {
  T trace = 0;
  for (size_t i = 0; i < N; ++i) {
    trace += matrix(i, i);
  }
  return trace;
}

template <class T, size_t N>
T Determinant(Matrix<T, N, N> matrix) {
  auto determinant = T(1);
  T cur_del;
  for (size_t i = 0; i < N; ++i) {
    if (matrix(i, i) == 0) {
      size_t point_to_swap = i;
      while (point_to_swap < N && matrix(point_to_swap, i) == 0) {
        ++point_to_swap;
      }
      if (point_to_swap == N) {
        return 0;
      }
      cur_del = matrix(point_to_swap, i);
      determinant *= cur_del;
      for (size_t k = i; k < N; ++k) {
        std::swap(matrix(i, k), matrix(point_to_swap, k));
        matrix(i, k) /= cur_del;
      }
    } else {
      cur_del = matrix(i, i);
      determinant *= cur_del;
      for (size_t k = i; k < N; ++k) {
        matrix(i, k) /= cur_del;
      }
    }
    for (size_t j = i + 1; j < N; ++j) {
      if (matrix(j, i) != 0) {
        cur_del = matrix(j, i);
        determinant *= cur_del;
        for (size_t k = i; k < N; ++k) {
          matrix(j, k) /= cur_del;
          matrix(j, k) -= matrix(i, k);
        }
      }
    }
  }
  return (determinant *= matrix(N - 1, N - 1));
}

template <size_t N>
int Determinant(Matrix<int, N, N> matrix) {
  int determinant = 0;
  int cur_val = 1;
  int inv;
  auto a = new int32_t[N];
  for (size_t i = 0; i < N; ++i) {
    *(a + i) = i;
    cur_val *= matrix(i, i);
  }
  determinant += cur_val;
  while (std::next_permutation(a, a + N)) {
    inv = 0;
    cur_val = 1;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = i + 1; j < N; ++j) {
        if (*(a + j) < *(a + i)) {
          inv += 1;
        }
      }
      cur_val *= matrix(i, *(a + i));
    }
    if (inv % 2 == 1) {
      cur_val *= -1;
    }
    determinant += cur_val;
  }
  delete[] a;
  return determinant;
}

template <class T, size_t N>
Matrix<T, N, N> GetInversed(Matrix<T, N, N> matrix) {
  if (Determinant(matrix) == 0) {
    throw MatrixIsDegenerateError{};
  }
  Matrix<T, N, N> a;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      a(i, j) = T(0);
    }
    a(i, i) = T(1);
  }
  T cur_del;
  for (size_t i = 0; i < N; ++i) {
    if (matrix(i, i) == 0) {
      size_t point_to_swap = i;
      while (point_to_swap < N && matrix(point_to_swap, i) == 0) {
        ++point_to_swap;
      }
      cur_del = matrix(point_to_swap, i);
      for (size_t k = 0; k < N; ++k) {
        std::swap(matrix(i, k), matrix(point_to_swap, k));
        matrix(i, k) /= cur_del;
        std::swap(a(i, k), a(point_to_swap, k));
        a(i, k) /= cur_del;
      }
    } else {
      cur_del = matrix(i, i);
      for (size_t k = 0; k < N; ++k) {
        matrix(i, k) /= cur_del;
        a(i, k) /= cur_del;
      }
    }
    for (size_t j = i + 1; j < N; ++j) {
      if (matrix(j, i) != 0) {
        cur_del = matrix(j, i);
        for (size_t k = 0; k < N; ++k) {
          matrix(j, k) /= cur_del;
          matrix(j, k) -= matrix(i, k);
          a(j, k) /= cur_del;
          a(j, k) -= a(i, k);
        }
      }
    }
  }
  // обратно
  auto a_int = static_cast<int32_t>(N);
  for (int32_t i = a_int - 1; i >= 0; --i) {
    if (matrix(i, i) == 0) {
      int32_t point_to_swap = i;
      while (point_to_swap >= 0 && matrix(point_to_swap, i) == 0) {
        --point_to_swap;
      }
      cur_del = matrix(point_to_swap, i);
      for (int32_t k = 0; k < a_int; ++k) {
        std::swap(matrix(i, k), matrix(point_to_swap, k));
        matrix(i, k) /= cur_del;
        std::swap(a(i, k), a(point_to_swap, k));
        a(i, k) /= cur_del;
      }
    } else {
      cur_del = matrix(i, i);
      for (int32_t k = 0; k < a_int; ++k) {
        matrix(i, k) /= cur_del;
        a(i, k) /= cur_del;
      }
    }
    for (int32_t j = i - 1; j >= 0; --j) {
      if (matrix(j, i) != 0) {
        cur_del = matrix(j, i);
        for (int32_t k = 0; k < a_int; ++k) {
          matrix(j, k) /= cur_del;
          matrix(j, k) -= matrix(i, k);
          a(j, k) /= cur_del;
          a(j, k) -= a(i, k);
        }
      }
    }
  }
  return a;
}

template <class T, size_t N>
void Inverse(Matrix<T, N, N>& matrix) {
  Matrix<T, N, N> inverse = GetInversed(matrix);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix(i, j) = inverse(i, j);
    }
  }
}

#endif
