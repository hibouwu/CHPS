# 性能评估：数学建模与排队论

[课程入口](../README.md) · [中文笔记 PDF](ed充满.pdf)

按原笔记顺序整理，保留法文术语；已修复的内容问题在相应小节标为“校注”。教师课件与核对依据见[审校说明](../审校说明.md)。

## 0 建模导论

### 0.1 定义

数学建模 (modélisation mathématique) 是一个相对简单的工具，它将真实系统 (système réel) 抽象为一组数学函数，用以表示其主要功能/服务 (fonctionnalités/services)，从而分析该系统的行为。

### 0.2 描述形式化 (Formalismes de description)

系统可以用不同的形式化方法描述：
- 排队论 (files d’attente)
- 马尔可夫链 (chaînes de Markov)
- Petri 网 (réseaux de Petri) 等

## 1 排队论导论 (Introduction aux files d’attente)

### 1.1 排队论

排队论是一种基于概率论的数学理论 (théorie mathématique)，用于评估系统性能，在这些系统中，客户 (clients) 可以到达并请求获取资源 (ressources) 一段时间。

某些客户必须在被服务之前等待，然后离开系统。

排队 (file d’attente) 由客户的到达流 (flux d’arrivée) 填充，由服务器 (serveurs) (资源) 清空。

### 1.2 应用条件

本节使用的无限容量 M/M/1 稳态公式要求到达率 $\lambda$ 小于服务率 $\mu$。排队论本身也可研究瞬态和饱和情况，不能将稳态条件理解为整个理论的适用范围。

到达 (Arrivée)  客户排队 (File d’attente des clients)  服务 (Service)  客户离开 (Départ)

### 1.3 分析建模的优势与局限

#### 1.3.1 优势 (Intérêt)

数学建模允许评估待分析系统的大量可能配置 (configurations possibles) 以及其可能承受的负载(charges)。

#### 1.3.2 局限 (Limitation)

建模所基于的假设和近似 (hypothèses et approximations) 可能限制其结果的应用范围并影响其精度(précision)。

## 2 排队模型 (Modèles de files d’attente)

### 2.1 通用概念 (Généralités)

#### 2.1.1 词汇表
- 资源 (CPU, 内存, 磁盘...) 服务器 (serveur)
- 作业 (Job), 进程 (Processus), IO 请求 客户 (client)

#### 2.1.2 定义

客户在队列中等待，直到服务器空闲来服务他们。

服务器根据定义的策略 (stratégie définie) 从等待队列中选择一个客户进行服务。

### 2.2 关键概念
- 逗留时间 (Temps de séjour) = 响应时间 (temps de réponse)
- 等待时间 (Temps d’attente)
- 服务规律 (Loi de service)
- 服务策略 (Stratégie de service)
- 到达过程 (Processus d’arrivée)

### 2.3 选择策略 (Stratégies de sélection)
- FIFO: 先到先服务 (premier arrivé, premier servi)
- LIFO: 后到先服务 (dernier arrivé, premier servi)
- Random: 随机 (aléatoire)
- Round Robin: 循环 (cyclique)
- Time Sharing (TS): 时间共享 (temps partagé)，主要适用于处理器资源

### 2.4 排队网络 (Réseaux de files d’attente)

服务器和队列可以互连形成排队网络 (réseau de files d’attente)。

### 2.5 稳态与瞬态 (Régime permanent et transitoire)

#### 2.5.1 瞬态 (Régime transitoire)

系统尚未达到稳定或稳态的演化状态 (régime d’évolution)。它可能在系统启动 (amorce) 或修改时出现。

#### 2.5.2 稳态 (Régime permanent)

系统在一定运行时间后达到的稳定状态 (régime de stabilité)。严格的平稳分布不随时间变化；达到稳定周期的系统仍依赖周期内的相位，应与严格平稳状态区分。

### 2.6 性能参数 (Paramètres de performance)

在排队网络中，瞬态和稳态下的性能参数定义为：
- 到达和离开的吞吐量或频率 (Débit ou fréquence d’arrivée et de sortie)
- 系统中客户的平均数量 (Nombre moyen de clients dans le système)
- 平均逗留时间 (Temps moyen de séjour)
- 服务器利用率 (Taux d’utilisation du serveur)

### 2.7 稳定性条件 (Condition de stabilité)

