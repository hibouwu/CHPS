# 1D Particle Simulator in C++

## 1. One-line Positioning
适合投递 C++ 后端 / C++ 工程基础 / 并行编程入门方向，重点是模板建模、策略/多态组织、Parallel STL、`std::thread` 和 `std::async` 对比。

## 2. Recruiter Summary
该项目是一个 C++ 一维粒子模拟器，支持 steady 和 unsteady 两类气体场下的粒子位置、速度演化，并输出可用于 gnuplot 绘图的数据文件。代码使用模板把气体场、模型和粒子系统组合起来，用抽象基类区分 steady/unsteady simulator，并在计算速度和位置更新时使用 Parallel STL。项目还包含 `std::thread` 与 `std::async` 的性能模式入口，可作为 C++ 类设计、模板泛型和基础并发实践的证据。该目录不是 git 仓库，附近也未发现包含该项目路径的 git 历史，因此个人贡献仍无法用 git 确认。

## 3. My Work
- 项目整体内容：C++ 粒子模拟器，支持 steady/unsteady 两种运行模式、文件输出、gnuplot 绘图、GoogleTest 测试和简单并行性能入口。
- 时间范围：该目录没有 git 历史；文件系统时间戳显示可参考范围为 2025-11-13 至 2025-12-21，其中主要代码文件集中在 2025-12-20 至 2025-12-21。该时间只能作为本地文件时间参考，不能作为严格开发周期证据。
- 我实际完成或主要参与的内容：缺少报告和分工记录，无法从材料确认个人完成范围。
- 需要人工确认的个人贡献：`include/simulator.h` 中模板模型、Parallel STL、`SimulatorBase` 多态结构，`src/main.cpp` 中 perf/thread/async 入口，以及测试文件是否由本人实现；当前只能作为“项目包含”表述。

## 4. Technical Stack
- 语言：C++17/20 风格代码
- 构建：CMake
- 并行：Parallel STL `std::execution::par`, `std::thread`, `std::async`
- 测试：GoogleTest
- 可视化：gnuplot
- 输出：`particles_positions_*`, `particles_velocities_*`, `unsteady_particule_positions_t0-t1.png`, `unsteady_particule_velocities_t0-t1.png`

## 5. Work Path / 工作路径
- baseline 是什么：一维粒子数组 `x/v`，在气体速度场 `v(x,t)` 下用 `x += v * dt` 更新。
- 遇到的主要问题是什么：需要同时支持 steady 与 unsteady 两种计算路径，并让 gas field 可替换。
- 如何定位问题：README 给出运行命令和输出文件；GoogleTest 验证 Array、常量气体场更新和两种 simulator 可运行。
- 做了哪些实现、重构或优化：用 `Model<Gas>` 模板抽象气体场；用 `SteadySimulator` / `UnsteadySimulator` 多态执行；用 Parallel STL 并行 `calc_v` 和 `calc_x`；在 `perf` 模式中对比 sequential、thread、async。
- 如何验证：`tests/test.cpp` 验证 `Array::fill/operator[]`、常量场一步更新 `x=0.1`，以及 steady/unsteady 初始化和运行不崩溃。
- 结果如何：README 确认可生成 steady/unsteady 数据文件和绘图；缺少 benchmark 输出和性能数字，需要补充。
- 还有什么局限：没有报告、没有性能输出文件、没有详细数值误差验证；个人贡献无法确认。

## 6. Evidence Map

