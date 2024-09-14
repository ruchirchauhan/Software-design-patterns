/*
The Adapter pattern is a structural design pattern that allows objects with incompatible interfaces to work together.
The Adapter acts as a bridge between two incompatible interfaces by converting one interface into another that the client expects.

Key Aspects of the Adapter Pattern:
- Client: The class that uses the Target interface.
- Target: The interface expected by the client.
- Adaptee: The class with an incompatible interface that needs to be adapted.
- Adapter: The class that implements the Target interface and translates calls to the Adaptee.

Scenario:
Let's say we have a MediaPlayer interface that expects to play mp3 files,
but we also have a VideoPlayer class that can only play mp4 files.
We'll use an adapter to make VideoPlayer compatible with MediaPlayer.

Explanation:
- MediaPlayer (Target Interface): This is the interface that the client (AudioPlayer) expects.
  It has a playAudio() method that takes an audio type (format) and a file name.

- VideoPlayer (Adaptee): This is the existing class with an incompatible interface.
  It has a playVideo() method that only plays mp4 video files.

- MediaAdapter (Adapter): This class adapts the VideoPlayer to the MediaPlayer interface.
  It implements the playAudio() method and internally calls playVideo() from the VideoPlayer class when the
  file is in the mp4 format.

- AudioPlayer (Client): The client that uses the MediaPlayer interface.
  It can directly handle mp3 files and uses the MediaAdapter to handle mp4 files.
  If an unsupported format is passed, it outputs an error message.

Advantages of Adapter Pattern:
- Decoupling: The client code (AudioPlayer) doesn't need to know anything about the VideoPlayer.
  It simply uses the MediaPlayer interface.
- Reusability: You can adapt new incompatible classes without modifying the client or the existing classes.
- Flexibility: The adapter allows the integration of classes with incompatible interfaces by acting as a middle layer.

Real-World Example:
Power Adapter: In the real world, a power adapter allows a device with one type of plug to
               connect to an outlet with a different type of socket.

*/
#include <iostream>
#include <string>

// Target interface (what the client expects)
class MediaPlayer {
public:
    virtual void playAudio(const std::string& audioType, const std::string& fileName) = 0;
    virtual ~MediaPlayer() = default;
};

// Adaptee (existing class with incompatible interface)
class VideoPlayer {
public:
    void playVideo(const std::string& videoType, const std::string& fileName) {
        if (videoType == "mp4") {
            std::cout << "Playing mp4 video: " << fileName << std::endl;
        } else {
            std::cout << "Unsupported video format: " << videoType << std::endl;
        }
    }
};

// Adapter (makes Adaptee compatible with Target)
class MediaAdapter : public MediaPlayer {
private:
    VideoPlayer* videoPlayer;

public:
    MediaAdapter() {
        videoPlayer = new VideoPlayer();  // Adaptee
    }

    ~MediaAdapter() {
        delete videoPlayer;
    }

    void playAudio(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp4") {
            videoPlayer->playVideo(audioType, fileName);  // Adapt the call
        } else {
            std::cout << "Unsupported audio format: " << audioType << std::endl;
        }
    }
};

// Client class that uses the MediaPlayer interface
class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter* mediaAdapter;

public:
    void playAudio(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            std::cout << "Playing mp3 audio: " << fileName << std::endl;
        } else if (audioType == "mp4") {
            // Use the adapter to play mp4 files
            mediaAdapter = new MediaAdapter();
            mediaAdapter->playAudio(audioType, fileName);
            delete mediaAdapter;
        } else {
            std::cout << "Unsupported format: " << audioType << std::endl;
        }
    }
};

int main() {
    AudioPlayer audioPlayer;

    // Playing an mp3 file (no need for adapter)
    audioPlayer.playAudio("mp3", "song.mp3");

    // Playing an mp4 file (adapter is used)
    audioPlayer.playAudio("mp4", "movie.mp4");

    // Trying to play an unsupported file format
    audioPlayer.playAudio("avi", "video.avi");

    return 0;
}
