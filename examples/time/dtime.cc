#include <parser_Time.h>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
  TTempo pkt;

  // definindo os valores de varios campos 
  pkt.set_data(time(NULL));
  vector<time_t> v;
  v.push_back(time(NULL));
  v.push_back(time(NULL)-86400);
  v.push_back(time(NULL)-2*86400);
  pkt.set_nada(v);

  uint8_t vb[2] = {0xaa,0xcc};
  pkt.set_bs(vb);

  pkt.set_oid("1.3.6.4.1.100");
  ASN1Oid & oid = pkt.get_oid_attr();
  oid += "20.30";  
    cout << "oid=" << oid.str() << endl;
  // verifica se os valores contidos na estrutura de dados respeitam
  // a especificação
  pkt.check_constraints();

  // mostra a estrutura de dados na tela
  cout << "Estrutura de dados em memória (antes de codificação DER):" << endl;
  pkt.show();

  // cria o codificador
  ofstream out("pkt.data");
  TTempo::XerSerializer encoder(out);

  // codifica a estrutura de dados
  encoder.serialize(pkt);
  out.close();

  // cria o decodificador
  ifstream arq("pkt.data");
  TTempo::XerDeserializer decoder(arq);

  // tenta decodificar uma estrutura de dados
  TTempo * other = decoder.deserialize();
  arq.close();

  cout << endl;

  if (other) {
    cout << "Estrutura de dados obtida da decodificação DER:" << endl;
    other->show();
    string soid = other->get_oid();
    cout << "oid=" << soid << endl;
    ASN1Oid & oid = other->get_oid_attr();
    cout << "oid=" << oid.str() << endl;
  } else cerr << "Erro: não consegui decodificar a estrutura de dados ..." << endl;

  // devem-se destruir explicitamente as estruturas de dados obtidas 
  // do decodificador 
  delete other; 
}
