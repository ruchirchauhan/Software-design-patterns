/*
The Prototype pattern is a creational design pattern that allows you to create new objects by copying an existing object,
known as the prototype, instead of creating new instances from scratch.
This pattern is useful when the cost of creating a new object is high,
or when you want to maintain the state of an existing object and create multiple clones of it.

Key Aspects of the Prototype Pattern:
- Prototype Interface: Declares a clone() method that will be implemented by concrete classes.
- ConcretePrototype: Implements the clone() method, allowing objects to be copied.
- Client: The client that requests a copy of the object via the prototype interface.

Scenario:
Imagine a system where we need to create different types of shapes (e.g., circles, squares)
with various properties like color and size. Instead of creating each shape from scratch,
we can clone a prototype shape and modify its properties as needed.

Explanation:
- Shape (Prototype Interface): This is the abstract base class that defines the clone() method.
  Each concrete shape class (e.g., Circle, Square) will implement this method to create a copy of itself.

- Circle and Square (ConcretePrototypes): These are concrete implementations of the Shape interface.
  They each define the clone() method, which returns a copy of the object using the copy constructor (*this).
  They also have a draw() method to display their properties and a setColor() method to modify their color after cloning.

- Client Code: In the main function, an original Circle and Square are created.
  Then, these objects are cloned using the clone() method. The cloned objects' colors are modified to
  demonstrate that they are independent copies of the original objects.
  Finally, both the original and cloned shapes are drawn to show their different properties.

Advantages of Prototype Pattern:
- Cloning Complex Objects: It is useful when creating a new object is a costly operation.
  Instead of creating new instances, you clone existing objects and modify them as needed.
- Avoids Subclassing Explosion: You don’t need to create subclasses for every possible object variation.
  Instead, you can clone and modify prototypes dynamically.
- Reduced Object Creation Time: If an object initialization involves a lot of computation or resource loading
  (e.g., large datasets), cloning existing objects is much faster.

Real-World Example:
- Game Development: In many games, character objects with different attributes (like weapons, armor, etc.) are created
  by cloning a prototype and modifying it. For example, an enemy prototype with default properties can be cloned to
  create multiple enemies with slight variations.
- Document Editing Software: When a user creates a new document based on a template, the system often clones a prototype
  document and modifies its content according to the user's preferences.

*/
#include <iostream>
#include <memory>  // For smart pointers
#include <string>

// Prototype interface (declares the clone method)
class Shape {
public:
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// ConcretePrototype: Circle
class Circle : public Shape {
private:
    int radius;
    std::string color;

public:
    Circle(int r, const std::string& c) : radius(r), color(c) {}

    // Implement the clone method
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);  // Copy itself
    }

    // Method to draw the shape (just for demonstration)
    void draw() const override {
        std::cout << "Drawing a " << color << " circle with radius " << radius << std::endl;
    }

    // Method to set a new color (after cloning)
    void setColor(const std::string& newColor) {
        color = newColor;
    }
};

// ConcretePrototype: Square
class Square : public Shape {
private:
    int side;
    std::string color;

public:
    Square(int s, const std::string& c) : side(s), color(c) {}

    // Implement the clone method
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Square>(*this);  // Copy itself
    }

    // Method to draw the shape
    void draw() const override {
        std::cout << "Drawing a " << color << " square with side " << side << std::endl;
    }

    // Method to set a new color (after cloning)
    void setColor(const std::string& newColor) {
        color = newColor;
    }
};

// Client code
int main() {
    // Create a prototype circle and square
    std::unique_ptr<Shape> originalCircle = std::make_unique<Circle>(10, "Red");
    std::unique_ptr<Shape> originalSquare = std::make_unique<Square>(5, "Blue");

    // Clone the circle and square
    std::unique_ptr<Shape> clonedCircle = originalCircle->clone();
    std::unique_ptr<Shape> clonedSquare = originalSquare->clone();

    // Modify the cloned shapes (to demonstrate they are independent objects)
    dynamic_cast<Circle*>(clonedCircle.get())->setColor("Green");
    dynamic_cast<Square*>(clonedSquare.get())->setColor("Yellow");

    // Draw the original and cloned shapes
    std::cout << "Original shapes:" << std::endl;
    originalCircle->draw();  // Should be red
    originalSquare->draw();  // Should be blue

    std::cout << "\nCloned and modified shapes:" << std::endl;
    clonedCircle->draw();  // Should be green
    clonedSquare->draw();  // Should be yellow

    return 0;
}
