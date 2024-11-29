#ifndef MENU_H
#define MENU_H

#include "dataManager.h"
#include "user.h"

#include <vector>

class Menu {
public:
    Menu();
    int start();

private:
    int systemType;
    DataManager manager;

    int getUserIndexInVec(int id, std::vector<User>& users);
    void showUsers(std::vector<User>& users);
    void selectUser(std::vector<User>& users);
    void editUser(User& user);
    void clearConsole();
    bool inputAndValidate(int* input, int a, int b);
    bool inputAndValidate(std::string* input, std::string match);
    bool isValidEmail(const std::string& email);
    bool isValidDate(int d, int m, int y);
    bool isOnlyDigits(const std::string& str);
    std::string inputEmail();
    std::string inputPassword();
    std::string inputName();
    std::string inputDate();
    std::string inputGender();
    std::string inputCPF();
    std::string inputPostalCode();
    std::string inputPhoneNumber();
};

#endif