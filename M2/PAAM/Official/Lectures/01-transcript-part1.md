NonNon francophone. And that's why I will present my course, my lectectures in English. So, don't worry if your English is not totally fluent; I have a strong French accent, it's very easy to understand what I say. Okay, so—o, so, Like that. And when you want to ask questions, youou just raise your hand, and you can ask the question in French or in English, not another language, because I only speak French and English, basically.
我不是法語系人士，所以我將用英語來授課。因此，即使你的英語不是非常流利，也不用擔心；我有濃重的法國口音，但我說的話很容易理解。好了，就這樣。當你想提問時，只要舉手，你可以用法語或英語提問，但不能用其他語言，因為我基本上只會說法語和英語。

Uh, what are you doing? English. Hi. Okay, so first of all, I have a beautiful web page that you can easilyily find on the internet, I. Imagine that you received for the CHES students, that you received a mail from the administration telling you— giving you the schedule for the classes. Yes? Okay. In this mail, probably there were— there was a link, there were a link., I'm not sure.
嗯，你在做什麼？英文。嗨。好，首先，我有一個漂亮的網頁，你可以輕鬆地在網路上找到。我想像你收到了一封來自CHES學生的郵件，這封郵件是行政部門寄來的，告訴你課程的時間表。對嗎？好。在這封郵件裡，可能有一個連結，我不太確定。

Anyway, if you want to find the course, it's easy on Google, you type "CSC 5101," it's the official name of the course for IP Paris, while the name for you is is P-PA. P-A-A-M. Okay. I don't know if we can still find it under the name PA. No. So let's try CSC 5101, and then you ar arrive here and you have everything that you need for the course.
無論如何，如果你想找到這門課程，在 Google 上很容易，只要輸入「CSC 5101」，這是 IP Paris 課程的正式名稱，而你那邊的名稱是 P-PA.P-A-A-M。好吧，我不確定我們是否還能用 PA 這個名稱找到它。不行的話，就試試 CSC 5101，然後你會到達這裡，裡面有你需要的所有課程資料。

You have the lecture, the lectures, you have the lab, you have— I will not present that, but if youou ne need some courses about C programming, you can catch up up with the rest of the class, like that. You have everything. You also have a lot of past examss. iff you need— if you want to tryy it yourself.
你有講座，有多場講座，也有實驗課程。我不會在這裡介紹，但如果你需要一些關於C語言的課程，你可以跟上班上的進度。你擁有一切資源，還有許多過去的考古題。如果你想自己嘗試的話。

Can be good. Okay, so I will quickly introduce that. So my goal in this course is to introduce you to the. Multicore programming, somehow. And what I'm interested in is to show you how we can efficiently use a modern computer with many cores distributed memory complete. Networks, complex caches, etc., etc.
可以的。好，我將快速介紹一下。這門課的目標是向你們介紹多核心程式設計。我的興趣在於展示如何有效利用現代擁有多核心、分散式記憶體、複雜網路和快取等特性的電腦。

I'm really interested in optimizing performance. In this course. So what we will do is not like classical HBC course where you study a new programming language or a new new programming abstraction, like OpenMP, NPI, etc. I suppose that you have courses for that. Here, what we will do is that we will start from nothing.
我對優化效能非常感興趣。在這門課程中，我們不會像傳統的高效能計算課程那樣學習新的程式語言或新的程式抽象，例如 OpenMP、MPI 等。我假設你們已有相關課程。在這裡，我們將從零開始。

We will just be at the C level, with the machine, the hardware, and we will show how we can optimize performance and make the best of our beautiful multicores. Maybe I have to say something. Yes. So just a few words. I suppose that you knowow how to code in C. All of you. So I'm totally fluent in C. I probably— I— my first— my native language is C before French and English.
我們將只使用 C 語言，搭配機器和硬體，並展示如何優化效能，充分發揮我們美麗的多核心處理器的效能。也許我得說幾句話。是的，就幾句話。我想你們都會用 C 語言編程。全部都會。所以我對 C 語言非常流利。可以說——我的第一語言是 C，甚至比法語和英語還要早。

So it means that I think in C. C, when When I see a codode in's somebadody is's bra When I see a code in somebody's brain for me, and I suppose that this will be the same thing for you. So don't worry if you are not a guru in C, you just need to know what are pointers, how you write C code, and have some basic— bas basic knowledge.
所以我的意思是，我在學習 C 語言時，當我看到別人腦海中的程式碼時，我會理解它。我想你也會有同樣的感覺。所以不用擔心自己不是 C 語言的大師，你只需要知道什麼是指標，如何撰寫 C 程式碼，並且具備一些基本的基礎知識。

I suppose that is the case for everybody. Almost. And if it's not the case, just tell me when we will do the lab. We will discussuss that, and how you can catch up. Okay. So I'm interested in multicore architectures. So multicore architectures are today everywhere. What we need is just a computer where, instead of having just a single computing unit, you have many computing units.
我想這幾乎適用於每個人。如果不是這樣，請告訴我我們什麼時候要做實驗。我們會討論這個問題，以及你如何趕上進度。好的。我對多核心架構很感興趣。如今，多核心架構無處不在。我們需要的只是這樣一台電腦，不是只有單一的運算單元，而是擁有多個運算單元。

So youou will will find them in large data centers, in. Any data center you will find multicores where you have 32 to 128 cores, you can even buy a machine with 512 cores if if you want.ant, It's funny. It's huge. It's very funny. But you can also find multicores on your smartphone. You have multicores everywhere. On my smartphone I have 8 cores.
所以你會在大型資料中心找到它們。在任何資料中心，你都會看到多核心處理器，核心數量從32到128不等，如果你願意，甚至可以購買擁有512核心的機器。這很有趣，非常龐大，也很有趣。但你也可以在你的智慧型手機上找到多核心處理器，到處都有多核心。在我的智慧型手機上，我有8個核心。

And I have other computing units for AI stuff, LLM, inference, and stuff like that. So there are absolutely everywhere. We will see why. Because it's quite strange to have multices.es. It's not so intuitive. During the course, and my goal will be be to to explain how we can program them at low level.
我還有其他用於人工智慧、大型語言模型（LLM）、推理等工作的計算單元。這些計算單元幾乎無處不在。我們將會了解原因，因為擁有多個計算單元是相當奇特的，並不那麼直觀。在課程中，我的目標是解釋如何在低階層次上對它們進行程式設計。

Okay? Here youou have have a be beautiful picture of my first multicore machine. That I bought— ooh, 18 years ago. It's Aria, and you will have the pleasure to use it, because the machine is is still running, 18 years old machine. Maintaining it is not so easy. The PCI Express bus is totally outdated, so modern Linux are difficult to run.
好嗎？這裡有一張我第一台多核心電腦的漂亮照片。我是在18年前買的，它叫Aria，你將有機會使用它，因為這台18歲的電腦仍然在運行。維護它並不容易，PCI Express匯流排已經完全過時，因此現代的Linux系統很難在上面運行。

