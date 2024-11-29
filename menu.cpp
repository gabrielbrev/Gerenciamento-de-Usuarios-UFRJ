#include "menu.h"
#include "dataManager.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono> 
#include <regex>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>

#define OTHER 0
#define WIN 1
#define LIN_MAC 2

Menu::Menu() {
    // Identifica o sistema operacional
    #if defined(_WIN32) || defined(_WIN64)
        systemType = WIN;
    #elif defined(__linux__)
        systemType = LIN_MAC;
    #elif defined(__APPLE__) || defined(__MACH__)
        systemType = LIN_MAC;
    #else
        systemType = OTHER;
    #endif
}

void Menu::clearConsole() {
    if (this->systemType == 0) {
        for (int i = 0; i < 100; i++) {
            std::cout << "\n";
        }
    } else if (this->systemType == 1) {
        system("cls");
    } else {
        system("clear");
    }
}

bool Menu::inputAndValidate(int* input, int a, int b) {
    std::cin >> *input;
    return (*input >= a && *input <= b);
}

bool Menu::inputAndValidate(std::string* input, std::string match) {
    std::cin >> *input;
    return (*input == match);
}

bool Menu::isOnlyDigits(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool Menu::isValidDate(int day, int month, int year) {
    if (year <= 1900) return false;

    if (month < 1 || month > 12) return false;

    int daysInMonth;
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            // Verificação para ano bissexto
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
            break;
        default:
            daysInMonth = 0;
            break;
    }

    return day >= 1 && day <= daysInMonth;
}

bool Menu::isValidEmail(const std::string& email) {
    std::regex padrao_email(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, padrao_email);
}

std::string Menu::inputCPF() {
    std::string cpf;
    std::cout << "Digite o CPF (somente números): ";
    std::cin >> cpf;

    while (cpf.length() != 11 || !isOnlyDigits(cpf)) {
        std::cout << "CPF inválido. Digite exatamente 11 números: ";
        std::cin >> cpf;
    }

    // Retorna o CPF formatado
    return cpf.substr(0, 3) + "." + cpf.substr(3, 3) + "." + cpf.substr(6, 3) + "-" + cpf.substr(9, 2);
}

std::string Menu::inputPostalCode() {
    std::string postalcode;
    std::cout << "Digite o CEP (somente números): ";
    std::cin >> postalcode;

    while (postalcode.length() != 8 || !isOnlyDigits(postalcode)) {
        std::cout << "CEP inválido. Digite exatamente 8 números: ";
        std::cin >> postalcode;
    }

    // Retorna o CEP formatado
    return postalcode.substr(0, 5) + "-" + postalcode.substr(5, 3);
}

std::string Menu::inputPhoneNumber() {
    // Numero de celular no formato (XXX) XXXX-XXXX para consistencia com o Faker
    std::string phonenumber;
    std::cout << "Digite o número de telefone (somente números), ou deixe vazio: ";
    std::cin.ignore();  // Ignora o caractere '\n' que possa estar no buffer
    std::getline(std::cin, phonenumber);

    if (phonenumber.empty()) {
        return "";
    }

    while (phonenumber.length() != 10 || !isOnlyDigits(phonenumber)) {
        std::cout << "Número de telefone inválido. Digite exatamente 10 números, ou deixe vazio: ";
        std::getline(std::cin, phonenumber);

        if (phonenumber.empty()) {
            return "";
        }
    }

    // Retorna o número de telefone formatado
    return "(0" + phonenumber.substr(0, 2) + ") " + phonenumber.substr(2, 4) + "-" + phonenumber.substr(6, 4);
}

std::string Menu::inputDate() {
    int day, month, year;
    std::string dateInput;

    std::cout << "Digite a data no formato DD MM YYYY: ";
    std::getline(std::cin, dateInput);

    std::stringstream ss(dateInput);
    ss >> day >> month >> year;

    while (!isValidDate(day, month, year)) {
        std::cout << "Data inválida. Digite novamente no formato DD MM YYYY: ";
        std::getline(std::cin, dateInput);
        std::stringstream ss(dateInput);
        ss >> day >> month >> year;
    }

    // Retorna a data formatada no formato YYYY-MM-DD
    std::ostringstream oss;
    oss << year << "-" 
        << std::setw(2) << std::setfill('0') << month << "-" 
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}

