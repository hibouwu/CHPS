Okay, so we've been through, uh, the physics interface to access threads,s. It's great thatem, this, for hor example, is the route. So it's not supposed to be very original., The The first part, uh, the way I present my processes and the threads, uh, can be be quite unexpected when you are not used to using it to managing threads.
好的，我们已经了解了用于访问线程的物理接口。举个例子，这是路径。所以它不需要非常原创。第一部分，我展示我的流程和线程的方式，当你不习惯使用它来管理线程时，可能会相当出乎意料。

For this part, it's supposed to be done.one Soo, in C, with the positive interface, a thread is represented by a thread identifier. A P-thread T variable. Under the hood, it's just an integer. A large integer. And you can, uh, retrieve your own thread identifier with this beautiful function. P-thread self. It's used ver very useful to know what is your name. Basically, a thread identifier is is the name of a thread, and like that y you can kn know your name.
在这部分，应该完成了。在C语言中，使用POSIX线程接口，一个线程由线程标识符表示，即一个pthread_t变量。底层它只是一个整数，一个较大的整数。你可以通过这个非常有用的函数pthread_self()来获取你自己的线程标识符。这个函数非常有用，能让你知道自己的“名字”。基本上，线程标识符就是线程的名字，通过它你可以知道自己的身份。

Which is given by the operating system. By y compour parent. I don't kn. Uh, if youou want to create a thread, you have this P-thread cre create function. So the signature of the function is a bit ugly. You have stars everywhere. It's bad sign in C. Just, you have to know the first parameter will be filled with the identifier of the thread you created.
这是由操作系统提供的。通过你的父进程。我不知道。如果你想创建一个线程，你可以使用 pthread_create 函数。这个函数的签名有点复杂，到处都是指针，在 C 语言中这不是一个好的写法。你需要知道，第一个参数将被填充为你创建的线程的标识符。

It It's's an output parameter. This one. The value that is returned is 0 or something that is not 0. to know that an error occurred. Here you have an attribute where you can specify how you want Linux to manage your thread. We will not use it. But with this parameter, you can fix where is y your stack of frame, what is the size of your stack, if you want to be scheduled to be the real-time algorithm, normal
这是一个输出参数。返回的值是0或非0，用于判断是否发生了错误。这里有一个属性，可以指定你希望Linux如何管理你的线程。我们不会使用它。但通过这个参数，你可以设置栈帧的位置、栈的大小，以及是否希望线程被调度为实时算法或普通调度。

lazy other algorithm, I don't rem remember the name, you can specify if you want to be the detailed or detailed state, you have millions of parameters that are possible. We will always use none. Here is the most important parameter. It's the start function. So when the thread is created, you give it.
懒惰的其他算法，我不记得名字了，你可以指定是否要详细状态，有数百万个可能的参数。我们总是使用无参数。这里是最重要的参数，就是启动函数。当线程被创建时，你需要提供它。

The stack will be be allocated by the GFC.P Not by the operating system. By the GFC. The GFC creates a thread, and the thread, when it starts, you start with an anti-stack of gold frames, and by giving the address where you want to start your thad. It's just what is the state of the initial state of the task that is there.
栈将由GFC.P分配，而不是操作系统分配。GFC负责创建线程，当线程启动时，你会从一组初始的黄金帧栈开始，并通过提供你希望线程开始的地址来指定。这里描述的就是任务的初始状态。

Okay? And you can give a thread an argument. Which is useful when you want to spawn multiple threads and you want each thread to have a rank, uh, to know where you have to work in the matririx or somethethinging like that. Okay? So the signature itself is ugly, but when when you use a thread, it's straightforward.
好的，你可以给线程传递参数。当你想创建多个线程，并且希望每个线程都有一个编号，以便知道它们在矩阵中需要处理的位置时，这非常有用。这个函数的签名虽然不太美观，但使用起来很简单明了。

Let's imagine here I have my function F., I want to to print F is running. And And I can write this ce.odode: P--thread createsates. P-thread creates. I give it the thread pointer to TID, which is a local variable. When after the call to P-thread create, in TID I can find the thread identifier of the new threread.
假设这里我有一个函数F，我想打印“F正在运行”。我可以这样写代码：pthread_create。pthread_create函数，我传入线程指针TID，这是一个局部变量。调用pthread_create之后，TID中会保存新线程的线程标识符。

I don't need a parameter. I start my function F, and my argument is done because I had nothing interesting to say. And then main is running in parallel with F. Okay? After this call, you have two threads. You don't't know which one will print the first. And you can even have a very unexpected result.
我不需要参数。我启动我的函数F，参数就完成了，因为我没有什么有趣的内容要说。然后主线程和函数F并行运行。明白吗？调用之后，你有两个线程。你不知道哪个线程会先打印。甚至可能会有非常意想不到的结果。

You made never se see F is running. It's a bit strange. No, it's very easy. When you return from main, you have have a system code to the exit function. The exit function is, uh, a function that destroys all the threads of your process. At once. So it will kill all your threads. So if if you are unlucky, main will create the new thread, continue continues execution, reach the end of main, you call exit, and the operating system kills all your threads, and this onee, was never scheduled by the operating system.
你从未看到线程F在运行。这有点奇怪。其实很简单。当你从main函数返回时，系统会调用exit函数。exit函数是一个会一次性销毁你进程中所有线程的函数。所以它会终止所有线程。如果你运气不好，main函数会创建一个新线程，继续执行，直到main结束，调用exit，操作系统就会杀死所有线程，而这个新线程可能根本没有被操作系统调度过。

It was too fast. Okay, we terminate a thread after a call to P-thread exit. So when you call P-thread exit, the. Onlyly the thread that is running will terminate. Instantaneously. At the end of the start routine, you end yourour thread. So when you return from F at this point, with none, uh, the system will dest destroy the thread.
速度太快了。好的，我们在调用 pthread_exit 后终止线程。所以当你调用 pthread_exit 时，只有正在运行的线程会立即终止。在启动例程结束时，你结束了你的线程。因此，当你从函数返回时，系统会销毁该线程。

Basically, your stack frame is empty. And you have a kind of trampoline that performs a system call for you. In the GFC to quit the thread. And the system will terminate all the threads of a process when you call the exit function. Exit is a— Very power. Full function. That terminates all the threads at once.
基本上，你的栈帧是空的。你有一种跳板，它会为你执行系统调用。在GFC中用于退出线程。当你调用exit函数时，系统会终止进程中的所有线程。exit是一个非常强大的函数，可以一次性终止所有线程。

