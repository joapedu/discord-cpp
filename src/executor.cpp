#include "../include/executor.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

//recebe um istringstream e lê todo texto restante até o fim da linha
string restante(istringstream &ss) {
  string resto;
  getline(ss, resto, '\0');
  if (resto != "" && (resto[0] == ' ' || resto[0] == '\t')) {
    resto = resto.substr(1);
  }
  return resto;
}

//construtor
Executor::Executor(Sistema &sistema) {
  this->sair = false;
  this->sistema = &sistema;
}

//iniciar do processamento dos comentos.
//faz o necessário para ler 1 comando por linha e processa
void Executor::iniciar(istream &inputStream, ostream &outputStream) {
  string linha, saida;
  this->sair = false;
  while (! this->sair)
  {
    if (std::getline(inputStream, linha)) {
      saida = processarLinha(linha);
      outputStream << saida << endl;
    }
  }
}

//responsável por processar cada linha, capturando o nome do comando
//e seus parâmetros em variáveis e executar o método correspondente
string Executor::processarLinha(string linha) {
  istringstream buf(linha);
  string nomeComando;
  buf >> nomeComando;

  if (nomeComando.empty()) {
    return "Comando Inválido <vazio>";
  }

  if (nomeComando == "quit" ) {
    this->sair = true;
    return sistema->quit();
  }

  else if (nomeComando == "create-user") {
    string email, senha, nome;
    buf >> email;
    buf >> senha;
    nome = restante(buf);
    return sistema->create_user(email, senha, nome);
  }

  else if (nomeComando == "login") {
    string email, senha;
    buf >> email;
    buf >> senha;
    return sistema->login(email, senha);
  }

  else if (nomeComando == "disconnect") {
    return sistema->disconnect();
  }

  else if (nomeComando == "create-server") {
    string nome;
    buf >> nome;
    return sistema->create_server(nome);
  }

  else if (nomeComando == "set-server-desc") {
    string nome, descricao;
    buf >> nome;
    descricao = restante(buf);;
    return sistema->set_server_desc(nome, descricao);
  }

  else if (nomeComando == "set-server-invite-code") {
    string nome, codigo;
    buf >> nome;
    buf >> codigo;
    return sistema->set_server_invite_code(nome, codigo);
  }

  else if (nomeComando == "list-servers") {
    return sistema->list_servers();
  }

  else if (nomeComando == "remove-server") {
    string nome;
    buf >> nome;
    return sistema->remove_server(nome);
  }

  else if (nomeComando == "enter-server") {
    string nome, codigo;
    buf >> nome;
    buf >> codigo;
    return sistema->enter_server(nome, codigo);
  }

  else if (nomeComando == "leave-server") {
    return sistema->leave_server();
  }

  else if (nomeComando == "list-participants") {
    return sistema->list_participants();
  }

  else if (nomeComando == "list-channels") {
    return sistema->list_channels();
  }

  else if (nomeComando == "create-channel") {
    string nome, tipo;
    buf >> nome;
    buf >> tipo;
    return sistema->create_channel(nome, tipo);
  }

  else if (nomeComando == "enter-channel") {
    string nome, tipo;
    buf >> nome;
    buf >> tipo;
    return sistema->enter_channel(nome, tipo);
  }

  else if (nomeComando == "leave-channel") {
    return sistema->leave_channel();
  }

  else {
    return "Comando não reconhecido [" + nomeComando + "]";
  }
}



