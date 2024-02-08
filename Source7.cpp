#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class User {
private:
    std::string username;
    std::string password;
    std::string name;
public:
    User(const std::string& username, const std::string& password, const std::string& name)
        : username(username), password(password), name(name) {}

    const std::string& getUsername() const {
        return username;
    }

    const std::string& getPassword() const {
        return password;
    }

    const std::string& getName() const {
        return name;
    }
};

class ChatRoom {
private:
    std::vector<User> users;
public:
    void registerUser(const User& user) {
        users.push_back(user);
    }

    User* loginUser(const std::string& username, const std::string& password) {
        for (User& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                return &user;
            }
        }
        return nullptr;
    }

    void sendMessageToUser(const User& sender, const std::string& receiverUsername, const std::string& message) {
        for (const User& user : users) {
            if (user.getUsername() == receiverUsername) {
                std::cout << "Message from " << sender.getName() << " to " << user.getName() << ": " << message << std::endl;
                return;
            }
        }
        std::cout << "User not found!" << std::endl;
    }

    void broadcastMessage(const User& sender, const std::string& message) {
        for (const User& user : users) {
            if (user.getUsername() != sender.getUsername()) {
                std::cout << "Broadcast message from " << sender.getName() << " to " << user.getName() << ": " << message << std::endl;
            }
        }
    }
};

int main() {
    ChatRoom chatRoom;

    // Регистрация пользователей
    User user1("user1", "password1", "User 1");
    User user2("user2", "password2", "User 2");

    chatRoom.registerUser(user1);
    chatRoom.registerUser(user2);

    // Вход в чат
    User* loggedInUser = chatRoom.loginUser("user1", "password1");
    if (loggedInUser) {
        std::cout << loggedInUser->getName() << " logged in successfully!" << std::endl;

        // Отправка сообщений
        chatRoom.sendMessageToUser(*loggedInUser, "user2", "Hello from user1!");
        chatRoom.broadcastMessage(*loggedInUser, "Broadcast message from user1!");
    }
    else {
        std::cout << "Invalid username or password!" << std::endl;
    }

    return 0;
}