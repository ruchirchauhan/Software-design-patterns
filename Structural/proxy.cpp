/*
The Proxy pattern is a structural design pattern that provides a surrogate or placeholder for another object to
control access to it. This is useful when you want to add an extra layer between the client and the actual
object to control access, lazy load resources, manage expensive operations, or add security checks.

Key Aspects of the Proxy Pattern:
- Subject (Interface): The common interface between the Real Object and the Proxy.
- RealSubject (Real Object): The actual object that the proxy represents or controls access to.
- Proxy: Controls access to the RealSubject. It can perform lazy initialization, access control,
  or logging before delegating the request to the RealSubject.

Types of Proxy:
- Virtual Proxy: Manages the creation and initialization of expensive objects on demand.
- Protection Proxy: Controls access to the real object based on permissions or security.
- Remote Proxy: Acts as a local representative for an object that exists in a different address space or server.
- Logging Proxy: Logs requests or actions before passing them to the real object.

Scenario:
We will implement a Virtual Proxy where a Large Image class represents an expensive object (such as loading an image from disk),
and the proxy will control when the image is actually loaded and displayed.
The proxy delays the loading of the image until it is needed.

Explanation:
- Image (Subject Interface): This is the abstract interface for both the RealImage and the ProxyImage.
  It declares the display() method that both classes must implement.

- RealImage (Real Subject): This class simulates an expensive object, like an image that is loaded from the disk.
  The constructor simulates the cost of loading an image, and the display() method simulates showing the image.

- ProxyImage (Proxy): The proxy class holds a reference to a RealImage, but it delays its instantiation until
  it's actually needed (lazy initialization). When display() is called on the proxy, it checks if the RealImage has been created;
  if not, it creates it and delegates the display() call to the real object.

- Client Code: In the main function, a ProxyImage is created with a file name. Initially, the real image is not loaded.
  When the client requests to display() the image, the proxy checks if the RealImage is already loaded.
  If not, it loads it and then displays it. Subsequent calls to display() do not reload the image.

Advantages of Proxy Pattern:
- Lazy Initialization: The proxy pattern can delay the creation of expensive objects until they are actually needed,
  improving performance.
- Access Control: The proxy can be used to control access to the real object, adding an additional layer of
  security or permission checking.
- Logging or Monitoring: The proxy can log actions or monitor interactions with the real object.
- Remote Representation: A proxy can act as a local representative for an object that exists remotely
  (e.g., in a distributed system).

Real-World Example:
- Virtual Proxy in GUI Systems: In graphical user interfaces (GUIs), when displaying large or high-resolution images,
  it’s common to use a proxy to delay the loading of images until they are actually needed
  (e.g., until they are scrolled into view).
- Database Connection Proxies: In applications where establishing a database connection is expensive,
  proxies are used to delay or pool connections, opening them only when necessary.
- Web Service Proxy: A proxy can represent an object located on a remote server, handling network communication and
  ensuring the client interacts with the server as though it were local.

Summary:
The Proxy pattern provides a surrogate or placeholder for another object to control access to it,
useful for scenarios where resource management, lazy loading, or access control is important.

*/
#include <iostream>
#include <memory>
#include <string>

// Subject interface (common interface between RealImage and Proxy)
class Image {
public:
    virtual void display() const = 0;  // Abstract display method
    virtual ~Image() = default;
};

// RealSubject: Represents the actual large image that is costly to load
class RealImage : public Image {
private:
    std::string filename;

    // Method to load the image from disk (expensive operation)
    void loadImageFromDisk() const {
        std::cout << "Loading image from disk: " << filename << std::endl;
    }

public:
    // Constructor which "loads" the image (simulated)
    RealImage(const std::string& file) : filename(file) {
        loadImageFromDisk();  // Simulate loading the image during construction
    }

    // Display the image (after it's loaded)
    void display() const override {
        std::cout << "Displaying image: " << filename << std::endl;
    }
};

// Proxy: Controls access to the RealImage
class ProxyImage : public Image {
private:
    std::string filename;
    mutable std::unique_ptr<RealImage> realImage;  // Delayed initialization of RealImage

public:
    // Constructor with the filename
    ProxyImage(const std::string& file) : filename(file), realImage(nullptr) {}

    // Display the image (load it if it's not already loaded)
    void display() const override {
        if (!realImage) {
            // If the real image is not loaded yet, load it
            realImage = std::make_unique<RealImage>(filename);
        }
        realImage->display();  // Delegate the display call to RealImage
    }
};

// Client code
int main() {
    // Create a proxy image (the real image is not loaded yet)
    std::unique_ptr<Image> image = std::make_unique<ProxyImage>("high_resolution_image.jpg");

    // First display (this will trigger the real image to load)
    std::cout << "First display:\n";
    image->display();

    // Second display (the image is already loaded, so no need to load it again)
    std::cout << "\nSecond display:\n";
    image->display();

    return 0;
}
