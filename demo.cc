#include <parser_Proto.h>
#include <iostream>
#include <fstream>

using namespace std;

void encapsula(TMensagem & msg) {
	TDados pktDados;
	//vector<TDados> vDados;
	
	vector<TSensorDados> vDados;


	for (int n=3; n > 0; n--) {
	    TSensorDados pktSensorDados;
	    vector<TValores> vValores;

	    for (int j=3; j > 0; j--) {
  	      TValores Valores;

	      Valores.set_valor(rand() % 100);
	      Valores.set_timestamp("21/11/2017");
	      vValores.push_back(Valores);
            }

	    pktSensorDados.set_sensor(n);
	    pktSensorDados.set_valores(vValores);

	    vDados.push_back(pktSensorDados);
        }
	pktDados.set_sensores(vDados);

	msg.set_id(1+(rand()%1000));
	TMensagem::Choice_msg & emb = msg.get_msg();
        emb.set_dados(pktDados);
}

int main() {
	//vector<TSensorDesc> v;
	//pkt.get_sensores(v);
        ofstream out("msg.data");
        TMensagem::DerSerializer enc(out);

	for (int i=0; i < 10; i++) {
          TMensagem m;

          encapsula(m);
          m.show();
          enc.serialize(m);
        }
       out.close();

       // decodifica as mensagens contidas no arquivo
       ifstream inp("msg.data");
       TMensagem::DerDeserializer dex(inp);

       cout << endl << endl;
       cout << "==========================" << endl;
       cout << "Decodificando mensagens ..." << endl;
       cout << "==========================" << endl << endl;

       TMensagem * msg;
       // para cada mensagem decodificada ...
       while (msg = dex.deserialize()) {
         // acessa o campo CHOICE
         TMensagem::Choice_msg & emb = msg->get_msg();

         // identifica o tipo de conteúdo que está no campo CHOICE
         switch (emb.get_choice()) {
           case msg_PR_val: {
             TValores val = emb.get_val();
             val.show();
             break;
           }
           case msg_PR_sensor: {
             TSensorDados sens = emb.get_sensor();
             sens.show();
             break;
           }
           case msg_PR_dados: {
             TDados data = emb.get_dados();
             data.show();
             break;
           }
           case msg_PR_NOTHING:
             cout << "NADA" << endl;
             break;
         }
         delete msg;
       }
}
