/*
The State pattern is a behavioral design pattern that allows an object to alter its behavior when its internal state changes.
The object will appear to change its class. The State pattern encapsulates state-specific behavior in separate state classes,
enabling the object to transition between states and change its behavior accordingly.

Key Aspects of the State Pattern:
- Context: Maintains an instance of a State subclass and delegates state-specific behavior to it.
- State (Interface): Defines an interface for encapsulating the behavior associated with a particular state.
- ConcreteState: Implements state-specific behavior for a particular state of the Context.

Scenario:
Let’s implement a state machine for a TCP connection. The TCP connection can be in different states, such as Closed,
Listening, Established, and Closed. Each state has its own behavior for handling events like opening, closing, and receiving data.

Explanation:
- State Interface: This defines the methods open(), close(), sendData(), and receiveData() that all concrete
  state classes must implement. These methods represent actions that can be performed in different states.

- TCPConnection (Context): This class maintains a reference to a State object and delegates state-specific behavior
  to the current state. It allows state transitions by changing the state object.

Concrete States:

- ClosedState: Represents the state when the connection is closed. It handles the behavior for actions in this state
  (e.g., cannot send or receive data).
- ListeningState: Represents the state when the connection is listening for incoming connections.
  It handles actions appropriate for this state and can transition to the EstablishedState.
- EstablishedState: Represents the state when the connection is established and active.
  It handles actions like sending and receiving data and can transition to the ClosedState.
- Client Code: The client creates instances of different states and a TCPConnection.
  It demonstrates how the TCPConnection can transition between states and how behavior changes based on the current state.

Advantages of the State Pattern:
- Encapsulation of State-Specific Behavior: Each state is encapsulated in its own class, making it easier to manage
  and extend behavior for each state.
- State Transitions: The pattern allows for complex state transitions and changes in behavior without modifying the
  client code or the state classes themselves.
- Improved Maintainability: Adding new states or modifying existing ones is straightforward because each state is
  handled independently.

Real-World Example:
- Media Players: Media players often have different states such as Playing, Paused, and Stopped.
  The behavior of the media player changes based on its current state.
- Order Processing Systems: In e-commerce systems, an order might go through states like Pending, Shipped, and Delivered.
  Each state has different processing logic and transitions.

Summary:
The State pattern helps manage state-specific behavior and transitions by encapsulating state-related logic in separate classes.
It provides a flexible way to handle different states and transitions, promoting cleaner and more maintainable code.

*/
#include <iostream>
#include <memory>

// State Interface
class State {
public:
    virtual void open() = 0;      // Method to transition to the "Open" state
    virtual void close() = 0;     // Method to transition to the "Closed" state
    virtual void sendData(const std::string& data) = 0;  // Method to handle data sending
    virtual void receiveData(const std::string& data) = 0;  // Method to handle data reception
    virtual ~State() = default;
};

// Context (TCPConnection)
class TCPConnection {
private:
    std::shared_ptr<State> state;  // Current state of the TCP connection

public:
    TCPConnection(std::shared_ptr<State> initialState) : state(initialState) {}

    void setState(std::shared_ptr<State> newState) {
        state = newState;
    }

    void open() {
        state->open();
    }

    void close() {
        state->close();
    }

    void sendData(const std::string& data) {
        state->sendData(data);
    }

    void receiveData(const std::string& data) {
        state->receiveData(data);
    }
};

// ConcreteState: Closed
class ClosedState : public State {
public:
    void open() override {
        std::cout << "Transitioning from Closed to Listening state." << std::endl;
        // Transition to Listening state
    }

    void close() override {
        std::cout << "Already in Closed state." << std::endl;
    }

    void sendData(const std::string& data) override {
        std::cout << "Cannot send data. Connection is closed." << std::endl;
    }

    void receiveData(const std::string& data) override {
        std::cout << "Cannot receive data. Connection is closed." << std::endl;
    }
};

// ConcreteState: Listening
class ListeningState : public State {
public:
    void open() override {
        std::cout << "Already in Listening state." << std::endl;
    }

    void close() override {
        std::cout << "Transitioning from Listening to Closed state." << std::endl;
        // Transition to Closed state
    }

    void sendData(const std::string& data) override {
        std::cout << "Cannot send data. Connection is in Listening state." << std::endl;
    }

    void receiveData(const std::string& data) override {
        std::cout << "Transitioning from Listening to Established state." << std::endl;
        // Transition to Established state
    }
};

// ConcreteState: Established
class EstablishedState : public State {
public:
    void open() override {
        std::cout << "Already in Established state." << std::endl;
    }

    void close() override {
        std::cout << "Transitioning from Established to Closed state." << std::endl;
        // Transition to Closed state
    }

    void sendData(const std::string& data) override {
        std::cout << "Sending data: " << data << std::endl;
    }

    void receiveData(const std::string& data) override {
        std::cout << "Receiving data: " << data << std::endl;
    }
};

// Client code
int main() {
    // Create states
    std::shared_ptr<State> closedState = std::make_shared<ClosedState>();
    std::shared_ptr<State> listeningState = std::make_shared<ListeningState>();
    std::shared_ptr<State> establishedState = std::make_shared<EstablishedState>();

    // Create a TCP connection in the Closed state
    TCPConnection connection(closedState);

    // Try to send and receive data in the Closed state
    connection.sendData("Hello");
    connection.receiveData("Hi");

    // Transition to Listening state
    connection.setState(listeningState);
    connection.receiveData("Hello");

    // Transition to Established state
    connection.setState(establishedState);
    connection.sendData("Hello");
    connection.receiveData("Hi");

    // Transition to Closed state
    connection.close();

    return 0;
}
