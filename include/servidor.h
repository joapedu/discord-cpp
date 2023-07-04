#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <string>
#include <vector>
#include <memory>

#include "canal.h"
#include "texto.h"
#include "voz.h"

using namespace std;

class Servidor {
  private:
    int usuarioID;
    string nome;
    string descricao;
    string solicitacao;
    vector <int> membrosIds;
    vector <shared_ptr <Canal>> canais;

  public:
//construtor
    Servidor();
//sobrecarregado
    Servidor(int usuarioID, string nome);
//destrutor
    ~Servidor();

//canais presentes no servidor
    vector <shared_ptr <Canal>> getCanais() const;
//cria um canal no servidor
    bool createCanal(shared_ptr <Canal> canal);

//nome cadastrado do servidor
    string getNome() const;
//altera nome do servidor
    void setNome(string const nome);

//descrição do servidor
    string getDescricao() const;
//altera a descrição do servidor
    void setDescricao(string const descricao);

//ID do dono do servidor
    int getUsuarioId() const;
//altera o ID do dono do servidor
    void setUsuarioId(int const usuarioID);

//lista ID's dos participantes do servidor
    vector<int> getMembrosIds();

//adiciona um participante no servidor
    bool pushParticipante(int const membroId);

//código de solicitacao para entrada no servidor
    string getSolicitacao() const;
//altera o código de solicitacao do servidor
    void setSolicitacao(string const solicitacao);

//canais de texto do servidor
    vector<string> getCanaisTexto() const;
//canais de voz do servidor
    vector<string> getCanaisVoz() const;
//vetor com as mensagens de um canal no servidor
    vector<Mensagem> getMensagens(const string nomeCanal);
//envia uma mensagem em um canal no servidor
    void sendMensagem(const string nomeCanal, const Mensagem mensagem);
};

#endif