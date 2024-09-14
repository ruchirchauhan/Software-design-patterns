/*
The Factory Method design pattern is a creational design pattern that provides an interface for creating objects,
but allows subclasses to alter the type of objects that will be created.
It is useful when the exact type of object required cannot be determined until runtime or when different subclasses
need to create different types of objects.

Key Aspects of the Factory Method Pattern:
- Creator (Factory): Declares the factory method that returns an object of a Product type.
  Subclasses override this method to return specific product types.
- Product: Defines the interface of objects the factory method creates.
- ConcreteProduct: Implements the Product interface.
- ConcreteCreator: Overrides the factory method to create a specific ConcreteProduct.

Scenario:
We'll create a factory that produces different types of vehicles like Car and Bike.

Explanation:
- Vehicle (Product Interface): This is an abstract base class for the products that the factory will create, such as Car and Bike.
  It defines a common interface (showDetails()) that all vehicles must implement.

- Car and Bike (Concrete Products): These are specific products created by the factory.
  Both Car and Bike inherit from Vehicle and implement the showDetails() method.

- VehicleFactory (Creator Interface): This is the abstract base class that declares the factory method (createVehicle())
  to produce vehicles. It is overridden by concrete factories to instantiate specific vehicles.

- CarFactory and BikeFactory (Concrete Creators): These are specific factories that override the createVehicle() method
  to create and return instances of Car and Bike, respectively.

- Client (Main Function): The client creates instances of CarFactory and BikeFactory, uses them
  to create Car and Bike objects, and calls the showDetails() method on these objects.

Advantages of Factory Method Pattern:
- Decoupling: The client code doesn't need to know which class to instantiate.
  It works with an interface and relies on the factory to create the actual objects.

- Flexibility: You can add new product types (e.g., Truck, Bus) without modifying the client code,
  simply by adding new factories.

*/
#include <iostream>
#include <memory>  // For using smart pointers

// The Product interface
class Vehicle {
public:
    virtual void showDetails() const = 0;  // Pure virtual method
    virtual ~Vehicle() = default;  // Virtual destructor
};

// ConcreteProduct: Car
class Car : public Vehicle {
public:
    void showDetails() const override {
        std::cout << "This is a Car." << std::endl;
    }
};

// ConcreteProduct: Bike
class Bike : public Vehicle {
public:
    void showDetails() const override {
        std::cout << "This is a Bike." << std::endl;
    }
};

// The Creator (Factory) interface
class VehicleFactory {
public:
    // Factory method to create vehicles (pure virtual)
    virtual std::unique_ptr<Vehicle> createVehicle() const = 0;
    virtual ~VehicleFactory() = default;
};

// ConcreteCreator: CarFactory
class CarFactory : public VehicleFactory {
public:
    std::unique_ptr<Vehicle> createVehicle() const override {
        return std::make_unique<Car>();  // Return a Car instance
    }
};

// ConcreteCreator: BikeFactory
class BikeFactory : public VehicleFactory {
public:
    std::unique_ptr<Vehicle> createVehicle() const override {
        return std::make_unique<Bike>();  // Return a Bike instance
    }
};

int main() {
    // Create a Car factory
    std::unique_ptr<VehicleFactory> carFactory = std::make_unique<CarFactory>();
    // Use the factory to create a Car
    std::unique_ptr<Vehicle> car = carFactory->createVehicle();
    car->showDetails();  // Output: This is a Car.

    // Create a Bike factory
    std::unique_ptr<VehicleFactory> bikeFactory = std::make_unique<BikeFactory>();
    // Use the factory to create a Bike
    std::unique_ptr<Vehicle> bike = bikeFactory->createVehicle();
    bike->showDetails();  // Output: This is a Bike.

    return 0;
}


/*
Example of Extending the Pattern:
If you want to add a Truck, you would:

- Create a Truck class that inherits from Vehicle.
- Create a TruckFactory class that inherits from VehicleFactory and implements the createVehicle() method.
*/
// ConcreteProduct: Truck
class Truck : public Vehicle {
public:
    void showDetails() const override {
        std::cout << "This is a Truck." << std::endl;
    }
};

// ConcreteCreator: TruckFactory
class TruckFactory : public VehicleFactory {
public:
    std::unique_ptr<Vehicle> createVehicle() const override {
        return std::make_unique<Truck>();  // Return a Truck instance
    }
};
