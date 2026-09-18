#include "gtest/gtest.h"
#include "MyClass.h"
#include <sstream>
#include <iostream>

// Test for the print method
TEST(UnitTest, MylibTestPrintTest) {
    MyLib::MyClass obj;
    // Redirect cout to capture output
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    
    // Test print method
    obj.print("Test message");
    std::cout.rdbuf(old_cout);
    EXPECT_TRUE(output.str().find("Test message") != std::string::npos);
}

// Additional test to verify constructor works
TEST(UnitTest, MylibTestConstructorTest) {
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    MyLib::MyClass obj;
    
    // Restore cout
    std::cout.rdbuf(old_cout);
    
    // Verify constructor message appears
    EXPECT_TRUE(output.str().find("MyClass constructor called") != std::string::npos);
}

TEST(UnitTest, MylibTestValueMethod) {
    MyLib::MyClass obj;
    EXPECT_EQ(42, obj.value());
}
