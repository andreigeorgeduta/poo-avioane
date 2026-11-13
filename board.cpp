#include <iostream>

class Board {
private:
    int** grid;
    int size;

    // Funcție privată utilitară pentru alocarea memoriei
    void allocateMemory() {
        grid = new int*[size];
        for (int i = 0; i < size; ++i) {
            grid[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                grid[i][j] = 0; // 0 înseamnă apă/spațiu gol
            }
        }
    }

    // Funcție privată utilitară pentru dezalocare
    void freeMemory() {
        if (grid != nullptr) {
            for (int i = 0; i < size; ++i) {
                delete[] grid[i];
            }
            delete[] grid;
            grid = nullptr;
        }
    }

public:
    // 1. Constructor
    Board(int boardSize = 10) : size(boardSize), grid(nullptr) {
        allocateMemory();
        std::cout << "[+] Board " << size << "x" << size << " alocat.\n";
    }

    // 2. Destructor (Rule of 3 - Partea 1)
    ~Board() {
        freeMemory();
        std::cout << "[-] Board distrus și memorie eliberată.\n";
    }

    // 3. Constructor de copiere (Rule of 3 - Partea 2) -> Deep Copy
    Board(const Board& other) : size(other.size), grid(nullptr) {
        allocateMemory();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                this->grid[i][j] = other.grid[i][j];
            }
        }
        std::cout << "[+] Board copiat.\n";
    }

    // 4. Operator de atribuire = (Rule of 3 - Partea 3)
    Board& operator=(const Board& other) {
        if (this != &other) { // Evităm auto-atribuirea (ex: tabla = tabla)
            freeMemory();     // Ștergem matricea veche
            size = other.size;
            allocateMemory(); // Alocăm spațiu nou
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    this->grid[i][j] = other.grid[i][j];
                }
            }
            std::cout << "[=] Board atribuit (copiat prin operator=).\n";
        }
        return *this;
    }

    // Funcție provizorie de test pentru afișare
    void print() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "--- Testare Task 1: Rule of 3 ---\n";
    
    Board tablaJucator1(10); // Apelează constructorul normal
    
    {
        Board tablaTemporara = tablaJucator1; // Apelează constructorul de copiere
        // La ieșirea din aceste acolade, tablaTemporara va fi ștearsă automat,
        // dar tablaJucator1 va rămâne intactă datorită Deep Copy-ului.
    } 

    Board tablaJucator2(5);
    tablaJucator2 = tablaJucator1; // Apelează operatorul de atribuire

    std::cout << "\nTabla Jucator 2 (ar trebui sa fie 10x10 cu 0):\n";
    tablaJucator2.print();

    std::cout << "--- Final ---\n";
    return 0;
}