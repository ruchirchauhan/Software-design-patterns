/*
The Singleton design pattern ensures that a class has only one instance and provides a global point of access to that instance.

Key Aspects of Singleton Pattern:
- Private Constructor: Prevents other classes from creating new instances.
- Static Method: Provides a way to get the sole instance of the class.
- Static Instance: The single instance is stored as a static member variable.

Explanation:
- static Singleton* instance: A static pointer to store the single instance of the class. It's initialized to nullptr.
- Private Constructor: The constructor is private to prevent creating objects from outside the class.
- static Singleton* getInstance(): A static method that checks if the instance exists. If it doesn't, it creates one. If it does, it returns the existing instance.
- Copy Prevention: The copy constructor and assignment operator are deleted to prevent copying the Singleton instance.
*/
#include <iostream>

class Singleton {
private:
    // Private static instance of the class (single instance)
    static Singleton* instance;

    // Private constructor to prevent instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

public:
    // Public static method to provide access to the instance
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    // Example method to demonstrate functionality
    void showMessage() {
        std::cout << "Hello from the Singleton instance!\n";
    }

    // Delete copy constructor and assignment operator to prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

// Initialize the static instance pointer to nullptr
Singleton* Singleton::instance = nullptr;

int main() {
    // Get the single instance of the Singleton class
    Singleton* singleton1 = Singleton::getInstance();
    singleton1->showMessage();

    // Attempting to get another instance will return the same instance
    Singleton* singleton2 = Singleton::getInstance();
    singleton2->showMessage();

    // Both pointers point to the same instance
    if (singleton1 == singleton2) {
        std::cout << "Both variables point to the same Singleton instance.\n";
    }

    return 0;
}
