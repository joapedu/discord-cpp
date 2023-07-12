#ifndef VOZ_HPP
#define VOZ_HPP
#include <string>
#include <vector>

#include "../include/canal.h"
#include "../include/mensagem.h"

using namespace std;

class Voz : public Canal {
  // Atributos da classe
  private:
    Mensagem ultimaMensagem;

  // Métodos da classe
  public:
    // Construtor
    Voz();
    // Construtor sobrecarregado
    Voz(string const nome, string const tipo);

    // Retorna um vetor de mensagens
    vector<Mensagem> getMensagens() const;
    // Adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