系统的稳定性仅对稳态有意义。

稳态下平均入口吞吐量等于平均出口吞吐量。但流量相等本身不是稳定的充分条件，例如无限容量 M/M/1 在 $\lambda=\mu$ 时无可归一化的稳态分布。

### 2.8 拓扑与类别

根据拓扑结构，排队网络可以是：
- 开放式 (Ouverts)：存在外部到达和离开，内部路由仍可有反馈环
- 封闭式 (Fermés)：固定客户群在网络内循环，没有外部到达和离开

## 3 开放式排队网络 (Réseaux de files d’attente ouverts)

### 3.1 定义

开放式排队网络是这样的网络：

1. 客户从外部源 (source externe) 到达

2. 被不同的服务器服务

3. 可以完全终止或生成新客户

### 3.2 备注
- 此类网络中的所有客户最终都会终止并离开系统
- 因此无限数量的客户构成进出系统的流

### 3.3 Jackson 网络 (Réseaux de Jackson)

Jackson 网络的特征：
- 单类客户 (Mono-classe de clients)
- 泊松到达 (Arrivées Poissoniennes)
- 本节模型中每个站点一个服务器，服务时间独立且服从指数分布
- 无限容量队列，FIFO 规则 (File de capacité illimitée, Discipline FIFO)
- 概率路由 (Routage probabiliste)

### 3.4 示例

下图来自教师课件第 20 页，便于核对路由概率：

![Jackson 网络及路由概率](Images/ed充满_jackson.jpg)

$$
\lambda_1=\frac{\lambda}{2},\qquad
\lambda_2=\frac{\lambda}{2}+\frac14\lambda_1=\frac{5\lambda}{8},
$$

$$
\lambda_3=\frac34\lambda_1+\frac15\lambda_2=\frac{\lambda}{2},\qquad
\lambda_4=\lambda_3=\frac{\lambda}{2}.
$$

> 校注：中文笔记 PDF 第 3 页已将三个 $\lambda/2$ 写成 $\lambda_2$，不是本次 Markdown 提取引入的问题；这里按教师课件与路由图修正。

## 4 封闭式排队网络 (Réseaux de files d’attente fermés)

### 4.1 定义

封闭式排队网络有固定数量的客户 (nombre fixe de clients) 在不同服务器和队列之间循环。

输出直接连接到网络的输入。

因此，该网络中既没有到达也没有离开。

### 4.2 备注
- 封闭网络表示客户总数固定；这不等于各站点的缓冲区都设有独立的容量限制
- 此类模型的求解更为复杂

## 5 建模过程 (Processus de modélisation)

### 5.1 假设 (Hypothèses)

#### 5.1.1 建模前需考虑的假设

客户流的平衡 (Équilibre du flux des clients) 考虑长期观察，离开的客户数量必须等于进入的客户数量。

单步行为 (Comportement à une étape) 每个时刻只有一个客户可以进入或离开系统。因此系统状态以增量方式变化 (de manière incrémentale)。

##### 关于单步行为的备注
- 不允许多重到达和离开
- 不允许同一系统内队列之间客户的同时移动

齐次性 (Homogénéité) 平均到达率和平均服务率独立于系统状态。

##### 独占性 (Exclusivité)
- 一个客户只能位于一个服务器处（服务中或等待中）
- 一个客户不能同时请求两个服务，当获得一个服务时，他是唯一被该服务器服务的

非阻塞服务 (Service non-bloquant) 服务器是所提供服务的唯一主控者。该服务不能被系统的任何组件控制。

### 5.2 符号表 (Notation)

在课程的其余部分，我们将使用以下符号：

