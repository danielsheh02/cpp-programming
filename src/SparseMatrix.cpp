#include "SparseVector.cpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

template <typename T> class SparseMatrix {
private:
  std::unordered_map<size_t, SparseVector<T>> rows;
  size_t numRows, numCols;

public:
  SparseMatrix(size_t numRows, size_t numCols)
      : numRows(numRows), numCols(numCols) {}

  void set(size_t row, size_t col, const T &value) {
    if (row >= numRows || col >= numCols) {
      throw std::out_of_range("Index out of range");
    }
    if (value != T(0)) {
      if (rows[row].size == 0) {
        rows[row] = SparseVector<T>(numCols);
      }
      rows[row].set(col, value);
    }
  }

  T get(size_t row, size_t col) const {
    if (row >= numRows || col >= numCols) {
      throw std::out_of_range("Index out of range");
    }
    auto it = rows.find(row);
    return it != rows.end() ? it->second.get(col) : T(0);
  }

  SparseMatrix<T> transpose() const {
    SparseMatrix<T> result(numCols, numRows);
    for (const auto &[row, vector] : rows) {
      for (size_t col = 0; col < numCols; ++col) {
        T value = vector.get(col);
        if (value != T(0)) {
          result.set(col, row, value);
        }
      }
    }
    return result;
  }

  static SparseMatrix<T> power(SparseMatrix<T> matrix, int power) {
    SparseMatrix<int> resultPower = matrix;
    for (int i = 0; i < power - 1; i++) {
      resultPower = resultPower * matrix;
    }
    return resultPower;
  }

  SparseMatrix<T> operator+(const SparseMatrix<T> &other) const {
    if (numRows != other.numRows || numCols != other.numCols) {
      throw std::invalid_argument("Matrices must be of the same dimensions");
    }
    SparseMatrix<T> result(numRows, numCols);
    for (const auto &[row, vector] : rows) {
      for (size_t col = 0; col < numCols; ++col) {
        T value = vector.get(col) + other.get(row, col);
        result.set(row, col, value);
      }
    }
    for (const auto &[row, vector] : other.rows) {
      if (rows.find(row) == rows.end()) {
        for (size_t col = 0; col < numCols; ++col) {
          T value = vector.get(col);
          result.set(row, col, value);
        }
      }
    }
    return result;
  }

  SparseMatrix<T> operator*(const SparseMatrix<T> &other) const {
    if (numRows != other.numCols) {
      throw std::invalid_argument(
          "Number of columns of the first matrix must match the number of rows "
          "of the second matrix");
    }

    SparseMatrix<T> result(numRows, other.numCols);
    for (const auto &[row, vector] : rows) {
      for (size_t col = 0; col < other.numCols; ++col) {
        T sum = 0;
        for (size_t k = 0; k < numCols; ++k) {
          T valueA = vector.get(k);
          T valueB = other.get(k, col);
          sum += valueA * valueB;
        }
        if (sum != 0) {
          result.set(row, col, sum);
        }
      }
    }
    return result;
  }

  void print() const {
    for (size_t i = 0; i < numRows; ++i) {
      for (size_t j = 0; j < numCols; ++j) {
        std::cout << get(i, j) << " ";
      }
      std::cout << std::endl;
    }
  }
};