But this machine is is absolutely beautiful. You can see what is re really a multicore. Here you have multiple sockets. You have 4 sockets. Inside— sockets is just the chip that you buy at the supermarket. Amazon today. Inside each socket you will have 12 cores. So it means that in total I have 48 cores in this machine.
但這台機器真的是非常漂亮。你可以看到它真的是一個多核心系統。這裡有多個插槽，你有4個插槽。插槽裡面就是你在超市或亞馬遜今天買的晶片。在每個插槽裡，你會有12個核心。所以這意味著這台機器總共有48個核心。

And then you can see that you have man manyy, many memory banks everywhere. And in the middle you cannot see it, but you have a network that interconnects all this world world. So it means that when the memory is very far, you have what we call non-uniform memory access effects, so it's difficult because you will not have an homogeneous latency when you access memory.
然後你可以看到，到處都有許多記憶體區塊。在中間你看不到，但有一個網路將整個系統互相連接。這表示當記憶體距離很遠時，會出現所謂的非一致性記憶體存取效應，因此存取記憶體時的延遲不會是均勻的，這會帶來困難。

And behind this machine you also have all the devices. The hard drives, the network cards, etc., etc. And they are spread around, so you have a network to interact with them, and basically it's a full distributed system. But at the scale of a small machine, a small machine like that. Slightly larger than my sme.
在這台機器的背後，你還有所有的裝置，包括硬碟、網路卡等等。這些裝置分散在各處，因此你需要一個網路來與它們互動，基本上這是一個完整的分散式系統。但規模僅限於一台小型機器，一台比我的小型機器稍微大一點的機器。

So it's a very— it's very interesting for you. So for the PDS students: of course you're interested in understanding how to code these machines, because it's really the very subject of PDS. How we program large infrastructures so at the scale of a single machine, which is already large, or at the scale of a data center, or the geo-distributed scale.
这对你们来说非常有趣。对于PDS的学生来说，当然你们会对如何编程这些机器感兴趣，因为这正是PDS的核心内容。我们如何编程大型基础设施，无论是在单台已经很大的机器上，还是在数据中心规模，甚至是地理分布式的规模上。

Between at the world scale. Bonj. For the CHPS students, for some of you you will be very interested in this course. Because you will want to optimize your code as much as you want, but many of you will just. Program with higher level APPIs. So you will never touch the hardware at this level. But I think that it's interesting for you because you will better understand what is really a large multicore, and even if you use— I don't know— Python?
在全球范围内。大家好。对于CHPS的学生来说，你们中的一些人会对这门课程非常感兴趣。因为你们会想尽可能地优化代码，但你们中的许多人只是使用更高级的API进行编程，所以你们可能永远不会接触到硬件的这个层面。但我认为这对你们来说很有趣，因为你们将更好地理解什么是真正的大型多核处理器，即使你们使用的是——我不知道——Python？

You will all use Python in the end. And you use Python to start big inference or whatever, you will have better idea of what is inside the machine and where are your but bottlenecks, even if you don't change program really at at this level. So it can give you some—— a lot of ideas. Okay, so the organization. I think that we have about 5 weeks now.
你们最终都会使用 Python。无论是用 Python 来启动大型推理还是其他操作，你都会更清楚机器内部的情况以及你的瓶颈所在，即使你在这个层面上并没有真正修改程序。所以它能给你很多启发。好了，关于组织安排，我想我们现在大约有五周时间。

Yes. One we week was cut last year. So for the CHPS students you will have 5 weeks, maybe for the PDS students I will keep my 6 weeks. Because I don't want to remove one of my course. Simply. But I will have to schedule it it. But for the CHPS students you have 5 weeks, and each week what we will do is that we will do between 1 to 3 hours of theory, some of my courseses will will be very long, it will be tired, and you will hate me.
是的。去年减少了一周。所以对于CHPS的学生来说，你们将有5周的时间，而对于PDS的学生，我可能会保持6周。因为我不想删掉我的任何一门课程。很简单，但我需要安排好时间。对于CHPS的学生来说，你们有5周，每周我们会安排1到3小时的理论课程。我的一些课程会比较长，可能会让你们感到疲惫，甚至会讨厌我。

You will dream about lunch. At 12. But I I have to give you some some background. I have to explain things. My slides are not self-contained. Which is rare. And then you will have to do a lot of practice. So the practice for the lab, you will code. You will code a lot. And that's all. I suppose that you will work for 1 hour each week.
你会梦到午餐，时间是12点。但我必须给你一些背景介绍，解释一些事情。我的幻灯片内容不够完整，这很少见。然后你需要做大量练习。实验的练习部分，你将进行大量编码。就这些。我估计你每周会花大约一小时来完成。

Alone. Basically for the students who didn't finish their. Lab, I suppose that you will finish them at home. But there will not be graded. I'm totally lazy. And I don't see the point of grading labs for master's students when a ChatGPT is so go. In the end you can always give my subject to ChatGPT. ChatGPT will g give you the code, and I will grade ChatGPT. It's totally us.
独自完成。基本上是针对那些没有完成实验的学生，我想你们会在家里完成，但不会被评分。我非常懒，而且我觉得给硕士生的实验打分没什么意义，尤其是现在ChatGPT这么厉害。最后，你们完全可以把我的课题交给ChatGPT，ChatGPT会给你代码，而我只需给ChatGPT评分。这完全没问题。

I think. And it's unfair. Basically. Grading the labs. Today. Because students that will cheat will have perfect code, they will have 20 out of 20, while the pooror students that will really do the job and work will not have 20, because they are not machines. And they will make mistakes. So for this reason I decided to never grade you.
我认为这很不公平，尤其是今天给实验打分。因为作弊的学生会有完美的代码，能拿到满分20分，而那些真正努力完成作业的学生却拿不到满分，因为他们不是机器，会犯错误。所以基于这个原因，我决定永远不给你们打分。

For the lab. So you are free. To not work at all if you want. Just you will fail at the exam. In the end. Each week we will study a subject. So I will have to remove one of them for the CHPS students, this will be prob probably this one, the non-uniform memory architectures. Which is not the most important.
关于实验室的事情，所以你可以自由选择是否工作。如果你选择不做，最终考试时你会不及格。每周我们都会学习一个主题，因此我必须为CHPS的学生删减其中一个主题，可能会删减非统一内存架构这一部分，因为它不是最重要的内容。

This first week what you will will see: I will recall you what are threads and synchronization, basic synchronizations. It's just a way to be sure that all the students have the same background in the the course. Most of you already know what is this threading text block. But it's better to recall you how I see that that.
在第一周，你将看到的是：我会回顾线程和同步的基本概念。这只是为了确保所有学生在课程中有相同的基础。你们大多数人已经知道什么是线程块，但我还是想回顾一下我对它的理解。

And I will also introduce my vocabulary. Because the way we name the threads, the process, and all the system elements that we use use, is very precise. And two And two teachers will have two ways of explaining that, they will use two different vocabularies. And I w wantant just to make surere that you will all use the same vocabulary.
我还会介绍我的词汇表。因为我们给线程、进程以及所有系统元素命名的方式非常精准。不同的两位老师会用两种不同的词汇来解释这些内容。我只是想确保你们都使用相同的词汇。

