#ifndef MENSAGEM_H
#define MENSAGEM_H
#include <string>

using namespace std;

class Mensagem {
  private:
    string dataHora;
    string conteudo;
    int enviadaPor;

  public:
    Mensagem();
    Mensagem(string dataHora, string conteudo, int enviadaPor);
    ~Mensagem();

//atributo dataHora
    string getDataHora() const;
//altera dataHora
    void setDataHora(string const dataHora);

//atributo conteudo
    string getConteudo() const;
//altera conteudo
    void setConteudo(string const conteudo);

//atributo enviadaPor
    int getEnviadaPor() const;
//altera enviadaPor
    void setEnviadaPor(int const enviadaPor);
};

#endif
