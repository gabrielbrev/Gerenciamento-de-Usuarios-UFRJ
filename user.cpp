#include "user.h"

#include <string>

User::User() {}

User::User(const int id) {
    user_id = id;
}

User::User(const std::string& id, const std::string& e, const std::string& p, const std::string& n, const std::string& b, const std::string& g, const std::string& c, const std::string& pc, const std::string& ph) {
    user_id = std::stoi(id);
    email = e;
    password = p;
    name = n;
    birth_date = b;
    gender = g;
    cpf = c;
    postal_code = pc;
    phone = ph;
}

bool User::operator==(const User& u) const {
    return (this->user_id == u.user_id);
}

int User::getUserId() const {
    return user_id;
}

void User::setUserId(const int id) {
    user_id = id;
}

std::string User::getEmail() const {
    return email;
}

void User::setEmail(const std::string& e) {
    email = e;
}

std::string User::getPassword() const {
    return password;
}

void User::setPassword(const std::string& p) {
    password = p;
}

std::string User::getName() const {
    return name;
}

void User::setName(const std::string& n) {
    name = n;
}

std::string User::getBirthDate() const {
    return birth_date;
}

void User::setBirthDate(const std::string& b) {
    birth_date = b;
}

std::string User::getGender() const {
    return gender;
}

void User::setGender(const std::string& g) {
    gender = g;
}

std::string User::getCpf() const {
    return cpf;
}

void User::setCpf(const std::string& c) {
    cpf = c;
}

std::string User::getPostalCode() const {
    return postal_code;
}

void User::setPostalCode(const std::string& pc) {
    postal_code = pc;
}

std::string User::getPhone() const {
    return phone;
}

void User::setPhone(const std::string& ph) {
    phone = ph;
}

void User::printInfo() {
    std::cout << "ID: " << user_id << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Senha: " << password << std::endl;
    std::cout << "Nome: " << name << std::endl;
    std::cout << "Data de Nascimento: " << birth_date << std::endl;
    std::cout << "Gênero: " << gender << std::endl;
    std::cout << "CPF: " << cpf << std::endl;
    std::cout << "CEP: " << postal_code << std::endl;
    if (this->phone != "") std::cout << "Telefone: " << phone << std::endl;
    else std::cout << "Telefone não cadastrado" << std::endl;
}

void User::printMainInfo() {
    std::cout << user_id << "\t"
              << name << "\n";
}