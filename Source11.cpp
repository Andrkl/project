#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <map>

std::vector<std::string> messages;
std::mutex mtx;
std::map<std::string, std::string> users;

void clientHandler(int clientSocket) {
}

void sendMessage(const std::string& message) {
    mtx.lock();
    messages.push_back(message);
    mtx.unlock();
}

bool login(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end() && users[username] == password) {
        return true;
    }
    return false;
}

void registerUser(const std::string& username, const std::string& password) {
    users[username] = password;
}

int main() {
    registerUser("user1", "password1");
    registerUser("user2", "password2");

    if (login("user1", "password1")) {
        std::cout << "User logged in successfully!" << std::endl;
    }
    else {
        std::cout << "Invalid username or password" << std::endl;
    }

    sendMessage("Hello, world!");

    return 0;
}