Then during the second course we will study how we design log algorithms. Which is the basic tool that that you use to synchronize two. Threads. So instead of using logs here, we will see how we can design them. And one of the problems that we will face is that to design a log we need a log. Because at some point we need to share variable, we have to change its state.
在第二部分课程中，我们将学习如何设计日志算法。日志算法是用于同步两个线程的基本工具。我们不会直接使用现成的日志，而是会探讨如何设计它们。我们面临的一个问题是，设计日志本身就需要日志，因为在某些时候我们需要共享变量并改变其状态。

So we have multiple readers and writers, and how can we handle that without a log? Because we have are creating the log. So we will see how we can do that. We will see 4, 5 algorithms. Then we will dig into what we call log-free algorithms.s, The goal of these algorithms is to remove log. Entirely.
所以我们有多个读者和写者，我们如何在没有日志的情况下处理它？因为我们正在创建日志。接下来我们将看看如何做到这一点。我们将介绍四五种算法，然后深入探讨我们所称的无日志算法。这些算法的目标是完全去除日志。

So basically we will design that data structures that remain correct even if you don't take logs. So it's a well-known subject that is well studied for 20 years. Here what for the students that are taking the course of PET, you will already know PET represents of. You will already know what are non-blocking algorithms.
基本上，我们将设计那些即使不记录日志也能保持正确的数据结构。这是一个已经研究了20年的著名课题。对于正在学习PET课程的学生来说，你们应该已经知道PET代表什么，也应该了解什么是非阻塞算法。

Whatat will be interesting here is that we will practice. We will see exactly how we can code them and make them efficient. So the way I present them is slightly different. I'm not interested at all by the theory. For me an algorithm is correct because it didn't crash. Which is a proof for me. Does That's pretty truuee.? In the reality.
这里有趣的是我们将进行实践。我们会具体看看如何编写代码并使其高效。所以我呈现它们的方式有些不同。我一点也不关心理论。对我来说，一个算法是正确的，因为它没有崩溃。这对我来说就是证明。现实中情况真的是这样吗？

If you run your algorithm on a 48-core machine and it doesn't crash, it means that you crashed the bug does not exist. Or it's so rare that it's an illusion. Then we will change our mind. We will study a w wayay of designing concurrent applications by simplifying a lot the code for the developer. So for that we will introduce what are transactional. What is a transactional memory?
如果你在一台48核的机器上运行你的算法且没有崩溃，这意味着程序中的错误不存在，或者错误非常罕见，以至于几乎可以忽略不计。接下来，我们将改变思路，研究一种通过大幅简化开发者代码来设计并发应用的方法。为此，我们将介绍什么是事务性内存。

And with a transactional memory is just like coding in Python for concurrent applications. You will see how easy it is for the developer. And of course under the hood it means that for the system developer it's way more difficult to make that efficient. So the result is not perfect. Still used a bit, but it's very interesting because it was.
使用事务性内存就像用Python编写并发应用程序一样简单。你会看到这对开发者来说有多么容易。当然，在底层，这意味着系统开发者要使其高效要困难得多。因此，结果并不完美，虽然仍有一些应用，但它非常有趣。

Very Bonj. All the algorithms that were presented introduce to implement transactional memory are. Used in practice, not not really like we will see, but they are still present. We use them a lot, for example, to design the internal structures of databases currently. Where we have transactional memory.
非常好。所有介绍的用于实现事务内存的算法在实践中都有应用，虽然不像我们将要看到的那样广泛，但它们仍然存在。例如，我们现在大量使用它们来设计数据库的内部结构，其中就包含事务内存。

You know that a database is a beautiful system. Where you have have millions of users that that are tr trying to change the data at the same time and you have to synchronize everybody. It's's very diffic. Then we will see how we can manage non-uniform memory architecture. And basicically I will learn my research about this subject.
你知道数据库是一个非常复杂的系统。成千上万的用户同时尝试更改数据，而你必须同步所有人，这非常困难。接下来我们将探讨如何管理非统一内存架构。基本上，我将分享我在这个课题上的研究成果。

I advise I will say 4 or 5 PhD students on this subject. So I have a lot of interesting foundings to present. Findings to present. On the subject. So I will present that only for the PhD students, because I have to kill one of of my course. And then I will introduce what are non-volatile memory which are pretty fun.
我建议在这个主题上有四到五名博士生。因此，我有很多有趣的发现要展示。我将只向博士生展示这些内容，因为我必须取消我的一门课程。然后，我会介绍什么是非易失性存储器，这非常有趣。

A non-volatile memory is just like a memory but when you power off your computer the state is still there. So when you power it on you will exactly retrieve your state. But it's not so so easy to use it. So the technology is. Has been released 7 or 8 years ago by Intel. The discontinued this technology and it's resurrected now with CXL.
非易失性存储器类似于普通存储器，但当你关闭电脑电源时，存储的状态仍然保留。因此，当你重新开机时，可以准确地恢复之前的状态。不过，使用起来并不那么简单。这项技术大约在七八年前由英特尔发布，后来被中止，现在随着CXL技术的出现又得到了复兴。

For 2 years. So it's really som somethething and we we don't know exactly how to efficiently use a non-volatile memory. So it's funny to learn that because it's really on the fence. In term terms of research. Okay, behind each of this course I. Advised in total 15 PhD students. And I will just recap what we did for 20 years instead.
两年来，我们一直在研究这个问题，但我们还不完全清楚如何高效地使用非易失性存储器。学习这一点很有趣，因为在研究领域中，这仍然是一个悬而未决的问题。好了，关于这门课程，我指导了总共15名博士生。接下来，我将简要回顾我们过去20年的工作。

It's really my favorite subject. I just. I don't present what I'm doing inside an operating system. It's very fun also. But when we work at the operating system level what we do is that we apply all this kind of algorithms. Okay, I suppose that you have you know how to code in C. For some of the algorithms I.
这真的是我最喜欢的科目。我只是……我不会展示我在操作系统内部所做的事情。操作系统也非常有趣。但当我们在操作系统层面工作时，我们所做的是应用各种算法。好吧，我假设你们知道如何用C语言编程。对于其中一些算法，我……

Will use tricks in C where I will just access memory without caring about the type. For example, you know that the void star is a pointer to anything it works for me it's an integer. Basically I use the C language as I assembly language. I level assembly language. Not really as a normal language. And in my life I don'tt. see the The types I se see a big bunch of integers.
我会在C语言中使用一些技巧，直接访问内存而不关心类型。例如，你知道void指针是指向任何类型的指针，对我来说它就是一个整数。基本上，我把C语言当作汇编语言来使用，低级汇编语言，而不是真正的高级语言。在我的生活中，我不太关注类型，我看到的只是大量的整数。

