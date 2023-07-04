#include <string>

#include "../include/canal.h"
#include "../include/texto.h"
#include "../include/mensagem.h"

using namespace std;

CanalTexto::CanalTexto() {}

CanalTexto::CanalTexto(string const nome, string const tipo) : Canal(nome, tipo) {}

vector<Mensagem> CanalTexto::getMensagens() const {
  return mensagens;
}

void CanalTexto::sendMensagem(const Mensagem mensagem) {
  mensagens.push_back(mensagem);
}
