#include <iostream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <fstream>

#include "../include/sistema.h"

using namespace std;

Sistema::Sistema() {
//0 se nao logado
  this->usuarioLogadoId = 0;
  this->nomeServidorConectado = "";
  this->nomeCanalConectado = "";
}

Sistema::~Sistema() {}

string Sistema::quit() {
  return "Saindo...";
}

//cria novo usuário.
string Sistema::create_user (const string email, const string senha, const string nome) {
  carregar();

  if (usuarioLogadoId) return "Não foi possível realizar o cadastro.\nO usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " encontra-se logado!";

  if (email.empty() && senha.empty() && nome.empty()) return "Preencha todos os campos para cadastrar um usuário";

  for (int i = 0; i < usuarios.size(); i++) {
    if (usuarios[i].getEmail() == email) return "Usuário já existe.";
  }

  Usuario newUsuario((int)(usuarios.size() + 1), email, senha, nome);
  usuarios.push_back(newUsuario);

  salvar();

  return "Usuário criado!";
}

//conecta um usuário.
string Sistema::login(const string email, const string senha) {
  carregar();

  if (!usuarioLogadoId) {
    for (int i = 0; i < usuarios.size(); i++) {
      if (usuarios[i].getEmail() == email && usuarios[i].getSenha() == senha) {
        usuarioLogadoId = usuarios[i].getId();

        return "Login realizado como " + usuarios[i].getEmail() + "!";
      }
    }

    return "Email ou senha incorretos. Verifique e tente novamente!";
  }

  return "Não foi possível realizar o login.\nO usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " encontra-se logado!";
}

//desconecta um usuário
string Sistema::disconnect() {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  int usuarioLogadoIdAnterior = usuarioLogadoId;
  usuarioLogadoId = 0;

  return "Desconectando usuário " + usuarios[usuarioLogadoIdAnterior - 1].getEmail() + ".";
}

//cria um novo servidor.
string Sistema::create_server(const string nome) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nome.empty()) return "Não é possível criar um servidor sem nome.";

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) return "Servidor com esse nome já existe.";
  }

  Servidor newServidor(usuarioLogadoId, nome);

  newServidor.pushParticipante(usuarioLogadoId);
  servidores.push_back(newServidor);

  nomeServidorConectado = nome;

  salvar();

  return "Servidor criado.";
}

//altera a descrição de um servidor.
string Sistema::set_server_desc(const string nome, const string descricao) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  if (!isServidor) return "Servidor \'" + nome + "\' não existe.";

  if (findServidor.getUsuarioId() != usuarioLogadoId)
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";

  findServidor.setDescricao(descricao);

  salvar();

  return "Descrição do servidor \'" + nome + "\' modificada.";
}

//altera o código de convite de um servidor.
string Sistema::set_server_invite_code(const string nome, const string codigo) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  if (!isServidor) return "Servidor \'" + nome + "\' não existe.";

  if (findServidor.getUsuarioId() != usuarioLogadoId)
    return "Você não pode alterar o código de convite de um servidor que não foi criado por você.";

  findServidor.setSolicitacao(codigo);

  salvar();

  if (!codigo.empty()) return "Código de convite do servidor \'" + nome + "\' modificado.";
  else return "Código de convite do servidor \'" + nome + "\' removido.";
}

//lista servidores.
string Sistema::list_servers() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (servidores.empty()) return "Não há servidores cadastrados.";

  string listaServidores = "";

  for (int i = 0; i < servidores.size(); i++) {
    listaServidores += servidores[i].getNome() + "\n";
  }

  return listaServidores;
}

//remove um servidor.
string Sistema::remove_server(const string nome) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  vector<Servidor>::iterator findServidor;

  findServidor = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
    return servidor.getNome() == nome;
  });

  if (findServidor == servidores.end()) return "Servidor \'" + nome + "\' não encontrado.";

  if (findServidor->getUsuarioId() != usuarioLogadoId)
    return "Você não é o dono do servidor \'" + nome + "\'.";

  if(findServidor->getNome() == nomeServidorConectado) leave_server();

  servidores.erase(findServidor);

  salvar();

  return "Servidor \'" + nome + "\' removido.";
}