Not just your own thread. And by default, when you return from main, the main GFC call exit and not P-thread exit. It's historical. It for insts itsance, when main terminates, it's supposed to terminate the main and not all the processes. But since all the applications in the world suppose that you terminate the process when you quit main and not the thread, it's the case today.
不仅仅是你自己的线程。默认情况下，当你从 main 返回时，主线程调用的是 exit 而不是 pthread_exit。这是历史原因。例如，当 main 终止时，应该只终止主线程，而不是所有进程。但由于世界上所有应用程序都假设退出 main 时会终止整个进程，而不是仅仅终止线程，所以现在就是这种情况。

No question? The difference between P-ththread exit and exit? Okay. To synchronize two threads, because sometimes we want to synchronize them, you have P-thread join. While you may want to synchronize two threads, for example, to be sure that F is running has been executed before leaving main. Can be a reason.
没有问题吗？P-thread退出和exit的区别是什么？好的。为了同步两个线程，因为有时我们需要同步它们，你可以使用P-thread join。例如，你可能想同步两个线程，以确保函数F在main函数结束之前已经执行完毕，这就是一个原因。

So for that, you have P-thread join. So P-thread join, you give it a thread ID, and it will wait for the termin termination of this thread. This parameter is a void start star. It's the return the value returned by the thread. So you have something strange. A P-thread a thread function take as parameter an argument, and return a a pointer.
为此，你可以使用 pthread_join。pthread_join 接受一个线程 ID 作为参数，并会等待该线程的终止。这个参数是一个 void 指针的二级指针，用于接收线程返回的值。这里有一点需要注意，pthread 线程函数接受一个参数，并返回一个指针。

I If you want to fill rate value with the val value of the pointer, you have to give a pointer to a pointer. That's why you have two stars. At this place. Basically, star P rate val. The The D reference P rate val, it will receive the void star returned by P-read create. In my mind, I don't see a pointer. I see integers.
如果你想用指针的 val 值来填充 rate 值，你必须传递一个指向指针的指针。这就是为什么这里有两个星号。基本上，*prate_val 是对 prate_val 的解引用，它将接收由 p_read_create 返回的 void*。在我看来，我看不到指针，我只看到整数。

So for me, a thread return an integer. And I replace in my mind the void starars that you see here by integer. Just a type returned by P-thread cree. So like that, you can be sure that so you create your thread with F, F is running, and main and F is running will be executed in parallel. So you don't know if you will see main is running first or F is running first. It can be any order, any schedule.
对我来说，线程返回一个整数。我在脑海中将你在这里看到的 void* 替换为整数。只是 P-thread 创建函数返回的类型。这样，你可以确定你创建的线程函数 F 正在运行，主线程和 F 线程会并行执行。所以你不知道是先看到“主线程正在运行”还是“F 正在运行”，执行顺序和调度都是不确定的。

After the join, you wait for the termination of this thread, and rate val will receive the value returned by F. So the cast is a void the type in the C language is a void star, uh, you can return an integerer. iff you want. Like that. It's ugly, but it works. Here is the value 42, cast as a void star, and return just the value 42, and you will fill the rate val with 42. You can print 42 at the end.
在调用 join 之后，你等待该线程的终止，rate_val 将接收函数 F 返回的值。这里的类型转换是将值转换为 void* 类型，在 C 语言中是 void 指针。你也可以返回一个整数。如果你愿意的话。虽然这样做不太优雅，但它能正常工作。这里将值 42 转换为 void* 并返回，然后你会在 rate_val 中得到 42。最后你可以打印出 42。

Like that. Okay. No problem? See? We Wh? Wait, wait. It's only. Uh, to get the value return returned by F that you will use it. But it's mandatory. You cannot givee, ah, none here. As That'side from Okay, it looks confusing. Forget to just ask to not return the value. Your P-thread. You return none and you will be very happy.
就是这样。好的，没问题吧？看到了吗？等等，等等。只是为了获取函数F返回的值，你会使用它。但这是必须的，你不能在这里传递None。除此之外，好吧，看起来有点混乱。忘了吧，只要不要返回值就行了。你的线程返回None，你会很满意的。

Okay, you have the detailach mode or the join label mode. So here,. When you call P-thread exit, thead. Is killed by the operating system. So it means that the thread will not be scheduled anymore. But at some point,. You have your thread that is running, and it return the value. So the thread is. In the.
好的，你有详细模式或连接标签模式。在这里，当你调用P-thread退出时，线程会被操作系统终止。这意味着该线程将不再被调度。但在某些情况下，你的线程仍在运行，并返回一个值。所以线程处于…

Zombie mode. It's not a zombie mode, but not so far. But the data structure is not destroyed. Immediately, by the the operating system, becauseuse y youou have to store this 42 somewhere. 42 is the value you have to store it in memory. Okay? And later, maybe half an hour later, you have another thread that call P-thread join.
僵尸模式。它不是严格意义上的僵尸模式，但也不远。数据结构并没有被销毁。操作系统会立即处理，因为你必须把这个42存储在某个地方。42是你必须存储在内存中的值。明白吗？之后，可能半小时后，你有另一个线程调用P-thread的join函数。

To get this value. So it means that the task that represents the thad. Inside the operating system has to remain alive. The system cannot free it just because you need this space, some space, for this value 42. And P-thread join what. The The operating system will do, it's that it will return 42 and free the task key at this step.
要获得这个值，这意味着代表线程的任务在操作系统内部必须保持存活。系统不能仅仅因为你需要这部分空间来存储值42而释放它。而pthread_join的作用是，操作系统会返回42并在此步骤释放该任务的资源。

Inside the join. Just because you need some space to keep this 42, this value 42. Okay, so by default,, when you create a thread, the operating system offers this behavior. It means that you can join the thread. And if you forget to call P-thread join, you will have a memory leak. Because the 42 will remain in memory forever.
在线程连接中。只是因为你需要一些空间来保存这个值42。好的，所以默认情况下，当你创建一个线程时，操作系统会提供这种行为。这意味着你可以连接线程。如果你忘记调用P-thread join，你将会有内存泄漏。因为42会永远保留在内存中。

Not forever. When the process terminates, of course, the system. Will not clean up everything. But if you have a server that is running for years, uh, in this case, you may have a small memory le leak and we don't like memory leaks in. When you program. When you see the price of memory today, uh, it's just we have problem to buy the fuel and the oil.il fuel
不会永远存在。当进程终止时，系统当然不会清理所有内容。但如果你的服务器运行了多年，在这种情况下，可能会有小的内存泄漏，而我们在编程时是不喜欢内存泄漏的。考虑到现在内存的价格，我们面临的问题是购买燃料和机油的成本。

