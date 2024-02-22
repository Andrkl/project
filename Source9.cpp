#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class User {
public:
    std::string name;
    int age;

    void print() {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

class Message {
public:
    std::string content;

    void print() {
        std::cout << "Message: " << content << std::endl;
    }
};

int main() {
    std::ifstream inputFile("data.txt");
    if (!inputFile) {
        std::cout << "Failed to open the input file." << std::endl;
        return 1;
    }

    std::vector<User> users;
    std::vector<Message> messages;

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line == "User") {
            User user;
            std::getline(inputFile, user.name);
            inputFile >> user.age;
            inputFile.ignore(); 
            users.push_back(user);
        }
        else if (line == "Message") {
            Message message;
            std::getline(inputFile, message.content);
            messages.push_back(message);
        }
    }

    inputFile.close();

    for (const auto& user : users) {
        user.print();
    }

    for (const auto& message : messages) {
        message.print();
    }

    users[0].name = "Alice";
    users[0].age = 30;
    messages[0].content = "Hello, world!";

    std::ofstream outputFile("data.txt");
    if (!outputFile) {
        std::cout << "Failed to open the output file." << std::endl;
        return 1;
    }

    for (const auto& user : users) {
        outputFile << "User\n";
        outputFile << user.name << '\n';
        outputFile << user.age << '\n';
    }

    for (const auto& message : messages) {
        outputFile << "Message\n";
        outputFile << message.content << '\n';
    }

    outputFile.close();

    return 0;
}