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
        cout << "������ �����: ";
        cin >> login;
        cout << "������ ��஫�: ";
        cin >> password;
        cout << "������ ���: ";
        cin >> name;

        User user(login, password, name);
        users.push_back(user);

        cout << "���짮��⥫� ��ॣ����஢��!\n";
    }

    void loginUser() {
        string login, password;
        cout << "������ �����: ";
        cin >> login;
        cout << "������ ��஫�: ";
        cin >> password;

        for (User user : users) {
            if (user.login == login && user.password == password) {
                cout << "�室 �믮����! ���� ����������, " << user.name << "!\n";
                return;
            }
        }

        cout << "������ ����� ��� ��஫�!\n";
    }

    void sendMessage() {
        string login, message;
        cout << "������ ����� �����⥫�: ";
        cin >> login;
        cout << "������ ᮮ�饭��: ";
        cin >> message;

        for (User user : users) {
            if (user.login == login) {
                messages.push_back(user.name + ": " + message);
                cout << "����饭�� ��ࠢ����!\n";
                return;
            }
        }

        cout << "���짮��⥫� �� ������!\n";
    }

    void broadcastMessage() {
        string message;
        cout << "������ ᮮ�饭��: ";
        cin >> message;

        for (User user : users) {
            messages.push_back(user.name + ": " + message);
        }

        cout << "����饭�� ��ࠢ���� �ᥬ ���짮��⥫�!\n";
    }

    void showMessages() {
        for (string message : messages) {
            cout << message << endl;
        }
    }
};

int main() {
    Chat chat;

    cout << "���� ���������� � ��!\n";

    while (true) {
        cout << "����:\n";
        cout << "1. ��ॣ����஢�����\n";
        cout << "2. ���� � ��\n";
        cout << "3. ��ࠢ��� ᮮ�饭�� ���짮��⥫�\n";
        cout << "4. ��ࠢ��� ᮮ�饭�� �ᥬ ���짮��⥫�\n";
        cout << "5. �������� ᮮ�饭��\n";
        cout << "�롥�� �㭪� ����: ";

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
            cout << "������ �롮�!\n";
            break;
        }
    }

    return 0;
}