| 符号 | 说明 |
| --- | --- |
| s | 客户的平均服务时间 |
| μ | 服务率 (taux de service) (1/s) |
| λ | 平均到达率 (taux d'arrivée moyen) |
| ρ | 流量强度 (intensité du trafic) (λ/μ) |
| r | 平均响应时间 (temps de réponse moyen) |
| w | 平均等待时间 (temps d'attente moyen) |
| q | 队列中客户的平均数量 |
| n | 系统中客户数量(等待 + 服务中) |
| U | 系统利用率 (fraction d'utilisation) |
| a | 观察时间 T 内的到达数量 |
| d | 观察时间 T 内的离开数量 |

## 6 操作分析 (L’analyse opérationnelle)

### 6.1 整体视图 (Vue globale)

分析从将待分析系统视为黑盒 (boîte noire) 开始，其输入端到达待处理的作业（客户），输出端是已处理的作业。

### 6.2 特征化 (Caractérisation)

系统特征通过测量或假设（用户、制造商/构造商）进行评估。然后可以在这个精确的环境中评估系统的行为。

### 6.3 利用率法则 (Lois d’utilisation)

#### 6.3.1 到达率 (Taux d’arrivée)

在时间周期 T 内观察系统，期间有 a 个客户到达，我们推导出到达率 λ：

$$
\lambda = \frac{a}{T}
$$

#### 6.3.2 服务器利用率 (Utilisation du serveur)

如果服务器在整个观察期 T 内仅被占用 b 个时间单位，我们推导出服务器利用率 U：

$$
U = \frac{b}{T} = \frac{b}{d} \times \frac{d}{T}
$$

其中 d 是被服务的客户数量， $\textstyle{\frac{b} {d}}$ 是服务一个客户的平均时间， $\textstyle{\frac{d} {T}}$ 是客户的离开率。根据平衡假设 (hypothèse d’équilibre)，入口流必须等于出口流，因此：

$$
\begin{array}{c} {U = \frac{b}{d} \times \frac{d}{T} = s \times \frac{d}{T}} \\ {U = \lambda \times s} \end{array}
$$

### 6.4 流量强度 (L’intensité du trafic)

$$
\rho = \frac{\lambda}{\mu}
$$
- ρ > 1: 意味着到达率高于离开率。队列中等待的客户数量将增加并导致无限等待时间。 系统不稳定
- ρ < 1: 意味着系统处于稳定状态。 利用率 U 永远不超过 100%。$(1-\rho)$: 服务器空闲的概率(probabilité que le serveur soit inactif)

### 6.5 Little 定律 (Loi de Little)

#### 6.5.1 定义

Little 定律是可应用于任何系统的通用法则：
- 对” 黑盒” 没有任何假设
- 对表征系统的随机变量 (variables aléatoires) 没有任何假设
- 本节在稳态下使用 Little 定律：长期平均量须存在，人数、逗留时间和吞吐量应对应同一系统边界与同一客户流

#### 6.5.2 公式

稳态系统的平均客户数量 (N)、平均逗留时间或响应时间 (t) 和平均吞吐量 λ 根据以下定律相关联：

$$
\boxed{N = t \times \lambda}
$$

#### 6.5.3 重要性
- 允许根据其他两个参数计算三个参数 (N,t,λ) 中的一个
- 可应用于任何系统：

仅缓冲区
- 缓冲区 + 服务器
- 队列的服务器

#### 6.5.4 应用

仅缓冲区 (Un buffer uniquement) N 表示队列中客户的平均数量，t 表示服务前的平均等待时间，λ表示客户的到达（或离开）流。

缓冲区 + 服务器 (Un buffer + serveur) N 表示系统中客户的平均数量（队列中或服务中），t 表示平均逗留时间（等待和服务），λ 表示到达流。

队列的服务器 (Le serveur de la file) N 表示服务中客户的平均数量，t 表示平均服务时间，λ 表示到达流。

## 7 随机分析 (L’analyse stochastique)

### 7.1 利用率法则和 Little 定律的局限

它们不考虑关于到达间隔 (inter-arrivées) 和服务的概率法则 (lois de probabilité) 的任何假设。它们完全独立于分布 (distributions)。

### 7.2 随机分析的优势

了解分布允许进行随机分析，从而通过提供比操作分析更详细的结果来细化系统分析。

### 7.3 定义

通过随机分析，系统不再是黑盒。这允许获得关于所分析系统的详细结果，例如：
- 客户的平均等待时间
- 队列中客户的平均数量
- 有一定数量客户等待的概率
- 平均响应时间...

### 7.4 Kendall 符号 (Notation de Kendall)

系统由一个队列和一个或多个服务器组成。它将用词 $A / S / C / B / N / D$ 表示：
- A: 到达过程的分布 (distribution du processus d’arrivée)，用 M 表示指数分布（典型情况），D 表示常数， $E _{k}$ 表示 Erlang 分布，G 表示一般分布
- S: 服务的分布 (distribution du service)，使用与到达过程类似的法则
- C: 系统中相同服务器的数量。如果系统包含不同的服务器，必须将其分解为每个都有相同服务器的子系统
- B: 系统中客户的总数（其容量 capacité），假设为无限以简化分析
- N: 潜在客户源的总体规模，假设为无限以简化分析
- D: 服务顺序或策略 (ordre ou stratégie de service)：FIFO、LIFO 等

### 7.5 M/M/1 情况

这是最简单的情况：
- 到达为速率 $\lambda$ 的泊松过程；到达间隔独立且服从参数 $\lambda$ 的指数分布
- 服务是速率为 µ 的指数分布 (exponentiel)
- 只有一个服务器
- 队列容量无限（默认）
- 可进入系统的客户数量无限（默认）
- 服务策略 FIFO（默认）

#### 7.5.1 稳态下的性能参数

吞吐量 (Débit) 队列是稳定的，因此流量平衡：

$$
\mathrm{Débit} = \lambda
$$

服务器利用率 这是服务器被占用的概率：

$$
U = \frac{\lambda}{\mu} = \rho
$$

系统为空的概率

$$
P _{0} = 1 - \rho
$$

到达客户需要等待的概率

$$
P _{a} = \rho
$$

系统中客户的平均数量

$$
n = \frac{\rho}{(1 - \rho)}
$$

平均逗留时间 由 Little 定律推导：

$$
r = \frac{n}{\lambda} = \frac{1}{\mu(1 - \rho)}
$$

可分解为：

$$
r = \frac{1}{\mu} + \frac{\rho}{\mu(1 - \rho)}
$$

队列中花费的时间

$$
w = \frac{\rho}{\mu(1 - \rho)}
$$

队列中客户的平均数量

$$
q = w \times \lambda = \frac{\rho^{2}}{(1 - \rho)}
$$

稳态下的概率 系统中有 0 个客户的概率：

$$
P _{0} = (1 - \rho)
$$

系统中有 n 个客户的概率：

$$
P _{n} = \rho^{n} P _{0}
$$

### 7.6 M/M/C 情况

这是前一种情况的 C 个相同类型且独立的服务器（处理器或磁盘）。

作业/IO 请求在同一队列中等待被服务。

如果 C 个服务器中有一个可用，它将服务队列中的一个作业/IO 请求。

#### 7.6.1 稳定性条件

为了达到稳定性，单位时间内到达队列的平均客户数量必须小于 C 个服务器单位时间内能够处理的客户数量。

因此：

$$
\lambda < C \mu
$$

#### 7.6.2 稳态下的性能参数

区分总业务量 $a$ 与单台服务器的平均利用率 $\rho$：

$$
a=\frac{\lambda}{\mu},\qquad \rho=\frac{\lambda}{C\mu}=\frac aC<1.
$$

> 校注：原教师课件第 52–55 页和中文笔记第 9 页混用了两种 $\rho$ 定义。以下公式统一采用上面的记号；$\mu$ 为每台服务器的服务率。

**吞吐量：** 稳态下为 $\lambda$。

**系统为空的概率：**

$$
P_0=\left[\sum_{k=0}^{C-1}\frac{a^k}{k!}+\frac{a^C}{C!(1-\rho)}\right]^{-1}.
$$

**到达客户需要等待的概率（Erlang C）：**

$$
P_a=P_0\frac{a^C}{C!(1-\rho)}
    =P_0\frac{a^C}{(C-1)!(C-a)}.
$$

**系统中的平均客户数：**

$$
n=a+\frac{\rho P_a}{1-\rho}
 =a\left(1+\frac{P_a}{C-a}\right).
$$

**平均逗留时间：** 由 Little 定律得到：

$$
r=\frac n\lambda=\frac1\mu\left(1+\frac{P_a}{C-a}\right)
 =\frac1\mu+\frac{P_a}{C\mu-\lambda}.
$$

**平均等待时间：**

$$
w=\frac{P_a}{C\mu-\lambda}
 =\frac{P_0a^C}{\mu(C-1)!(C-a)^2}.
$$

**队列中的平均客户数：** $q=\lambda w$。这些公式要求泊松到达、独立指数服务时间、相同服务器、共同的无限容量 FIFO 队列及稳定条件。令 $C=1$，可退化为前一节的 M/M/1 公式。