And a pointer is an integer like any other integer. I don't see any difference in my mind. So I will help you to understand that. So I suppose that you know what are pointers and that you know the malloc and free functions. And that you are able to go printf I hope. Okay, if you have some background in systems it's better for you. It will be helpful. But it's's not necessary.
指针本质上就是一种整数，和其他整数没有什么区别。我会帮助你理解这一点。我假设你已经知道什么是指针，了解 malloc 和 free 函数，并且能够使用 printf。好的，如果你有一些系统方面的背景知识，那对你会更有帮助，但这并不是必须的。

For the CFPPS students it's the case if you were in master one because you have a course about operating systems for the PTS students there should not be any problem. And for the CHPS students that arrived in master two sometime you don't have any background you will discover. Okay, you really wantant to kn know oh I will grade you. So the only way that I am to grade the students is to use a sheet of paper and a pen.
对于CFPPS的学生来说，如果你们是在硕士一年级，因为你们有一门关于操作系统的课程；对于PTS的学生，应该没有任何问题。至于那些在硕士二年级才入学的CHPS学生，有时你们没有任何相关背景，你们会逐渐发现。好的，你们真的想了解的话，我会给你们打分。所以，我评分的唯一方式就是用一张纸和一支笔。

I don't have any other solutions. So we will have an exam. But very exciting to code in C with a sheet of paper that I don't know how to do better today. All know that. And my goal is to be as fair as possible for you. Because when I was a student I really didn't like when students that were cheating at better grades than mee. so I tried to have the same principle also as a professor and the only solution today is to use a sheet of paper.
我没有其他解决方案，所以我们将进行一次考试。但用一张纸在C语言中编程，虽然我今天还不知道怎样做得更好，这也非常令人兴奋。我知道大家都明白这一点。我的目标是尽可能公平对待大家。因为当我还是学生时，我真的不喜欢那些作弊却比我得更好成绩的同学，所以作为教授，我也尽力遵循同样的原则。今天唯一的解决办法就是使用一张纸。

The more busy price. Yes, you have to code in C. Basically if you give me a code in Python or in ASII or JavaScript I will be be a bit surpred. In Rust I'm unable to read Rust. Please don't tryy to code in Rust. But if you forget the semicolons youou forget the star somewhere etc etc I really don't care. What I'm interested in is the see if y you if you understood the course I know that when you will really be in front of a machine you will use VS Code, Emacs, Vim, whatever also.
越忙价格越高。是的，你必须用C语言编程。基本上，如果你给我一段Python、ASCII或JavaScript代码，我会有点惊讶。至于Rust，我无法阅读Rust代码。请不要尝试用Rust编程。但如果你忘记了分号，或者某处忘记了星号等等，我真的不在意。我关心的是你是否理解了课程内容。我知道当你真正面对一台机器时，你会使用VS Code、Emacs、Vim或其他编辑器。

And you will oh we have 2 minutes. So you will be helped by your code editor to avoid the small mistakes. I'm not a compiler. You are not compilers. So I know that you will forget your star. So you will just have one grade. Not two.o. So Prepare yourself. For the exam. Please. No question about the organization?
你们还有两分钟。代码编辑器会帮助你们避免一些小错误。我不是编译器，你们也不是编译器。我知道你们会忘记星号，所以你们只会得到一个等级，而不是两个。请为考试做好准备。请问关于考试安排有没有问题？

No. 23 data Do Do y you know the date of y the exam? Yes. No. I don't really kn. I think that I have have it. So most of the time what I do is that I do two exams. One for the the CHPS students and another one for the PTS students. Because the schedule is not compatible. So I have to schedule that.
23号数据，你知道考试的日期吗？知道。不，我不太清楚。我想我有考试时间表。大多数时候，我会安排两场考试，一场给CHPS的学生，另一场给PTS的学生，因为时间安排不兼容，所以我必须重新安排时间。

I'm very good at science but in term of administration I'm the worst. Professor of I think. Basically I'm not a professor by the way. I I'm not supposed to teach. I'm only a researcher. But I love teaching. I could do that for free. No. No. Okay, so let's start really the course. I will speak about processes threads and symbolization.
我在科学方面非常擅长，但在行政管理方面是最差的。我想我是教授吧。其实我并不是教授，我不应该教书，我只是一个研究员。但我喜欢教学，我甚至愿意免费教。好了，好了，那我们正式开始课程吧。我将讲解进程、线程和符号化。

And I will define these different elements. I hope that Yes. You can have any printed paper for the for the exam. Just you cannot use the smartphe. Or a computer. It's I have my weapons. Okay, so what is a process for me? A process is a running instance of a program. And a program is classified. Okay? So So you have your file that is stored on your hard drive. It's a file. And at the end of the file you have this .exe when you use windows. And the .nothing when you use Linux.
我将定义这些不同的元素。希望是的。你可以携带任何打印的纸张参加考试，但不能使用智能手机或电脑。这是我的规定。好的，那么什么是进程？进程是程序的一个运行实例。程序是有分类的。你有存储在硬盘上的文件，这就是一个文件。在文件名的末尾，如果你使用的是Windows系统，通常是.exe；如果你使用的是Linux系统，通常没有扩展名。

When you start a program you double click on the on the program the operating system takes the file lo loads it in memory and inside the program you have some code that the processor can execute. The machine code. Okay? And at. The moment where the program is loaded in memory and starts executing it it becomes a process.
当你启动一个程序时，你双击该程序，操作系统会将文件加载到内存中。在程序内部，有一些处理器可以执行的代码，也就是机器码。当程序被加载到内存并开始执行时，它就成为了一个进程。

So why we define there is a separation between process and program is because youou have a state. The file is a read-only element. It never change. So if you write in your source code int x equals 32 in the fileile you will find x equals 32 but it's not it's the reality in the file when you load the file initially x is equals 32 but when the process is running you can execute code that will change your state. You can execute x equals 21.
我们之所以定义进程和程序的区别，是因为进程有状态。文件是只读的元素，它不会改变。所以如果你在源代码中写了 int x = 32，在文件里你会看到 x 等于 32，但这并不代表文件中的真实状态。当你最初加载文件时，x 确实等于 32，但当进程运行时，你可以执行代码来改变状态，比如执行 x = 21。

And you change this state. So there is a difference between a. The read-only program. And the line version of the program that can be quite different. You have memories that is allocated. You have the state of the processor. Where the register where are the values of the registers etc. So when you have a program you can run multiple instances of the same program.
你可以改变这个状态。所以只读程序和可修改版本的程序之间是有区别的，二者可能截然不同。你有分配的内存，有处理器的状态，比如寄存器的位置和寄存器的值等等。因此，当你有一个程序时，可以运行多个该程序的实例。

So why you you may may want to do that for Chrome for example each tab is a process. Independent process. So why we have this design it's a problem of is isolation. When one tab is attacked by a a JavaScript code even if the attacker is able to break the sandbox around the JavaScript runtime you have the process that still protect you. So it means that the attacker can tak takee control of one tab but not all the tabs at the same time.
那么，为什么你可能想这样做呢？以Chrome为例，每个标签页都是一个独立的进程。为什么会有这样的设计呢？这是为了实现隔离。当一个标签页受到JavaScript代码攻击时，即使攻击者能够突破JavaScript运行时的沙箱，进程本身仍然会保护你。这意味着攻击者可能控制一个标签页，但无法同时控制所有标签页。

