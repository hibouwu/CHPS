# TD 2 à 5 simulateur de pollution atmosphérique （大气污染模拟器第2至5次）

Contexte : il est aujourd'hui primordial de contrôler la quantité de polluants dans l'air de nos grandes agglomérations ainsi que son évolution.  
（背景：必须监测大城市空气污染物的浓度及其变化。）  
Il est possible de prédire cette quantité par des simulations particulaires où l'on pourra suivre la dispersion des particules de polluants dans l'air.  
（可以通过粒子模拟来预测污染物数量并跟踪扩散。）

![Image de dispersion turbulente de particules dans un champ de gaz bidimensionnel](<dispersion_turbulente.png>)
*Image de dispersion turbulente de particules dans un champ de gaz bidimensionnel (source [S. de Chaisemartin](https://theses.hal.science/tel-00443982/en/))*
（二维气体场中粒子湍流扩散示意图）

Nous proposons d'utiliser ce contexte comme fil rouge de nos séances de TD.  
（本系列TD以此场景为主线。）

## TD 2 Mise en place de l'infrastructure （建立基础架构）

## 2.1 Structure du simulateur （模拟器结构）

Le simulateur pourra effectuer deux types de calculs :  
（模拟器可执行两类计算：）

- calcul d'un état stationnaire,
- （稳态计算，）
- calcul d'un transitoire.
- （瞬态计算。）

Créez une structure de code qui permet d'exécuter une initialisation et au choix un état transitoire ou un état stationnaire.  
（创建能初始化并选择瞬态或稳态计算的代码结构。）  
Le code devra appeler une méthode d'affichage des particules après chaque calcul d'état.  
（每次状态计算后调用粒子显示函数。）

Indications : vous pouvez créer un seul fichier .cpp pour l'instant.  
（提示：暂时用单个.cpp文件即可。）  
Le but de ce TP est uniquement d'avoir la structure du code.  
（目标只是搭好代码框架。）  
Vous créerez trois fonctions :  
（需要创建三个函数：）

- ``init_particles``
- （初始化粒子）
- ``compute_particles``
- （计算粒子）
- ``print_particles``
- （打印粒子）

qui, pour l'instant, ne feront qu'afficher un message à l'écran.  
（目前仅打印消息。）  
Vous encapsulerez ces fonctions dans un namespace **``Simulator``**.  
（将这些函数封装在命名空间**Simulator**中。）  
Les sorties attendues pour un état stationnaire ressemblent à :  
（稳态计算的预期输出如下：）

```txt
--- init particles ---
--- compute particle evolution at time : 1 ---
--- print particle positions at time : 1 ---
```

et pour un transitoire :  
（瞬态计算的输出如下：）

```--- init particles ---
--- compute particle evolution at time : 0 ---
--- print particle positions at time : 0 ---
--- compute particle evolution at time : 0.2 ---
--- print particle positions at time : 0.2 ---
--- compute particle evolution at time : 0.4 ---
--- print particle positions at time : 0.4 ---
--- compute particle evolution at time : 0.6 ---
--- print particle positions at time : 0.6 ---
--- compute particle evolution at time : 0.8 ---
--- print particle positions at time : 0.8 ---
```

Le choix entre le calcul stationnaire ou transitoire se fera à l'aide d'une structure `switch` et d'une `enum class` `ComputeType` avec les états `Steady` et `Unsteady` qui sera passée en argument de la fonction `compute_particles`.  
（通过`switch`和`enum class ComputeType{Steady,Unsteady}`选择模式并传给`compute_particles`。）

## 2.2 Compiler avec CMake （用CMake编译）

- Définir un projet CMake avec votre simulateur. Il n'y a pour l'instant qu'un .cpp à ajouter. Tester votre projet. Depuis vos sources faire :  
  （用模拟器定义CMake项目，目前只需添加一个.cpp，并按下述命令测试。）

```bash
mkdir build
cd build
cmake .. 
make
```

## 2.3 Tester avec Gtest （用Gtest测试）

- Vous allez maintenant ajouter de premiers tests à votre projet en vous liant à la bibliothèque gtest, comme réalisé dans le sous-projet du TD 1.  
  （像TD1子项目那样链接gtest，为项目添加首批测试。）  
  Vous utiliserez les commandes `find_package`, `target_link_libraries` et `enable_testing` dans votre CMakeLists.txt.  
  （在CMakeLists.txt中使用`find_package`、`target_link_libraries`和`enable_testing`。）
- Comme fait avec le projet démo du TD 1, vous ajouterez un exécutable de test, via un fichier `test.cpp` et vous utiliserez la macro `TEST` de gtest pour tester toutes les fonctions de base de votre projet de simulateur :
  （参照TD1示例，新增`test.cpp`测试可执行文件，用gtest的`TEST`宏覆盖基础函数。）

```c++
TEST(MainFunctionTest,InitParticlesTest){
  initParticles();
}

TEST(MainFunctionTest,PrintParticlesTest){
  printParticles(0);
}
...
```

- Il faudra donc sortir ces méthodes de votre `main.cpp`, pour les rendre accessible dans dans un fichier `.h` : `simulator.h`, qui vous permettra de les inclure dans `main.cpp` et dans `test.cpp`. Attention, les fonctions doivent être uniquement déclarées dans le fichier `simulator.h`. Elles seront définies dans un .cpp, `simulator.cpp`.  
  （需将这些函数从`main.cpp`抽出到头文件`simulator.h`声明，在`simulator.cpp`定义，便于`main.cpp`和`test.cpp`复用。）
- En ajoutant la commande `gtest_discover_test(target)` dans votre CMakeLists.txt, vos tests seront disponibles depuis la commande `ctest`:  
  （在CMakeLists.txt中加入`gtest_discover_test(target)`后，可用`ctest`发现并运行测试：）

```txt
>ctest -N
Test project /work/irlin214_1/dechaiss/DOCUMENTS/cours/UVSQ/poocs/thoughts/proto_TD/TD_cmake_test/build_local_gtest
  Test #1: MainFunctionTest.InitParticlesTest
  Test #2: MainFunctionTest.PrintParticlesTest
  Test #3: MainFunctionTest.ComputeParticleEvolution
  Test #4: MainFunctionTest.ComputeSteadyStateTest
  Test #5: MainFunctionTest.ComputeUnsteadyStateTest
  Test #6: AllTestsInTest

Total Tests: 6

```

```txt
>ctest -I 1,3
Test project /work/irlin214_1/dechaiss/DOCUMENTS/cours/UVSQ/poocs/thoughts/proto_TD/TD_cmake_test/build_local_gtest
    Start 1: MainFunctionTest.InitParticlesTest
1/3 Test #1: MainFunctionTest.InitParticlesTest ..........   Passed    0.15 sec
    Start 2: MainFunctionTest.PrintParticlesTest
2/3 Test #2: MainFunctionTest.PrintParticlesTest .........   Passed    0.00 sec
    Start 3: MainFunctionTest.ComputeParticleEvolution
3/3 Test #3: MainFunctionTest.ComputeParticleEvolution ...   Passed    0.00 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.16 sec

```

## 2.4 Refactoring orienté objet （面向对象重构）

### 2.4.1 Création d'une classe `Particules` （创建`Particles`类）

Introduisez la classe `Particles` au sein du namespace ``simulator`` afin qu'elle prenne en charge les méthodes `init_particles()`, `compute_particles()` et `print_particles()`, sans changer pour l'instant le contenu de ces méthodes.  
（在`simulator`命名空间引入`Particles`类，承载三大方法，暂不改其内容。）

Mettez à jour votre programme principal et vos tests unitaires pour utiliser cette nouvelle classe `Particles`. Cette étape peut être faite en premier, avant de créer votre classe, afin d'avoir une approche dirigée par les tests (*test driven*).  
（更新主程序与单测以使用`Particles`类，甚至可先写测试再实现类，走TDD。）

### 2.4.2 Création d'une classe polymorphe `Simulator` （创建多态`Simulator`类）

Dans cette nouvelle étape, le calcul ne va plus être effectué directement au seine de la méthode ``Particles::compute()``.  
（此步骤中，计算不再直接在`Particles::compute()`内完成。）  
Une classe `Simulator` va être utilisée pour pouvoir gérer de manière polymorphe l'exécution d'un calcul stationnaire ou instationnaire.  
（引入`Simulator`类以多态方式处理稳态与非稳态计算。）

Vous définirez une classe de base `Simulator` et deux classes dérivées `SteadySimulator` et `UnsteadySimulator`. La classe de base proposera une méthode `Simulator::compute()` qui sera spécialisée par les deux classes filles. Ainsi la branche du switch `Steady` se retrouvera dans `SteadySimulator::compute()`, et la branche `Unsteady` se retrouvera dans `UnsteadySimulator::compute()`.  
（定义基类`Simulator`及子类`SteadySimulator`、`UnsteadySimulator`，基类`compute`由子类具体实现，对应原先switch的两支。）

Vous pouvez maintenant :
（现在你可以：）

- créer une nouvelle méthode `Particles::compute()` qui ne prendra pas d'argument mais appellera une donnée membre de type `Simulator*` que vous aurez ajouté dans `Particles`.  
  （新增无参`Particles::compute()`，调用成员指针`Simulator*`。）
- créer une nouvelle méthode `Particles::init(ComputeType)`, qui permettra d'initialiser le pointeur `Simulator*` en fonction du type de calcul, `Steady`ou `Unsteady`.  
  （新增`Particles::init(ComputeType)`，按计算类型初始化`Simulator*`。）

Votre classe contient maintenant un pointeur, attention à gérer correctement la mémoire...  
（类里有裸指针，注意正确管理内存。）

## Bonus : choix dynamique de la configuration de calcul （加分：动态选择计算配置）

Pour l'instant le choix de la configuration du problème (stationnaire ou instationnaire) est réalisé statiquement dans votre programme, lorsque vous créez une instance de votre `enum` `ComputeType`.  
（目前通过创建`ComputeType`实例静态选择模式。）  
Vous allez maintenant permettre à l'utilisateur de choisir la simulation qu'il souhaite lancer en ligne de commande.  
（现在允许用户在命令行选择运行的模拟。）  
Votre programme prendra donc en paramètre un argument, que vous récupérerez grâce aux arguments `(int argc, char** argv)` de la fonction `main`. Il devra :  
（程序将通过`main`的参数获取一个输入参数，需要完成：）

- récupérer une chaîne de caractères : "steady" ou "unsteady" en argument (attention à bien indiquer ces valeurs possibles à l'utilisateur lorsqu'il ne donne pas d'argument).  
  （读取参数字符串“steady”或“unsteady”，无参数时提示可选值。）
- créer ensuite une fabrique, qui en prenant cette argument d'entrée sera capable de créer l'instance souhaitée de la classe `Simulator`. Votre fabrique assurera, grâce à un dictionnaire, la conversion entre la chaîne de caractères donnée en entrée et l'enum.
  （创建工厂，根据输入字符串生成对应`Simulator`实例，用映射完成字符串到枚举的转换。）

Le livrable de ce TD doit être configurable via CMake, compilable et avoir une base de tests ok.  
（最终交付需可用CMake配置、可编译并具备基本通过的测试。）
