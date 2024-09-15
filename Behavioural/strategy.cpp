/*
The Strategy pattern is a behavioral design pattern that defines a family of algorithms, encapsulates each one,
and makes them interchangeable. The Strategy pattern allows a client to choose an algorithm from a family of
algorithms at runtime without altering the code that uses the algorithm.
This pattern promotes the use of composition over inheritance, enabling you to select and switch algorithms dynamically.

Key Aspects of the Strategy Pattern:
- Strategy (Interface): Defines a common interface for all supported algorithms.
- ConcreteStrategy: Implements specific algorithms or behaviors following the Strategy interface.
- Context: Maintains a reference to a Strategy object and allows switching between different strategies.

Scenario:
Let's implement a payment system where users can choose different payment methods (e.g., credit card, PayPal) at runtime.
The PaymentStrategy interface will define a method for processing payments,
and different concrete strategies will implement the actual payment processing.
The PaymentContext class will use the selected strategy to process payments.

Explanation:
- PaymentStrategy (Strategy Interface): This interface declares a pay() method, which all concrete payment strategies
  must implement. This method processes payments.

- CreditCardPayment (ConcreteStrategy): Implements the PaymentStrategy interface for credit card payments.
  It processes payments using the provided credit card details.

- PayPalPayment (ConcreteStrategy): Implements the PaymentStrategy interface for PayPal payments.
  It processes payments using the provided PayPal email address.

- PaymentContext (Context): This class uses a PaymentStrategy object to process payments.
  It allows setting a new strategy dynamically with setStrategy() and uses the current strategy to
  process payments with processPayment().

- Client Code: The client creates instances of CreditCardPayment and PayPalPayment, and a PaymentContext.
  It sets different strategies in the PaymentContext and processes payments using the selected strategy.

Advantages of the Strategy Pattern:
- Flexibility: The pattern allows you to change the algorithm or behavior at runtime without modifying the client code.
- Encapsulation: Each strategy is encapsulated in its own class, adhering to the Single Responsibility Principle.
  Changes to one strategy do not affect others.
- Reusability: Strategies can be reused across different contexts or scenarios, making the code more modular and maintainable.

Real-World Example:
- Sorting Algorithms: In a software application where different sorting algorithms (e.g., quicksort, mergesort)
  can be chosen dynamically, the Strategy pattern allows the user to select and apply different sorting strategies
  without altering the code that uses them.
- Text Formatting: In a text editor, different formatting strategies (e.g., bold, italic, underline) can be applied
  to text dynamically using the Strategy pattern.

Summary:
The Strategy pattern is useful for scenarios where you need to switch between different algorithms or behaviors dynamically.
By encapsulating each algorithm in its own class and providing a common interface, the Strategy pattern promotes flexibility,
encapsulation, and reusability, allowing the client to select and change strategies at runtime.

*/
#include <iostream>
#include <memory>
#include <string>

// Strategy Interface
class PaymentStrategy {
public:
    virtual void pay(float amount) const = 0;  // Method to process payment
    virtual ~PaymentStrategy() = default;
};

// ConcreteStrategy 1: CreditCardPayment
class CreditCardPayment : public PaymentStrategy {
private:
    std::string cardNumber;
    std::string cardHolder;

public:
    CreditCardPayment(const std::string& number, const std::string& holder)
        : cardNumber(number), cardHolder(holder) {}

    void pay(float amount) const override {
        std::cout << "Processing credit card payment of $" << amount
                  << " for card holder " << cardHolder << " with card number "
                  << cardNumber << "." << std::endl;
    }
};

// ConcreteStrategy 2: PayPalPayment
class PayPalPayment : public PaymentStrategy {
private:
    std::string email;

public:
    PayPalPayment(const std::string& emailAddress) : email(emailAddress) {}

    void pay(float amount) const override {
        std::cout << "Processing PayPal payment of $" << amount
                  << " for email address " << email << "." << std::endl;
    }
};

// Context: Uses the Strategy to process payments
class PaymentContext {
private:
    std::shared_ptr<PaymentStrategy> strategy;  // Strategy object

public:
    // Set the payment strategy
    void setStrategy(std::shared_ptr<PaymentStrategy> newStrategy) {
        strategy = newStrategy;
    }

    // Process payment using the current strategy
    void processPayment(float amount) const {
        if (strategy) {
            strategy->pay(amount);
        } else {
            std::cout << "No payment strategy set!" << std::endl;
        }
    }
};

// Client code
int main() {
    // Create payment strategies
    std::shared_ptr<PaymentStrategy> creditCard = std::make_shared<CreditCardPayment>("1234-5678-9876-5432", "John Doe");
    std::shared_ptr<PaymentStrategy> payPal = std::make_shared<PayPalPayment>("john.doe@example.com");

    // Create a PaymentContext
    PaymentContext paymentContext;

    // Set CreditCardPayment strategy and process payment
    paymentContext.setStrategy(creditCard);
    paymentContext.processPayment(100.0f);

    // Set PayPalPayment strategy and process payment
    paymentContext.setStrategy(payPal);
    paymentContext.processPayment(200.0f);

    return 0;
}
