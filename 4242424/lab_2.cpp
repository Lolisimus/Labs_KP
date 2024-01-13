//�������� ������ ����� �9122-02.03.03��, ���� 2
#include <iostream>
#include <string>

using namespace std;

// Базовый класс "Животные"
class Animal {
protected:
    string name;

public:
    Animal(const string& name) : name(name) {}

    virtual void makeSound() const {
        cout << "The animal makes a sound.\n";
    }
};

// Промежуточный класс "Млекопитающие"
class Mammal : public Animal {
public:
    Mammal(const string& name) : Animal(name) {}

    void feed() const {
        cout << "The mammal is feeding.\n";
    }
};

// Класс "Коты" (наследуется от Mammal)
class Cat : public Mammal {
public:
    Cat(const string& name) : Mammal(name) {}

    void makeSound() const override {
        cout << "Meow!\n";
    }
};

int main() {
    // Создание объекта класса "Коты" и взаимодействие с ним
    Cat cat("Barsik");
    cat.feed();
    cat.makeSound();

    return 0;
}
