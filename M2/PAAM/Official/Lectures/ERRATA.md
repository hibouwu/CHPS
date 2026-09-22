# 课件勘误与阅读说明

以下按原课件页码列出需要留意的代码、概念与数据问题。原文稿保留对应的逐页原图，中文教程在相关段落解释处理方式。

## 逐讲勘误与边界

### 01-threads

- [第4页](01-threads.md#page-4)：OCR覆盖标注残片已从PDF重建；图示不能保证物理栈布局。
- [第8页](01-threads.md#page-8)：课件pthread_create省const且例子未join；中文注明。
- [第9页](01-threads.md#page-9)：原文start_rountine拼写；退出进程与线程区别。
- [第10页](01-threads.md#page-10)：0x42是教学返回指针值不可直接解引用。
- [第12页](01-threads.md#page-12)：交错例子不穷尽C数据竞争行为。
- [第16页](01-threads.md#page-16)：signal不储存事件，while谓词必须保留。
### 02-locks

- [第2页](02-locks.md#page-2)：原文FREE等待条件反向；宏含=和分号；旁注曾混入OCR代码。
- [第8页](02-locks.md#page-8)：遮挡页的底层条件与p7不一致，采用p7清晰模型。
- [第11页](02-locks.md#page-11)：原文if(entering[i]){}不等待；应为等待循环。
- [第13页](02-locks.md#page-13)：maximum与算法优先最小二元组不符；计数为示意。
- [第24页](02-locks.md#page-24)：普通C消息示例不能只凭TSO认定正确。
- [第25页](02-locks.md#page-25)：Java/ARM描述过度概括，不作可移植代码证明。
- [第29页](02-locks.md#page-29)：图文层叠；非原子C数据竞争不能仅按撕裂枚举。
- [第30页](02-locks.md#page-30)：原文atomic接口缺&；未读到发布值时普通数据读取不安全。
- [第31页](02-locks.md#page-31)：原文z非原子且读取端没有所述依赖。
- [第32页](02-locks.md#page-32)：原图读顺序下存在合法SC反例；已穷举验证。
- [第38页](02-locks.md#page-38)：原子性无成本说法过强，仅保留通信/排序动机。
- [第39页](02-locks.md#page-39)：变量lock与函数lock同名是片段，非完整可编译程序。
- [第44页](02-locks.md#page-44)：<my使用无回绕假设；不推广到有限有符号计数。
- [第48页](02-locks.md#page-48)：函数名原文string，标题strong；C CAS与返回旧值版本区分。
- [第52页](02-locks.md#page-52)：head旁注实为全局队尾比较；节点生命期与链接窗口。
### 03-non-blocking

- [第2页](03-non-blocking.md#page-2)：Amdahl low原文拼写；近似数与模型条件已说明。
- [第9页](03-non-blocking.md#page-9)：循环内分配、变量作用域均为教学伪代码。
- [第10页](03-non-blocking.md#page-10)：空栈处理至p11才出现。
- [第16页](03-non-blocking.md#page-16)：空队列分支未展示，不当作完整实现。
- [第31页](03-non-blocking.md#page-31)：法语注释为C帮助B移动tail；不是代码。
- [第39页](03-non-blocking.md#page-39)：value与element原文字段不一致。
- [第40页](03-non-blocking.md#page-40)：辅助tail CAS不能一概等同完整操作结束。
- [第48页](03-non-blocking.md#page-48)：最低位标记依赖对齐；摘链不等于释放。
- [第60页](03-non-blocking.md#page-60)：found未完整初始化、n未声明，是逐步片段。
- [第67页](03-non-blocking.md#page-67)：逻辑删除可完成而物理节点尚在。
- [第68页](03-non-blocking.md#page-68)：void函数return 0是原文伪代码不一致。
- [第71页](03-non-blocking.md#page-71)：未定义重复键语义，不能宣称为严格集合API。
### 04-stm

- [第3页](04-stm.md#page-3)：结果44/43需x初值21，原页未显式给出；b,c,e标签应包含写回d。
- [第7页](04-stm.md#page-7)：addLast缺e；addLast/removeLast不是FIFO。
- [第16页](04-stm.md#page-16)：HTM容量、检测时机和STM任意大小是简化概括。
- [第28页](04-stm.md#page-28)：原文not read x again按缺少版本复验理解。
- [第35页](04-stm.md#page-35)：跨对象不一致即使最终abort也可能先导致异常。
- [第37页](04-stm.md#page-37)：>=与写版本后增时钟的约定保持一致。
- [第46页](04-stm.md#page-46)：旧不可变对象不得立即free。
- [第51页](04-stm.md#page-51)：伪Java类型不一致；提交锁不自动同步无锁读取端。
- [第52页](04-stm.md#page-52)：递归重设n=16破坏指数退避状态。
- [第54页](04-stm.md#page-54)：无死锁/无饥饿不是无条件保证；性能仅历史配置。
### 05-numa

- [第4页](05-numa.md#page-4)：Moore low原文拼写与历史趋势。
- [第8页](05-numa.md#page-8)：未初始化读取、依赖循环、结果未消费，不是可直接复现基准。
- [第15页](05-numa.md#page-15)：256GB与16x8GB局部标注范围未说明，不擅自统一。
- [第24页](05-numa.md#page-24)：mbind是简化接口，不可原样调用。
- [第26页](05-numa.md#page-26)：条件命中率未明说；32/156取整无法精确推出385%。
- [第27页](05-numa.md#page-27)：70%为条件概率才合理；7/17不精确推出137%。
- [第31页](05-numa.md#page-31)：接口名为概念写法；核集合与节点集合不同。
- [第38页](05-numa.md#page-38)：Carrefour原论文为ASPLOS2013而非2015。
- [第44页](05-numa.md#page-44)：按样本标准差n-1可复现283%，总体标准差不能。
- [第52页](05-numa.md#page-52)：高不均衡文字FT/Carrefour与图及前页Interleaved/Carrefour矛盾。
- [第75页](05-numa.md#page-75)：高处黑色线为参考线；各性能曲线按原图识别。
- [第78页](05-numa.md#page-78)：MangoDB应理解为MongoDB名称拼写。
- [第82页](05-numa.md#page-82)：固定48vCPU/48pCPU；最佳策略选择不等于默认部署。
- [第83页](05-numa.md#page-83)：SLR/SRL原文缩写不统一，中文称运行库。
- [第88页](05-numa.md#page-88)：3 VM和48vCPU/42pCPU条件保留。
### 06-nvmm

- [第3页](06-nvmm.md#page-3)：单位按PDF；概括性能倍数与表格部分列不一致。
- [第6页](06-nvmm.md#page-6)：O_CREAT缺mode；MAP_SYNC在普通文件上不通用；错误检查省略。
- [第8页](06-nvmm.md#page-8)：结构committed但条件isCommitted；原课件笔误。
- [第11页](06-nvmm.md#page-11)：一次pwb只涵盖一行；跨行数据需完整范围，初始标志需保证。
- [第12页](06-nvmm.md#page-12)：durable linearizability说明非完整定义。
- [第13页](06-nvmm.md#page-13)：visible易失且需初始false；持久域和同步模型前提。
- [第14页](06-nvmm.md#page-14)：Pentium残余能量不能泛化；持久域决定保证。

## 保留的证据限制

- 原课件个别历史硬件容量、性能表单位及测量条件并不完整；保留原值并说明，不以推测替换。
- 对并发伪代码作语义和反例审查，没有宣称完成形式化证明；课件片段没有作为实际程序运行。
- 未复现历史NUMA基准、未在持久内存硬件上进行掉电实验；教程中的性能与恢复结论均保留前提。
- 外部标准/论文链接用于核对关键语义和文献年份，具体来源放在相应教程段落。