For that the attacker has to break the boundary of the process itself to take control of Linux the full operating system which is wayay more more difficult. Okay? And. When When you have a large machine and you are all connected to this machine you can have multiple instances of the same program simply because you have multiple users.
为此，攻击者必须突破进程本身的边界，才能控制整个Linux操作系统，这要困难得多。明白了吗？当你拥有一台大型机器，并且所有人都连接到这台机器时，你可以运行同一程序的多个实例，因为有多个用户。

Makes sense. And you can also have a. Several instances of batch becaause y you have multiple terminals that are open. If I show you here I have no it's the same but. Okay you can see that I have multiple version multiple processes batch processes that are running at the same time. Okay? They are just independent.
有道理。你也可以有多个批处理实例，因为你可能打开了多个终端。如果我在这里给你看，虽然是一样的，但你可以看到我有多个版本、多个批处理进程同时运行。它们是相互独立的。

They have their own state just like if they were running alone on the machine. Okay.ay. So the operating system the role of the operating system is very simple. An operating system is in chargege of of managing the life cycle of the process. All the process processes. So the operating system can start and stop a process and.
它们有自己的状态，就好像它们独自运行在机器上一样。好的。所以操作系统的作用非常简单。操作系统负责管理所有进程的生命周期。操作系统可以启动和停止进程。

Not more basically. A bit more. Sometimes you want to have processes that communicate if you take your beautiful smartphone you have your screen saving stuff what is the name of screen saver? I was Alwayss on on the the screen. Horizontal scen. Alwayss on on the scen. Always on the screen I don't know..
不完全是这样。稍微多一点。有时候你希望有一些进程能够相互通信。如果你拿起你漂亮的智能手机，你会看到屏幕保护程序，那个屏幕保护程序叫什么名字？我记得屏幕一直是开启的，横屏显示。屏幕一直是开启的，我不太确定具体叫什么。

I don't have the exactly the same picture here and when I unblock it. I don't know. that re wasason my I ignore that. So it's not very important. But if you want on my smartphone I have have applications I have for example WhatsApp to discuss with my children and I have notification on the top. So for that I have two processes. One is in charge of displaying the notification and the other one is in in charge of communicating with the WhatsApp server.
我这里没有完全相同的图片，当我解锁时，我也不确定原因，所以我忽略了它，这并不是很重要。但如果你想知道，在我的智能手机上，我有一些应用程序，比如用来和我的孩子们聊天的WhatsApp，屏幕顶部会显示通知。为此，我有两个进程：一个负责显示通知，另一个负责与WhatsApp服务器通信。

So basically they need a way to communicate. And when we have processes they in always some of them are totally independent if you start a Fortnite and Chrome they have no reason to communicate. Why not? It may happen because youou have to use web service. But there is a reason but you have many processes that need communication channels.
基本上，他们需要一种沟通的方式。当我们有多个进程时，其中一些进程是完全独立的，比如启动 Fortnite 和 Chrome，它们之间没有必要进行通信。为什么呢？可能会因为需要使用网络服务而通信，但这只是其中一种情况。实际上，有许多进程是需要通信通道的。

And the your operating system will also implement some communication primitives to allow the processes to communicate together. So you in theory you know them you have signals signals is very e easy it's a way to stop a program when it misbehaves. Or to reload your configuration with a minus patch etc.
你的操作系统还会实现一些通信原语，以允许进程之间进行通信。理论上你应该了解它们，信号（signals）非常简单，它是一种在程序出现异常时停止程序的方法，或者用来重新加载配置文件等。

You have the types ls type graph etc. You have two processes and you send send the output of one process to the other. Two processes. You have the sockets sockets is just a communication channel between two processes that that are located on two machines. You have local unique socket that is just a very old way of it.
你有类型，比如 ls 类型图等。你有两个进程，并且将一个进程的输出发送给另一个进程。两个进程之间。你有套接字，套接字只是两个位于不同机器上的进程之间的通信通道。你还有本地唯一套接字，这只是一种非常古老的方式。

A. Uselseless attempt to unify typeipe and sockets. Nobody use using unique sockets. But you use network sockets a lot. Just to connect to machine. You You know what are sockets. It still exists. Okay. So you manage the life cycle. You have some communication channels. And the last main role of the system is to isolate the processes just to protect yourself.
A. 无用的尝试去统一打印机类型和套接字。没有人使用独特的套接字，但你经常使用网络套接字，仅仅是为了连接机器。你知道什么是套接字，它依然存在。好的，所以你管理它们的生命周期，拥有一些通信通道。系统的最后一个主要作用是隔离进程，以保护自身安全。

Because you may have multiple users and some some of your processes can be connected to the outside world to the internet be under attack and you don't want to for example that allows you to become administrator of your machine to be in the same protection domain than your Chrome. Of course an. Operating system is the kernel of operating system is slightly larger because it also expose the hardware through well defined API.
因为你可能有多个用户，并且你的一些进程可能连接到外部互联网，面临攻击风险。你不希望例如允许你成为计算机管理员的进程与Chrome处于同一保护域中。当然，操作系统的内核稍微复杂一些，因为它还通过定义良好的API暴露硬件。

But the hardware you can see it as a way not the hardware but you can see the interfaces of the operating system as ways to to communicate when you write to a file you communicate with the world somehow. By making something visible to everybody in the directory. It's a way of communication. But very different.
但硬件本身你可以不把它看作硬件，而是把操作系统的接口看作一种交流的方式。当你写入一个文件时，你以某种方式与外界进行沟通，通过在目录中让某些东西对所有人可见。这是一种交流方式，但非常不同。

So a process roughly it virtualizes it virtualizes a complete machine. When a process runs it has the illusion of being alone and have communication channels with the world. Sockets etc. Okay? And the operating system will just hide the fact that the process is not alone. Basically you write a main function and you will feel alone there is no other process around except if you explicitly create a communication channel.
一个进程大致上实现了对一台完整机器的虚拟化。当一个进程运行时，它会有一种独自运行的错觉，并且拥有与外界的通信通道，比如套接字等。操作系统会隐藏进程并非独自运行的事实。基本上，你编写一个主函数时，会感觉自己是唯一的进程，除非你显式地创建了通信通道。

Okay. So it's the first step of virtualization. That's why we say that containers and virtual machines are virtualization technologies. The wording is not very good but somehow it's not totally false. Okay. I want to introduce new know what are the strengths. So for that I have to recall what is a call frame.
好的。这是虚拟化的第一步。这就是为什么我们说容器和虚拟机都是虚拟化技术。表述不是很准确，但某种程度上并非完全错误。好的，我想介绍新的内容，了解它们的优势。为此，我需要回顾一下什么是调用帧。

