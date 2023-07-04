#include <string>

#include "../include/canal.h"
#include "../include/voz.h"
#include "../include/mensagem.h"

using namespace std;

CanalVoz::CanalVoz() {}

CanalVoz::CanalVoz(string const nome, string const tipo) : Canal(nome, tipo) {}

vector<Mensagem> CanalVoz::getMensagens() const {
  vector<Mensagem> mensagens;

  if (!ultimaMensagem.getConteudo().empty()) mensagens.push_back(ultimaMensagem);

  return mensagens;
}

void CanalVoz::sendMensagem(const Mensagem mensagem) {
  ultimaMensagem.setConteudo(mensagem.getConteudo());
  ultimaMensagem.setDataHora(mensagem.getDataHora());
  ultimaMensagem.setEnviadaPor(mensagem.getEnviadaPor());
}
