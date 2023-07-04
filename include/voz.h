#ifndef VOZ_H
#define VOZ_H
#include <string>
#include <vector>

#include "../include/canal.h"
#include "../include/mensagem.h"

using namespace std;
/*
cópia de texto.h !!!
pois não foi especificado o que fazer sobre chat de voz
*/
class CanalVoz : public Canal {
  private:
    Mensagem ultimaMensagem;

  public:
    CanalVoz();
    CanalVoz(string const nome, string const tipo);

// vetor de mensagens
    vector<Mensagem> getMensagens() const;
// adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