So when you load your process in memory its. You load. The global variables you load the code and then you start the execution. And when you want to execute your process you have to execute functions. And a function may have what we call local variables. A local variable is just a variable that exists while the function executes.
当你将进程加载到内存中时，会加载全局变量和代码，然后开始执行。当你想执行进程时，需要执行函数。函数可能包含我们称之为局部变量的变量。局部变量是在函数执行期间存在的变量。

Okay? So when I start main my main has for example two two variables. Rc rg and I will have to allocate some memory for them. And then in main I will code the add function and add as three variables x y z and I have to allocate them. Basically imagine that you call malloc each time you call a function.
好的？所以当我开始主函数时，比如说有两个变量 Rc 和 rg，我需要为它们分配一些内存。然后在主函数中，我会编写一个加法函数，参数有三个变量 x、y、z，我也需要为它们分配内存。基本上，可以想象每次调用一个函数时都会调用 malloc 来分配内存。

It's not very more difficult. Okay. So when we do that it's just to save memory. Because it's not that useless to have x y and z that are reserved in memory when add is not executing. Okay? And when you have a function you don't know how many times it will be called on the dynamic end. You can have weaker seed ce.
这并不难。好的，所以我们这样做只是为了节省内存。因为当 add 函数没有执行时，保留 x、y 和 z 在内存中并没有什么用处。明白吗？而且当你有一个函数时，你不知道它在运行时会被调用多少次。你可以使用更弱的种子。

And when you have a weaker seed code with x y and z how many xs y versions of x y and z you would have to preallocate. You cannot guess that just just by looking at the ce. So we allocate this memory dynamically. And it's wh what we call a call frame. A call frame is just a a memory region where you have your local variables and a way to return from the function.
当你有一个较弱的种子代码包含 x、y 和 z 时，你需要预先分配多少个 x、y 和 z 的版本是无法仅凭代码片段来猜测的。因此，我们动态分配这部分内存。这就是我们所说的调用帧。调用帧只是一个内存区域，用来存放局部变量以及函数返回的相关信息。

Okay? So you end up with a kind of link list of call frames when you call functions. So you have this beautiful example you have main that call add and I I have my add function here with my three local variables a parameter is just a special kind of local variable that is fed when you enter the function.
好的？所以当你调用函数时，会形成一种调用帧的链表。举个很好的例子，你有一个 main 函数调用 add 函数，而我的 add 函数这里有三个局部变量，参数只是一种特殊的局部变量，在进入函数时被赋值。

And I have my state. So at this step exactly I I have my add function I'm executing the code of add at this place and I have my state with one two three for x y z. And main you have the rc rg you don't know exactly what it is it exists. Okay?? There is something very important this small arrow when.
我有我的状态。所以在这一步，我正在执行 add 函数的代码，我的状态是包含 x、y、z 的一二三。至于 main，你有 rc 和 rg，但你并不确切知道它们是什么，只知道它们存在。好的？这里有一个非常重要的点，就是这个小箭头。

You come back back from you execute the code of add so it means that the processor has an internal register that is called the program counter or the generic name RIP for an Intel machine and your program counterunter is exactly at this place in the ce. So here you have the machine instructions the machine instructions are just like code except that they are very elementary instructions you have add null sub call which.
你执行完加法指令后返回，这意味着处理器有一个内部寄存器，称为程序计数器，或者在英特尔机器上通用名称为RIP，而你的程序计数器正好位于这个位置。所以这里有机器指令，机器指令就像代码，只不过它们是非常基础的指令，比如加法、清零、减法、调用等。

A processor is just an additition. Yes. A jump is a function that call or jump is is a function that add a number to your program counter to jump somewhere. So you just need to addition. You are able to add two elements you have a processor. If you want I can give you a lab where you design the processor from scratch by starting from the transistor with aol.
处理器只是一个加法器。是的，跳转是一种函数，它通过向程序计数器添加一个数值来实现跳转。因此，你只需要加法操作。只要你能够将两个元素相加，你就拥有了一个处理器。如果你愿意，我可以给你一个实验，让你从零开始设计处理器，从晶体管和有源负载（aol）开始。

An online tool that was developed in India. It's very funny. If you want to reallyally kn know what is a processor. You can do that in 12 hours. No but during the weekend it's much more interesting than seeing friends. It's useless. Maybe not. Okay. So if you take a snapshot of that yes I have my program counter. The problem that okay I'm executing add but at some point I have to return from add into main because I was executing add and I want to continue the execution just after the call to add.
这是一个在印度开发的在线工具，非常有趣。如果你真的想了解什么是处理器，你可以在12小时内学会。不过，在周末使用它比见朋友更有趣。它没用吗？也许不是。好吧，如果你截取那个画面，是的，我有我的程序计数器。问题是，我正在执行加法操作，但在某个时刻我必须从加法操作返回到主程序，因为我刚才执行的是加法操作，现在我想继续执行加法调用之后的代码。

The problem that in the add function I don't know that I will be called by main when I compile add and it's just a function. Let's imagine three tests. You don't know where three tests will jump at the end of three tests. You need something. So for this reason inside the call frame you have your local variables but you have the program counter in your caller to be able to continue the execution in main.
在 add 函数中，我不知道当我编译 add 时，main 会调用我，它只是一个函数。假设有三个测试，你不知道这三个测试结束后会跳转到哪里，你需要某种机制。因此，在调用帧中，你有局部变量，同时调用者中有程序计数器，以便能够继续在 main 中执行。

So basically when I call I'm in main I'mm calling add it means that I create a frame with four elements my three local variables and the program counter that we have to use when we come back from add when we return. Everything is clear. It's supposed to be easy. So we have two elements that are very important now.
基本上，当我在主函数中调用 add 时，这意味着我创建了一个包含四个元素的栈帧：我的三个局部变量和程序计数器，当我们从 add 返回时需要使用它。一切都很清楚，应该很简单。现在我们有两个非常重要的元素。

Four. You have the globalal variables that are located outside they exist regardless of the function calls they are allocated when the program starts and they are freed when the program stops. You have your next instructions that is there and here you have a sta stack of call frames. So we say that it's a stack because you push the elements one after the other add call f call g and you pop them so it's a stack.
四、你有位于外部的全局变量，它们存在于函数调用之外，程序启动时分配，程序结束时释放。接下来是指令，然后这里有一个调用帧栈。我们称它为栈，因为你一个接一个地压入元素，比如调用f、调用g，然后再弹出它们，所以它是一个栈。

Okay? At low level insideide the machine it's really a stack organized with just the bottom of the stack and you move it when you call the function. Not very important but you could do the inverse you could call malloc you can allocate your memory as you want. Some programming languages like R you know R with a language to perform data analytics is so str.
好的？在机器的底层，实际上是一个堆栈结构，只有堆栈底部，当你调用函数时堆栈会移动。这不是很重要，但你也可以反过来操作，比如调用 malloc，根据需要分配内存。一些编程语言，比如 R，作为一种用于数据分析的语言，非常强大。

