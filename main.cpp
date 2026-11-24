#include <iostream>
#include <vector>
#include "Aircraft.h"

int main() {
    // Polimorfism: Un vector de pointeri catre clasa de baza (Aircraft*),
    // dar in el bagam obiecte derivate diferite!
    std::vector<Aircraft*> flota;

    flota.push_back(new BomberPlane(2, 3)); // Capul e la (2, 3)
    flota.push_back(new FighterJet(5, 5));  // Capul e la (5, 5)

    std::cout << "--- Simulare Atacuri ---\n";
    
    // Atacam Bombardierul in aripa (sa zicem la 2,4)
    flota[0]->takeHit(2, 4); 
    // Atacam Bombardierul fix in CAP (2,3) -> ar trebui sa moara instant!
    flota[0]->takeHit(2, 3); 

    std::cout << "\n";

    // Atacam Avionul de vanatoare in cap (5,5) -> NU moare instant, doar scade viata la 1
    flota[1]->takeHit(5, 5);
    // Il mai lovim o data -> abia acum moare
    flota[1]->takeHit(5, 6);

    // Curatam memoria alocata cu 'new'
    for (Aircraft* avion : flota) {
        delete avion; // Aici intra in actiune destructorul virtual!
    }

    return 0;
}