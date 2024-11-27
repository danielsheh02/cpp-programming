#pragma once
#include <string>
#include <iostream>

class Number {
public:
    int number;
    std::string* str;

    Number(int num);

    Number(const Number& other);

    Number(Number&& other) noexcept;

    Number& operator=(const Number& other);

    Number& operator=(Number&& other) noexcept;

    ~Number();

    std::string numberToText(int num);
    
    void display() const;

    unsigned id;

    static inline unsigned counter{};
};
