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
    int getId() const;
    string getNome() const;
    string getEmail() const;
    string getSenha() const;
    bool getLogado();

//setters dos atributos da classe User
    void setId(int id);
    void setLogado(bool logado);
    void setNome(string const nome);
    void setEmail(string const email);
    void setSenha(string const senha);
};

#endif
