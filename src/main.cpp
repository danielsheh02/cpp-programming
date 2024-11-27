#include "Number.cpp"
#include <list>
#include <vector>

void processByValue(Number obj) { obj.display(); }

void processByReference(const Number &obj) { obj.display(); }

Number createInstance(int num) {
  Number obj(num);
  return obj;
}

int main() {
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== Static Instance ===" << std::endl;
    Number obj(765);
    obj.display();
  }
  std::cout << "----------------------------------" << std::endl;

  {
    std::cout << "=== Dynamic Instance ===" << std::endl;
    Number *obj = new Number(20);
    obj->display();
    delete obj;
  }
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== Static Instance ===" << std::endl;
    Number obj(10);

    std::cout << "\n=== Passing by Value ===" << std::endl;
    processByValue(obj);

    std::cout << "\n=== Passing by Reference ===" << std::endl;
    processByReference(obj);
  }
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== Returning by Value ===\n" << std::endl;
    Number returnObj = createInstance(30);
    returnObj.display();
  }
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== Static Instance ===" << std::endl;
    Number obj(10);

    std::cout << "\n=== Copy constructor ===" << std::endl;
    Number obj2{obj};
  }
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== Static Instance ===" << std::endl;
    Number obj(10);

    std::cout << "\n=== Move constructor ===" << std::endl;
    Number obj2{std::move(obj)};
  }
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== Static Instance ===" << std::endl;
    Number obj(10);
    Number obj2(11);
    Number obj3(12);

    std::cout << "\n=== Assign ===" << std::endl;
    obj = obj2;

    std::cout << "\n=== Assign with move ===" << std::endl;
    obj = std::move(obj3);
  }
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== Vector push by rvalue ===" << std::endl;
    std::vector<Number> myVector;
    for (int i = 1; i <= 5; i++) {
      std::cout << "-----DO PUSH BACK " << i << "-----" << std::endl;
      myVector.push_back(Number{i});
      std::cout << "-----DO PUSH BACK " << i << "-----\n" << std::endl;
    }
  }
  std::cout << "----------------------------------" << std::endl;
  {
    std::cout << "=== List push by rvalue ===\n" << std::endl;
    std::list<Number> myList;
    for (int i = 1; i <= 5; i++) {
      std::cout << "-----DO PUSH BACK " << i << "-----" << std::endl;
      myList.push_back(Number{i});
      std::cout << "-----DO PUSH BACK " << i << "-----\n" << std::endl;
    }
  }

  return 0;
}
