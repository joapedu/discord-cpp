#include <string>

#include "../include/usuario.h"

using namespace std;

//construtor
Usuario::Usuario() {}

//sobrecarregado
Usuario::Usuario(int id, string email, string senha, string nome) {
  this->id = id;
  this->email = email;
  this->senha = senha;
  this->nome = nome;
}

//destrutor
Usuario::~Usuario() {}

//ID do usuário
int Usuario::getId() const {
  return id;
}

//nome do usuário
string Usuario::getNome() const {
  return nome;
}
//define o nome
void Usuario::setNome(string const nome) {
  this->nome = nome;
}

//email do usuário
string Usuario::getEmail() const {
  return email;
}
//define o email
void Usuario::setEmail(string const email) {
  this->email = email;
}

//senha do usuário
string Usuario::getSenha() const {
  return senha;
}

//define a senha
void Usuario::setSenha(string const senha) {
  this->senha = senha;
}