// entra em um servidor.
string Sistema::enter_server(const string nome, const string codigo) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  if (!isServidor) return "Servidor \'" + nome + "\' não existe.";

  if (findServidor.getUsuarioId() == usuarioLogadoId) {
    findServidor.pushParticipante(usuarioLogadoId);
    salvar();
    nomeServidorConectado = nome;
    return "Entrou no servidor com sucesso.";
  } else if (findServidor.getSolicitacao().empty()) {
    findServidor.pushParticipante(usuarioLogadoId);
    salvar();
    nomeServidorConectado = nome;
    return "Entrou no servidor com sucesso.";
  } else if (findServidor.getSolicitacao() == codigo) {
    findServidor.pushParticipante(usuarioLogadoId);
    salvar();
    nomeServidorConectado = nome;
    return "Entrou no servidor com sucesso.";
  } else if (!findServidor.getSolicitacao().empty() && codigo.empty()) {
    return "Servidor requer código de convite";
  } else {
    return "Código de convite incorreto";
  }
}

//sai de um servidor.
string Sistema::leave_server() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a nenhum servidor.";

  string nomeServidor = nomeServidorConectado;

  nomeServidorConectado = "";

  return "Saindo do servidor \'" + nomeServidor + "\'.";
}

//lista participantes de um servidor.
string Sistema::list_participants() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "Não há um servidor conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nomeServidorConectado) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  string listaParticipantes = "";
  vector<int> listaIds = findServidor.getMembrosIds();

  for (int i = 0; i < usuarios.size(); i++) {
    for (int j = 0; j < listaIds.size(); j++) {
      if (usuarios[i].getId() == listaIds[j]) listaParticipantes += usuarios[i].getNome() + "\n";
    }
  }

  return listaParticipantes;
}

//lista canais de um servidor. 
string Sistema::list_channels() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  string canais;

  if (canais.empty()) return "Sem canais criados.";
  
  return canais;
}

//cria um novo canal em um servidor
string Sistema::create_channel(const string nome, const string tipo) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nome.empty()) return "Não é possível criar um canal sem nome.";

  if (tipo != "texto" && tipo != "voz") return "Tipo inválido.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

    salvar();
}

//entra em um canal.
string Sistema::enter_channel(const string nome, const string tipo) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nome.empty()) return "Não é possível entrar em um canal sem nome.";

  if (tipo != "texto" && tipo != "voz") return "Tipo de canal inválido.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });
}

//sai de um canal.
string Sistema::leave_channel() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nomeCanalConectado.empty()) return "O usuário não está conectado a um canal no momento.";

  string nomeCanal = nomeCanalConectado;

  nomeCanalConectado = "";

  return "Saindo do canal \'" + nomeCanal + "\'.";
}

// salva usuários em um arquivo de texto.
void Sistema::salvarUsuarios() {
  ofstream file("usuarios.txt");

  if (!file) {
    cerr << "Houve um problema ao criar o arquivo." << endl;
    exit(1);
  }

  file << usuarios.size() << endl;

  for (int i = 0; i < usuarios.size(); i++) {
    file << usuarios[i].getId() << endl;
    file << usuarios[i].getNome() << endl;
    file << usuarios[i].getEmail() << endl;
    file << usuarios[i].getSenha() << endl;
  }

  file.close();
}