That they cannot use the seed stack to execute the frames. They have to use malloc. Because you have something stupid just sorry for the story but it's funny when you are executing add in R you can create a variable inside main on the fly. So if you have just a stack and you move the stack pointer you have a small problem because you have to move everybody but all the pointers that are on the stack have to be updated.
他们不能使用种子栈来执行帧，必须使用 malloc。因为有些设计很愚蠢，抱歉讲这个故事，但当你在 R 中执行加法时，可以在 main 函数中动态创建变量。如果你只有一个栈并且移动栈指针，就会遇到一个小问题，因为你必须移动所有内容，而且栈上的所有指针都必须更新。

So it's a mess. So the only way to manage that is to allocate the frame by using malloc. That's why this language is stupid. Very cool for to for analyzing data but for a system programmer you take a look at that and you say no it's impossible. Please. Don't create on the the fly new variables on your inside your c code.e. Your
所以这很混乱。唯一的解决方法是使用 malloc 来分配内存。这就是为什么这门语言很愚蠢。它非常适合数据分析，但对于系统程序员来说，看到这种情况会觉得不可能。请不要在你的 C 代码中动态创建新的变量。

Okay.ay. So but know what is a thread? A thread is the executable part of your process. So it contains basically it's a context that contains two elements a. Stack of call frames and the next instruction. If you take my previous picture you take a snapshot of this applicplication you know exactly where you are in the execution flow by hav having the full stack and the next instruction. That's enough.
好的。那么，什么是线程呢？线程是进程中可执行的部分。它基本上包含两个元素的上下文：调用栈和下一条指令。如果你看我之前的图片，拍摄这个应用程序的快照，你就能通过完整的调用栈和下一条指令准确知道执行流程的位置。这就足够了。

You restart the execution. Okay? And the processor what he will do it. Will move the program counter and create new frames on the fly or destroy them when you call and return some function. Okay? So here it's really a stack. So the stack is in reverse order but very important. But at at some point you have a top of the stack. So it's's just just an address the stack.
你重新开始执行。明白吗？处理器会做什么呢？它会移动程序计数器，并在调用和返回某个函数时动态创建或销毁栈帧。这里的确是一个栈。栈是逆序的，但非常重要。在某个时刻，你会有栈顶的位置。栈顶只是一个地址。

You just need a pointer to the active frame the one that is active at one moment and then you take this stack pointer and if you want to return from your function you just have to update it. So basically if you want to takee a snapshot of a process while it is running you need two numbers. The program counter and a pointer to your stack.
你只需要一个指向活动栈帧的指针，也就是当前时刻处于活动状态的那个栈帧，然后你拿这个栈指针，如果你想从函数返回，只需更新它即可。基本上，如果你想在进程运行时拍摄快照，你需要两个数值：程序计数器和指向栈的指针。

That's enough. To describe fully the thread. It's not totally true. You have all the the other internal registers of the processor of course that are in the context and not in the stack. But if you imagine that you have a processor with only two registers that's enough. You need the RIP RSP. Stack pointer program counter.
够了。要完整描述线程情况，这并不完全准确。当然，处理器还有其他内部寄存器，它们存在于上下文中，而不在栈里。但如果你想象一个只有两个寄存器的处理器，那也足够了。你需要RIP和RSP，栈指针和程序计数器。

Okay. So the operating system does not schedule process. A process is a very is a too large to be scheduled. At high level you have tooo many elements. You have the memory, the files that are open, the signal depending signals etc etc. At the level of the operating system when the operating system sees is the context the stackck pointer and the program counter.
好的，操作系统不会调度进程。进程太大，无法被调度。在高层次上，你有太多元素，包括内存、打开的文件、信号等。在操作系统层面，当操作系统进行调度时，它关注的是上下文、栈指针和程序计数器。

And when the operating system wants to execute the process it just has to installall the these two registers. Not more. And the page table. But it's not very important. Okay Let's imagine memory. I have two processes. I hope that's one of my enemy words. Yes. You have the process P1 and you have the process P2.
当操作系统想要执行进程时，它只需要安装这两个寄存器，不需要更多。还有页表，但这不是很重要。好，让我们想象一下内存。我有两个进程。我希望这是我最熟悉的词。是的，你有进程P1，还有进程P2。

In P1 you have a call from main f g and you are inside the code of g. So you have the code.ode You have your program counter RIP with an Intel machine. And here you have the call frames and. You have your stack pointer. Here you have a second process. Where a main call. Function A and a function B.
在P1中，你有一个来自main函数的调用，并且你正处于函数g的代码内部。所以你有代码。你有你的程序计数器RIP（在Intel机器上）。这里有调用帧，还有你的栈指针。这里有第二个进程，其中main调用了函数A和函数B。

They are different processes. In memory basically the binary itself are different. So that's why you don't have the same string. Stream of functions. And you are inside B and you are you have some code and you have your. Your program counter. So for the the processor it's very easy. For the system. Here you have the CPU.
它们是不同的进程。在内存中，二进制文件本身就是不同的，所以你不会有相同的字符串或函数流。当你处于进程B时，你有一些代码和程序计数器。对于处理器来说，这非常简单。对于系统来说，这里有CPU。

If I want to execute P1 I just have to load these two registers and I'm executing P1. And if I want to switch from P1 to P2 it's very easy. I just have to save these two registers in memory somewhere so here you have what we call a task T inside Linux. It's called the structure prop when when you use a free VSD etc.c.
如果我想执行P1，只需加载这两个寄存器，就可以执行P1。如果我想从P1切换到P2，也非常简单。我只需将这两个寄存器保存到内存中的某个地方，这里就是Linux中所谓的任务T。当你使用free、VSD等时，它被称为结构体prop。

And what you will do is just you will save these two registers and load the one of P2 and P2 executes. P2 accesses memory etc. And it works. And P1 and P2 are in memory. I don't have virtual memory here. For the the students that know what is virtual memororyy. I don't need it. For MS-DOS 3.3 that I use when it was a kid all the processes were running in a flash memory without any isolation.
你要做的是保存这两个寄存器的值，然后加载P2的寄存器，P2开始执行。P2访问内存等操作，这样就能正常工作。P1和P2都在内存中。我这里没有使用虚拟内存。对于那些了解虚拟内存的学生来说，我不需要它。我小时候用的MS-DOS 3.3中，所有进程都运行在闪存中，没有任何隔离。

Today of course we have virtual memory to isolate the process one from the other. Means that when you run P1 you have P2 from your address sp. Just a way to hide some physical memory. Okay. So now. You know that. Basically for yes something that is important for the. At the system level the. So what is important is that here you have. Yourour memory and.
当然，现在我们有虚拟内存来隔离不同的进程。这意味着当你运行进程P1时，进程P2的地址空间是独立的。这只是一种隐藏部分物理内存的方法。好了，现在你知道了。基本上，这对于系统层面来说是非常重要的。重要的是，你在这里拥有你自己的内存。

