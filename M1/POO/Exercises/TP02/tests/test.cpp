#include <gtest/gtest.h>
#include "simulator.h"

TEST(ParticlesTest, InitParticlesTest) {
    Simulator::Particles particles;
    particles.init_particles();
}

TEST(ParticlesTest, PrintParticlesTest) {
    Simulator::Particles particles;
    particles.print_particles(0);
}

TEST(ParticlesTest, ComputeParticleEvolution) {
    Simulator::Particles particles;
    particles.compute_particles(0.5);
}

TEST(ParticlesTest, SteadyStateTest) {
    Simulator::Particles particles;
    particles.init(ComputeType::Steady);
    particles.compute();
}

TEST(ParticlesTest, UnsteadyStateTest) {
    Simulator::Particles particles;
    particles.init(ComputeType::Unsteady);
    particles.compute();
}

TEST(SimulatorTest, SteadySimulatorTest) {
    Simulator::Particles particles;
    particles.init(ComputeType::Steady);
    particles.compute();
}

TEST(SimulatorTest, UnsteadySimulatorTest) {
    Simulator::Particles particles;
    particles.init(ComputeType::Unsteady);
    particles.compute();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}