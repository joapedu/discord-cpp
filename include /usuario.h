#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>

using namespace std;

class Usuario {
   private:
    string nome;
    string email;
    string senha;
//será atribuído um id ao usuário
    int id;
//controle se o usuário esta logado ou não
    bool logado = false;

   public:
//construtor com parametros da classe usuario
    Usuario(int id, string nome, string email, string senha);

//construtor padrão
    Usuario();

//destrutor
    ~Usuario();

//getters dos atributos da classe User
    int getId();
    string getNome();
    string getEmail();
    string getSenha();
    bool getLogado();

//setters dos atributos da classe User
    void setId(int id);
    void setLogado(bool logado);
    void setNome(string nome);
    void setEmail(string email);
    void setSenha(string senha);
};

#endif
