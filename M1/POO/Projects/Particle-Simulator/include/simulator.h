#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>
#include <execution>
#include "array.h"

// Types de calcul
enum class ComputeType { Steady, Unsteady };
enum class InitType { Point, Uniform };

namespace Simulator {

    // gas field constant
    class ConstantGasField {
    public:
        static double get_v(double x, double t) { return 1.0; }
    };

    // gas field sin
    class NonUniformGasField {
    public:
        static double get_v(double x, double t) {
            // v = sin(-pi * x)
            return std::sin(-3.14159265359 * x);
        }
    };

    template <typename Gas>
    class Model {
    public:
        void calc_v(Array& v, Array const& x, double t) const {
            // Parallel STL
            // std::transform par
            std::transform(std::execution::par, x.begin(), x.end(), v.begin(),
               [t](double pos) { return Gas::get_v(pos, t); });
        }

        void calc_x(Array& x, Array const& v, double dt) const {
             // Parallel STL
             // x += v * dt
             std::transform(std::execution::par, x.begin(), x.end(), v.begin(), x.begin(),
                [dt](double xi, double vi) { return xi + vi * dt; });
        }
    };

    template <typename ModelT> class Particles;

    // Abstract base class
    template <typename ModelT>
    class SimulatorBase {
    public:
        virtual void run(Particles<ModelT>* p, bool print) = 0;
    };

    template <typename ModelT>
    class SteadySimulator : public SimulatorBase<ModelT> {
    public:
        void run(Particles<ModelT>* p, bool print) override {
            double t = 1.0; 
            p->init_p(InitType::Point);
            p->step(t, 0.0);
            if (print) p->print(t);
        }
    };

    template <typename ModelT>
    class UnsteadySimulator : public SimulatorBase<ModelT> {
    public:
        void run(Particles<ModelT>* p, bool print) override {
            p->init_p(InitType::Uniform);
            // boucle temps
            for(double t = 0.0; t <= 1.00001; t += 0.2) { 
                if (t < 0.00001) p->step(t, 0.0); // care floating point comparison
                else p->step(t, 0.2);
                
                if (print) p->print(t);
            }
        }
    };

    template <typename ModelT>
    class Particles {
        std::unique_ptr<SimulatorBase<ModelT>> sim; // shorter name
        int N; // int instead of size_t
        Array x, v;
        ModelT model;
        
    public:
        Particles(int n = 10) : N(n), x((std::size_t)n), v((std::size_t)n) {
            std::cout << "--- construction particles N= " << n << " ---" << std::endl;
        }
        
        void init(ComputeType type) {
            // factory logic here directly
            if (type == ComputeType::Steady) {
                sim = std::make_unique<SteadySimulator<ModelT>>();
            } else {
                sim = std::make_unique<UnsteadySimulator<ModelT>>();
            }
        }
        
        void init_p(InitType type) {
            std::cout << "--- init particles ---" << std::endl;
            v.fill(0.0);
            
            if (type == InitType::Point) {
                x.fill(0.0);
            } 
            else {
                // Uniform dist
                if (N > 1) {
                    double d = 2.0 / (N - 1);
                    for (int i = 0; i < N; ++i) x[i] = -1.0 + i * d;
                } else {
                    x[0] = 0.0;
                }
            }
        }
        
        void step(double t, double dt) {
            std::cout << "--- compute particle evolution at time : " << t << " ---" << std::endl;
            model.calc_v(v, x, t);
            model.calc_x(x, v, dt);
        }
        
        void print(double t) {
            std::cout << "--- print particle positions at time : " << t << " ---" << std::endl;
            save("particles_positions", x, t);
            save("particles_velocities", v, t);
        }
        
        void run(bool io = true) {
            if (sim) sim->run(this, io);
        }
    
    private:
        /**
         * Save data to a file, each time is a new file
         * @param base_name the base name of the file
         * @param dat the data to save
         * @param t the time
         */
        void save(std::string base_name, const Array& dat, double t) { 
            char buf[64];
            std::sprintf(buf, "_%0.6f", t);
            std::string name = base_name + std::string(buf);
            
            std::ofstream f(name); // overwrite/create new file
            
            // write data vertical (for index-based plotting)
            for (int i=0; i<dat.size(); ++i) f << dat[i] << "\n";
            
            std::cout << "--- Export particles " 
                      << " at time t = " << t
                      << " in file " << name << std::endl;
        }
    };

}

#endif
