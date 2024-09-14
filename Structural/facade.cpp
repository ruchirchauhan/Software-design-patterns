/*
The Facade pattern is a structural design pattern that provides a simplified interface to a complex subsystem or set of classes.
This pattern hides the complexity of the system and makes it easier for the client to interact with it by
offering a unified and simple interface.

Key Aspects of the Facade Pattern:
- Facade Class: Provides a simplified interface to the subsystem.
- Subsystem Classes: These are the complex classes that the Facade interacts with. The client is shielded from their complexity.
- Client: The client interacts only with the Facade and is unaware of the subsystem’s complexity.

Scenario:
Let's assume we have a Home Theater System with various components like a DVD Player, Projector, and Sound System.
The user wants to watch a movie, but controlling each component individually can be complex.
The Facade will simplify the process.

Explanation:
- Subsystem Classes (DVDPlayer, Projector, SoundSystem): These classes represent the complex components of the home theater system.
  Each class has methods that control the component (e.g., turning it on/off, setting modes, playing media).

- HomeTheaterFacade (Facade Class): This class provides a simplified interface for the client to interact with the
  home theater system. Instead of having to control each component individually,
  the client can simply call watchMovie() to set everything up and endMovie() to turn everything off.

- Client: In the main function, the client only interacts with the HomeTheaterFacade, unaware of the complexity of the subsystems.

Advantages of Facade Pattern:
- Simplification: It simplifies the interaction with a complex system by providing a unified, easy-to-use interface.
- Decoupling: The client code is decoupled from the subsystems, meaning the subsystems can change without affecting the client.
- Ease of Use: Facade makes complex subsystems easier to use for clients who don't need the full flexibility of
  the underlying system.

Real-World Example:
Operating System Facade: When you click "shutdown" on your computer, the operating system (facade)
interacts with various subsystems like file systems, memory management, and hardware controllers to
gracefully shut down the computer. The user doesn't need to know about these subsystems.

*/
#include <iostream>
#include <string>

// Subsystem class: DVD Player
class DVDPlayer {
public:
    void on() {
        std::cout << "DVD Player is ON." << std::endl;
    }

    void play(const std::string& movie) {
        std::cout << "Playing movie: " << movie << std::endl;
    }

    void off() {
        std::cout << "DVD Player is OFF." << std::endl;
    }
};

// Subsystem class: Projector
class Projector {
public:
    void on() {
        std::cout << "Projector is ON." << std::endl;
    }

    void setWideScreenMode() {
        std::cout << "Projector set to widescreen mode." << std::endl;
    }

    void off() {
        std::cout << "Projector is OFF." << std::endl;
    }
};

// Subsystem class: Sound System
class SoundSystem {
public:
    void on() {
        std::cout << "Sound System is ON." << std::endl;
    }

    void setSurroundSound() {
        std::cout << "Sound System set to surround sound." << std::endl;
    }

    void off() {
        std::cout << "Sound System is OFF." << std::endl;
    }
};

// The Facade class: Home Theater Facade
class HomeTheaterFacade {
private:
    DVDPlayer* dvdPlayer;
    Projector* projector;
    SoundSystem* soundSystem;

public:
    HomeTheaterFacade(DVDPlayer* dvd, Projector* proj, SoundSystem* sound)
        : dvdPlayer(dvd), projector(proj), soundSystem(sound) {}

    // Simplified method to watch a movie
    void watchMovie(const std::string& movie) {
        std::cout << "Setting up the home theater to watch a movie...\n";
        projector->on();
        projector->setWideScreenMode();

        soundSystem->on();
        soundSystem->setSurroundSound();

        dvdPlayer->on();
        dvdPlayer->play(movie);
    }

    // Simplified method to end the movie
    void endMovie() {
        std::cout << "Shutting down the home theater...\n";
        dvdPlayer->off();
        soundSystem->off();
        projector->off();
    }
};

// Client code
int main() {
    // Create subsystem components
    DVDPlayer dvd;
    Projector projector;
    SoundSystem soundSystem;

    // Create a facade to simplify the interaction
    HomeTheaterFacade homeTheater(&dvd, &projector, &soundSystem);

    // Use the facade to watch a movie
    homeTheater.watchMovie("Inception");

    // After watching the movie, turn everything off
    homeTheater.endMovie();

    return 0;
}
