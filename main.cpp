// hello.cpp

// g++ -std=c++11 -DNDEBUG -O3 -ffast-math -fPIC *.cpp -I./smile -L./smile -lsmile

#include <smile.h>
#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
#include "smile_license.h"
int main() {

/*
St: estado del bot en tiempo t.
Sus valores pueden ser:
Atacar: El bot dispara al oponente manteniendo una distancia constante con éste
Recoger Armas: El bot recoge un arma que ha detectado
Recoger Energía: El bot recoge un paquete de energía
Explorar: El bot explora el entorno
Huir: El bot intenta separarse del enemigo
Detectar Peligro: El bot busca oponentes en otras localizaciones
*/
// Make a list of pairs with the name of the state and the value of it
  std::pair<std::string, std::vector<std::string>> states[8];
  states[0] = std::make_pair("H", std::vector<std::string>{"Alta","Baja"});
  states[1] = std::make_pair("W", std::vector<std::string>{"Armado","Desarmado"});
  states[2] = std::make_pair("OW", std::vector<std::string>{"Armado","Desarmado"});
  states[3] = std::make_pair("HN", std::vector<std::string>{"Si","No"});
  states[4] = std::make_pair("NE", std::vector<std::string>{"Si","No"});
  states[5] = std::make_pair("PW", std::vector<std::string>{"Si","No"});
  states[6] = std::make_pair("PH", std::vector<std::string>{"Si","No"});
  states[7] = std::make_pair("ST", std::vector<std::string>{"Atacar","RecogerArmas","RecogerEnergia","Explorar","Huir","DetectarPeligro"});


  // Make a map with the posible values for the states 
  int responses[8];


  for (int i = 0; i < 8; i++) {
    // Take the input from the user and store it in the second value of the pair
    std::cout << "Introduce el valor de " << states[i].first << ":" << std::endl << "Posibles valores: ";
    // Muestra los posibles valores
    for (int j = 0; j < states[i].second.size(); j++) {
      std::cout << "(" << j << ") " <<states[i].second[j] << " ";
    }
    std::cout << std::endl;
    std::cin >> responses[i];
  }
  

  DSL_errorH().RedirectToFile(stdout);
  DSL_network net;
  int res = net.ReadFile("bot.xdsl");

  for (int i = 0; i < 8; i++) {
    net.GetNode(states[i].first.c_str())->Val()->SetEvidence(states[i].second[responses[i]].c_str());
  }

  net.UpdateBeliefs();
  DSL_node* sn = net.GetNode("ST_1");
  const DSL_Dmatrix& beliefs = *sn->Val()->GetMatrix();
  const DSL_idArray& outcomes = *sn->Def()->GetOutcomeIds();
  for (int i = 0; i < outcomes.GetSize(); i++) {
    printf("%s=%g\n", outcomes[i], beliefs[i]);
  }
  return DSL_OKAY;
}