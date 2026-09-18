#include <gtest/gtest.h>

#include "simulator.h"

TEST(ArrayTest, BasicOperations) {
    Array a(5, 10.0);
    EXPECT_EQ(a.size(), 5);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_DOUBLE_EQ(a[i], 10.0);
    }

    a.fill(2.0);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_DOUBLE_EQ(a[i], 2.0);
    }
    
    a[0] = 5.0;
    EXPECT_DOUBLE_EQ(a[0], 5.0);
}

TEST(PhysicsTest, ConstantModelStep) {
    // Verify that Model correctly calculates v and x
    using ModelT = Simulator::Model<Simulator::ConstantGasField>;
    ModelT model;
    
    Array x(1, 0.0); // 1 particle at 0.0
    Array v(1, 0.0);
    
    double t = 0.5;
    double dt = 0.1;
    
    // Step 1: calc_v
    // ConstantGasField returns 1.0 regardless of x or t
    model.calc_v(v, x, t);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    
    // Step 2: calc_x
    // x_new = x_old + v * dt = 0.0 + 1.0 * 0.1 = 0.1
    model.calc_x(x, v, dt);
    EXPECT_DOUBLE_EQ(x[0], 0.1);
}

TEST(ParticlesTest, InitSteadyAndCompute) {
    using ModelT = Simulator::Model<Simulator::ConstantGasField>;
    Simulator::Particles<ModelT> p;
    p.init(ComputeType::Steady);
    p.run(false); // run instead of compute, false to skip IO during test
}

TEST(ParticlesTest, InitUnsteadyAndCompute) {
    using ModelT = Simulator::Model<Simulator::NonUniformGasField>;
    Simulator::Particles<ModelT> p;
    p.init(ComputeType::Unsteady);
    p.run(false);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
