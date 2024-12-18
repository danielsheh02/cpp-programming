MAIN = main
SRCS = main.cpp SparseVector.cpp SparseMatrix.cpp # Указываем все файлы с исходным кодом
OBJS = $(SRCS:.cpp=.o)     # Создаем список объектных файлов

# Компилятор и его флаги
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17  # Включаем все предупреждения и используем стандарт C++17

# Правила для сборки
all: run_main

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Линковка объектных файлов
$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(MAIN)

# Запуск программы
run_main: $(MAIN)
	./$(MAIN)

# Очистка собранных файлов
clean:
	rm -f $(MAIN) $(OBJS)
