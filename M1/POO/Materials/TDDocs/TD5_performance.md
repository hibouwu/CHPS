# TD 2 à 5 simulateur de pollution atmosphérique （大气污染模拟器第2至5次）

Contexte : il est aujourd'hui primordial de contrôler la quantité de polluants dans l'air de nos grandes agglomérations ainsi que son évolution. Il est possible de prédire cette quantité par des simulations particulaires où l'on pourra suivre la dispersion des particules de polluants dans l'air. 
（背景：必须监测大城市空气污染物的数量及其变化，可用粒子模拟预测并跟踪扩散。）

Nous proposons d'utiliser ce contexte comme fil rouge de nos séances de TD.
（本系列TD以此场景为主线。）

## TD 5 Optimisation （优化）

## 5.1 Analyse de performances （性能分析）

Afin de mesurer les performances de votre code, vous construirez une classe `Timer` qui grâce à des méthodes `start`, `stop` et `print` vous permettra de calculer le temps passé entre les appels à `start` et `stop` et de l'afficher avec la méthode `print`. A l'intérieur de cette classe vous utiliserez les outils du standard `std::chrono` pour effectuer ces mesures. Vous pourrez par exemple stocker dans la classe deux `time_point`, l'un affecté lors du `start` et l'autre lors du `stop`.
（为了衡量代码性能，编写一个`Timer`类，利用`start`、`stop`和`print`方法计算`start`和`stop`之间的耗时，并由`print`打印出来。类中使用标准库`std::chrono`提供的工具进行计时，例如在类里存两份`time_point`，一个在`start`时赋值，另一个在`stop`时赋值。）

Vous créerez deux `Timer`, l'un pour calculer le temps pris par la simulation stationnaire et l'autre pour calculer le temps pris pour la simulation instationnaire. Vous afficherez ces résultats à l'écran en millisecondes. Ces mesures doivent être faites en faisant tourner le code en mode **Release**. Vous pourrez laisser CMake choisir les options de compilation adaptées, il vous suffira alors de le lancer avec l'option : ```cmake -DCMAKE_BUILD_TYPE=Release```. Il vous faudra également désactiver tous les affichages à l'écran et dans les fichiers que vous pouviez avoir mis pour le debug et qui sont très consommateurs de temps CPU. Afin de pouvoir faire des mesures significatives, vous réaliserez un calcul pour un nombre de particules de l'ordre $10^6$. Afin d'équilibrer la charge de calcul entre le stationnaire et l'instationnaire, vous pourrez mettre trois fois plus de particules pour le cas stationnaire.
（创建两个`Timer`，一个测稳态模拟时间，另一个测非稳态模拟时间，并以毫秒打印。计时需在Release模式下运行，可用`cmake -DCMAKE_BUILD_TYPE=Release`让CMake选择编译选项。同时关闭所有调试用的屏幕/文件输出，因为耗CPU。为得到有意义的测量，粒子数量做到约$10^6$；为平衡稳态与非稳态的计算量，稳态可多用三倍粒子数。）

## 5.2 Amélioration des performances via `std::thread` （利用`std::thread`改进性能）

Un premier travail d'optimisation à grain grossier pourra consister à exécuter dans des threads distincts les différents noyaux de calcul de votre applications. Les phase d'`init` et de `compute` ne sont pas parallélisables entre elles en revanche vous allez pouvoir séparer dans des threads différents les deux populations de particules introduites au TD 4 pour simuler les différents modèles de vitesse de l'air (4.2). Afin de pouvoir comparer vos performances séquentielles et parallèles vous déplacerez le contenu de votre `main` au sein d'une fonction `solve()`. Vous créerez ensuite une nouvelle fonction `solve_parallel()` dans laquelle vous recopierez le contenu de `solve()`. C'est dans cette nouvelle méthode que vous ferez la parallélisation. Pour mieux encapsuler vous pouvez aussi décider de créer une nouvelle classe `Problem` qui contiendra ces deux méthodes Problem::solve() et `Problem::solve_parallel()`.
（第一步粗粒度优化可以把应用的不同计算核心放在各自的线程里执行。`init`与`compute`阶段不能互相并行，但可以把TD4中为不同空气速度模型（4.2）引入的两类粒子分配到不同线程。为比较串行与并行性能，将`main`的内容移入函数`solve()`，再复制到新函数`solve_parallel()`中进行并行化。为更好封装，也可以新建`Problem`类，包含`Problem::solve()`和`Problem::solve_parallel()`。）