I think that with memory, the problem is worse. Really? I bought two machines last year. In September, with the same price, I could have bought three machines. Just because Totally crazy. I had to divide by three. Amount of memory. A bigat machine or 3eth0,000. Uh, okay. In some cases, youou don't care about, uh, jo joining the thread. You're not not interested in the value returned by your thad.
我认为内存方面的问题更严重。真的吗？我去年买了两台机器。九月份，同样的价格我本可以买三台。简直疯狂。我不得不把内存除以三。一台大机器或3万多。嗯，好吧。在某些情况下，你并不关心线程的加入，也不在意线程返回的值。

And you don't know exactly where to call this P-thread join. Because you have to call it. But starting a thread just to call P-thread join to join all the threads that you created, to do nothing with with the the returned value, is totally stupid. So for this reason, you can start a thread in detach mode.
你不确定具体在哪里调用 pthread_join，因为你必须调用它。但仅仅为了调用 pthread_join 来等待所有你创建的线程结束，而不处理返回值，这是完全没有意义的。因此，你可以以分离模式启动线程。

In detach mode, it means that when the thread call P-thread exit, in this case, the operating system will destroy immediately the task. It will free the memory. And you cannot join it anymore. That's's why it's not joinableable. So it can be useful, uh, it's the only parameter that for me matterss, uh, in in the course so you can you can call P-thread detach. You give your thread ID,.
在分离模式下，当线程调用 pthread_exit 时，操作系统会立即销毁该任务，释放内存。此时无法再对该线程进行 join，因此它是不可连接的。这就是为什么它不可连接的原因。所以这很有用，对我来说这是课程中唯一重要的参数。你可以调用 pthread_detach，并传入线程 ID。

And probably Boolean value after. I'm not sure. If you want to switch from the detach or joinable mode. Not very important. So we have threads. So we introduce beautiftiful tool to parallelize our applications. But at the same time, we introduce the worst problem of computer science, which is the problem of concurry.
可能后面还有布尔值，但我不确定。如果你想在分离模式和可连接模式之间切换，这并不是很重要。我们有线程，所以我们引入了一个非常棒的工具来实现应用程序的并行化。但与此同时，我们也引入了计算机科学中最棘手的问题——并发问题。

And it's difficult. Very difficult. Even Claude AI is totally bad at solving this kind of problem. Really? Not for stupid codes, but as soon as it becomes complex. Claude AI is unable to understandstand anything. That's why I'm pretty sure that I will not be replaced by an AI. Very hard. And better than AI.
这很难，非常难。即使是Claude AI在解决这类问题时也表现得很差。真的吗？对于简单的代码还好，但一旦变得复杂，Claude AI就无法理解任何东西。这就是为什么我很确定我不会被AI取代。非常难，而且我比AI更优秀。

Uh, so as soon as you share memory, the problem is that when you design an application, you don't design you design. Your application by designing high-level operations. But you don't care about the low-level execution of each instruction. It's not your business. What you want for example, let's imagine you want to design a bug.
嗯，所以一旦你共享内存，问题就在于当你设计一个应用程序时，你并不是设计每一条指令的具体执行过程，而是通过设计高级操作来构建你的应用程序。底层每条指令的执行细节并不在你的关注范围内。举个例子，假设你想设计一个程序。

Okay? You will implement two functions. One is credit. The other one is debit. But My code is a bit stupid bec because I could have written just a single function. And give a negative parameter. Illustrate. Uh, so I'm very bad programmer. So I write explicitly. So I write explicitly. I I take the balance, which is a global variable. I put put it in a local variable. Then I add 100 euros to my account. And then I write back the temporary value.
好的？你需要实现两个函数，一个是存款（credit），另一个是取款（debit）。但我的代码有点笨，因为我本可以只写一个函数，然后传入一个负数参数来实现。举个例子……嗯，我是个很糟糕的程序员，所以我写得很明确。我先把余额（这是一个全局变量）取出来，放到一个局部变量里，然后给我的账户加上100欧元，最后再把临时变量的值写回去。

A normal programmer will never write that. Normal programmer will write balance plus equal 100. The reason why I decompose is to show you what happens inside the processor. So the other thread, You you remove some money from your account. And if you execute the two threads in parallel, you may you will you can have any schedule of the two threads.
一个普通程序员永远不会那样写。普通程序员会写 balance += 100。之所以我将其拆解，是为了向你展示处理器内部发生了什么。假设另一个线程从你的账户中取出一些钱。如果你并行执行这两个线程，它们的执行顺序可能是任意的。

Because you have a single core or maybe because you have two cores and the timing can be any timing between the different instructions. At each step, very important, you execute atomically each instruction. Which is a strong hypothesis. Alrey. So I may have this schedule I start by the thread of. G. I start with the thread 2..
因为你只有一个核心，或者可能有两个核心，不同指令之间的执行时序可以是任意的。在每一步，非常重要的是，你必须以原子方式执行每条指令。这是一个强假设。好了，所以我可能有这样的执行顺序：我先从线程1开始，然后是线程2。

I execute F and G. So you have a. The. Two threads. You have bal balance and you are very rich. You have 1,000 euros. You start with F, G, okay? So T and P is equal to 1,000. Then you execute A, B, C, D, E, so you add your salary to your bank account. You're very happy. You have 1,100 euros. And then you continue the execution in thread 2.
我执行了F和G。所以你有两个线程。你有余额，你非常富有。你有1000欧元。你从F和G开始，好吗？所以T和P等于1000。然后你执行A、B、C、D、E，把你的工资存入银行账户。你非常高兴，你有1100欧元。然后你继续执行线程2。

The problem is that between this reread and this write, you have an hidden operation that you haven't seen. The ones that increment the balance. So you will just fin finish your code. You will compute T and P equal 999. And B equal T and P. Let's imagine that you receivedive your salary. At the same time, you go to the dad and take 1 euro and your salary is lost. You will be really upset.
问题在于，在这次重读和这次写入之间，有一个你没有注意到的隐藏操作，就是那个增加余额的操作。所以你会完成你的代码，计算出 T 和 P 等于 999，而 B 等于 T 和 P。假设你同时收到了工资，同时你去找爸爸拿了1欧元，但你的工资却丢失了。你会非常生气。

