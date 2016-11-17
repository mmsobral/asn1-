#include <parser_Ativo.h>
#include <iostream>
#include <sstream>
#include "TCPBaseSocket.h"

using namespace std;

int main() {
  TAtivo pkt, pkt1, pkt2;

  // definindo os valores de varios campos 
  TAtivo::Choice_id & id = pkt.get_id();
  TTipo2 t2 = id.get_t2();

  t2.set_nome("PETR3");
  vector<bool> v;
  v.push_back(true);
  v.push_back(false);
  t2.set_id(v);
 
  //pkt.set_codigo(111);
  pkt.set_valor(1298);
  //pkt.set_nome( "PETR3");
  pkt.set_data("30092015");
  pkt.set_horario("135812");

  TAtivo::Choice_id & id2 = pkt2.get_id();
  TTipo2 t2b = id2.get_t2();

  t2b.set_nome("PETR3");
  vector<bool> v2;
  v2.push_back(true);
  v2.push_back(false);
  v2.push_back(true);
  v2.push_back(false);
  t2b.set_id(v2);
 
  pkt2.set_valor(9999);
  pkt2.set_data("01082016");
  pkt2.set_horario("230100");

  TAtivo::Choice_id & id1 = pkt1.get_id();
  TTipo1 t1 = id1.get_t1();

  t1.set_nome("PETR3");
  vector<long> v1;
  v1.push_back(11);
  v1.push_back(22);
  v1.push_back(33);
  t1.set_id(v1);
 
  pkt1.set_valor(5566);
  pkt1.set_data("29022016");
  pkt1.set_horario("010203");
  // verifica se os valores contidos na estrutura de dados respeitam
  // a especificação
  pkt.check_constraints();

  // mostra a estrutura de dados na tela
  cout << "Estrutura de dados em memória (antes de codificação DER):" << endl;
  pkt.show();
  pkt1.show();
  pkt2.show();

  // cria o codificador
  ostringstream out;
  TAtivo::DerSerializer encoder(out);
  encoder.serialize(pkt);
  encoder.serialize(pkt1);
  encoder.serialize(pkt2);

  TCPClientSocket sock;

  sock.connect("127.0.0.1", 9999);
  // codifica a estrutura de dados
  string conteudo = out.str();
  cout << "E#nviou: " << sock.send(conteudo) << " bytes de " << conteudo.size() << endl;

  sleep(1);

  sock.close();
}

