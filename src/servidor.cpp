#include <string>
#include <memory>
#include <algorithm>

#include "../include/servidor.h"
#include "../include/canal.h"

using namespace std;

//construtor
Servidor::Servidor() {}

//sobrecarregado
Servidor::Servidor(int usuarioID, string nome) {
  this->usuarioID = usuarioID;
  this->nome = nome;
}

//destrutor
Servidor::~Servidor() {}

//ID do dono do servidor
int Servidor::getUsuarioId() const {
  return usuarioID;
}
//define o ID dono do servidor
void Servidor::setUsuarioId(int const usuarioDonoId) {
  this->usuarioID = usuarioDonoId;
}

//nome do servidor
string Servidor::getNome() const {
  return nome;
}
//define nome do servidor
void Servidor::setNome(string const nome) {
  this->nome = nome;
}

//descrição do servidor
string Servidor::getDescricao() const {
  return descricao;
}
//define a descrição do servidor
void Servidor::setDescricao(string const descricao) {
  this->descricao = descricao;
}

//código de convite do servidor
string Servidor::getSolicitacao() const {
  return solicitacao;
}

//define o código de convite
void Servidor::setSolicitacao(string const solicitacao) {
  this->solicitacao = solicitacao;
}

//IDs dos participantes do servidor
vector<int> Servidor::getMembrosIds(){
    return membrosIds;
}

vector <shared_ptr <Canal>> Servidor::getCanais() const {
  return canais;
}


bool Servidor::createCanal(shared_ptr <Canal> canal) {
  if (canal == nullptr) return false;

  canais.push_back(canal);

  return true;
}

//coloca um usuário na lista de participantes do servidor
bool Servidor::pushParticipante(int const participanteId) {
  for (int i = 0; i < membrosIds.size(); i++) {
    if (membrosIds[i] == participanteId) return false;
  }

  membrosIds.push_back(participanteId);

  return true;
}