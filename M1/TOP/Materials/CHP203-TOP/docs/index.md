# Introduction 简介

This site contains lectures and practical work for the course **CHP203: Parallel Optimization Techniques** offered by Hugo Taboada and Gabriel Dos Santos as part of the [High Performance Computing & Simulation](https://chps.uvsq.fr/) M.Sc. program at [ISTY/UVSQ](https://www.uvsq.fr/institut-des-sciences-et-techniques-des-yvelines-isty). Its use is reserved for students of the [Paris-Saclay University](https://www.universite-paris-saclay.fr/). 本网站包含课程 **CHP203: Parallel Optimization Techniques** 的讲义与实验内容，该课程由 Hugo Taboada 和 Gabriel Dos Santos 开设，属于 [ISTY/UVSQ](https://www.uvsq.fr/institut-des-sciences-et-techniques-des-yvelines-isty) 的 [High Performance Computing & Simulation](https://chps.uvsq.fr/) 硕士项目的一部分。本站仅供 [Paris-Saclay University](https://www.universite-paris-saclay.fr/) 的学生使用。

The Spring 2026 session will start on Tuesday, 24 March and end on Tuesday, 28 April. 2026 年春季学期将于 3 月 24 日星期二开始，并于 4 月 28 日星期二结束。

## Course Information 课程信息

### Description & objectives 课程描述与目标

This course provides an overview of common optimization techniques for modern HPC architectures, as well as giving an introduction to supercomputing tools and environments. 本课程概述现代 HPC 架构中的常见优化技术，并介绍超级计算所使用的工具与环境。

By the end of the course, the students are expected to have acquired a thorough understanding of the following concepts: 课程结束时，学生应当对以下概念有较为深入的理解：

- Compilers, build systems, and HPC toolchains - 编译器、构建系统与 HPC 工具链
- Parallel and distributed programming models - 并行与分布式编程模型
- Parallel and distributed profiling tools - 并行与分布式性能分析工具
- Performance benchmarking methodology - 性能基准测试方法
- Memory and data structure layout optimizations - 内存与数据结构布局优化
- CPU microarchitecture optimizations optimizations - CPU 微架构优化
- Shared-memory parallelism performance pitfalls & optimizations - 共享内存并行中的性能陷阱与优化
- Distributed programming performance pitfalls & optimizations - 分布式编程中的性能陷阱与优化

### Lecture sessions 讲课时间

Tuesday, 13:45 - 17:00 CET, room CN2, Rabelais building, Guyancourt campus. 每周二 CET 时间 13:45 - 17:00，地点为 Guyancourt 校区 Rabelais 楼 CN2 教室。

### Lab sessions 实验时间

Tuesday, 9:30 - 12:45 CET, room CN2, Rabelais building, Guyancourt campus. 每周二 CET 时间 9:30 - 12:45，地点为 Guyancourt 校区 Rabelais 楼 CN2 教室。

### Examination 考核方式

This course is evaluated for the 1st Year of Paris-Saclay University's M.Sc. in High Performance Computing & Simulation. 本课程面向 Paris-Saclay University 的 High Performance Computing & Simulation 硕士一年级学生进行考核。

!!! warning

    All lecture and lab sessions are mandatory. Any absence shall be justified to the administration and the course organizers. 所有讲课和实验课均为必修。任何缺席都必须向教务部门和课程组织者说明理由。

**ECTS credits** ECTS 学分
: 3 credits (out of 30 semester credits) : 3 学分（学期总学分 30 分中的 3 分）

**Grades** 成绩构成

| Examination 考核项目 | Grading 评分形式 | Breakdown 占比 |
| --- | --- | --- |
| Quizz 小测 | Mid-semester (surprise) test 期中（突击）测试 | 15% |
| Project 项目 | Report & presentation 报告与展示 | 35% |
| Exam 考试 | End-semester finals 学期末考试 | 50% |
| **Total 总计** | | **100%** |

## Staff Information 教学团队信息

| Name 姓名 | Role 角色 | E-mail 邮箱 |
| --- | --- | --- |
| Hugo Taboada | Instructor 授课教师 | [hugo.taboada@cea.fr](mailto:hugo.taboada@cea.fr) |
| Gabriel Dos Santos | Teaching Assistant 助教 | [gabriel.dossantos@cea.fr](mailto:gabriel.dossantos@cea.fr) |

Please contact the instructor or TA for any questions regarding the course. E-mails can be sent in either French or English at your convenience. 如对课程有任何问题，请联系授课教师或助教。你可以根据方便使用法语或英语发送邮件。

Be mindful when sending e-mails. If it is your first contact with the instructor or TA, don't forget to present yourself. Try to clearly and concisely express your problem. Detail the steps you have already taken and what you have tried. 发送邮件时请注意礼貌与规范。如果这是你第一次联系授课教师或助教，请不要忘记先做自我介绍。尽量清晰、简洁地说明你的问题，并详细写明你已经采取过的步骤和尝试过的方法。

!!! note

    For filtering reasons and easier e-mail management from the teaching staff, please make sure that all e-mail subjects you send are in the form: `[M1CHPS-TOP] <your subject>`. 出于筛选和便于教学团队管理邮件的原因，请确保你发送的所有邮件主题都采用如下格式：`[M1CHPS-TOP] <your subject>`。

    ***Any e-mail written in an informal manner or without proper syntax will be ignored.*** ***任何以不正式方式书写或缺乏适当语法的邮件都将被忽略。***

Additionally, the HPCS Master has a Discord server on which students can reach the TA (handle: `@gabrl`), either by Private Message or through the `#techniques-optimisation-paralleles` channel. 此外，HPCS 硕士项目还有一个 Discord 服务器，学生可以通过私信或 `#techniques-optimisation-paralleles` 频道联系助教（账号：`@gabrl`）。

:arrow_right: [**Invite link**](https://discord.gg/8rJ7hvJE) :arrow_right: [**邀请链接**](https://discord.gg/8rJ7hvJE)

## Material 资料

### Lectures 讲义

Lecture slides are available [here](artifacts/TOP_course_2025.pdf) (last year's slides). 课程幻灯片可在[这里](artifacts/TOP_course_2025.pdf)获取（去年版本的讲义）。

### Labs 实验

Lab material for this course is available on the following GitHub repository: [TOP-26](https://github.com/dssgabriel/TOP-26) 本课程的实验材料可在以下 GitHub 仓库中获取：[TOP-26](https://github.com/dssgabriel/TOP-26)

### Resources 参考资源

See the [dedicated page](./resources.md). 详细参考资源请见[专门页面](./resources.md)。
