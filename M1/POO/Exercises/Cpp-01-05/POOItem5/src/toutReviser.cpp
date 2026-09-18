#include <iostream>
#include <string>
#include <cctype>

enum class BoucleMode {
    FOR,
    WHILE,
    INVALID
};

BoucleMode parseChoix(const std::string& input) {
    std::string choix = input;
    // Convertir en minuscules
    for (auto& c : choix) {
        c = std::tolower(c);
    }
    
    if (choix == "for") {
        return BoucleMode::FOR;
    } else if (choix == "while") {
        return BoucleMode::WHILE;
    } else {
        return BoucleMode::INVALID;
    }
}

void executerBoucle(BoucleMode mode) {
    switch (mode) {
        case BoucleMode::FOR:
            std::cout << "Boucle FOR sélectionnée:" << std::endl;
            for (int i = 0; i < 10; i++) {
                std::cout << i << std::endl;
            }
            break;
            
        case BoucleMode::WHILE:
            std::cout << "Boucle WHILE sélectionnée:" << std::endl;
            int i = 0;
            while (i < 10) {
                std::cout << i << std::endl;
                i++;
            }
            break;
            
        case BoucleMode::INVALID:
            // Ne devrait pas arriver ici
            break;
    }
}

int main() {
    std::string choix;
    BoucleMode mode = BoucleMode::INVALID;
    
    while (mode == BoucleMode::INVALID) {
        std::cout << "Veuillez choisir la mode de boucle (for/while): " << std::endl;
        std::cin >> choix;
        
        mode = parseChoix(choix);
        
        if (mode == BoucleMode::INVALID) {
            std::cout << "Choix invalide. Veuillez entrer 'for' ou 'while'.\n" << std::endl;
        }
    }
    
    executerBoucle(mode);
    return 0;
}