#include "dataManager.h"
#include "user.h"

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

void DataManager::setMessage(const std::string& msg) {
    this->message = msg;
}

void DataManager::printMessage() const {
    if (this->message != "") {
        std::cout << this->message << std::endl;
    }
}

std::string DataManager::execute(const std::string& command) {   
    // Executa o comando usando popen e armazena todo o output em apenas uma string 
    FILE* pipe = popen(command.c_str(),  "r");

    if (!pipe) {
        throw std::runtime_error("Erro ao ler o retorno do comando");
    }

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);

    return result;
}

std::vector<std::string> DataManager::parseResults(const std::string& str) {
    // Transforma o output em um vetor de strings separando por '\n'
    std::vector<std::string> result;
    std::istringstream stream(str);
    std::string line;

    while (std::getline(stream, line)) {
        result.push_back(line);
    }

    this->message = result[1];

    if (result[0] != "true") {
        throw std::runtime_error(result[1]);
    }

    return result;
}

int DataManager::init() {
    try {
        std::string result = execute("python3 db/init_db.py");
        std::vector<std::string> values = parseResults(result);
        return 0;
    } catch (const std::exception& e) {
        return 1;
    }
}

std::vector<User> DataManager::listUsers() {
    std::vector<User> users;
    try {
        std::string result = execute("python3 db/list_users.py");
        std::vector<std::string> values = parseResults(result);

        // Os atributos dos usuários são retornados em sequencia
        // Itera o vetor a partir da terceira posição e de 9 em 9 (qtd. atributos de cada usuário)
        for (int i = 2; i < static_cast<int>(values.size()); i += 9) {
            User u = User(values[i], values[i + 1], values[i + 2], values[i + 3], values[i + 4], values[i + 5], values[i + 6], values[i + 7], values[i + 8]);
            users.push_back(u);
        }
    } catch (const std::exception& e) {} 
    return users;
}

std::string DataManager::trim(const std::string& str) {
    // Remove os espaços em branco das extremidades da string
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) return "";

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    
    return str.substr(first, last - first + 1);
}

std::vector<User> DataManager::searchUsers(const std::string& name) {
    std::vector<User> users;
    try {
        std::string result = execute("python3 db/get_users_by_name.py " + trim(name));
        std::vector<std::string> values = parseResults(result);

        for (int i  = 2; i < static_cast<int>(values.size()); i += 9) {
            User u = User(values[i], values[i + 1], values[i + 2], values[i + 3], values[i + 4], values[i + 5], values[i + 6], values[i + 7], values[i + 8]);
            users.push_back(u);
        }
    } catch (const std::exception& e) {} 
    return users;
}

int DataManager::deleteUser(const int id) {
    try {
        std::string result = execute("python3 db/delete_user.py " + std::to_string(id));
        std::vector<std::string> values = parseResults(result);
        return 0;
    } catch (const std::exception& e) {
        return 1;
    } 
}

int DataManager::eraseDatabase() {
    try {
        std::string result = execute("python3 db/erase_data.py");
        std::vector<std::string> values = parseResults(result);
        return 0;
    } catch (const std::exception& e) {
        return 1;
    } 
}

int DataManager::generateRandoUsers(int num) {
    try {
        std::string result = execute("python3 db/generate_users.py " + std::to_string(num));
        std::vector<std::string> values = parseResults(result);
        return 0;
    } catch (const std::exception& e) {
        return 1;
    } 
}

int DataManager::addUser(
    const std::string& email, 
    const std::string& password, 
    const std::string& name, 
    const std::string& birthdate, 
    const std::string& gender, 
    const std::string& cpf, 
    const std::string& zipCode,
    const std::string& phoneNumber
) {
    try {
        std::string command = "python3 db/add_user.py " + email + " " + password + " '" + name + "' " + birthdate + " " + gender + " " + cpf + " " + zipCode + " '" + phoneNumber + "'";
        std::string result = execute(command);
        std::vector<std::string> values = parseResults(result);
        return 0;
    } catch (const std::exception& e) {
        return 1;
    } 
}

int DataManager::editUser(const int id, const std::string &column, const std::string &value) {
    try {
        std::string result = execute("python3 db/modify_user.py " + column + " '" + value + "' " + std::to_string(id));
        std::vector<std::string> values = parseResults(result);
        return 0;
    } catch (const std::exception& e) {
        return 1;
    } 
}
