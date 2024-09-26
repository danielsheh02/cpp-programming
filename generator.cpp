#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Открываем файл для чтения типов данных и операций
    ifstream fin("config.txt");

    // Открываем файл для записи сгенерированной функции
    ofstream fout("func_generated.cpp");

    // Проверка на успешное открытие файла
    if (!fin.is_open() || !fout.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        return 1;
    }

    // Начало программы
    fout << "#include <iostream>" << endl;
    fout << "using namespace std;" << endl;

    // Включаем необходимые заголовочные файлы
    fout << "#include <random>" << std::endl;
    fout << "#include <type_traits>" << std::endl;
    fout << std::endl;

    // Объявление глобальных переменных
    fout << "const int GLOBAL_MIN = 0;" << std::endl;
    fout << "const int GLOBAL_MAX = 100;" << std::endl;
    fout << std::endl;

    // Начало шаблонной функции
    fout << "template<typename T>" << std::endl;
    fout << "T generateRandomNumber() {" << std::endl;
    
    // Объявление генератора случайных чисел
    fout << "    std::random_device rd;" << std::endl;
    fout << "    std::mt19937 gen(rd());" << std::endl;
    fout << std::endl;

    // Условие для целочисленных типов
    fout << "    if constexpr (std::is_integral<T>::value) {" << std::endl;
    fout << "        std::uniform_int_distribution<T> dist(GLOBAL_MIN, GLOBAL_MAX);" << std::endl;
    fout << "        return dist(gen);" << std::endl;
    fout << "    }" << std::endl;
    
    // Условие для типов с плавающей точкой
    fout << "    else if constexpr (std::is_floating_point<T>::value) {" << std::endl;
    fout << "        std::uniform_real_distribution<T> dist(GLOBAL_MIN, GLOBAL_MAX);" << std::endl;
    fout << "        return dist(gen);" << std::endl;
    fout << "    }" << std::endl;
    fout << "}" << std::endl;

    fout << std::endl;

    fout << "int f(void) {" << endl;
    fout << "    try {" << endl;
    string type1, type2, operation;

    int i = 1;
    int i_result = 1;
    // Чтение файла по три строки: два типа данных и операция
    while (fin >> type1 >> type2 >> operation) {
        // Объявление и инициализация переменных
        fout << "        " << type1 << " var" << i << " = " << "generateRandomNumber<" << type1 << ">()" << ";" << endl;
        fout << "        " << type2 << " var" << i + 1 << " = " << "generateRandomNumber<" << type2 << ">()" << ";" << endl;
        // Если производится деление необходимо проверить делитель на 0
        if (operation == "/") {
            fout << "        if (var" << i + 1 << " == 0) {" << endl;
            fout << "            throw std::invalid_argument(\"Деление на ноль!\");" << endl;
            fout << "        }" << endl;
        }
        // Выполнение арифметической операции
        fout << "        auto result" << i_result << " = var" << i << " " << operation << " var" << i + 1 << ";" << endl;
        fout << "        cout << \"Результат: \" << result" << i_result << " << endl;" << endl;
        i = i + 2;
        i_result++;
    }

    // Завершение функции
    fout << "        return 0;" << endl;
    fout << "    }" << endl;
    fout << "    catch (const std::invalid_argument& e) {" << endl;
    fout << "        std::cerr << \"Ошибка: \" << e.what() << std::endl;" << endl;
    fout << "        return -1;" << endl;
    fout << "    }" << endl;
    fout << "}" << endl;

    // Закрытие файлов
    fin.close();
    fout.close();

    cout << "Программа успешно сгенерирована в файле func_generated.cpp" << endl;
    return 0;
}
