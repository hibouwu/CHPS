#include "simulator.h"
#include <iostream>
#include <map>
#include <stdexcept>

namespace Simulator {

    // Implémentation de la classe Particles
    Particles::Particles() : simulator_(nullptr) {
    }
    
    Particles::~Particles() {
        delete simulator_;
    }
    
    void Particles::init(ComputeType compute_type) {
        // Nettoyer l'ancien simulateur
        delete simulator_;
        
        // Créer le simulateur approprié selon le type
        switch(compute_type) {
            case ComputeType::Steady:
                simulator_ = new SteadySimulator();
                break;
            case ComputeType::Unsteady:
                simulator_ = new UnsteadySimulator();
                break;
        }
    }
    
    void Particles::init_particles() {
        std::cout << "--- init particles ---" << std::endl;
    }
    
    void Particles::compute_particles(double time) {
        std::cout << "--- compute particle evolution at time : " << time << " ---" << std::endl;
    }
    
    void Particles::print_particles(double time) {
        std::cout << "--- print particle positions at time : " << time << " ---" << std::endl;
    }
    
    void Particles::compute() {
        if (simulator_) {
            simulator_->compute(this);
        }
    }
    
    void SteadySimulator::compute(Particles* particles) {
        particles->init_particles();
        particles->compute_particles(1.0);
        particles->print_particles(1.0);
    }
    
    void UnsteadySimulator::compute(Particles* particles) {
        particles->init_particles();
        for(double time = 0.0; time <= 0.8; time += 0.2) {
            particles->compute_particles(time);
            particles->print_particles(time);
        }
    }

    void run_simulation(ComputeType compute_type) {
        Particles particles;
        particles.init(compute_type);
        particles.compute();
    }


    
    // Implémentation de la fabrique SimulatorFactory
    ComputeType SimulatorFactory::stringToComputeType(const std::string& type_str) {
        static const std::map<std::string, ComputeType> stringToTypeMap = {
            {"steady", ComputeType::Steady},
            {"unsteady", ComputeType::Unsteady}
        };
        
        auto it = stringToTypeMap.find(type_str);
        if (it != stringToTypeMap.end()) {
            return it->second;
        }
        
        throw std::invalid_argument("Invalid compute type: " + type_str);
    }
    
    SimulatorBase* SimulatorFactory::createSimulator(ComputeType compute_type) {
        switch(compute_type) {
            case ComputeType::Steady:
                return new SteadySimulator();
            case ComputeType::Unsteady:
                return new UnsteadySimulator();
            default:
                throw std::invalid_argument("Unknown compute type");
        }
    }
    
    void SimulatorFactory::printUsage() {
        std::cout << "Usage: ./Myproject <simulation_type>" << std::endl;
        std::cout << "Available simulation types:" << std::endl;
        std::cout << "  steady   - Run steady state simulation" << std::endl;
        std::cout << "  unsteady - Run unsteady (transient) simulation" << std::endl;
        std::cout << std::endl;
        std::cout << "Example: ./Myproject steady" << std::endl;
        std::cout << "Example: ./Myproject unsteady" << std::endl;
    }

} // espace de noms Simulator