Your function when you have two processes two processes and. Your functions act on the memory of of your process. And we have a way to isolate that. So when you write somewhere in memory you write for example 4001 star equal 42 between between I write the value 22 at the address 4000 and the address 4000 in memory belongs to my process.
当你有两个进程时，你的函数作用于你进程的内存。我们有一种方法可以实现隔离。所以当你在内存中的某个位置写入数据时，比如写入地址4001的值为42，而我在地址4000写入值22，地址4000的内存属于我的进程。

And the 8000 here bels. To this process. Okay. But as soon as we see the execution context we can also execute. Two threads two execution context in the same process. There is no problem. So at some point you can spool a new thread and spooling a thread just mean I create a new task in my operating system that I initialize with so here you have the function x at.
这里的8000是指进程。好的，但一旦我们看到执行上下文，我们也可以在同一个进程中执行两个线程、两个执行上下文，这没有问题。所以在某些时候，你可以创建一个新线程，而创建线程的意思就是在操作系统中创建一个新任务并进行初始化。这里你有函数x。

The beginning of x to start the execution with x this thread creates x and my stack is initialized to be empty becaause I will start the execution of a new function. Okay. So like that I can have two threads that are sharing the same memory. They They are acting on the same memory. So they they are not is isolated.
x的开始用于启动执行，线程创建了x，并且我的栈被初始化为空，因为我将开始执行一个新函数。这样，我就可以有两个线程共享相同的内存。它们操作的是同一块内存，所以它们并不是相互隔离的。

At the operating system level there is no difference between a thread and a process. What matters are the process. So now you can define the process. A process is. Just a bunch of memory where you have have your data your glob global variable you have your code whou. Execute and you have have your heap the heap is just a memory region just like a big data segment that you manage dynamically.
在操作系统层面，线程和进程没有区别。重要的是进程。那么现在你可以定义进程。进程就是一块内存区域，里面包含你的数据、全局变量、代码以及堆。堆只是一个内存区域，就像一个大型数据段，由你动态管理。

Imagine that your heap is pre-allococated. with works worklos. There there is no not a big differ difference between the data and heap segment at high level. Both contain data. It's just the data in the heap is not named. You allocate it with with malloc but it does not have a symbol to represent it in the source ce.
假设你的堆是预先分配的，并且工作负载正常。在高层次上，数据段和堆段之间没有太大区别。两者都包含数据，只是堆中的数据没有命名。你通过 malloc 分配它，但在源代码中没有符号来表示它。

The symbol will represent a pointer that points to the data. Okay. And you start and the process may contain one or multiple threads. So when the process starts it starts with a single thread and you can spool new thread on the fly if youou need. So while we want to create multiple threads it's not its.
该符号将表示一个指向数据的指针。好的。一个进程可能包含一个或多个线程。当进程启动时，它会以单个线程开始，如果需要，你可以动态创建新的线程。虽然我们想创建多个线程，但情况并非总是如此。

For a different reason. You want different processes because you want to execute different activities. You want to play Fortnite and you want to browse the web at the same time. So you will need two processes. That are totally independent. They don't have the same state. They don't share anything. They don't communicate at all.
出于不同的原因，你需要不同的进程，因为你想执行不同的活动。你想同时玩《堡垒之夜》和浏览网页，所以你需要两个进程。它们是完全独立的，拥有不同的状态，彼此不共享任何内容，也完全不进行通信。

For the threads we will create threads basically to improve parallelism. To be able to divide the work between multiple threads. Let's imagine you have a web server Nginx for example and you want to handle millions of clients. So what you will do is is that Nginx will create threads to handle the different clients at the same time but the execute in the same process because you want to share their memory I don't know for statistics to know the number of clients that are connected y you need the global variable for for that.
我们创建线程的主要目的是为了提高并行性，能够将工作分配给多个线程。假设你有一个像Nginx这样的网络服务器，并且想要处理数百万的客户端。那么Nginx会创建多个线程，同时处理不同的客户端，但这些线程在同一个进程中执行，因为你希望它们共享内存，比如用于统计连接的客户端数量，这时你需要使用全局变量来实现。

That is shared. You have a big matrix that you want to mul multiptiply but youou will take your matrix divide it in column whatever and spool threads parallelize the work. Okay. So we use a lot yes another reason is just to make the code more straightforward. For example for a video game it's quite con convenient to have one thread in charge of managing the mouse and the keyboard that is waiting for events while another threadad is in charge of the rendering like that you can have a thread that is suspended in the operating system waiting for an event while the other is displaying your thing.
这是共享的。你有一个大矩阵，想要进行矩阵乘法，但你会将矩阵按列划分，然后使用线程池并行处理工作。好的，所以我们大量使用线程，另一个原因是让代码更简洁。例如，对于一个视频游戏来说，让一个线程负责管理鼠标和键盘，等待事件，而另一个线程负责渲染是非常方便的。这样，一个线程可以在操作系统中挂起，等待事件，而另一个线程则负责显示内容。

So in this case it's it's a different kind of parallelism. It's not that you divide and acquire you have a large bunch of work to do and you want to divide it. Here it's really a matter of concern because it's easier. You avoid using a. Asynchronous API the. Asynchronous APIs of Linux that are totally new thing.
在这种情况下，这是一种不同类型的并行处理。并不是你将大量工作分割开来完成，而是出于方便的考虑。这样做更简单，你可以避免使用异步API——Linux的异步API是全新的东西。

I don't know how people are able to cope with that. Okay. For the operating system the process is aligned when it it still has threads. So a thread can start and quit when you want. Start and die. And at some point the last thread die and in this case the memory used by the thread become becomes totally useless.
我不知道人们是如何应对这种情况的。好的，对于操作系统来说，当进程仍然有线程时，进程是活动的。线程可以在你想要的时候启动和退出。启动然后结束。最终，当最后一个线程结束时，该线程所使用的内存就完全没有用了。

You can create so at this step the operating system will consider that the process is terminated and it will. Free the memory of the of the process. So inside the operating system a process. You have a description of of your memory where is your data where is your code etc where are the stacks and you have a link list of tasks.
在这一步，你可以创建一个操作系统会认为该进程已终止的状态，并释放该进程的内存。在操作系统内部，一个进程有一个内存描述，说明数据所在位置、代码所在位置、栈的位置等，同时还有一个任务的链表。

Of threads. 21 22 2. And as soon as the last thread die you free the memory. You can impl implement your own operating system just with this small figure. It's very easy. Five 500 5,000 lines of code. Even less. You will have a small program to install your operating system. Okay. What time is it? We started 1 hour ago.go
线程的数量是21、22、2。当最后一个线程结束时，你就可以释放内存。你甚至可以仅凭这小部分代码实现你自己的操作系统。这非常简单，大约500到5000行代码，甚至更少。你将拥有一个小程序来安装你的操作系统。好了，现在几点了？我们已经开始一个小时了。

Okay. We will have a break. I want to drink a coffee and smoke a cigarette. And I will then present the API which should be straightforward.
好的，我们休息一下。我想喝杯咖啡，抽根烟。然后我将介绍API，这应该很简单。