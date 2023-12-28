#include <iostream>
#include <vector>

using namespace std;

class User {
public:
    string login;
    string password;
    string name;

    User(string _login, string _password, string _name) {
        login = _login;
        password = _password;
        name = _name;
    }
};

class Chat {
private:
    vector<User> users;
    vector<string> messages;

public:
    void registerUser() {
        string login, password, name;
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;
        cout << "Введите имя: ";
        cin >> name;

        User user(login, password, name);
        users.push_back(user);

        cout << "Пользователь зарегистрирован!\n";
    }

    void loginUser() {
        string login, password;
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;

        for (User user : users) {
            if (user.login == login && user.password == password) {
                cout << "Вход выполнен! Добро пожаловать, " << user.name << "!\n";
                return;
            }
        }

        cout << "Неверный логин или пароль!\n";
    }

    void sendMessage() {
        string login, message;
        cout << "Введите логин получателя: ";
        cin >> login;
        cout << "Введите сообщение: ";
        cin >> message;

        for (User user : users) {
            if (user.login == login) {
                messages.push_back(user.name + ": " + message);
                cout << "Сообщение отправлено!\n";
                return;
            }
        }

        cout << "Пользователь не найден!\n";
    }

    void broadcastMessage() {
        string message;
        cout << "Введите сообщение: ";
        cin >> message;

        for (User user : users) {
            messages.push_back(user.name + ": " + message);
        }

        cout << "Сообщение отправлено всем пользователям!\n";
    }

    void showMessages() {
        for (string message : messages) {
            cout << message << endl;
        }
    }
};

int main() {
    Chat chat;

    cout << "Добро пожаловать в чат!\n";

    while (true) {
        cout << "Меню:\n";
        cout << "1. Зарегистрироваться\n";
        cout << "2. Войти в чат\n";
        cout << "3. Отправить сообщение пользователю\n";
        cout << "4. Отправить сообщение всем пользователям\n";
        cout << "5. Показать сообщения\n";
        cout << "Выберите пункт меню: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            chat.registerUser();
            break;
        case 2:
            chat.loginUser();
            break;
        case 3:
            chat.sendMessage();
            break;
        case 4:
            chat.broadcastMessage();
            break;
        case 5:
            chat.showMessages();
            break;
        default:
            cout << "Неверный выбор!\n";
            break;
        }
    }

    return 0;
}