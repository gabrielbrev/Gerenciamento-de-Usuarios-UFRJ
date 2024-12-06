#include "menu.h"
#include "user.h"

#include <string>
#include <iostream>

using namespace std;

int main() {
    Menu menu;

    const string user = "admin";
    const string password = "admin";

    string user_input = "";
    string password_input = "";
    const int max_attempts = 5; // Número máximo de tentativas permitidas
    int attempts = 0; // Contador de tentativas

    cout << "Realize seu login antes de prosseguir.\n";

    while (attempts < max_attempts) {
        cout << "Usuário: ";
        cin >> user_input;
        cout << "Senha: ";
        cin >> password_input;

        if (user_input == user && password_input == password) {
            cout << "Login realizado com sucesso!\n";
            menu.start();
            return 0;
        }

        attempts++;
        if (attempts < max_attempts) {
            cout << "Usuário/Senha incorretos. Você tem mais "
                 << (max_attempts - attempts) << " tentativa(s).\n";
        }
    }

    cout << "Número máximo de tentativas atingido. Encerrando programa.\n";
    return 0;
}
