#include <cmath>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

template <typename T> class SparseVector {
private:
  std::unordered_map<size_t, T> data;

public:
  size_t size;
  SparseVector(size_t size) : size(size) {}

  SparseVector() : size(0) {}

  void set(size_t index, const T &value) {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }
    if (value != T(0)) {
      data[index] = value;
    }
  }

  T get(size_t index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }
    auto it = data.find(index);
    return it != data.end() ? it->second : T(0);
  }

  size_t getSize() const { return size; }

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

  SparseVector<T> operator*(const T &scalar) const {
    SparseVector<T> result(size);
    for (const auto &[index, value] : data) {
      result.set(index, value * scalar);
    }
    return result;
  }

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

  void print() const {
    for (size_t i = 0; i < size; ++i) {
      std::cout << get(i) << " ";
    }
    std::cout << std::endl;
  }
};