Something that you don't want. Here the problem is that we have re readers and writers to share variable. So for my my example, I have two writers. But I may have the same problem with two readers. But I will will show show you in a just a min.ute. And. Here it's very complex. Because you have two levels of understanding.
你不想要的情况是这样的：问题在于我们有多个读者和写者共享变量。以我的例子来说，我有两个写者，但两个读者也可能出现同样的问题。我稍后会给你演示。这里情况非常复杂，因为你需要理解两个层面。

I don't know if it's correct or not, this code. Basically. Maybe I want to have an approximations of the number of user of my data center. And it's not a big deal. At 100 user Im. It's not very important to know that I had 1,00999 or 1,100 user connected today. I want to know that I am at the scale of 1,000.
我不确定这段代码是否正确。基本上，我可能想要大致估算一下我的数据中心的用户数量，这并不是特别重要。对于100个用户来说，我并不在意今天是有10,099还是11,000个用户连接。我只想知道用户数量大致在1000的规模。

So maybe that this code is correct. If it's a bank system, it's not not cor correct. Basically, it's obvious. But if it's balance is updated only for statistics, this code is cort. So you have a first problem. Is that what is correctness behind this code? And it's something that we don't explain to the students a lot.
所以这段代码可能是正确的。如果这是一个银行系统，它就不正确。基本上，这是显而易见的。但如果余额只是为了统计而更新，这段代码就是正确的。所以你面临的第一个问题是，这段代码背后的正确性是什么？而这是我们很少向学生解释的内容。

We arrive, we say, "Hey, you have got some money. You are un unhappy. Take a look. Your life will be happy." Maybe not. Maybe that this code was correct. It's really up to the semantics of the application to define what is correctness. Here I cannot abstractly tell you this code is correct or not. You understand why? Yes? It's very important to have to keep that in mind.
我们到达时会说：“嘿，你有些钱。你不开心。看看吧，你的生活会变得幸福。”也许不会。也许这段代码是正确的。真正取决于应用程序的语义来定义什么是正确。在这里，我无法抽象地告诉你这段代码是否正确。你明白为什么吗？是的，牢记这一点非常重要。

So what is correctness behind is somethething that we will try to do is to express what is correctness. Uh, we we will have to identify invariants. For example, if I put m money in my account in my account, I don't w wantant the money to be l. It's an invariant. But it's something that has to be specified to know if the code is correct or not.
那么，什么是正确性呢？我们将尝试表达什么是正确性。我们需要识别不变量。例如，如果我在我的账户里存入了m金额，我不希望这笔钱丢失。这就是一个不变量。但这需要被明确规定，才能判断代码是否正确。

You have to know that. And then youou have the reality. Okay, I run my my application. I don't want to lose money. Because I I'm not stupid.id. How can I make that correct? So here I introduce of course No, I want before to present you a reader-writer problem. Because a single writer and a single reader are enough to crush an application.
你必须知道这一点。然后你会面对现实。好吧，我运行我的应用程序，我不想亏钱，因为我不是傻瓜。我要怎么做才正确呢？所以这里我当然要介绍一下，在向你展示之前，我想先介绍一个读写者问题。因为一个写者和一个读者就足以让一个应用程序崩溃。

So a very simple example. You have a message that. And the value is none. Okay? And you write the a code if message is. None. You waiting for a message to arrive. And then you print it. Like that. The code is not complex. Two lines of code. It's easy. And then you. Have another thread. That create a message.
这是一个非常简单的例子。你有一条消息，值是 None。然后你写了一段代码，如果消息是 None，你就等待消息到达，然后打印它。代码不复杂，只有两行，很简单。接着你还有另一个线程来创建消息。

Not more. Okay? So this code is correct. For the moment. You're waiting for message to become not none. Someone write hello. It unblocks this code. And And you print it. Okay? Now let's imagine that you complexify slightly the code. I execute message equal none. Because I have to make some space for another incoming message.
不多了，好吗？所以这段代码目前是正确的。你在等待消息变为非空。有人写了“hello”，这就解除了代码的阻塞，然后你打印它。好了，现在假设你稍微复杂化一下代码。我执行了 message = None，因为我需要为另一个即将到来的消息腾出空间。

Ok Okay? Like that, I will have a. T1, T2, and T3. Let's imagine that you have two threads that are processing the messages. So we'll have a1a to. a2b to c thread3a3b33c. Like that. And I can have this schedule to. 1a execute. So I write my message. Then T2 start it execution.tion. See that message is not none.
好的，明白了吗？就像这样，我会有 T1、T2 和 T3。假设你有两个线程在处理消息。我们会有 a1a 到 a2b 到 c，线程3a3b33c。就是这样。我可以有这样的调度：先执行 1a，所以我写下我的消息。然后 T2 开始执行。看到消息不是空的。

I'm unlucky. T3 is scheduled. So I execute 3 3a3b3c. Message is now none. And I continue the execution of T2. So I will try to access none. I will have a segmentation code. Okay? Here I. T3 is a reader and a writer. T1 is a pure writer. And T2 is a pure reader at this moment. Because T2 has not reached the line 3c.
我很倒霉。T3 已经被调度了。所以我执行了 3 3a3b3c。消息现在为空。然后我继续执行 T2。所以我将尝试访问空值，结果会发生段错误。明白吗？这里，T3 既是读者又是写者。T1 是纯写者。而此时 T2 是纯读者，因为 T2 还没有执行到 3c 行。

It only read memory. So just by by adding a writer and a reader is enough to crash a program. And here it's always incorrect. Basically, a program that end with a segmentation fault is by definition an incorrect program. Just to name the instructions that are executed. It's just that I have two threads that are executing this three lines.
它只是读取内存。因此，仅仅添加一个写入者和一个读取者就足以使程序崩溃。而且这里总是错误的。基本上，一个以段错误结束的程序从定义上来说就是一个错误的程序。只是为了说明执行的指令，我有两个线程在执行这三行代码。

The same ce. And so T3 execute here 2a means thread two execute whileile. thread three execute whileile. print and message equal none. And then I execute with the second th thread, I execute the third time. Exactly. And this will be worse. I will end with a ch. Not really because probably the GPC is not stupid.
同样的情况。所以这里的 T3 执行 2a，意味着线程二执行 while 循环，线程三也执行 while 循环。打印的信息等于 None。然后我用第二个线程执行，第三次执行。完全正确。情况可能会更糟，但最终不会出错，因为可能 GPC 并不傻。

