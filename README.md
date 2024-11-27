# Отчет по лабораторной работе task-2

Данный код демонстрирует основные аспекты работы с конструкторами, операторами присваивания, а также взаимодействие со стандартными контейнерами `std::vector` и `std::list` в C++. В логах отображаются вызовы конструкторов и деструкторов, что позволяет отслеживать, как объекты перемещаются и копируются в процессе выполнения программы. Рассмотрим каждый этап подробнее.

## Описание программы с соответствующими логами из консоли:

1. _Статический экземпляр_
    ```cpp
    std::cout << "=== Static Instance ===" << std::endl;
    Number obj(765);
    obj.display();
    ```
    **Вызов конструктора:** Создается объект obj с числом 765.  
    **Вывод:** Отображается значение и текст, соответствующие числу.  
    **Деструктор:** После завершения блока деструктор вызывается для очистки ресурса.  

    Лог:

        Сonstructor id = 1  
        Number: 765, Text: seven hundred sixty five  
        Destructor id = 1  

2. _Динамический экземпляр_
    ```cpp
    std::cout << "=== Dynamic Instance ===" << std::endl;
    Number *obj = new Number(20);
    obj->display();
    delete obj;
    ```
    **Вызов конструктора:** Создается объект в динамической памяти.  
    **Вывод:** Отображается значение 20.  
    **Деструктор:** Удаление объекта из памяти приводит к вызову деструктора.  

    Лог:

        Сonstructor id = 2  
        Number: 20, Text: twenty  
        Destructor id = 2  

3. _Передача по значению_
    ```cpp
    std::cout << "\n=== Passing by Value ===" << std::endl;
    processByValue(obj);
    ```
    **Вызов конструктора копирования:** Объект передается по значению, создается копия.  
    **Вывод:** Отображение значения копии.  
    **Деструктор:** Деструктор вызывается для копии после выхода из функции.  

    Лог:

        Copy constructor id = 4  
        Copy 3 to 4  
        Number: 10, Text: ten  
        Destructor id = 4  

4. _Передача по ссылке_
    ```cpp
    std::cout << "\n=== Passing by Reference ===" << std::endl;
    processByReference(obj);
    ```
    **Нет копирования:** Объект передается по ссылке, копирование не происходит.  
    **Вывод:** Отображение значения оригинала.  
    **Деструктор:** Вызывается только деструктор оригинального объекта.  

    Лог:

        Number: 10, Text: ten  
        Destructor id = 3  

5. _Возврат объекта по значению_
    ```cpp
    std::cout << "=== Returning by Value ===\n" << std::endl;
    Number returnObj = createInstance(30);
    returnObj.display();
    ```
    **Вызов конструктора:** Создается объект внутри функции.  
    **Вывод:** Отображается значение объекта, который вернули.  

    Лог:

        Сonstructor id = 5  
        Number: 30, Text: thirty  
        Destructor id = 5  

6. _Конструктор копирования_
    ```cpp
    std::cout << "\n=== Copy constructor ===" << std::endl;
    Number obj2{obj};
    ```
    **Вызов конструктора копирования:** Создается новый объект obj2 как копия obj.  

    Лог:

        Сonstructor id = 6  
        Copy constructor id = 7  
        Copy 6 to 7  
        Destructor id = 7  
        Destructor id = 6  

7. _Конструктор перемещения_
    ```cpp
    std::cout << "\n=== Move constructor ===" << std::endl;
    Number obj2{std::move(obj)};
    ```
    
    **Вызов конструктора перемещения:** Перемещение obj в obj2.  

    Лог:

        Сonstructor id = 8  
        Move constructor id = 9  
        Move 8 to 9  
        Destructor id = 9  
        Destructor id = 8  

8. _Операторы присваивания_
    ```cpp
    std::cout << "\n=== Assign ===" << std::endl;
    obj = obj2;
    ```
    Лог:

        Copy assignment operator 
        
    **Оператор присваивания:** Копирование obj2 в obj.  
    ```cpp
    std::cout << "\n=== Assign with move ===" << std::endl;
    obj = std::move(obj3);
    ```

    **Оператор присваивания с перемещением:** Перемещение obj3 в obj.  

    Лог:

        Move assignment operator  
        Destructor id = 12  
        Destructor id = 11  
        Destructor id = 10  

9. _Работа с `std::vector`_
    ```cpp
    std::cout << "=== Vector push by rvalue ===" << std::endl;
    std::vector<Number> myVector;
    for (int i = 1; i <= 5; i++) {
        myVector.push_back(Number {i});
    }
    ```

    **Вызов конструктора:** Создание временного объекта при `push_back`.  
    **Вызов конструктора перемещения:** Перемещение временного объекта в вектор.  
    **Деструктор:** Удаление временного объекта.  

    Лог:

        Сonstructor id = 13  
        Move constructor id = 14  
        Move 13 to 14  
        Destructor id = 13  
        ...  
        Сonstructor id = 15
        Move constructor id = 16
        Move 15 to 16
        Move constructor id = 17
        Move 14 to 17
        Destructor id = 14
        Destructor id = 15

    В процессе работы вектора временные объекты создаются и перемещаются, кроме того объекты, которые уже находились в векторе при добавлении новых элементов тоже перемещаются и удаляются. 

10. _Работа с `std::list`_
    ```cpp
    std::cout << "=== List push by rvalue ===\n" << std::endl;
    std::list<Number> myList;
    for (int i = 1; i <= 5; i++) {
        myList.push_back(Number {i});
    }
    ```

    **Вызов конструктора:** Создание временного объекта при `push_back`.  
    **Вызов конструктора перемещения:** Перемещение временного объекта в список.  
    **Деструктор:** Удаление временного объекта.  

    Лог:

        Сonstructor id = 30  
        Move constructor id = 31  
        Move 30 to 31  
        Destructor id = 30  
        ...  
        Сonstructor id = 32
        Move constructor id = 33
        Move 32 to 33
        Destructor id = 32

    Список требует перемещения объектов только один раз при добавлении, в отличие от вектора, где перемещение происходит для всех ранее добавленных объектов в связи с изменением размера контейнера.  

## Дополнительно:
 Для создания объектов `Number` используется функция [`numberToText`](https://github.com/danielsheh02/cpp-programming/blob/task-2/src/Number.cpp#L3), которая переводит числа, переданные в конструктор, в текстовое представление.

## Заключение:

В коде демонстрируются ключевые концепции работы с функциями конструкторов, операциями перемещения и копирования, а также особенности работы с динамическими структурами данных, такими как векторы и списки. Логи демонстрируют, как на практике происходят вызовы конструкторов и деструкторов, что помогает наглядно понять управление памятью.