| Claim | Evidence | File / Path | Confidence | Interview Risk |
|---|---|---|---|---|
| 项目是 C++ 一维粒子模拟器，支持 steady/unsteady | README 描述和 CLI 命令 | `POO/POO-TPProjet/README.md` | High | 可能被问物理模型是否足够真实，需说明是课程模拟器 |
| steady 输出 `particles_positions`, `particles_velocities` | README execution 章节 | `POO/POO-TPProjet/README.md` | High | 实际代码会追加时间后缀 `_1.000000`，需解释 README 与实现差异 |
| unsteady 以 `t=0..1`、步长 0.2 输出多组文件 | README 和 `UnsteadySimulator::run` 循环 | `POO/POO-TPProjet/README.md`; `POO/POO-TPProjet/include/simulator.h` | High | 浮点时间命名和文件覆盖策略可能被问 |
| 使用模板 `Model<Gas>` 支持不同气体场 | `ConstantGasField`, `NonUniformGasField`, `Model<Gas>` | `POO/POO-TPProjet/include/simulator.h` | High | 需要说明模板相比虚函数的取舍 |
| 使用 Parallel STL 并行速度和位置更新 | `std::transform(std::execution::par, ...)` | `POO/POO-TPProjet/include/simulator.h` | High | Parallel STL 实际后端依赖标准库实现，性能不可保证 |
| 提供 `std::thread` 和 `std::async` perf 模式 | `solve_par`, `solve_async`, README perf 命令 | `POO/POO-TPProjet/src/main.cpp`; `POO/POO-TPProjet/README.md` | High | 缺少性能输出，不应声称加速比 |
| 有 GoogleTest 基础测试 | `ArrayTest`, `PhysicsTest`, `ParticlesTest` | `POO/POO-TPProjet/tests/test.cpp` | High | 测试偏 smoke/correctness，覆盖率有限 |
| 个人贡献无法从材料确认 | 仅 README/代码，无分工报告 | `POO/POO-TPProjet/README.md` | High | 不能写“我实现了”，需人工确认 |
| 可参考文件时间为 2025-11-13 至 2025-12-21 | 本地文件系统 mtime；主要代码集中在 2025-12-20 至 2025-12-21 | `POO/POO-TPProjet/` | Low | mtime 可被复制/解压/编辑改变，不等同 git 历史 |

## 7. Detailed Project Experience / 详细项目经历母版
项目整体目标是实现一个简单的一维粒子模拟程序，使粒子在不同气体场下演化，并将位置、速度输出为可绘图文件。项目不是大型物理仿真，而是 C++ 面向对象课程项目，重点在类设计、模板、运行模式组织和基本并行 API 使用。

我承担或主要参与的模块缺少证据，需要人工确认。可以确认的项目模块包括：`Array` 容器封装、`GasField` 策略、`Model<Gas>` 计算模型、`Particles<ModelT>` 状态管理、steady/unsteady simulator 多态、CLI 入口、性能入口和 GoogleTest。

技术实现上，`ConstantGasField` 返回常数速度，`NonUniformGasField` 使用 `sin(-pi*x)`。`Model<Gas>::calc_v` 和 `calc_x` 使用 `std::transform(std::execution::par)` 执行逐粒子并行更新。`Particles` 通过 `std::unique_ptr<SimulatorBase<ModelT>>` 保存具体 simulator，用 `init(ComputeType)` 选择 steady 或 unsteady。steady 模式初始化为 point，unsteady 模式初始化为 `[-1,1]` 上均匀分布并按 `dt=0.2` 推进到 `t=1`。

关键代码路径为 `include/simulator.h`、`include/array.h`、`src/main.cpp`、`tests/test.cpp`、`scripts/plot.gp`。验证方式主要是 GoogleTest 和 README 中的运行命令。可量化结果缺少证据：虽然代码中 perf 模式使用 3000000 和 1000000 粒子，但没有保存的计时结果或 benchmark 表，不能写性能提升。

适合写进简历的是 C++ 模板/多态组织、Parallel STL、`std::thread/std::async` 对比入口和 GoogleTest。只适合面试展开的是为什么 Parallel STL 不一定带来稳定加速、steady/unsteady 模式的抽象方式、输出文件如何被 gnuplot 使用。

## 8. Resume Bullet Candidates / 简历要点候选

### 训练系统 / AI Infrastructure 方向
弱相关，不建议作为该方向简历主项目。
- 可补充 C++ 并行基础：使用 Parallel STL 和 `std::async` 组织独立任务执行，但缺少训练系统相关证据。

### HPC / 性能优化方向
弱相关，不建议作为 HPC 主项目；缺少 benchmark 输出。
- 为粒子更新路径接入 `std::execution::par`，并提供 sequential/thread/async 三种运行模式；性能数字缺少证据，需要补充。
- 使用百万级粒子规模作为 perf 入口负载，但缺少正式计时结果，不建议写加速比。