### 5.2.1 Premier exemple d'utilisation de `std::thread` （`std::thread`的首个示例）

Depuis C++11, il est assez facile d'introduire des processus légers (threads). En effet vous avez accès à la classe `thread` depuis le header `<thread>`. Cette classe prend à la construction une $\lambda$-fonction qui sera exécutée par le processus. Ainsi, l'exemple de code suivant exécutera en parallèle deux threads :
（自C++11起，可轻松引入轻量进程（线程）：`<thread>`头里提供`std::thread`类，构造时接受要在线程中执行的lambda。下面的示例会并行执行两个线程：）

```c++
#include <thread>

int main(){
    std::thread first_thread([](){
        //  do something : compute a first particle group
    });
    std::thread second_thread([](){
        //  do something : compute a second particle group
    });
    first_thread.join();
    second_thread.join();
    return 0;
}
```

Pour pouvoir exécuter un programme avec des `std::thread` il faudra embarquer la bibliothèque de threads de votre système d'exploitation à l'édition des liens. CMake est là pour vous aider dans ce travail : il faudra ajouter les lignes suivantes dans votre CMakeLists.txt, en remplaçant `MyExe` par le nom de la target CMake associée à votre exécutable :
（要运行使用`std::thread`的程序，链接时需带上系统的线程库。CMake可以帮忙：在CMakeLists.txt中加入以下内容，并用你的可执行目标名替换`MyExe`：）

```cmake
find_package(Threads)
target_link_libraries(MyExe Threads::Threads)
```

### 5.2.2 Mise en oeuvre dans le simulateur （在模拟器中的实现）

Comme vous le voyez dans l'exemple, les opérations effectuées dans le thread, sont passées sous la forme d'une $\lambda$-fonction. Vous pouvez accéder à la mémoire du thread principal en capturant des variables dans les $\lambda$ mais attention aux accès concurrents. Dans notre exemple, vous pourrez créer plusieurs groupes de particules, par exemple pour des modèles de vitesses différents et faire l'initialisation, le calcul et l'affichage dans un thread différent pour chaque groupe de particules.
（如示例所示，线程中的操作以lambda形式传入。可以在lambda中捕获主线程的变量，但要注意并发访问。这里可以为不同速度模型创建多个粒子群，每个群在独立线程中完成初始化、计算与输出。）

Vous comparerez ensuite les temps de calcul au temps séquentiel, toujours en mode Release.
（随后在Release模式下，把并行的计算时间与串行时间进行对比。）

## 5.3 Amélioration des performances via une parallélisation des boucles （通过循环并行化提升性能）

Les gains possibles avec cette approche à grains grossiers sont relativement limités : ils ne permettent pas de paralléliser pour un groupe de particules données. Or les boucles de calculs sur les particules sont *embarrassingly parallel*. En effet les calculs sont complètement indépendants pour chaque particule. Nous allons donc maintenant réaliser un parallélisme à grain plus fin, au niveau des boucles de calcul.
（这种粗粒度方法的收益有限，无法对单个粒子群内并行。但粒子计算循环是“尴尬并行”（天然可并行）的：每个粒子的计算彼此独立。接下来在循环层面进行更细粒度的并行。）