std::string Menu::inputEmail() {
    std::string email;
    std::cout << "Digite o email: ";
    std::cin >> email;

    while (!isValidEmail(email)) {
        std::cout << "Email inválido. Digite um email válido: ";
        std::cin >> email;
    }

    return email;
}

std::string Menu::inputGender() {
    std::string gender;
    std::cout << "Digite o gênero (M para Masculino ou F para Feminino): ";
    std::cin >> gender;

    while (gender != "M" && gender != "F") {
        std::cout << "Gênero inválido. Digite M para Masculino ou F para Feminino: ";
        std::cin >> gender;
    }

    return gender;
}

std::string Menu::inputName() {
    std::string name;
    std::cout << "Digite o nome completo: ";
    std::cin.ignore();  // Ignora o caractere '\n' que possa estar no buffer
    std::getline(std::cin, name);
    return name;
}

std::string Menu::inputPassword() {
    std::string password;
    std::cout << "Digite a senha: ";
    std::cin >> password;
    return password;
}

int Menu::start() {
    this->manager.init();
    this->clearConsole();

    int opt;
    do {
        std::cout << "Bem vindo ao sistema de gerenciamento de usuários\n\n";
        this->manager.printMessage();
        std::cout << "[1] Adicionar usuário\n";
        std::cout << "[2] Listar usuários\n";
        std::cout << "[3] Buscar usuários\n";
        std::cout << "[4] Gerar usuários aleatórios\n";
        std::cout << "[5] Resetar dados\n";
        std::cout << "\n";
        std::cout << "[0] Sair\n";
        std::cout << "-> ";

        bool valid = this->inputAndValidate(&opt, 0, 5);
        if (!valid) {
            std::cout << "Opção inválida\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            this->clearConsole();
            continue;
        }

        switch (opt) {
            case 1: {
                this->manager.addUser(
                    this->inputEmail(),
                    this->inputPassword(),
                    this->inputName(),
                    this->inputDate(),
                    this->inputGender(),
                    this->inputCPF(),
                    this->inputPostalCode(),
                    this->inputPhoneNumber()
                );
                break;
            }

            case 2: {
                std::vector<User> users = this->manager.listUsers();
                this->showUsers(users);
                break;
            }

            case 3: {
                std::cout << "Nome do usuário: ";
                std::string nome;
                std::cin >> nome;
                std::vector<User> users = this->manager.searchUsers(nome);
                this->showUsers(users);
                break;
            }

            case 4: {
                std::cout << "Numero do usuários a serem gerados: ";
                int num;
                bool valid = this->inputAndValidate(&num, 1, std::pow(2, 31) - 1);
                if (!valid) {
                    break;
                }
                this->manager.generateRandoUsers(num);
                break;
            }

            case 5: {
                std::cout << "Essa ação é irreversível. Deseja prosseguir? (s/n)\n-> ";
                std::string confirm;
                bool valid = this->inputAndValidate(&confirm, "s");
                if (!valid) {
                    break;
                }
                this->manager.eraseDatabase();
                this->manager.init();
                break;
            }
        }
        this->clearConsole();
    } while (opt != 0);

    return 0;
} 

