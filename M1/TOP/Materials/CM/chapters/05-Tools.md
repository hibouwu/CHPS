# 5 Tools 工具

## Overview 概览

<table style="width: 100%; border-collapse: collapse;">
  <tr>
    <td style="width: 100%; vertical-align: top;">
      <ul>
        <li>This chapter is a compact list of useful performance-analysis and code-inspection tools 这一章整理了一些常用的性能分析与代码观察工具</li>
        <li>Some tools focus on runtime profiling, while others help inspect generated machine code 有些工具侧重运行时性能分析，有些工具则帮助检查生成的机器代码</li>
        <li>Different tools answer different questions, so it is common to combine several of them 不同工具回答的问题不同，因此实际工作中通常会组合使用</li>
      </ul>
    </td>
  </tr>
</table>

## Profiling tools 性能分析工具

<table style="width: 100%; border-collapse: collapse;">
  <tr>
    <td style="width: 100%; vertical-align: top;">
      <ul>
        <li><strong>Linux perf</strong>: a standard Linux profiler for CPU events, call stacks, and hotspots <strong>Linux perf</strong>：Linux 上常用的标准性能分析工具，可查看 CPU 事件、调用栈与热点</li>
        <li><strong>KDAB Hotspot</strong>: a graphical viewer built on top of `perf` data <strong>KDAB Hotspot</strong>：基于 `perf` 数据的图形化分析界面</li>
        <li><strong>gprof</strong>: a classic profiler for function-level performance breakdown <strong>gprof</strong>：经典的函数级性能分析工具</li>
        <li><strong>TAU</strong>: a performance system for profiling and tracing parallel applications <strong>TAU</strong>：适合并行程序的性能分析与跟踪工具</li>
        <li><strong>Scalasca</strong> and <strong>Score-P</strong>: tools for profiling and tracing large-scale parallel executions <strong>Scalasca</strong> 和 <strong>Score-P</strong>：用于大规模并行程序的剖析与跟踪</li>
        <li><strong>MAQAO</strong>: a performance-analysis and optimization suite <strong>MAQAO</strong>：面向性能分析与优化的一整套工具</li>
        <li><strong>Intel VTune</strong>: a performance-analysis and optimization suite <strong>Intel VTune</strong>：面向性能分析与优化的一整套工具</li>
      </ul>
    </td>
  </tr>
</table>

## Code and microarchitecture inspection 代码与微架构观察工具

<table style="width: 100%; border-collapse: collapse;">
  <tr>
    <td style="width: 100%; vertical-align: top;">
      <ul>
        <li><strong>Compiler Explorer / godbolt</strong>: inspect generated assembly from different compilers and flags <strong>Compiler Explorer / godbolt</strong>：查看不同编译器和编译选项生成的汇编代码</li>
        <li><strong>uops.info</strong>: inspect instruction-level properties such as latency, throughput, and micro-op decomposition <strong>uops.info</strong>：查看指令级延迟、吞吐率以及微操作分解等信息</li>
      </ul>
    </td>
  </tr>
</table>

## Links 链接

<table style="width: 100%; border-collapse: collapse;">
  <tr>
    <td style="width: 100%; vertical-align: top;">
      <ul>
        <li>Linux perf + KDAB Hotspot video Linux perf 与 KDAB Hotspot 视频：<a href="https://www.youtube.com/watch?v=3HtR89L2u9Q">https://www.youtube.com/watch?v=3HtR89L2u9Q</a></li>
        <li>uops.info: <a href="https://www.uops.info/">https://www.uops.info/</a></li>
        <li>Compiler Explorer / godbolt: <a href="https://godbolt.org/">https://godbolt.org/</a></li>
      </ul>
    </td>
  </tr>
</table>

## How to use them 如何使用这些工具

<table style="width: 100%; border-collapse: collapse;">
  <tr>
    <td style="width: 100%; vertical-align: top;">
      <ul>
        <li>Use profilers first to find where time is spent 先用性能分析器找出时间主要花在哪里</li>
        <li>Then inspect assembly or instruction data when the bottleneck is already localized 之后在瓶颈已经定位的前提下，再去看汇编或指令级细节</li>
        <li>Do not start from assembly unless the high-level performance picture is already clear 不要一开始就钻进汇编，除非你已经清楚整体性能问题在哪</li>
      </ul>
    </td>
  </tr>
</table>