### C++ 后端 / 系统开发方向
- 用模板 `Model<Gas>` 抽象气体速度场，使 constant/non-uniform 场在编译期组合到粒子模型中。
- 用 `SimulatorBase` + `unique_ptr` 管理 steady/unsteady 两类运行策略，避免在主循环中堆叠模式判断。
- 使用 Parallel STL 对粒子速度计算和位置更新做逐元素并行表达，代码路径集中在 `include/simulator.h`。
- 提供 `std::thread` 与 `std::async` 两种任务级并发入口，用于同时运行 steady/unsteady 大规模负载（性能数字缺少证据）。
- 编写 GoogleTest 覆盖 Array、常量场一步更新和两种 simulator smoke test。

### 数值计算 / 科研计算方向
- 实现一维粒子在给定速度场中的显式位置更新 `x += v*dt`，支持 steady 和 unsteady 两类场景。
- 对 non-uniform gas field 使用 `sin(-pi*x)` 构造空间相关速度，并按 `t=0..1, dt=0.2` 输出轨迹数据。
- 通过 gnuplot 脚本将粒子位置/速度输出转换为图像结果。
- 局限：缺少误差分析、稳定性分析和物理 benchmark，不建议作为科研计算主项目。

## 9. Interview Pitch
- 30 秒讲法：这是一个 C++ 一维粒子模拟器，主要展示面向对象和泛型设计。它用模板把气体场组合进模型，用多态区分 steady/unsteady simulator，用 Parallel STL 做逐粒子更新，还提供 `std::thread` 和 `std::async` 的 perf 入口。这个项目我不会夸大性能，因为目前缺少 benchmark 输出。
- 2 分钟讲法：项目的数据结构很简单，`Array` 封装 `std::vector<double>`，`Particles` 保存位置和速度。建模上我把速度场写成 `GasField` 类型，例如常量场和 `sin(-pi*x)` 非均匀场，再通过 `Model<Gas>` 计算 `v(x,t)` 和 `x += v*dt`。运行模式由 `SteadySimulator` 和 `UnsteadySimulator` 实现，`Particles::init` 选择对应策略。并行层面有两种：粒子级更新使用 `std::execution::par`，任务级入口用 `std::thread` 或 `std::async` 同时跑 steady/unsteady 大负载。验证上有 GoogleTest 检查 Array 和常量场一步更新。个人贡献和性能结果需要补充材料确认。

可能被追问的 8 个问题：
1. 为什么用模板表示 GasField？回答要点：编译期组合、无虚调用；但会增加模板实例化。
2. steady 和 unsteady 的差别？回答要点：steady point 初始化并一步计算；unsteady uniform 初始化并 `dt=0.2` 多步输出。
3. Parallel STL 是否一定并行？回答要点：不一定，取决于标准库后端和编译链接配置。
4. `std::thread` 和 `std::async` perf 模式测了什么？回答要点：两个独立负载并发执行；缺少输出，不能说加速。
5. 输出文件命名有什么问题？回答要点：代码总是加时间后缀，README steady 描述可能不完全一致。
6. 测试覆盖是否充分？回答要点：目前是基础单元和 smoke test，缺少轨迹数值参考。
7. 这个项目的物理模型复杂吗？回答要点：不复杂，重点是工程结构和 C++ API。
8. 个人贡献怎么确认？回答要点：现有材料没有分工，需要补充提交记录或课程报告。

## 10. What Not To Overclaim
- 不要声称有确定加速比；没有 benchmark 输出。
- 不要声称是高保真物理模拟；模型是教学级一维粒子演化。
- 不要说个人独立实现全部模块；缺少证据，需要人工确认。
- 不要把 Parallel STL 写成稳定 HPC 优化；实际并行行为依赖实现。
- 不要忽略 README 与代码输出命名可能存在的小差异。

## 11. Keywords for Internship Search
C++ 后端, 面向对象设计, 模板编程, 泛型编程, Parallel STL, std::thread, std::async, GoogleTest, CMake, 粒子模拟, 数值模拟入门, gnuplot, C++ Backend, Object-Oriented Design, Template Programming, Concurrency, Particle Simulation, Scientific C++
