/*
The Observer pattern is a behavioral design pattern that defines a one-to-many relationship between objects,
where when one object (the Subject) changes its state, all of its dependent objects (the Observers) are notified
and updated automatically. This pattern is useful for implementing distributed event handling systems,
where one event (a change in the subject) triggers multiple reactions from dependent objects.

Key Aspects of the Observer Pattern:
- Subject (Observable): Maintains a list of observers and provides methods to add, remove, and notify them.
- Observer: Defines an interface for objects that should be notified of changes in the subject.
- ConcreteSubject: Implements the Subject interface and tracks its state. When the state changes, it notifies all the observers.
- ConcreteObserver: Implements the Observer interface and updates itself when the subject's state changes.

Scenario:
Let's implement an example where a WeatherStation acts as the subject. It tracks temperature changes.
Two observers, a PhoneDisplay and a WindowDisplay, will react to the temperature changes and display
the updated temperature when it changes.

Explanation:
- Observer Interface: This defines the update() method, which will be called by the subject when its state changes.
  Every observer must implement this method.

- Subject Interface: This declares methods for adding, removing, and notifying observers
  (addObserver(), removeObserver(), notifyObservers()).

- WeatherStation (ConcreteSubject): This class holds the temperature (state) and maintains a list of observers.
  When the temperature changes (via setTemperature()), it calls notifyObservers(), which loops through the list
  of observers and calls their update() method with the new temperature.

- PhoneDisplay and WindowDisplay (ConcreteObservers): These are concrete implementations of the Observer interface.
  They define the update() method, which is triggered when the subject changes its state.
  In this case, they simply print out the new temperature to simulate a display updating.

- Client Code: The client creates a WeatherStation object (subject) and registers two observers (PhoneDisplay and WindowDisplay).
  When the WeatherStation changes its temperature, both observers are notified, and they display the updated temperature.

Advantages of the Observer Pattern:
- Loose Coupling: The subject and observers are loosely coupled. The subject does not need to know the details of its observers.
  It only needs to call the update() method on them.
- Dynamic Subscription: Observers can be added or removed dynamically at runtime, allowing flexibility in how the system behaves.
- Centralized Change Notification: When the state of the subject changes, all registered observers are notified automatically.
  This centralizes the notification mechanism.

Real-World Example:
- User Interface Event Systems: In many graphical user interface (GUI) systems, widgets such as buttons and text fields
  act as subjects. When a user interacts with them (e.g., clicking a button), all registered listeners (observers) are
  notified of the event.
- Publish-Subscribe Systems: In pub-sub systems like messaging frameworks (e.g., MQTT, RabbitMQ), clients (subscribers)
  register with a message broker (subject) to receive notifications when a new message (event) is published to a topic.

Summary:
The Observer pattern is a powerful pattern for implementing distributed event-handling systems.
It promotes loose coupling between the subject and its observers, enabling dynamic addition and removal of observers,
and ensuring that when the subject's state changes, all observers are notified and can react accordingly.

*/
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Observer Interface
class Observer {
public:
    virtual void update(float temperature) = 0;  // Update method to be called when subject's state changes
    virtual ~Observer() = default;
};

// Subject Interface (Observable)
class Subject {
public:
    virtual void addObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

// ConcreteSubject (WeatherStation)
class WeatherStation : public Subject {
private:
    float temperature;  // Current temperature (the state)
    std::vector<std::shared_ptr<Observer>> observers;  // List of observers

public:
    // Add an observer to the list
    void addObserver(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    // Remove an observer from the list
    void removeObserver(std::shared_ptr<Observer> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Notify all observers of the state change
    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(temperature);
        }
    }

    // Change the temperature and notify the observers
    void setTemperature(float newTemperature) {
        std::cout << "WeatherStation: New temperature is " << newTemperature << " degrees." << std::endl;
        temperature = newTemperature;
        notifyObservers();  // Notify all observers of the change
    }
};

// ConcreteObserver (PhoneDisplay)
class PhoneDisplay : public Observer {
public:
    void update(float temperature) override {
        std::cout << "PhoneDisplay: The temperature is now " << temperature << " degrees." << std::endl;
    }
};

// ConcreteObserver (WindowDisplay)
class WindowDisplay : public Observer {
public:
    void update(float temperature) override {
        std::cout << "WindowDisplay: The temperature is now " << temperature << " degrees." << std::endl;
    }
};

// Client code
int main() {
    // Create a WeatherStation (the subject)
    std::shared_ptr<WeatherStation> weatherStation = std::make_shared<WeatherStation>();

    // Create some displays (observers)
    std::shared_ptr<Observer> phoneDisplay = std::make_shared<PhoneDisplay>();
    std::shared_ptr<Observer> windowDisplay = std::make_shared<WindowDisplay>();

    // Register the observers with the WeatherStation
    weatherStation->addObserver(phoneDisplay);
    weatherStation->addObserver(windowDisplay);

    // Simulate a temperature change (this should notify the observers)
    weatherStation->setTemperature(25.0f);

    // Simulate another temperature change
    weatherStation->setTemperature(30.0f);

    return 0;
}
