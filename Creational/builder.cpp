/*
The Builder design pattern is used to construct a complex object step by step.
The pattern allows the construction process to be separated from the object’s actual representation.
This is useful when an object can be created in many ways or involves multiple steps.

Key Aspects of the Builder Pattern:
- Builder Class: Defines how to construct different parts of the object.
- Product Class: Represents the complex object that is being built.
- Director Class (optional): Controls the construction process (though it can be omitted if the client controls the process).

Scenario:
We'll build a "House" that can have different components like windows, doors, and rooms.

Explanation:
- House (Product): Represents the object that is being built, i.e., the house.
  It has methods to set different components like windows, doors, and rooms.

- HouseBuilder (Abstract Builder): Declares the interface for creating parts of the House object.
  It ensures that each step (like building windows, doors, rooms) is defined,
  but it's up to concrete builders to implement those steps.

- ConcreteHouseBuilder (Concrete Builder): Implements the steps for creating specific parts of the House.
  In this case, it defines how to build the windows, doors, and rooms of the house.

- Director (optional): Controls the construction process. It can specify the order in which parts of the object are built.

- Client (Main Function): The client creates a ConcreteHouseBuilder and uses the Director to control the building process.
  After construction, the client retrieves the House and displays its properties.
*/
#include <iostream>
#include <string>

// The Product class: represents the complex object to be built
class House {
private:
    std::string windows;
    std::string doors;
    std::string rooms;

public:
    void setWindows(const std::string& windows) {
        this->windows = windows;
    }

    void setDoors(const std::string& doors) {
        this->doors = doors;
    }

    void setRooms(const std::string& rooms) {
        this->rooms = rooms;
    }

    void showHouse() const {
        std::cout << "House with: " << windows << ", " << doors << ", " << rooms << std::endl;
    }
};

// The Builder class: provides an interface to build parts of the object
class HouseBuilder {
protected:
    House* house;  // The product being built

public:
    HouseBuilder() {
        house = new House();
    }

    virtual ~HouseBuilder() {
        delete house;
    }

    House* getHouse() {
        return house;
    }

    virtual void buildWindows() = 0;
    virtual void buildDoors() = 0;
    virtual void buildRooms() = 0;
};

// A concrete builder: implements the steps defined in the builder interface
class ConcreteHouseBuilder : public HouseBuilder {
public:
    void buildWindows() override {
        house->setWindows("4 large windows");
    }

    void buildDoors() override {
        house->setDoors("2 wooden doors");
    }

    void buildRooms() override {
        house->setRooms("3 spacious rooms");
    }
};

// The Director class: controls the building process (optional)
class Director {
private:
    HouseBuilder* builder;

public:
    void setBuilder(HouseBuilder* builder) {
        this->builder = builder;
    }

    // Directs the builder to construct the house step by step
    void constructHouse() {
        builder->buildWindows();
        builder->buildDoors();
        builder->buildRooms();
    }
};

// Example to build it with director
void buildWithDirector() {
    // Create the builder and director
    ConcreteHouseBuilder builder;
    Director director;

    // Set the builder in the director and construct the house
    director.setBuilder(&builder);
    director.constructHouse();

    // Retrieve and display the constructed house
    House* house = builder.getHouse();
    house->showHouse();

}

// Example to build it without director
void buildWithoutDirector() {
    // Create the builder
    ConcreteHouseBuilder builder;

    // Manually control the building process
    builder.buildWindows();
    builder.buildDoors();
    builder.buildRooms();

    // Retrieve and display the constructed house
    House* house = builder.getHouse();
    house->showHouse();

}

int main() {

    buildWithDirector();
    buildWithoutDirector();


    return 0;
}
