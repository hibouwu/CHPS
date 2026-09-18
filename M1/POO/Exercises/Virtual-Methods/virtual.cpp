#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

struct ISolver {
  virtual ~ISolver() = default;
  virtual void solve() const = 0;
};

class MySolver : public ISolver {
public:
  explicit MySolver(std::string name) : name_(std::move(name)) {}

  void solve() const override {
    std::cout << "[MySolver] solving " << name_ << std::endl;
  }

private:
  std::string name_;
};

class MyOtherSolver : public ISolver {
public:
  explicit MyOtherSolver(std::string name) : name_(std::move(name)) {}

  void solve() const override {
    std::cout << "[MyOtherSolver] solving " << name_ << std::endl;
  }

private:
  std::string name_;
};

class Solvers {
public:
  template <typename Solver, typename... Args>
  void addSolver(std::string name, Args &&...args) {
    static_assert(std::is_base_of_v<ISolver, Solver>,
                  "Solver must derive from ISolver");
    solvers_.push_back(
        std::make_unique<Solver>(std::move(name), std::forward<Args>(args)...));
  }

  void solve() const {
    std::for_each(solvers_.begin(), solvers_.end(),
                  [](const std::unique_ptr<ISolver> &solver) {
                    solver->solve();
                  });
  }

private:
  std::vector<std::unique_ptr<ISolver>> solvers_;
};

int main() {
  Solvers solvers;
  solvers.addSolver<MySolver>("Navier-Stokes");
  solvers.addSolver<MyOtherSolver>("Poisson");
  solvers.addSolver<MySolver>("Heat");

  solvers.solve();
  return 0;
}
