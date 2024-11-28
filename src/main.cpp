#include "Number.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <vector>

// Функция для печати значений поля number в векторе
template <typename Container>
void printContainer(const Container &container,
                    const std::string &containerName) {
  std::cout << "\n";
  std::cout << containerName << " contains: ";
  for (const auto &element : container) {
    std::cout << element.number << " ";
  }
  std::cout << std::endl;
}

// Функция для печати пар (для контейнеров типа list<std::pair>)
template <typename PairContainer>
void printPairContainer(const PairContainer &container,
                        const std::string &containerName) {
  std::cout << "\n";
  std::cout << containerName << " contains pairs: ";
  for (const auto &pair : container) {
    std::cout << "(" << pair.first.number << ", " << pair.second.number << ") ";
  }
  std::cout << std::endl;
}

int main() {
  // 1. Создание вектора v1 с элементами Number
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist_size(500, 1000);
  std::uniform_int_distribution<> dist_value(1, 999);

  int size_v1 = dist_size(gen);
  std::vector<Number> v1;
  v1.reserve(size_v1);
  std::generate_n(std::back_inserter(v1), size_v1,
                  [&]() { return Number(dist_value(gen)); });
  printContainer(v1, "v1");
  std::cout << "v1 size: " << v1.size() << std::endl;

  // 2. Создание вектора v2 из последних 200 элементов вектора v1
  int b = size_v1 - 200;
  int e = size_v1;
  std::vector<Number> v2(v1.begin() + b, v1.begin() + e);
  printContainer(v2, "v2");
  std::cout << "v2 size: " << v2.size() << std::endl;

  // 3. Создание списка list1 из n наибольших элементов вектора v1
  int n = std::uniform_int_distribution<>(20, 50)(gen);
  std::vector<Number> temp_vector1(n);
  std::partial_sort_copy(
      v1.begin(), v1.end(), temp_vector1.begin(), temp_vector1.end(),
      [](const Number &a, const Number &b) { return a.number > b.number; });
  temp_vector1.resize(n);
  std::list<Number> list1(temp_vector1.begin(), temp_vector1.end());
  printContainer(list1, "list1");
  std::cout << "list1 size: " << list1.size() << std::endl;

  // 4. Создание списка list2 из n наименьших элементов вектора v2
  std::vector<Number> temp_vector2(n);
  std::partial_sort_copy(
      v2.begin(), v2.end(), temp_vector2.begin(), temp_vector2.end(),
      [](const Number &a, const Number &b) { return a.number < b.number; });
  temp_vector2.resize(n);
  std::list<Number> list2(temp_vector2.begin(), temp_vector2.end());
  printContainer(list2, "list2");
  std::cout << "list2 size: " << list2.size() << std::endl;

  // 5. Удаление перемещенных элементов из v1 и v2
  auto remove_from_vector = [](std::vector<Number> &vec,
                               const std::list<Number> &list) {
    for (const auto &el : list) {
      vec.erase(std::remove_if(
                    vec.begin(), vec.end(),
                    [&](const Number &num) { return num.number == el.number; }),
                vec.end());
    }
  };
  remove_from_vector(v1, list1);
  remove_from_vector(v2, list2);
  printContainer(v1, "v1 after removal");
  std::cout << "v1 size after removal: " << v1.size() << std::endl;
  printContainer(v2, "v2 after removal");
  std::cout << "v2 size after removal: " << v2.size() << std::endl;

  // 6. Перегруппировка list1 по среднему значению
  int sum = std::accumulate(
      list1.begin(), list1.end(), 0,
      [](int acc, const Number &num) { return acc + num.number; });
  int avg = sum / list1.size();
  list1.sort([avg](const Number &a, const Number &b) {
    return (a.number > avg) && (b.number <= avg);
  });
  printContainer(list1, "list1 after regrouping");
  std::cout << "average for list1: " << avg << std::endl;

  // 7. Удаление нечетных элементов из list2
  list2.remove_if([](const Number &num) { return num.number % 2 != 0; });
  printContainer(list2, "list2 after removing odd numbers");
  std::cout << "list2 size after removing odd numbers: " << list2.size()
            << std::endl;

  // 8. Создание вектора v3 из пересечения v1 и v2
  std::vector<Number> v3;
  std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        std::back_inserter(v3));
  printContainer(v3, "v3");

  // 9. Выравнивание размеров list1 и list2 и создание list3
  if (list1.size() > list2.size()) {
    auto it = list1.begin();
    std::advance(it, list1.size() - list2.size());
    list1.erase(list1.begin(), it);
  } else if (list2.size() > list1.size()) {
    auto it = list2.begin();
    std::advance(it, list2.size() - list1.size());
    list2.erase(list2.begin(), it);
  }
  std::list<std::pair<Number, Number>> list3;
  auto it1 = list1.begin(), it2 = list2.begin();
  while (it1 != list1.end() && it2 != list2.end()) {
    list3.emplace_back(*it1++, *it2++);
  }
  printPairContainer(list3, "list3");
  std::cout << "list3 size: " << list3.size() << std::endl;

  // 10. Создание списка пар из векторов v1 и v2 без выравнивания размеров
  std::list<std::pair<Number, Number>> list_pairs;
  auto v1_it = v1.begin();
  auto v2_it = v2.begin();
  while (v1_it != v1.end() && v2_it != v2.end()) {
    list_pairs.emplace_back(*v1_it++, *v2_it++);
  }
  printPairContainer(list_pairs, "list_pairs");
  std::cout << "list_pairs size: " << list_pairs.size() << std::endl;

  return 0;
}