So it's's really a nightmare. As soon as you have a sharp variable. And writers exist, you may have crashes. Or inconsistencies. Exactly. So to solve the problem, the normal way is is to use to define critical sections. So we say that. We will prevent two sections of code to interlee. We will execute atomically section of ce.
这真的是一场噩梦。只要你有一个共享变量，并且存在写操作，就可能会发生崩溃或数据不一致。没错。为了解决这个问题，通常的方法是定义临界区。也就是说，我们会防止两个代码段交错执行，确保临界区内的代码是原子执行的。

And as soon as we have the critical sections, we can define what is mutual ex exclusion. Two critical sections are in mutual execution if one execute entirely before the other. Okay? It's very important. So it's a kind of atomicity. The section of code that contains multiple inst instructions will execute just in one shot for the others.
一旦我们确定了临界区，就可以定义什么是互斥。两个临界区是互斥执行的，如果一个在另一个之前完全执行完毕。明白吗？这非常重要。这是一种原子性。包含多条指令的代码段将作为一个整体一次性执行，不会被其他代码打断。

And the go goalal will be to drill this so we say that the critical section executes atomically and the goal will be to design an API to execute critical sections in mutual exclusion. So quite often the the crit critical section is in mutual exclusion with itself., But it's not mandatory. You could imagine executing critical sections that prevent a that prevent execution of critical section b but not of the same a at the same time.
目标是设计一个API，使临界区能够以互斥的方式执行，从而保证临界区的操作是原子性的。通常情况下，临界区会与自身互斥执行，但这并非强制要求。你可以设想一种情况，执行的临界区A会阻止临界区B的执行，但不会阻止同一临界区A的同时执行。

With read-write lock, you can immediately imagine this kind of constru. Okay. So to implement that, we have anI. Provideded by POSIX, which is the mutex. So mutex is a lock in mutual exclusion. So at high level, a mutex is just a Boolean value that tells you whether another thread is in the critical section.
使用读写锁，你可以立即想象这种结构。好的。为了实现它，我们有一个由POSIX提供的互斥锁（mutex）。互斥锁是一种互斥锁定。从高层次来看，互斥锁只是一个布尔值，用来告诉你是否有其他线程正在进入临界区。

So it will give you the algorithm.m Just to ill illustrate and show you that it's a real problem. So youou have a lock. A lock can have two states. Free or. Busy. Okay? And at high level, when you want to take a lock, what you will do is to wait for the lock to become free. So you write something like while l.
所以它会给你算法。只是为了说明并展示这是一个真实的问题。你有一个锁。锁可以有两种状态：空闲或忙碌。好的？从高层次来看，当你想获取锁时，你会等待锁变为空闲。所以你会写类似“while l”的代码。

Equal busy whe. And you say, "Okay, now the the lock is taken." And you have the unlock function. Where you write lock equal free. And basically, you start a critical section by tak taking a lock and you end it by unlocking the mutex. So when you arrive, if another threadad is executing the critical section, you wait for the critical section to execute entirely. And then you execute it.
同样忙碌的时候。你会说：“好了，现在锁已经被占用了。”然后你有一个解锁函数，在那里你将锁设置为释放状态。基本上，你通过获取锁来开始一个临界区，通过解锁互斥量来结束它。所以当你到达时，如果另一个线程正在执行临界区，你会等待该临界区执行完毕，然后你再执行。

So you cannot have any interleaving. Of the two critical sections. At high level, it works. Just here I have a small problem. This code is incorrect. I guess. Here I see that the lock is busy. But maybe another thread already took the the lock. Between this line and this line. So to implement a lock, we have a small issue.
所以你不能让两个临界区交错执行。从高层次来看，这个方法是可行的。只是这里我遇到了一个小问题。这段代码是不正确的。我猜想，在这一行和这一行之间，我看到锁是忙的，但可能另一个线程已经获取了锁。因此，在实现锁时，我们遇到了一个小问题。

Because we need a lock. A lock is basically a sharp variable that is readad and written read and written by threads so we have a concurrency issue. We will see how we solve this problem suppose that it exists. We We have some help given by the hardware for that. And we have algorithms able to solve the problem without the help the help of the hardware.
因为我们需要一个锁。锁本质上是一个被线程读取和写入的共享变量，所以会存在并发问题。我们将看到如何解决这个问题，假设它确实存在。硬件在这方面提供了一些帮助，同时我们也有一些算法能够在没有硬件帮助的情况下解决这个问题。

Okay. So in C, you have a. The type T thread mutex T. So it's basically the state of the mutex. And you have two functions, lock unlock. Lock acquire the mutex. And unlock release it. And if you want to execute your code in mutual exclusion, you just have to write that. I take the lock, T thread mutex lock, before adding some money to my ac accocount, I rele release the lock. And then I execute the code with a lock taken to debit my account.
好的。在C语言中，有一个类型叫做 `pthread_mutex_t`，它表示互斥锁的状态。你有两个函数，`lock` 和 `unlock`。`lock` 用于获取互斥锁，`unlock` 用于释放互斥锁。如果你想让代码在互斥的情况下执行，只需这样写：在向我的账户中存钱之前，我先获取锁 `pthread_mutex_lock`，然后释放锁，接着在获取锁的情况下执行扣款操作。

No problem? Okay.ay. One of the questions that you may as ask is. My c code is artificially complex. We have this temporary variable. So is it necessary to have a lock if I write balance. Plus equal 100? The The problem that this operation is. Not atomic. For the processor. And that's absolutely terrible because in terms of assembly code, on an Intel machine, you will have thise.
没问题？好的。你可能会问的一个问题是：我的C代码人为地复杂。我们有这个临时变量。那么，如果我写 balance += 100，是否有必要加锁？问题在于这个操作对处理器来说不是原子性的。这非常糟糕，因为在Intel机器的汇编代码中，你会看到这种情况。

A single instruction. Add and. Ax 100. For example. Where RAX is a pointer. To balance. So we have the illusion of a single instruction. But at a low level, you have two objects in the computer. You have the memory and. You have the CPU. And in between, you have a link, a bus, and imagine a network and cables the same thing.
一条单一的指令：加法指令，例如“add ax, 100”。其中，RAX 是一个指针，指向内存地址。因此，我们有一种单条指令的错觉。但在底层，计算机中有两个对象：内存和 CPU。它们之间通过一个连接——总线相连，可以把它想象成网络和电缆的关系。

