/*
The Iterator pattern is a behavioral design pattern that provides a way to sequentially access elements of a collection
(such as a list, array, or other aggregate objects) without exposing its underlying representation.
The iterator encapsulates the logic for traversing the collection, allowing the client to iterate
over the collection without needing to understand its internal structure.

Key Aspects of the Iterator Pattern:
- Iterator Interface: Defines methods for traversing elements in the collection (e.g., next(), hasNext()).
- ConcreteIterator: Implements the Iterator interface for a specific collection type.
- Aggregate Interface (or Collection Interface): Declares a method to create an iterator object.
- ConcreteAggregate: Implements the aggregate interface and provides an iterator.

Scenario:
Let's implement the iterator pattern for a collection of Books. We'll define an Iterator that allows the
client to traverse the book collection and print the details of each book.

Explanation:
- Book: This class represents the elements in the collection. Each Book object contains a title and an
  author and provides getter methods to access these details.

- Iterator (Abstract Interface): This defines the interface for iterators, with two key methods:

- hasNext(): Checks whether there are more elements in the collection.

- next(): Returns the next element and advances the iterator.

- BookIterator (ConcreteIterator): This class implements the Iterator interface for a vector of Book objects.
  It tracks the current position in the collection using the index and provides the logic to traverse through the books collection.

- BookCollection (Aggregate Interface): This is the interface for the collection that declares a method createIterator()
  to return an iterator.

- Library (ConcreteAggregate): This class represents a collection of Book objects. It allows books to be added to the
  collection and provides a method to create an iterator for traversing the book list.

- Client Code: The client creates a Library and adds several Book objects to it.
  Then, it creates an iterator using the createIterator() method.
  The client iterates through the collection using the iterator, printing out the details of each book.

Advantages of Iterator Pattern:
- Encapsulation: The iterator pattern encapsulates the details of how elements are traversed. The client code does not need to know the internal structure of the collection.
- Multiple Iterators: Multiple iterators can be created for the same collection, allowing for different types of traversal or multiple concurrent iterations.
- Supports Different Collections: The pattern provides a consistent way to iterate over different types of collections (arrays, lists, trees) without exposing the underlying data structure.

Real-World Example:
- STL Iterators in C++: The C++ Standard Template Library (STL) uses iterators extensively to provide generic ways to traverse containers like vectors, lists, and sets.
- File Systems: Many file systems provide iterators to traverse directories and files without the user having to deal with the underlying file structures directly.
- Social Media Feeds: In social media platforms, an iterator could be used to fetch posts or messages one at a time from a collection of posts or a database, abstracting how they are stored and retrieved.

Summary:
The Iterator pattern provides a standard way to traverse a collection of objects without exposing the underlying implementation. It's particularly useful for abstracting the traversal logic, making the code flexible and easy to maintain.

*/
#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Book class (elements in the collection)
class Book {
private:
    std::string title;
    std::string author;

public:
    Book(const std::string& t, const std::string& a) : title(t), author(a) {}

    // Getter methods to retrieve book details
    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }
};

// Iterator Interface (defines methods for traversing a collection)
class Iterator {
public:
    virtual bool hasNext() const = 0;  // Check if there are more elements
    virtual std::shared_ptr<Book> next() = 0;  // Return the next element
    virtual ~Iterator() = default;
};

// ConcreteIterator (implements the Iterator interface for a vector of Books)
class BookIterator : public Iterator {
private:
    const std::vector<std::shared_ptr<Book>>& books;  // Reference to the book collection
    size_t index;  // Current position in the collection

public:
    BookIterator(const std::vector<std::shared_ptr<Book>>& b) : books(b), index(0) {}

    // Check if there are more books in the collection
    bool hasNext() const override {
        return index < books.size();
    }

    // Return the next book and increment the index
    std::shared_ptr<Book> next() override {
        if (hasNext()) {
            return books[index++];
        }
        return nullptr;
    }
};

// Aggregate Interface (defines a method to create an iterator)
class BookCollection {
public:
    virtual std::unique_ptr<Iterator> createIterator() const = 0;
    virtual ~BookCollection() = default;
};

// ConcreteAggregate (implements the collection and provides an iterator)
class Library : public BookCollection {
private:
    std::vector<std::shared_ptr<Book>> books;

public:
    // Add a new book to the collection
    void addBook(const std::string& title, const std::string& author) {
        books.push_back(std::make_shared<Book>(title, author));
    }

    // Create and return an iterator for the book collection
    std::unique_ptr<Iterator> createIterator() const override {
        return std::make_unique<BookIterator>(books);
    }
};

// Client code
int main() {
    // Create a library and add some books
    Library library;
    library.addBook("The Catcher in the Rye", "J.D. Salinger");
    library.addBook("To Kill a Mockingbird", "Harper Lee");
    library.addBook("1984", "George Orwell");

    // Create an iterator for the library
    std::unique_ptr<Iterator> iterator = library.createIterator();

    // Iterate through the collection and print book details
    std::cout << "Books in the library:\n";
    while (iterator->hasNext()) {
        std::shared_ptr<Book> book = iterator->next();
        std::cout << "Title: " << book->getTitle() << ", Author: " << book->getAuthor() << std::endl;
    }

    return 0;
}
