# Network Events Implementation

#include <iostream>
#include <string>
#include <unordered_map>

class NetworkEvents {
public:
    void onPlayerJoin(int playerID) {
        std::cout << "Player " << playerID << " has joined the game." << std::endl;
    }

    void onPlayerLeave(int playerID) {
        std::cout << "Player " << playerID << " has left the game." << std::endl;
    }

    void onPlayerMove(int playerID, float x, float y, float z) {
        std::cout << "Player " << playerID << " moved to (" << x << ", " << y << ", " << z << ")." << std::endl;
    }

    void onPlayerAction(int playerID, const std::string &action) {
        std::cout << "Player " << playerID << " performed action: " << action << std::endl;
    }

    void onPlayerChat(int playerID, const std::string &message) {
        std::cout << "Player " << playerID << " says: " << message << std::endl;
    }
};

// Example usage
int main() {
    NetworkEvents networkEvents;
    networkEvents.onPlayerJoin(1);
    networkEvents.onPlayerMove(1, 10.0, 20.0, 5.0);
    networkEvents.onPlayerAction(1, "Jump");
    networkEvents.onPlayerChat(1, "Hello, everyone!");
    networkEvents.onPlayerLeave(1);
    return 0;
}