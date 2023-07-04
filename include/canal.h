#ifndef CANAL_H
#define CANAL_H
#include <string>
#include <vector>

#include "mensagem.h"

using namespace std;

class Canal {
  protected:
    string nome;
    string tipo;

  public:
//construtor
    Canal();

//sobrecarregado
    Canal(string const nome, string const tipo);

//destrutor
    ~Canal();

//retorna o nome do canal
    virtual string getNome() const;

//altera o nome do canal
    virtual void setNome(string const nome);

//retorna o tipo do canal
    virtual string getTipo() const;

//altera o tipo do canal
    virtual void setTipo(string const tipo);

//vetor de mensagens
    virtual vector<Mensagem> getMensagens() const = 0;
//adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem) = 0;
};

#endif
