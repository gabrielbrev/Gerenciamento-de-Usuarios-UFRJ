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

    cout << "Realize seu login antes de prosseguir.\n";
    cout << "Usuário: ";
    cin >> user_input;
    cout << "Senha: ";
    cin >> password_input;

    if (user_input != user || password_input != password) {
        cout << "Usuário/Senha incorretos. Encerrando programa.\n";
        return 0;
    }

    menu.start();

    return 0;
}