Le plus simple pour paralléliser nos boucles tout en restant sur du C++ standard sera d'utiliser les algorithmes parallèles de la STL. En effet dans les parties 3.5.2 du TD3 et 4.1 du TD4, vous avez introduit des algorithmes de la STL dans la totalité des boucles sur le nuage de particules (initialisation et calcul). Nous allons pouvoir introduire assez simplement du parallélisme.
（在保持标准C++的同时并行化循环，最简单的方法是使用STL并行算法。在TD3第3.5.2节和TD4第4.1节，你已将粒子云的所有循环（初始化与计算）改用STL算法，因此可以相当容易地加入并行。）

### 5.3.1 Préparation （准备）

Pour pouvoir faire fonctionner les algorithmes parallèles de la STL, il est nécessaire d'embarquer Intel TBB à l'édition des liens. Pour l'installer sur votre machine Linux, vous pouvez le faire via le paquet :
（要让STL并行算法工作，链接时需要带上Intel TBB。在Linux机器上可通过以下包安装：）

```shell
sudo apt install libtbb-dev
```

Il faudra donc modifier votre CMakeLists.txt, comme d'habitude en remplaçant `MyExe` par le nom de la target CMake associée à votre exécutable :
（因此需要修改CMakeLists.txt，照例用你的可执行目标名替换`MyExe`：）

```cmake
find_package(Threads)
find_package(TBB)
target_link_libraries(MyExe Threads::Threads TBB::tbb)
```

### 5.3.2 Mise en oeuvre （实现）

La parallélisation de votre algorithme se fera maintenant très simplement, en ajoutant en paramètre l'environnement d'exécution :
（并行化算法现在很简单，只需在参数中添加执行策略即可：）

```c++
#include <execution>
#include <algorithm>
int main() {
    std::for_each(std::execution::par,times.begin(),times.end(),[](auto time) {
      // your function
    });
}
```

Vous pourrez regarder sur https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t le sens des différentes valeurs dans std::execution pour choisir la plus adaptée. Vous pourrez comparer avec le séquentiel grâce à la valeur `std::execution::seq`.
（可查阅 https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t 了解`std::execution`不同取值含义，从中选择最合适的策略，并用`std::execution::seq`与串行进行对比。）

Vous utiliserez cette syntaxe dans toutes les boucles sur votre nuage de particules, que ce soit pour l'initialisation ou pour le calcul des positions et des vitesses.
（在所有粒子云循环中使用这种语法，无论是初始化还是位置、速度计算。）

## Bonus remplacer `std::thread` par `std::async` （加分项：用`std::async`替代`std::thread`）

L'utilisation de `std::async` peut être assez intéressante. En effet cette fonction va créer le thread pour vous, encapsuler son éventuel résultat dans une classe `std::future`, et vous permettre de choisir entre une exécution séquentielle ou parallèle. Si nous reprenons l'exemple donné en 5.2.1 et que nous le réécrivons à base d'`async` cela donnera :
（使用`std::async`也很有意思：它会为你创建线程，把可能的结果封装到`std::future`中，并允许在串行与并行之间选择。若用`async`重写5.2.1的例子，会得到下面的代码：）

```c++
#include <future>

int main(){
    std::future first_task = std::async(std::launch::async,[](){
        //  do something : compute a first particle group
    });
    std::future second_task = std::async(std::launch::async,[](){
        //  do something : compute a second particle group
    });
    first_task.wait();
    second_task.wait();
    return 0;
}
```

Il est également possible de mettre comme premier argument `std::launch::deferred` ; il n'y aura alors pas de création de thread et la tâche sera exécutée séquentiellement à l'appel du `wait()`. Vous pourrez alors facilement comparer les performances en séquentiel ou parallèle. Vous pourrez aussi comparer les performances de la solution à base d'`async` avec celles de la solution à base de `thread`.
（也可以把第一个参数设为`std::launch::deferred`，此时不会创建线程，任务会在调用`wait()`时串行执行。这样就能轻松对比串行与并行性能，并将基于`async`的方案与基于`thread`的方案比较。）
