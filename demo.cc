#include <parser_Exemplo2.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {
  if (argc < 2) {
    cerr << "Uso: " << argv[0] << " arquivo_codificado" << endl;
    return 0;
  }
  
  // cria o decodificador
  ifstream arq(argv[1]);
  if (! arq.is_open()) {
    perror("Ao abrir o arquivo");
    return errno;
  }
  
  TAlgo::DerDeserializer decoder(arq);

  // tenta decodificar uma estrutura de dados
  auto other = decoder.deserialize();
  arq.close();

  cout << endl;

  if (other) {
    cout << "Estrutura de dados obtida da decodificação DER:" << endl;
    other->show();
  } else cerr << "Erro: não consegui decodificar a estrutura de dados ..." << endl;

  // devem-se destruir explicitamente as estruturas de dados obtidas 
  // do decodificador 
  delete other; 
}
