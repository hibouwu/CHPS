# EXPRESSO — 并行运行时课程项目

[返回 AISE](../../README.md)

## 题目与报告

- [项目题目](ProjetDoc/sujet.md) · [原题 PDF](ProjetDoc/assignment.pdf)
- [报告](rapport.pdf) · [LaTeX 源码](ProjetRapportlatex/rapport.tex)
- [原提交包](SHI.Jianye.tar.gz)

## 源码

- [expresso](expresso/)：运行时实现、头文件和测试。
- [expresso-benchmarks](expresso-benchmarks/)：dot、list、matmul、vecmul 以及已有测量结果。

两部分保留本地课程实现，原始教学仓库分别是 [expresso](https://gitlab.com/expresso-student/expresso) 和 [expresso-benchmarks](https://gitlab.com/expresso-student/expresso-benchmarks)。

## 构建与测试

需要 GCC、Make 和系统线程支持。在本目录执行：

```bash
make -C expresso
make -C expresso test
make -C expresso install PREFIX="$PWD/install_dir"
make -C expresso-benchmarks PREFIX="$PWD/install_dir"
```

`install_dir/` 是可重新生成的本地安装目录。benchmark 参数与历史实验命令见 [说明](expresso-benchmarks/README.md)。
