/*
The Decorator pattern is a structural design pattern that allows behavior to be added to an individual object, dynamically,
without affecting the behavior of other objects from the same class.
This pattern is useful when you want to extend the functionalities of a class without modifying the existing code.

Key Aspects of the Decorator Pattern:
- Component (Interface or Abstract Class): Defines the interface for objects that can have responsibilities added dynamically.
- ConcreteComponent: The class to which additional responsibilities can be added.
- Decorator (Abstract Class): Wraps the ConcreteComponent and implements the same interface so that it can add behavior.
- ConcreteDecorator: Adds new behavior or responsibilities to the ConcreteComponent.

Scenario:
We'll create a basic Coffee class that can be "decorated" with different add-ons like Milk and Sugar to dynamically
extend its functionality.

Explanation:
- Coffee (Component Interface): This is the abstract interface for all coffee objects.
  It has two methods: getDescription() to get the description of the coffee and cost() to get the cost.

- SimpleCoffee (ConcreteComponent): This class represents the basic coffee without any add-ons.
  It returns a description of "Simple Coffee" and a base cost of $5.00.

- CoffeeDecorator (Decorator): This is an abstract class that implements the Coffee interface and
  holds a reference to a Coffee object. The CoffeeDecorator passes method calls to the wrapped object and
  can be extended to add new functionality.

- MilkDecorator (ConcreteDecorator): This class extends CoffeeDecorator and adds the functionality of "milk" to the coffee.
  It appends ", Milk" to the description and adds $1.00 to the cost.

- SugarDecorator (ConcreteDecorator): This class extends CoffeeDecorator and adds "sugar" to the coffee.
  It appends ", Sugar" to the description and adds $0.50 to the cost.

- Client Code: In the main function, a SimpleCoffee is created first. Then, the coffee is wrapped with a MilkDecorator to add milk,
  and then a SugarDecorator to add sugar.

Advantages of Decorator Pattern:
- Open for Extension, Closed for Modification: You can add new functionalities to an object without altering its structure.
  You don't need to modify the existing classes to add new behaviors.
- Flexible Combinations: You can mix and match decorators dynamically at runtime, allowing multiple combinations of behavior.
- Lightweight: Each decorator adds only the specific functionality, avoiding the need for subclassing to achieve similar results.

Real-World Example:
Text Editing: In a text editor, decorators might be used to add functionality like bold, italic, and underline to text.
Instead of creating a new class for every combination of bold, italic, and underline,
you can use decorators to apply these styles dynamically.

*/
#include <iostream>
#include <string>
#include <memory>  // For smart pointers

// Component interface
class Coffee {
public:
    virtual std::string getDescription() const = 0;  // To get the description of the coffee
    virtual double cost() const = 0;  // To get the cost of the coffee
    virtual ~Coffee() = default;  // Virtual destructor
};

// ConcreteComponent: Basic coffee without any add-ons
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }

    double cost() const override {
        return 5.0;  // Base cost of the coffee
    }
};

// Decorator abstract class (must implement the Coffee interface)
class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;  // Pointer to the wrapped component

public:
    CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee(std::move(coffee)) {}

    virtual std::string getDescription() const override {
        return coffee->getDescription();
    }

    virtual double cost() const override {
        return coffee->cost();
    }
};

// ConcreteDecorator: Adding Milk to the coffee
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double cost() const override {
        return coffee->cost() + 1.0;  // Adding the cost of milk
    }
};

// ConcreteDecorator: Adding Sugar to the coffee
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double cost() const override {
        return coffee->cost() + 0.5;  // Adding the cost of sugar
    }
};

// Client code
int main() {
    // Create a Simple Coffee
    std::unique_ptr<Coffee> myCoffee = std::make_unique<SimpleCoffee>();
    std::cout << "Description: " << myCoffee->getDescription() << std::endl;
    std::cout << "Cost: $" << myCoffee->cost() << std::endl;

    // Add Milk to the coffee
    myCoffee = std::make_unique<MilkDecorator>(std::move(myCoffee));
    std::cout << "Description: " << myCoffee->getDescription() << std::endl;
    std::cout << "Cost: $" << myCoffee->cost() << std::endl;

    // Add Sugar to the coffee (after Milk)
    myCoffee = std::make_unique<SugarDecorator>(std::move(myCoffee));
    std::cout << "Description: " << myCoffee->getDescription() << std::endl;
    std::cout << "Cost: $" << myCoffee->cost() << std::endl;

    return 0;
}