So here you have your balance. With 100, 1 1000, the language, and the memory is not able to compute. If you want to compute something, you have to load your data to. Okay, and you keep stickick with my red pen. You load your data in the C CPPU. Inside the CPU, you have the. Circuit that is able to add two numbers.ers,
这是你的余额。拥有100或1000时，语言和内存无法进行计算。如果你想进行计算，你必须先加载你的数据。好的，继续用我的红笔标记。你需要将数据加载到CPU中。在CPU内部，有一个能够将两个数字相加的电路。

So you will compute a new value. Like that. And then write back the result. So this single instruction at a high level is not executed atomically. It's access memory 100 no. Seconds. It's very long. It performs the computation one nanosecond, and it's right back back the result 100 nanosecs. 100 nanoseconds is is very long.
所以你将计算一个新值，就像那样，然后写回结果。因此，这条高级指令并不是原子执行的。它访问内存需要100纳秒，非常长。计算只需1纳秒，而写回结果又需要100纳秒。100纳秒是非常长的时间。

For a processor. So during that time, the 100 can can be copied by by another core. And you will have the inconsistency. At low level, you have internal registers. In the CPU, that are totally hidden to the cododer, to the programmer, and when you write when the processor executes this instruction, what it does is that it loads the.
对于处理器来说，在这段时间内，100 可能会被另一个核心复制，从而导致不一致。在底层，CPU 中有一些对程序员完全隐藏的内部寄存器。当处理器执行这条指令时，它所做的是加载这些寄存器的内容。

What is located in RAX inside the hidden register. Then add to the hidden register 100, and then store the result. In balance. At low level. So you are not helped by the. Code. It's really at the hardware level that the problem occurs. So even writing X plus plus will not saveou. Sorry. Okay. We have another tool that I love.
RAX寄存器中存储着隐藏寄存器的内容。然后将隐藏寄存器的值加上100，再将结果存储起来，保持平衡。在底层操作中，代码并不能帮到你。问题实际上发生在硬件层面，所以即使写X++也无法解决。抱歉。好了，我们还有另一个我非常喜欢的工具。

It's the variable condition. When so for the locks, we will solve almost all the problem of inconsistencies in efficiciently for the five other lectures you will see how we can do better than locks. Because it's lockock is totally inefficient. In terms of parallelism, parallelism, sometimes you want synchronizations that are slightly more complex.
这是可变条件。对于锁来说，我们几乎可以解决所有不一致性的问题，提高效率。在接下来的五节课中，你将看到我们如何做得比锁更好。因为锁机制在并行性方面完全低效。有时你需要稍微复杂一些的同步方式。

Like this one. What you want is to wait for an event to happen. Here I have exactly the c code with my message. I have my sender write message in message. And I'm waiting for the message to arrive. In the other thread to print it. Exactly the code that I gave five minutes ago. Okay? So the problem is that if the message becomes null between the while and the print, I will have an inconsistency.
就像这个例子。你想做的是等待一个事件发生。这里我有一段包含我消息的C代码。我让发送者将消息写入变量message，然后我等待消息到达。在另一个线程中打印它。就是我五分钟前给出的那段代码。问题是，如果在while循环和打印之间消息变成了null，就会导致不一致。

You all agree? The The writer is not there, but you have a writer somewhere. That's write message equal n. So for this reason, I didn't l. To prote protect myself. So I forget the blue line for the moment. So you take a lock here, you write hello in the message, you release the lock, it's a bit stupid, because I have a single instruction, it's just a memory store, and it's atomic.
你们都同意吗？作者不在这里，但你们某处有一个作者。消息写入等于 n。所以出于这个原因，我没有保护自己。所以我暂时忽略蓝线。你在这里加锁，写入消息“hello”，然后释放锁，这有点多余，因为我只有一条指令，那只是一次内存存储操作，而且是原子的。

At low level. But who knows? I protect myself, I'm a bit paranoid. And for this one, it's very important, I take my lock, I read message, and I consume message. To avoid any writer between these two lines, I take a lock and I release it after. Okay? Ex Exactly the same example. Except that now I I have a reader and a writer.
在低级别上。但谁知道呢？我保护自己，我有点多疑。对于这个来说，非常重要，我先获取锁，读取消息，然后处理消息。为了避免这两行代码之间有任何写入操作，我先获取锁，之后再释放。明白吗？完全相同的例子，只是现在我既有读者也有写者。

You agree? It's okay for the team? Okay. Now let's imagine that my code is. I do while message and I don't do any anything. Forget the blue line. I just have a loop. You will have a small issue with this codee, isuse that that the l lock is taken while while youou wa wait for message to have a value.
你同意吗？团队可以接受吗？好的。现在让我们假设我的代码是这样的：我使用一个 do-while 循环，但实际上什么也没做。忽略蓝色的那一行，我只有一个循环。这个代码会有一个小问题，就是在等待消息有值的时候，锁会一直被占用。

So now. And this mutex is used to protect the access to message. So you have have the writer,. Who wants to send a message,. For that he has to take the lock,. But the sender cannot. Because the lock is taken by the reader. The receiver. Okay? So if you want to make this code correct, you have to release the lock.
现在，这个互斥锁用于保护对消息的访问。写入者想要发送消息时，必须先获取锁，但发送者无法获取锁，因为锁已经被接收者占用。如果你想让这段代码正确运行，就必须释放锁。

And reacquire it just behind. This gives a chance for the writer to acquire the lock. Here I could write the code without taking a lock at the writer side. But imagine that you have something that has structure that is slightly more complex with two integers. One that gives the size of the message and the other one gives the message.
然后在后面重新获取它。这给了写入者获取锁的机会。在这里，我可以在写入端不加锁的情况下编写代码。但假设你有一个结构稍微复杂一些的东西，包含两个整数：一个表示消息的大小，另一个表示消息内容。

You have two writes so you need a lock to be atomic. Okay? Okay, this code is correct. You agree? Yes. At this time. But this code is totally stupid. Because I will burn my CPU for nothing. My CPU will loop for hours waiting for a message to arrive, and okay, yes, I will consume electricity for nothing.
你有两个写操作，所以需要一个锁来保证原子性。明白吗？好的，这段代码是正确的，你同意吗？是的，目前是这样。但这段代码完全愚蠢，因为我会白白浪费CPU资源。我的CPU会循环运行数小时等待消息到来，没错，我会无谓地消耗电力。

During that time, it's probably more interestinging to execute my Fortnite instead of having it freeze the. Because of the lock taken somewhere. I want to save energy. Okay, so for that, we have the this read code function.tion. This one is really for the moment... I remove the writer. Don't wait.its Just send0 the processor
在那段时间里，运行我的《堡垒之夜》可能更有趣，而不是让它卡住，因为某处被锁住了。我想节省能源。好的，为此，我们有这个读取代码功能。这个功能目前还在开发中……我移除了写入器，不要等待，直接发送给处理器。

