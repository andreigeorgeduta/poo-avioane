#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <iostream>
#include <string>

// Clasa de baza ABSTRACTA
class Aircraft {
protected: // 'protected' inseamna ca doar aceasta clasa si copiii ei (Bomber, Fighter) au acces la aceste variabile
    std::string name;
    int health;
    int headX;
    int headY;
    bool isDestroyed;

public:
    // Constructor
    Aircraft(const std::string& aircraftName, int hp, int x, int y)
        : name(aircraftName), health(hp), headX(x), headY(y), isDestroyed(false) {}

    // Destructor VIRTUAL -> OBLIGATORIU cand folosim mostenire si polimorfism!
    virtual ~Aircraft() {}

    // Functie VIRTUALA PURA (= 0) -> Transforma clasa in una abstracta.
    // Returneaza true daca avionul tocmai a fost doborat la aceasta lovitura, false altfel.
    virtual bool takeHit(int hitX, int y) = 0;

    // Metode comune (Gettere)
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    bool getIsDestroyed() const { return isDestroyed; }
    int getHeadX() const { return headX; }
    int getHeadY() const { return headY; }
};

// ---------------------------------------------------------
// CLASA DERIVATA 1: Bombardierul clasic (moare instant la lovitura in cap)
// ---------------------------------------------------------
class BomberPlane : public Aircraft {
public:
    // Apeleaza constructorul parintelui (Aircraft) trimitandu-i numele si 3 vieti
    BomberPlane(int x, int y) : Aircraft("Bombardier Clasic", 3, x, y) {}

    // Suprascriem (override) functia virtuala din parinte
    bool takeHit(int hitX, int hitY) override {
        if (isDestroyed) return false; // Deja mort

        // Verificam daca a fost lovit fix in CAP
        if (hitX == headX && hitY == headY) {
            health = 0;
            isDestroyed = true;
            std::cout << "[CRITIC] " << name << " a fost lovit in CAP si a explodat instant!\n";
            return true;
        }

        // Daca a fost lovit in aripa/coada
        health--;
        std::cout << "[LOVIT] " << name << " a fost avariat! Viata ramasa: " << health << "\n";
        
        if (health <= 0) {
            isDestroyed = true;
            std::cout << "[DOBORAT] " << name << " s-a prabusit!\n";
            return true;
        }
        return false;
    }
};

// ---------------------------------------------------------
// CLASA DERIVATA 2: Avion de vanatoare (2 vieti, fara punct slab in cap)
// ---------------------------------------------------------
class FighterJet : public Aircraft {
public:
    FighterJet(int x, int y) : Aircraft("Avion de Vanatoare", 2, x, y) {}

    bool takeHit(int hitX, int hitY) override {
        if (isDestroyed) return false;

        // Ignoram coordonatele capului, scadem pur si simplu 1 viata
        health--;
        std::cout << "[LOVIT] " << name << " incasat o lovitura! Viata ramasa: " << health << "\n";

        if (health <= 0) {
            isDestroyed = true;
            std::cout << "[DOBORAT] " << name << " a fost distrus!\n";
            return true;
        }
        return false;
    }
};

#endif