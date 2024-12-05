#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "user.h"

#include <string>
#include <vector>

class DataManager {
public:
    int init();
    std::vector<User> listUsers();
    std::vector<User> searchUsers(const std::string& name);
    int addUser(
        const std::string& email, 
        const std::string& password, 
        const std::string& name, 
        const std::string& birthdate, 
        const std::string& gender, 
        const std::string& cpf, 
        const std::string& zipCode, 
        const std::string& phoneNumber
    );
    int editUser(
        const int id,
        const std::string& column,
        const std::string& value
    );
    int deleteUser(const int id);
    int eraseDatabase();
    int generateRandoUsers(int num);
    void setSystemType(int systemType);
    void setMessage(const std::string& msg);
    void printMessage() const;

private:
    std::string message;
    std::string pythonCommand;

    std::string execute(const std::string& command);
    std::vector<std::string> parseResults(const std::string& str);
    std::string trim(const std::string& str);
};

#endif