void Menu::showUsers(std::vector<User>& users) {
    int listLen = 25 > users.size() ? users.size() : 25;
    int start = 0;
    int end = listLen;

    int opt;
    do {
        this->clearConsole();

        std::cout << users.size() << " usuários encontrados:\n";
        std::cout << "\n";
        std::cout << "ID" << "\t" << "NOME\n";
        for (int i = start; i < end && i < static_cast<int>(users.size()); i++) {
            users[i].printMainInfo();
        }

        std::cout << "\n";
        this->manager.printMessage();
        if (end < static_cast<int>(users.size())) std::cout << "[1] Descer lista\n";
        if (start > 0) std::cout << "[2] Subir lista\n";
        if (users.size() > 0) std::cout << "[3] Selecionar usuário\n";
        std::cout << "\n";
        std::cout << "[0] Voltar\n";
        std::cout << "-> ";

        bool valid = this->inputAndValidate(&opt, 0, 3);
        if (!valid) {
            std::cout << "Opção inválida\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        std::cout << "\n";

        switch (opt) {
            case 1: {
                // Mostra os proximos usuários na lista
                if (end + listLen >= static_cast<int>(users.size())) {
                    end = users.size();
                    start = end - listLen;
                }
                else {
                    start += listLen;
                    end += listLen;
                }
                break;
            }
            
            case 2:{
                // Mostra os usuários anteriores na lista
                if (start - listLen < 0) {
                    start = 0;
                    end = start + listLen;
                }
                else {
                    start -= listLen;
                    end -= listLen;
                }
                break;
            }

            case 3: {
                this->selectUser(users);
                break;
            }
        }
    } while (opt != 0);
    this->manager.setMessage("");
}

int Menu::getUserIndexInVec(int id, std::vector<User>& users) {
    // Realiza busca binária no vetor
    User u = User(id);
    int i, start = 0, end = users.size() - 1;
    while (start <= end) {
        i = (start + end) / 2;

        if (users[i] == u) {
            return i;
        } 
        else if (users[i].getUserId() > id) {
            end = i - 1;
        }
        else {
            start = i + 1;
        }
    }
    return -1;
}

void Menu::selectUser(std::vector<User>& users) {
    this->manager.setMessage("");

    int id;
    int index = -1;
    while (index == -1) {
        std::cout << "ID do usuário (-1 para cancelar): ";
        std::cin >> id;
        if (id == -1) {
            return;
        }
        index = this->getUserIndexInVec(id, users);
        if (index == -1) {
            std::cout << "Usuário não encontrado\n";
        }
    }

    int opt;
    do {
        this->clearConsole();
        std::cout << "Usuário selecionado:\n";
        std::cout << "\n";
        users[index].printInfo();
        std::cout << "\n";
        this->manager.printMessage();
        std::cout << "[1] Atualizar usuário\n";
        std::cout << "[2] Remover usuário\n";
        std::cout << "\n";
        std::cout << "[0] Voltar\n";
        std::cout << "-> ";
        
        bool valid = this->inputAndValidate(&opt, 0, 2);
        if (!valid) {
            std::cout << "Opção inválida\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        switch (opt) {
            case 1: {
                this->editUser(users[index]);
                break;
            }

            case 2: {
                int result = this->manager.deleteUser(id);
                if (result == 0) {
                    users.erase(users.begin() + index);
                }
                return;
            }
        }
    } while (opt != 0);
}

void Menu::editUser(User& user) {
    std::cout << "\n";
    std::cout << "Qual dado deseja alterar?\n";
    std::cout << "[1] Email\n";
    std::cout << "[2] Senha\n";
    std::cout << "[3] Nome\n";
    std::cout << "[4] Data de nascimento\n";
    std::cout << "[5] Gênero\n";
    std::cout << "[6] CPF\n";
    std::cout << "[7] CEP\n";
    std::cout << "[8] Telefone\n";
    std::cout << "\n";
    std::cout << "[0] Cancelar\n";
    std::cout << "-> ";

    int opt;
    while (!inputAndValidate(&opt, 0, 8)) {
        std::cout << "Opção inválida\n";
        std::cout << "-> ";
    }

    std::cout << "\n";

    switch (opt) {
        case 1: {
            std::string email = inputEmail();
            this->manager.editUser(user.getUserId(), "email", email);
            user.setEmail(email);
            break;
        }
        case 2: {
            std::string password = inputPassword();
            this->manager.editUser(user.getUserId(), "senha", password);
            user.setPassword(password);
            break;
        }
        case 3: {
            std::string name = inputName();
            this->manager.editUser(user.getUserId(), "nome", name);
            user.setName(name);
            break;
        }
        case 4: {
            std::string date = inputDate();
            this->manager.editUser(user.getUserId(), "dataNasc", date);
            user.setBirthDate(date);
            break;
        }
        case 5: {
            std::string gender = inputGender();
            this->manager.editUser(user.getUserId(), "genero", gender);
            user.setGender(gender);
            break;
        }
        case 6: {
            std::string cpf = inputCPF();
            this->manager.editUser(user.getUserId(), "cpf", cpf);
            user.setCpf(cpf);
            break;
        }
        case 7: {
            std::string postalcode = inputPostalCode();
            this->manager.editUser(user.getUserId(), "cep", postalcode);
            user.setPostalCode(postalcode);
            break;
        }
        case 8: {
            std::string phone = inputPhoneNumber();
            this->manager.editUser(user.getUserId(), "telefone", phone);
            user.setPhone(phone);
            break;
        }
    }
}

