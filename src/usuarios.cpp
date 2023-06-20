#include <iostream>
#include <string>
#include <map>

using namespace std;

// estrutura para armazenar informações do usuário
struct User {
    string username;
    string password;
};

// função para verificar o login
bool verifyLogin(const string& username, const string& password, const map<string, User>& users) {
    if (users.count(username) > 0) {
        User user = users.at(username);
        return user.password == password;
    }
    return false;
}

// função para cadastrar um novo usuário
void registerUser(map<string, User>& users) {
    User newUser;

    cout << "Digite o nome de usuário: ";
    cin >> newUser.username;

    // verifica se o nome de usuário já está em uso
    if (users.count(newUser.username) > 0) {
        cout << "O nome de usuário já está em uso. Escolha outro." << endl;
        return;
    }

    cout << "Digite a senha: ";
    cin >> newUser.password;

    // adiciona o novo usuário ao mapa de usuários
    users[newUser.username] = newUser;
    cout << "Usuário cadastrado com sucesso!" << endl;
}

int main() {
    // mapa para armazenar usuários
    map<string, User> users;

    char choice;
    do {
        cout << "Selecione uma opção:" << endl;
        cout << "1. Cadastrar novo usuário" << endl;
        cout << "2. Fazer login" << endl;
        cout << "3. Sair" << endl;
        cout << "Opção: ";
        cin >> choice;

        switch (choice) {
            case '1':
                registerUser(users);
                break;
            case '2':
                {
                    string username, password;
                    cout << "Digite o nome de usuário: ";
                    cin >> username;
                    cout << "Digite a senha: ";
                    cin >> password;
                    if (verifyLogin(username, password, users)) {
                        cout << "Login bem-sucedido!" << endl;
                    } else {
                        cout << "Nome de usuário ou senha incorretos." << endl;
                    }
                }
                break;
            case '3':
                cout << "Encerrando o programa." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }

        cout << endl;
    } while (choice != '3');

    return 0;
}
