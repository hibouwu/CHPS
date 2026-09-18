#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class ISolver {
public : 
  virtual void solve() = 0;
  virtual ~ISolver() = default;
};

class MySolver : public ISolver {
  std::string m_name;
public:
 MySolver(std::string name) : m_name(std::move(name)){}
 void solve() override {std::cout << "MySolver::"<<m_name << "::solve()" << std::endl;}
};

class MyOtherSolver : public ISolver {
   std::string m_name;
 public:
   MyOtherSolver(std::string name) : m_name(std::move(name)){}
 void solve() override {std::cout << "MyOtherSolver::"<<m_name << "::solve()" << std::endl;}
};

class Solvers {
  using ISolverPtr = std::unique_ptr<ISolver>;
  std::vector<ISolverPtr> m_solvers;
public:
  template <typename T>
  void addSolver(std::string name) {
    m_solvers.push_back(std::make_unique<T>(std::move(name)));
  }

  void solve() {
    std::for_each(m_solvers.begin(), m_solvers.end(),
                  [](auto& solver){solver->solve();});
  }
};

int main() {
  Solvers solvers{};
  solvers.addSolver<MySolver>("first_solver");
  solvers.addSolver<MyOtherSolver>("second_solver");
  solvers.solve();
}