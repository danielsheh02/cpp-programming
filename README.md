# Отчет по лабораторной работе task-4

## Введение
Разреженная матрица была реализована с использованием разреженных векторов, которые хранятся в строках матрицы. Каждый разреженный вектор представлен в виде хеш-таблицы, где ключом является индекс элемента, а значением — значение элемента. Нули не хранятся, что позволяет экономить память при работе с разреженными данными.

## Реализованный функционал

### Операции с векторами
1. **Сложение векторов**
    ```cpp
    SparseVector<T> operator+(const SparseVector<T> &other) const {
    if (size != other.size) {
      throw std::invalid_argument("Vectors must be of the same size");
    }
    SparseVector<T> result(size);
    for (const auto &[index, value] : data) {
      result.set(index, value + other.get(index));
    }
    for (const auto &[index, value] : other.data) {
      if (data.find(index) == data.end()) {
        result.set(index, value);
      }
    }
    return result;
    }
    ```
   - Результат сложения двух разреженных векторов:
     ```
     vec: 0 10 0 20 0
     ------------
     vec2: 0 5 15 0 0
     ------------
     sum vec + vec2: 0 15 15 20 0
     ```

2. **Скалярное произведение векторов**
    ```cpp
    T dot(const SparseVector<T> &other) const {
        if (size != other.size) {
        throw std::invalid_argument("Vectors must be of the same size");
        }
        T result = T(0);
        for (const auto &[index, value] : data) {
        result += value * other.get(index);
        }
        return result;
    }
    ```
   - Результат скалярного произведения:
     ```
     dot vec * vec2: 50
     ```

3. **Умножение вектора на число**
    ```cpp
    SparseVector<T> operator*(const T &scalar) const {
        SparseVector<T> result(size);
        for (const auto &[index, value] : data) {
        result.set(index, value * scalar);
        }
        return result;
    }
    ```
   - Результат умножения вектора на число:
     ```
     vec * 5: 0 50 0 100 0
     ```

### Операции с матрицами
1. **Сложение матриц**
    ```cpp
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
    ```
   - Пример сложения матрицы с её транспонированной версией:
     ```
     mat:
     0 5 0
     0 0 10
     0 0 0
     ------------
     transpose matT:
     0 0 0
     5 0 0
     0 10 0
     ------------
     sum mat + matT:
     0 5 0
     5 0 10
     0 10 0
     ```

2. **Произведение матриц**
    ```cpp
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
    ```
   - Результат умножения матриц:
     ```
     mult mat * matT:
     25 0 50
     0 100 0
     0 0 0
     ```

3. **Возведение матрицы в степень**
    ```cpp
    static SparseMatrix<T> power(SparseMatrix<T> matrix, int power) {
        SparseMatrix<int> resultPower = matrix;
        for (int i = 0; i < power - 1; i++) {
        resultPower = resultPower * matrix;
        }
        return resultPower;
    }
    ```
   - Пример возведения матрицы в степень 2:
     ```
     power 2 of matPower:
     625 0 1250
     0 10000 0
     0 0 0
     ```

### Сравнение производительности
Было проведено сравнение производительности умножения больших матриц размером 200x200. Сравнивались две структуры:
1. Матрицы, которые хранятся в виде обычных векторов с нулями.
2. Разреженные матрицы, где данные представлены в виде разреженных векторов с использованием хеш-таблиц.

Результаты:
- Разреженные матрицы:
  ```
  Time mult big sparse matrices size of 200: 2806 ms
  ```
- Обычные матрицы:
  ```
  Time mult big vector matrices size of 200: 61 ms
  ```

Вывод: умножение плотных матриц значительно быстрее, так как в разреженной структуре данных происходит поиск по ключу в хеш-таблице, что замедляет операцию. Однако разреженные матрицы выигрывают по памяти, так как не хранят нулевые элементы.

## Заключение
В данной работе была реализована структура разреженной матрицы и набор операций над ней. Основные преимущества заключаются в экономии памяти, особенно при работе с сильно разреженными данными. Однако операции с разреженными матрицами требуют больше времени из-за накладных расходов на поиск данных в хеш-таблице. Сравнение с плотными матрицами продемонстрировало значительный разрыв в скорости выполнения операций при работе с большими матрицами.
