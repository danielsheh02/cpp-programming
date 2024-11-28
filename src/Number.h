#pragma once
#include <iostream>
#include <string>

class Number {
public:
  int number;
  std::string *str;

  Number(int num);

  Number();

  Number(const Number &other);

  Number(Number &&other) noexcept;

  Number &operator=(const Number &other);

  Number &operator=(Number &&other) noexcept;

  bool operator<(const Number &other) const;

  bool operator==(const Number &other) const;

  ~Number();

  std::string numberToText(int num);

  void display() const;

  unsigned id;

  static inline unsigned counter{};
};
