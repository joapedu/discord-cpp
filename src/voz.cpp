#include <string>

#include "../include/canal.h"
#include "../include/voz.h"
#include "../include/mensagem.h"

using namespace std;

Voz::Voz() {}

Voz::Voz(string const nome, string const tipo) : Canal(nome, tipo) {}

vector<Mensagem> Voz::getMensagens() const {
  vector<Mensagem> mensagens;

  if (!ultimaMensagem.getConteudo().empty()) mensagens.push_back(ultimaMensagem);

  return mensagens;
}

void Voz::sendMensagem(const Mensagem mensagem) {
  ultimaMensagem.setConteudo(mensagem.getConteudo());
  ultimaMensagem.setDataHora(mensagem.getDataHora());
  ultimaMensagem.setEnviadaPor(mensagem.getEnviadaPor());
}
