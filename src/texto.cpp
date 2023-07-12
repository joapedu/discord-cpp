#include <string>

#include "../include/canal.h"
#include "../include/texto.h"
#include "../include/mensagem.h"

using namespace std;

Texto::Texto() {}

Texto::Texto(string const nome, string const tipo) : Canal(nome, tipo) {}

vector<Mensagem> Texto::getMensagens() const {
  return mensagens;
}

void Texto::sendMensagem(const Mensagem mensagem) {
  mensagens.push_back(mensagem);
}
