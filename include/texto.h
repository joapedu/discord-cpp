#ifndef TEXTO_H
#define TEXTO_H
#include <string>
#include <vector>

#include "../include/canal.h"
#include "../include/mensagem.h"

using namespace std;

class CanalTexto : public Canal {
  private:
    vector<Mensagem> mensagens;
  public:
    CanalTexto();
    CanalTexto(string const nome, string const tipo);

// vetor de mensagens
    vector<Mensagem> getMensagens() const;
// adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
