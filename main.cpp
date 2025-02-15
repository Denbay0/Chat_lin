#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

struct User {
    std::string name;
    std::string login;
    std::string pass;
};

struct Message {
    std::string text;
    std::string sender;
    std::string receiver;
};

const std::string userFile = "users.dat";
const std::string messageFile = "messages.dat";

void setFilePermissions(const std::string& filename) {
    fs::permissions(filename, fs::perms::owner_read | fs::perms::owner_write);
}

void saveUsers(const std::vector<User>& users) {
    std::ofstream file(userFile, std::ios::trunc);
    if (file) {
        for (const auto& user : users) {
            file << user.name << ' ' << user.login << ' ' << user.pass << '\n';
        }
    }
    setFilePermissions(userFile);
}

void saveMessages(const std::vector<Message>& messages) {
    std::ofstream file(messageFile, std::ios::trunc);
    if (file) {
        for (const auto& msg : messages) {
            file << msg.text << ' ' << msg.sender << ' ' << msg.receiver << '\n';
        }
    }
    setFilePermissions(messageFile);
}

std::vector<User> loadUsers() {
    std::vector<User> users;
    std::ifstream file(userFile);
    if (file) {
        User user;
        while (file >> user.name >> user.login >> user.pass) {
            users.push_back(user);
        }
    }
    return users;
}

std::vector<Message> loadMessages() {
    std::vector<Message> messages;
    std::ifstream file(messageFile);
    if (file) {
        Message msg;
        while (file >> msg.text >> msg.sender >> msg.receiver) {
            messages.push_back(msg);
        }
    }
    return messages;
}

int main() {
    std::vector<User> users = loadUsers();
    std::vector<Message> messages = loadMessages();

    users.push_back({"Alice", "alice123", "password"});
    messages.push_back({"Hello, Bob!", "Alice", "Bob"});

    saveUsers(users);
    saveMessages(messages);

    std::cout << "Data saved successfully." << std::endl;
    return 0;
}
