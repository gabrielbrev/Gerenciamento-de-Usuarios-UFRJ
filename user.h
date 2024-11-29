#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
private:
    int user_id;
    std::string email;
    std::string password;
    std::string name;
    std::string birth_date;
    std::string gender;
    std::string cpf;
    std::string postal_code;
    std::string phone;

public:
    User();
    User(const int id);
    User(const std::string& id, const std::string& e, const std::string& p, const std::string& n, const std::string& b, const std::string& g, const std::string& c, const std::string& pc, const std::string& ph = "");

    bool operator==(const User& u) const;

    int getUserId() const;
    void setUserId(const int id);

    std::string getEmail() const;
    void setEmail(const std::string& e);

    std::string getPassword() const;
    void setPassword(const std::string& p);

    std::string getName() const;
    void setName(const std::string& n);

    std::string getBirthDate() const;
    void setBirthDate(const std::string& b);

    std::string getGender() const;
    void setGender(const std::string& g);

    std::string getCpf() const;
    void setCpf(const std::string& c);

    std::string getPostalCode() const;
    void setPostalCode(const std::string& pc);

    std::string getPhone() const;
    void setPhone(const std::string& ph);

    void printInfo();
    void printMainInfo();
};

#endif