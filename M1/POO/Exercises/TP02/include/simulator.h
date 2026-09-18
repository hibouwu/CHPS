#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>

enum class ComputeType {
    Steady,
    Unsteady
};

namespace Simulator {
    
    // Classe de base Simulator
    class SimulatorBase {
    public:
        virtual ~SimulatorBase() = default;
        virtual void compute(class Particles* particles) = 0;
    };
    
    // Fabrique utilisée pour créer un simulateur
    class SimulatorFactory {
    public:
        static ComputeType stringToComputeType(const std::string& type_str);
        static SimulatorBase* createSimulator(ComputeType compute_type);
        static void printUsage();
    };
    
    // Simulateur en régime permanent
    class SteadySimulator : public SimulatorBase {
    public:
        void compute(class Particles* particles) override;
    };
    
    // Simulateur instationnaire
    class UnsteadySimulator : public SimulatorBase {
    public:
        void compute(class Particles* particles) override;
    };
    
    // Classe Particles
    class Particles {
    private:
        SimulatorBase* simulator_;
        
    public:
        Particles();
        ~Particles();
        
        // Constructeur de copie et opérateur d'affectation désactivés (simplifie la gestion mémoire)
        Particles(const Particles&) = delete;
        Particles& operator=(const Particles&) = delete;
        
        void init(ComputeType compute_type);
        void init_particles();
        void compute_particles(double time);
        void print_particles(double time);
        void compute();
    };
}

#endif // SIMULATOR_H
