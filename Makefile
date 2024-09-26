# Makefile для сборки и запуска generator и main

# Названия файлов
GENERATOR = generator
MAIN = main

# Компилятор и его флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17  # Включаем все предупреждения и используем стандарт C++17

# Правила для сборки
all: run_generator run_main

# Правило для генератора
$(GENERATOR): generator.cpp
	$(CXX) $(CXXFLAGS) generator.cpp -o $(GENERATOR)

run_generator: $(GENERATOR)
	./$(GENERATOR)

# Правило для основной программы
$(MAIN): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(MAIN)

run_main: $(MAIN)
	./$(MAIN)

# Очистка собранных файлов
clean:
	rm -f $(GENERATOR) $(MAIN)
