#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include "simulator.h"
#include "timer.h"

// fonction seq
void solve() { 
    std::cout << "--- Sequential Solve ---" << std::endl;
    Timer t("Sequential Total");

    // partie 1
    {
        using ModelT = Simulator::Model<Simulator::ConstantGasField>;
        Simulator::Particles<ModelT> p(3000000); 
        p.init(ComputeType::Steady);
        p.run(false);
    }

    // partie 2
    {
        using ModelT = Simulator::Model<Simulator::NonUniformGasField>;
        Simulator::Particles<ModelT> p(1000000); 
        p.init(ComputeType::Unsteady);
        p.run(false);
    }
    
    t.stop();
}

// fonction par thread
void solve_par() {
    std::cout << "--- Parallel Solve (std::thread) ---" << std::endl;
    Timer t("Parallel Total");

    // thread 1 steady
    std::thread t1([](){
        using ModelT = Simulator::Model<Simulator::ConstantGasField>;
        Simulator::Particles<ModelT> p(3000000); 
        p.init(ComputeType::Steady);
        p.run(false);
    });

    // thread 2 unsteady
    std::thread t2([](){
        using ModelT = Simulator::Model<Simulator::NonUniformGasField>;
        Simulator::Particles<ModelT> p(1000000); 
        p.init(ComputeType::Unsteady);
        p.run(false);
    });

    t1.join();
    t2.join();
    
    t.stop();
}

// fonction par async
void solve_async() {
    std::cout << "--- Parallel Solve (std::async) ---" << std::endl;
    Timer t("Async Total");

    auto f1 = std::async(std::launch::async, [](){
        using ModelT = Simulator::Model<Simulator::ConstantGasField>;
        Simulator::Particles<ModelT> p(3000000); 
        p.init(ComputeType::Steady);
        p.run(false);
    });

    auto f2 = std::async(std::launch::async, [](){
        using ModelT = Simulator::Model<Simulator::NonUniformGasField>;
        Simulator::Particles<ModelT> p(1000000); 
        p.init(ComputeType::Unsteady);
        p.run(false);
    });

    f1.wait();
    f2.wait();
    
    t.stop();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "faut mettre un argument ! ./Myproject steady ou something" << std::endl;
        return 0;
    }

    std::string s = argv[1]; // arg string

    if (s == "perf") {
        std::string m = "thread";
        if (argc > 2) m = argv[2];

        // test tout
        solve();
        std::cout << std::endl;
        
        if (m == "thread") {
            solve_par();
        } 
        else if (m == "async") {
            solve_async();
        } 
        else if (m == "all") {
            solve_par();
            std::cout << std::endl; // espace
            solve_async();
        }
    }else if (s == "steady") {
         using ModelT = Simulator::Model<Simulator::ConstantGasField>;
         Simulator::Particles<ModelT> p;
         p.init(ComputeType::Steady);
         p.run();
    }else if (s == "unsteady") {
         using ModelT = Simulator::Model<Simulator::NonUniformGasField>;
         // Simulator::Particles<ModelT> p;
         Simulator::Particles<ModelT> p(200); // 200 particles for draw the graph
         p.init(ComputeType::Unsteady);
         p.run();
    } 
    
    return 0;
}
