#include <parser_Ativo.h>
#include <iostream>
#include <fstream>
 
using namespace std;
 
int main() {
  TAtivo pkt;
 
  // definindo os valores de varios campos 
  vector<long> vn;
  vn.push_back(35123);
  pkt.set_codigo(vn);
  pkt.set_nome( "PETR3");
  pkt.set_data("30092015");
  pkt.set_horario("135812");
 
  // este campo "cod" é do tipo enumerated "Teste"
  pkt.set_cod(Teste_um);
 
  // "valor" é um campo do tipo sequence of, e pode ser 
  // definido usando um vector ...
  vector<TExtra> v;
  TExtra e;
  e.set_id(11);
  e.set_desc("teste");
  v.push_back(e);
  pkt.set_valor(v);
 
  // "conteudo" é um choice ... aqui se escolhe seu campo "ot" 
  // que é do tipo TOutro (um sequence)
  Choice_Conteudo & con = pkt.get_conteudo();
  TOutro ot = con.get_ot();
  ot.set_id(777);
  vector<string> vt;
  vt.push_back("um");
  ot.set_valor(vt);
  ot.set_ok(0);
 
  // verifica se os valores contidos na estrutura de dados respeitam
  // a especificação
  pkt.check_constraints();
 
  // mostra a estrutura de dados na tela
  cout << "Estrutura de dados em memória (antes de codificação XER):" << endl;
  pkt.show();
 
  // cria o codificador
  ofstream out("pkt.data");
  TAtivo::XerSerializer encoder(out);
 
  // codifica a estrutura de dados
  encoder.serialize(pkt);
  out.close();
 
  // cria o decodificador
  ifstream arq("pkt.data");
  TAtivo::XerDeserializer decoder(arq);
 
  // tenta decodificar uma estrutura de dados
  TAtivo * other = decoder.deserialize();
  arq.close();
 
  cout << endl;
 
  if (other) {
    cout << "Estrutura de dados obtida da decodificação XER:" << endl;
    other->show();
  } else cerr << "Erro: não consegui decodificar a estrutura de dados ..." << endl;
 
  // devem-se destruir explicitamente as estruturas de dados obtidas 
  // do decodificador 
  delete other; 
}
