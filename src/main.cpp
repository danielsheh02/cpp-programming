#include "SparseMatrix.cpp"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<int> multiplyMatrices(const std::vector<int> &matA,
                                  const std::vector<int> &matB, int rowsA,
                                  int colsA, int colsB) {
  if (rowsA != colsB) {
    throw std::invalid_argument("Matrices must be of the same dimensions");
  }
  std::vector<int> result(rowsA * colsB, 0);

  for (int i = 0; i < rowsA; ++i) {
    for (int j = 0; j < colsB; ++j) {
      for (int k = 0; k < colsA; ++k) {
        result[i * colsB + j] += matA[i * colsA + k] * matB[k * colsB + j];
      }
    }
  }

  return result;
}

void printMatrix(const std::vector<int> &mat, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << mat[i * cols + j] << " ";
    }
    std::cout << std::endl;
  }
}

std::pair<SparseMatrix<int>, std::vector<int>> generateBigMatrix(int numRows,
                                                                 int numCols) {
  SparseMatrix<int> matSparse(numRows, numCols);
  std::vector<int> matVector(numRows * numCols, 0);
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {

      int value = (std::rand() % 10 == 0) ? (std::rand() % 100) : 0;
      matSparse.set(i, j, value);
      matVector[i * numCols + j] = value;
    }
  }
  return {matSparse, matVector};
}

int main() {
  SparseVector<int> vec(5);
  vec.set(1, 10);
  vec.set(3, 20);
  std::cout << "vec: ";
  vec.print();

  std::cout << "------------\n";

  SparseVector<int> vec2(5);
  vec2.set(1, 5);
  vec2.set(2, 15);
  std::cout << "vec2: ";
  vec2.print();

  std::cout << "------------\n";

  SparseVector<int> vecSum = vec + vec2;
  std::cout << "sum vec + vec2: ";
  vecSum.print();
  std::cout << "------------\n";

  std::cout << "dot vec * vec2: " << vec.dot(vec2) << std::endl;
  std::cout << "------------\n";

  SparseVector<int> vecMult = vec * 5;
  std::cout << "vec * 5: ";
  vecMult.print();
  std::cout << "------------\n";

  SparseMatrix<int> mat(3, 3);
  mat.set(0, 1, 5);
  mat.set(1, 2, 10);
  std::cout << "mat: \n";
  mat.print();
  std::cout << "------------\n";

  SparseMatrix<int> matT = mat.transpose();
  std::cout << "transpose matT: \n";
  matT.print();
  std::cout << "------------\n";

  SparseMatrix<int> matSum = mat + matT;
  std::cout << "sum mat + matT: \n";
  matSum.print();
  std::cout << "------------\n";

  SparseMatrix<int> matMult = mat * matSum;
  std::cout << "mult mat * matT: \n";

  matMult.print();
  std::cout << "------------\n";
  int power = 2;
  SparseMatrix<int> resultPower = SparseMatrix<int>::power(matMult, power);

  std::cout << "power " << power << " of matPower: \n";
  resultPower.print();
  std::cout << "------------\n";
  int sizeBigMat = 200;
  auto [bigSparseMat, bigVectorMat] = generateBigMatrix(sizeBigMat, sizeBigMat);

  auto start = std::chrono::high_resolution_clock::now();
  SparseMatrix<int> bigMatMult = bigSparseMat * bigSparseMat;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  // bigMatMult.print();
  std::cout << "Time mult big sparse matrices size of " << sizeBigMat << ": "
            << duration.count() << " ms" << std::endl;
  std::cout << "------------\n";

  start = std::chrono::high_resolution_clock::now();
  std::vector<int> result = multiplyMatrices(
      bigVectorMat, bigVectorMat, sizeBigMat, sizeBigMat, sizeBigMat);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  // printMatrix(result, sizeBigMat, sizeBigMat);
  std::cout << "Time mult big vector matrices size of " << sizeBigMat << ": "
            << duration.count() << " ms" << std::endl;
  return 0;
}
