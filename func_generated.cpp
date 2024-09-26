#include <iostream>
using namespace std;
#include <random>
#include <type_traits>

const int GLOBAL_MIN = 0;
const int GLOBAL_MAX = 100;

template<typename T>
T generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dist(GLOBAL_MIN, GLOBAL_MAX);
        return dist(gen);
    }
    else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dist(GLOBAL_MIN, GLOBAL_MAX);
        return dist(gen);
    }
}

int f(void) {
    try {
        int var1 = generateRandomNumber<int>();
        int var2 = generateRandomNumber<int>();
        auto result1 = var1 + var2;
        cout << "Результат: " << result1 << endl;
        long var3 = generateRandomNumber<long>();
        long var4 = generateRandomNumber<long>();
        auto result2 = var3 - var4;
        cout << "Результат: " << result2 << endl;
        float var5 = generateRandomNumber<float>();
        float var6 = generateRandomNumber<float>();
        auto result3 = var5 * var6;
        cout << "Результат: " << result3 << endl;
        double var7 = generateRandomNumber<double>();
        double var8 = generateRandomNumber<double>();
        if (var8 == 0) {
            throw std::invalid_argument("Деление на ноль!");
        }
        auto result4 = var7 / var8;
        cout << "Результат: " << result4 << endl;
        int var9 = generateRandomNumber<int>();
        int var10 = generateRandomNumber<int>();
        if (var10 == 0) {
            throw std::invalid_argument("Деление на ноль!");
        }
        auto result5 = var9 / var10;
        cout << "Результат: " << result5 << endl;
        return 0;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return -1;
    }
}
