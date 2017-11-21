#include <parser_Proto.h>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	//vector<TSensorDesc> v;
	//pkt.get_sensores(v);

	TDados pktDados;
	//vector<TDados> vDados;
	
	vector<TSensorDados> vDados;
	TSensorDados pktSensorDados;

	TValores Valores;
	vector<TValores> vValores;

	    Valores.set_valor(1);
	    Valores.set_timestamp("17/11/2017");
	    vValores.push_back(Valores);

	    pktSensorDados.set_sensor(6);
	    pktSensorDados.set_valores(vValores);

	    vDados.push_back(pktSensorDados);
	    pktDados.set_sensores(vDados);
 	    pktDados.show();
}