Just send the processor please suspend me. I don't want to be scheduled anymore. Forget me for the moment. And you will give it an argument which is the variable the condition. And when you create your message in thread one, you will t. The system if you have a thread that is wa waititing for an event on the condition, please wake it up. So code signal...
请将处理器发送过来，暂停我的账号。我不想再被安排时间。暂时忘记我。你需要给它一个参数，即变量条件。当你在线程一中创建消息时，你会通知系统，如果有线程在该条件上等待事件，请唤醒它。代码信号……

With the same condition. And this will tell Linux please wake me up. Okay? They are independ independent. You have the variable condition, just I sleep, please wake me up later, and you have the lock. But this pattern of code is so common that the API includes it by default. Basically, when you want to signal something, you have to take a lock, modify the state.
在相同的条件下，这会告诉 Linux 请唤醒我。它们是独立的。你有条件变量，我只是睡觉，请稍后唤醒我，同时你还有锁。但这种代码模式非常常见，因此 API 默认包含了它。基本上，当你想发出信号时，你必须先获取锁，然后修改状态。

Signal the completion of the job, and unlock. Here when you use the. State. You will have this pattern all the time. You are waiting for the state to reach a value, and you have a message, I reach 100 users, my. Barrier is yes, every all the threads have reached my barrier, whatever. So I'm waiting for something, and I want to sleep, but in in the meantime I have to release the lock because the thread that modified the state has to take the lock to access the state.
发出任务完成的信号并解锁。当你使用状态时，你会一直遇到这种模式：你在等待状态达到某个值，同时你有一个消息，比如“我达到了100个用户”，或者“我的屏障是的，所有线程都已到达我的屏障”，等等。所以你在等待某些东西，并且想要休眠，但与此同时你必须释放锁，因为修改状态的线程必须获取锁才能访问状态。

Okay? So this pattern is so common that. Releasing and acquiring the lock are included directly in this read code brain. So this read code brain has a second parameter which is a mutex, and before sleeping the mutex is released, and after sleeping when we are woken up up, the lock is reacquired. It It's's just the reason why we have this mutex in this API is just that it's so common that we need it.
好的？这个模式非常常见，以至于释放和获取锁直接包含在这个读取代码块中。这个读取代码块有第二个参数是互斥锁，在休眠之前会释放互斥锁，休眠结束被唤醒后会重新获取锁。我们在这个API中使用互斥锁的原因就是因为这种需求非常普遍。

There is a second reason... Internally, to implement the variable condition and the signal, you will have to create a link list of waiters. Okay? And this link list of waiter is a shared state. So the main advantage is that with this API, the system, the GDC, or Linux, leverage the fact that a lock is necessarily taken around.
还有第二个原因……在内部，为了实现变量条件和信号，你必须创建一个等待者的链表。明白吗？而这个等待者链表是一个共享状态。因此，使用这个API的主要优势在于，系统、GDC或Linux能够利用锁必然被持有这一事实。

So we know that we don't have to synchronize to access the queue of waiters, because the lock was taken we have have to to release it. Okay? So it's pragmatic API. For two reasons. For the system developer, and for the user, because anyway they will have have to unlock to release the l lockock while you wait.
所以我们知道访问等待队列时不需要同步，因为锁已经被获取，我们必须释放它。明白吗？所以这是一个务实的API，有两个原因：一是为了系统开发者，二是为了用户，因为无论如何他们在等待时都必须解锁以释放锁。

And if you don't do it, you will have deadlocks. Not really a deadlock., but Oh, it's a kind of deadl. No question? So I. Do have an interface. A monitor. You. All All. So thread will wa wait for a condition to become true; the condition is not specified. It's up up to the developer to define it. Whenat I put in my while while and whenat I modify here for the signal, it's up to the developer. The condition is just the common identifier you know which threads I have have to wake up.
如果你不这样做，就会出现死锁。其实不完全是死锁，但有点类似死锁。没问题吧？所以我确实有一个接口，一个监视器。所有线程都会等待某个条件变为真；这个条件没有具体规定，由开发者来定义。当我在while循环中设置条件，或者在这里修改以发送信号时，这都取决于开发者。条件只是一个通用的标识符，用来确定哪些线程需要被唤醒。

Just a small point, yes, this condition could be just a number. One, two, three,e, four four, five. Not very important. It's just an agreement between the waiter and the thread that wake up the other one. And it's very funny to see in a Unix version 6, the code that fails to back from the 70s, that the variable condition that is used internally inside the Unix code is just it's a pointer, but never the reference. It's just a number.
只是一个小问题，是的，这个条件可以只是一个数字。一、二、三、四、五。不是很重要。这只是服务员和线程之间的一个约定，用来唤醒另一个线程。在Unix第六版中看到这段代码非常有趣，这段代码从70年代沿用下来，内部使用的条件变量只是一个指针，而不是引用，它只是一个数字。

And only the number matters. It's a add not at that time link list or stuff like that. They just add the condition which is an identifier of what you are waiting for. So it's funny.ny. Very cool code if youou want to readad an amazing code.od Take the codeode of Unix version 6. You will love it. But just in in terms of of typing,ing, it's quite str strange sometimes.
只有数字才重要。这不是当时的链表之类的东西。他们只是添加了一个条件，这个条件是你正在等待的标识符。所以这很有趣。非常酷的代码，如果你想读一段惊人的代码，可以看看 Unix 第六版的代码，你会喜欢的。但仅就打字来说，有时会觉得相当奇怪。

You know that the C language has was designed to implement the first version of Unix. So the language was not very major at that time. You cannot say that the C language is very major today. Okay. So you have three functions for this interface. You have code wait, code wait will unlock the mutex, wait.
你知道C语言是为实现第一个版本的Unix而设计的。所以当时这种语言并不算非常重要。你也不能说C语言今天非常重要。好的。这个接口有三个函数。你有code_wait，code_wait会解锁互斥锁，然后等待。

For an event, so the thread will go to sleep, and as soon as the thread is woken up, it will reacquire the mutex. And then you have two ways of waking up the other threads. Don't signal me means please wait one threadad that is waiting on the condition, and broadcast means wait wake up all the threads that are waiting on the condition.
对于一个事件，线程将进入休眠状态，一旦线程被唤醒，它将重新获取互斥锁。然后，有两种方式可以唤醒其他线程。signal 表示唤醒一个正在等待该条件的线程，而 broadcast 表示唤醒所有正在等待该条件的线程。

