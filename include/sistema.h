#ifndef SISTEMA_H
#define SISTEMA_H
#include <vector>
#include <string>
#include <iostream>

#include "usuario.h"
#include "servidor.h"

using namespace std;

class Sistema {
  private:
    vector <Servidor> servidores;
    vector <Usuario> usuarios;
    int usuarioLogadoId;
    string nomeServidorConectado;
    string nomeCanalConectado;

    void salvarUsuarios();
    void salvarServidores();
    
    void carregarUsuarios();
    void carregarServidores();

  public:
    Sistema();
    ~Sistema();

//salva dados da aplicação.
    void salvar();
//carrega dados da aplicação.
    void carregar();

//sair
    string quit();

//cria um novo usuário.
    string create_user (const string email, const string senha, const string nome);
    
//conecta um usuário.
    string login(const string email, const string senha);

//desconecta um usuário
    string disconnect();

//cria um novo servidor.
    string create_server(const string nome);

//altera a descrição de um servidor.
    string set_server_desc(const string nome, const string descricao);

//altera o código de convite de um servidor.
    string set_server_invite_code(const string nome, const string codigo);

//lista servidores.
    string list_servers();

//remove um servidor.
    string remove_server(const string nome);

//entra em um servidor.
    string enter_server(const string nome, const string codigo);

//sai de um servidor.
    string leave_server();

//lista participantes de um servidor.
    string list_participants();

//lista canais de um servidor.
    string list_channels();

//cria um novo canal em um servidor.
    string create_channel(const string nome, const string tipo);

//entra em um canal.
    string enter_channel(const string nome, const string tipo);

//sai de um canal.
    string leave_channel();
};

#endif