// salva servidores em um arquivo de texto.
void Sistema::salvarServidores() {
  ofstream file("servidores.txt");

  if (!file) {
    cerr << "Houve um problema ao criar o arquivo." << endl;
    exit(1);
  }

  file << servidores.size() << endl;

  for (int itServidores = 0; itServidores < servidores.size(); itServidores++) {
    file << servidores[itServidores].getUsuarioId() << endl;
    file << servidores[itServidores].getNome() << endl;
    file << servidores[itServidores].getDescricao() << endl;
    file << servidores[itServidores].getSolicitacao() << endl;

    file << servidores[itServidores].getMembrosIds().size() << endl;

    for (int itParticipante = 0; itParticipante < servidores[itServidores].getMembrosIds().size(); itParticipante++) {
      file << servidores[itServidores].getMembrosIds()[itParticipante] << endl;
    }

    file << (servidores[itServidores].getCanais().size()) << endl;
  }

  file.close();
}

// carrega usuários de um arquivo de texto.
void Sistema::carregarUsuarios() {
  ifstream file("usuarios.txt");

  if (!file) {
    cout << "Não foi possível abrir o arquivo." << endl;
    exit(1);
  }

  string size, id, nome, email, senha;
  int sizeUsuarios;

  file >> size;
  sizeUsuarios = stoi(size);

  file.ignore();

  for (int itUsuarios = 0; itUsuarios < sizeUsuarios; itUsuarios++) {
    getline(file, id);
    getline(file, nome);
    getline(file, email);
    getline(file, senha);

    int usuarioId = stoi(id);

    auto findUsuario = find_if(usuarios.begin(), usuarios.end(), [usuarioId](Usuario usuario) {
      return usuarioId == usuario.getId();
    });

    if (findUsuario == usuarios.end()) {
      Usuario newUsuario(usuarioId, nome, email, senha);
      usuarios.push_back(newUsuario);
    }
  }

  file.close();
}

// carrega servidores de um arquivo de texto.
void Sistema::carregarServidores() {
  ifstream file("servidores.txt");

  if (!file) {
    cout << "Não foi possível abrir o arquivo." << endl;
    exit(1);
  }

  string size, id, nome, descricao, codigoConvite, nomeCanal, tipoCanal, data, texto;
  int sizeServidores, sizeUsuarios, sizeCanais, sizeMensagens;

  servidores.clear();

  file >> size;
  sizeServidores = stoi(size);

  file.ignore();

  for (int itServidores = 0; itServidores < sizeServidores; itServidores ++) {
    getline(file, id);
    getline(file, nome);
    getline(file, descricao);
    getline(file, codigoConvite);

    int servidorId = stoi(id);

    Servidor newServidor(servidorId, nome);
    newServidor.setDescricao(descricao);
    if (codigoConvite.empty()) newServidor.setSolicitacao("");
    else newServidor.setSolicitacao(codigoConvite);

    getline(file, size);
    sizeUsuarios = stoi(size);

    for (int itUsuarios = 0; itUsuarios < sizeUsuarios; itUsuarios++) {
      getline(file, id);
      newServidor.pushParticipante(stoi(id));
    }

    getline(file, size);
    sizeCanais = stoi(size);

    for (int itCanais = 0; itCanais < sizeCanais; itCanais++) {
      getline(file, nomeCanal);
      getline(file, tipoCanal);

      shared_ptr <Canal> newCanal;
    }

    servidores.push_back(newServidor);
  }

  file.close();
}

// salva dados da aplicação.
void Sistema::salvar() {
  salvarUsuarios();
  salvarServidores();
}

// carrega dados da aplicação.
void Sistema::carregar() {
  int fileSize = 0;

  ifstream usuarioFile("usuarios.txt");
  ifstream servidorFile("servidores.txt");

  if (usuarioFile) {
    usuarioFile.seekg(0, ios::end);
    fileSize = usuarioFile.tellg();

    if (fileSize > 0) carregarUsuarios();

    usuarioFile.close();
  }

  if (servidorFile) {
    servidorFile.seekg(0, ios::end);
    fileSize = servidorFile.tellg();

    if (fileSize > 0) carregarServidores();

    servidorFile.close();
  }
}