If you have multiple threads that are waiting. So if you want to implement a barrier to you know what is a barrier, you have just a number n that you have to reach. Ever Everybody sleeps up to reaching the value n. So you will end up with n minus one threads that are sleeping when the last will arrive. It has to wake up everybody. So in this this case, we use this reread code broadcast.
如果你有多个线程在等待，并且想要实现一个屏障（barrier），你需要设定一个数字 n，所有线程必须达到这个数字。每个线程都会一直等待，直到达到值 n。因此，当最后一个线程到达时，其他 n-1 个线程都处于等待状态。此时，最后一个线程必须唤醒所有线程。在这种情况下，我们使用 reread 代码中的广播（broadcast）操作。

To wake up all all the threads that were waiting. When wee. A web server, we will use signal you will have one thread that will waitit for the incoming connection, a pool of threads to do the job. You just have to wait up one of the threads to tell okay, I have some job for you, please process the request.
唤醒所有正在等待的线程。当我们作为一个网络服务器时，我们会使用信号机制。你会有一个线程等待传入的连接，以及一个线程池来处理任务。你只需唤醒其中一个线程，告诉它“好了，我有任务给你，请处理这个请求”。

So signal is enough. That's why you have the pool. In Java, you have exactly the same language construcctt. With wait... Wake up. I think. I'm not very sure. I haven't used Java for 10 years. I realize. My initial specialty is to write Java virtual machines. So it's a bit strange to have forgotten totally this language.
所以信号就足够了。这就是为什么你有线程池。在Java中，你有完全相同的语言结构，使用wait... wake up。我想是这样，但我不太确定。我已经有十年没用Java了。我意识到，我最初的专长是编写Java虚拟机，所以完全忘记这门语言有点奇怪。

I'm still go cing to Java vir virtual machines, but I don't care about the language. Okay. Okay, you know everything. So ye. A lab that is not very complex. For the students, that are used to. Implementlementing the. Concurrent applications. You will probably be able to implement the lab in two, three hours.
我仍然会使用Java虚拟机，但我并不在意具体的编程语言。好的，你已经了解了一切。所以，这是一个对习惯实现并发应用程序的学生来说不太复杂的实验。你们大概可以在两到三个小时内完成这个实验。

For the students that discover this API, you will spendend some time. So I. Can find the lab here. Online. I suggest we do the break in half an hour. It's okay for you, or we can do it now and restart at at half past 1 and. I need more than one hour to it. It It's the most important moment of my day.
对于发现这个API的学生们，你们会花一些时间。我可以在这里找到实验的在线版本。我建议我们半小时后休息，这样你们觉得可以吗？或者我们现在休息，1点半再开始。我需要超过一个小时来完成。这是我一天中最重要的时刻。

I'm saying that I love coding, yes,es, but but I love getting distracted. Okay, no, you have the lab here. Yes, something important. You have solutions for almost all the lab labs. And you can click and you will see the solution. Don't do that because it's totally useless. It takes some time to try ale.
我想说我喜欢编程，是的，但我也喜欢分心。好了，不，你这里有实验室，是的，有些重要的东西。你几乎有所有实验的解决方案，你可以点击查看答案。但不要那样做，因为那完全没用。尝试一下需要一些时间。

Something important. For, I guessess, that as usual, some of the students arrive in Master 2 in CA,, yes. And some of you don't have a lot of background in computer science. There are programs. If it's your case, don't worry.. You can spend all the course doing this lab and not the other. And you will val validate the module.
重要的事情。我猜，像往常一样，有些学生进入计算机应用硕士二年级时，确实有些同学在计算机科学方面的基础不太扎实。如果是这种情况，不用担心。你可以整个课程都专注于做这个实验，而不做其他实验。这样你也能通过该模块的考核。

To reach 10 at this course, you just just have to master this lab. Slightly more. You will end up with 7 or 8. Okay? You start fighting after 10 points. So to reach 10 points, you have to master this lab. And the concepts and to go go from 10 to 20, it's the work. And to go from 18 to 200, it's very, very fun. So don't worry if you are good at programming. You will have fun doing the data.
要在这门课程中达到10分，你只需要掌握这个实验。稍微多学一点，你最终会得到7或8分。明白吗？你在达到10分后才开始真正竞争。所以，要达到10分，你必须掌握这个实验和相关概念。然后，从10分提升到20分，需要付出努力；而从18分提升到200分，则非常有趣。所以，如果你擅长编程，不用担心，你会在处理数据时玩得很开心。

But it's's just just because we have a huge heterogeneity in the book, that I had to find a solution. So don't worry if you are really struggling with this lab, spend more than one week on it. Ask me questions. It It's not a big deal if you don't try the other labs. Ok Okay? And let's go. For the lab, you need a computer, GCC, that's all.
但正因为书中内容差异很大，我才不得不找到解决办法。所以，如果你在这个实验中真的很挣扎，不要担心，可以花超过一周的时间来完成。有问题随时问我。如果你没有尝试其他实验也没关系。好吗？我们开始吧。做这个实验你只需要一台电脑和GCC编译器，就这些。

I If you don't have if you only have Windows, install WSL, plee. Don't use I don't know if GCC is provided by Windows, but Ie. Used Windows for several years. Okay.ay, We do the break We do the break now. Yes, something important. For the lab, for the lecture, you are free to turn the lecture, the lab, do what you want in your life. You will be working in companies in three months. So I will not take it a tendence or whatever.er.
如果你只有Windows系统，请安装WSL。请不要使用……我不知道Windows是否自带GCC，但我用了好几年Windows。好了，我们现在休息一下。是的，有件重要的事。关于实验和讲座，你可以自由安排，做你想做的事情。三个月后你们就要去公司工作了，所以我不会考勤或者其他什么的。

I know that my children will hate that., taking a tendence They are hating going in class. For the lab, you can do them by yourself at hom homee, with friends. Coming here is not necessary. You are very free. And if you for the students that have courses duringing the the afternoon of the course, there is no problem.
我知道我的孩子们会讨厌那样，上课他们越来越不喜欢了。实验可以自己在家或者和朋友一起做，不必非得来这里。你们非常自由。如果学生下午有课程，也没有问题。

And And I bring you back at half past 1. I guess something very important. For many students, you are not discovering anything, so it looks very pretty simple. Don't imagine that everything will be at this level for the the remaining weeks. I will increase the level step by step. 他理解有人喜欢在家家里 Nothing on that.