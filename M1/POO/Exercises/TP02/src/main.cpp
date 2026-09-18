#include <iostream>
#include "simulator.h"

int main(int argc, char** argv) {
    // Vérifier les arguments de la ligne de commande
    if (argc != 2) {
        std::cout << "Error: Incorrect number of arguments." << std::endl;
        std::cout << std::endl;
        Simulator::SimulatorFactory::printUsage();
        return 1;
    }
    
    try {
        // Récupérer l'argument de la ligne de commande
        std::string simulation_type(argv[1]);
        
        // Utiliser la fabrique pour convertir la chaîne en ComputeType
        ComputeType compute_type = Simulator::SimulatorFactory::stringToComputeType(simulation_type);
        
        // Créer l'objet Particles et lancer la simulation
        std::cout << "=== Running " << simulation_type << " simulation ===" << std::endl;
        Simulator::Particles particles;
        particles.init(compute_type);
        particles.compute();
        
        std::cout << "=== Simulation completed successfully ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << std::endl;
        Simulator::SimulatorFactory::printUsage();
        return 1;
    }
    
    return 0;
}
