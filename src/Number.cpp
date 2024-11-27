#include "Number.h"

std::string Number::numberToText(int number) {
    if (number < 0 || number > 999) {
        return "Out of range";
    }

    const std::string units[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const std::string teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const std::string tens[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    std::string result;

    if (number >= 100) {
        int hundred = number / 100;
        result += units[hundred] + " hundred";
        number %= 100;

        if (number != 0) {
            result += " ";
        }
    }

    if (number >= 10 && number < 20) {
        result += teens[number - 10];
    } else if (number >= 20) {
        int ten = number / 10;
        result += tens[ten - 2];
        int unit = number % 10;

        if (unit != 0) {
            result += " " + units[unit];
        }
    } else if (number > 0) {
        result += units[number];
    } else if (result.empty()) {
        result = units[0];
    }

    return result;
}


Number::Number(int num) {
    id = ++counter;
    std::cout << "Сonstructor id = " << id << std::endl;
    number = num;
    str = new std::string(numberToText(num));
}

Number::Number(const Number& other) {
    id = ++counter;
    std::cout << "Copy constructor id = " << id << std::endl;
    number = other.number;
    str = new std::string(*other.str);
    std::cout << "Copy " << other.id << " to " << id << std::endl;
}

Number::Number(Number&& other) noexcept {
    id = ++counter;
    std::cout << "Move constructor id = " << id << std::endl;
    number = other.number;
    str = other.str;
    other.str = nullptr;
    std::cout << "Move " << other.id << " to " << id << std::endl;
}

Number& Number::operator=(const Number& other) {
    std::cout << "Copy assignment operator" << std::endl;
    if (this != &other) {
        delete str;
        number = other.number;
        str = new std::string(*other.str);
    }
    return *this;
}

Number& Number::operator=(Number&& other) noexcept {
    std::cout << "Move assignment operator" << std::endl;
    if (this != &other){
        delete str;
        number = other.number;
        str = other.str;
        other.str = nullptr;
    }
    return *this;
}

Number::~Number() {
    delete str;
    std::cout << "Destructor id = " << id << std::endl;
}

void Number::display() const {
    std::cout << "Number: " << number << ", Text: " << *str << std::endl;
}
