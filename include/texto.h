#ifndef TEXTO_H
#define TEXTO_H
#include <string>
#include <vector>

#include "../include/canal.h"
#include "../include/mensagem.h"

using namespace std;

class Texto : public Canal {
  // Atributos da classe
  private:
    vector<Mensagem> mensagens;

  // Métodos da classe
  public:
    // Construtor
    Texto();
    // Construtor sobrecarregado
    Texto(string const nome, string const tipo);

    // Retorna um vetor de mensagens
    vector<Mensagem> getMensagens() const;
    // Adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
