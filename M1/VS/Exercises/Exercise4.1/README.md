# Exercise 4.1: Running a visualization script in parallel

这个目录对应 ParaView tutorial 的 Exercise 4.1，目标是在命令行下用 `mpiexec` 启动 `pvbatch`，并行执行一个 ParaView Python 脚本。
这部分内容对应教程中“Running a visualization script in parallel”的示例。

## 目录内容

- `parasphere.py`：并行可视化脚本，创建一个球体并按 `vtkProcessId` 着色。
- `run.sh`：运行脚本，使用所配置的 ParaView 安装执行并行渲染。
- `parasphere.png`：运行完成后生成的输出图像。

## 运行方式

在当前目录执行：

```bash
./run.sh
```

如果想手动运行，对应命令是：

```bash
"$PARAVIEW_BIN"/mpiexec -n 4 \
  "$PARAVIEW_BIN"/pvbatch \
  parasphere.py
```

## 教程中的可执行文件位置

教程里给出了不同平台上 `mpiexec` 和 `pvbatch` 的常见位置。

### On Mac

```text
/Applications/ParaView-x.x.x.app/Contents/MacOS/mpiexec
```

```text
/Applications/ParaView-x.x.x.app/Contents/bin/pvbatch
```

### On Linux

如果将 ParaView 二进制文件解压到 `/usr/local`，则典型路径为：

```text
/usr/local/lib/paraview-x.x.x/mpiexec
```

```text
/usr/local/bin/pvbatch
```

如果使用 ParaView 自带 MPI，通常还需要把 ParaView 的 `lib` 目录加入 `LD_LIBRARY_PATH`。

### On Windows

```text
C:/Program Files/Microsoft MPI/Bin/mpiexec
```

```text
C:/Program Files/ParaView x.x.x/bin/pvbatch
```

## 教程中的命令行示例

### On Mac

```bash
/Applications/ParaView-x.x.x.app/Contents/MacOS/mpiexec -np 4 \
  /Applications/ParaView-x.x.x.app/Contents/bin/pvbatch \
  parasphere.py
```

### On Linux

```bash
/usr/local/lib/paraview-x.x.x/mpiexec -np 4 \
  /usr/local/bin/pvbatch \
  parasphere.py
```

### On Windows

```powershell
mpiexec -np 4 "C:/Program Files/ParaView x.x.x/bin/pvbatch" parasphere.py
```

### 在本目录中的实际命令

本仓库里使用的是已经解压好的本地 ParaView，可直接运行：

```bash
"$PARAVIEW_BIN"/mpiexec -n 4 \
  "$PARAVIEW_BIN"/pvbatch \
  parasphere.py
```

## 说明

- `mpiexec` 用来启动 MPI 并行任务。
- `pvbatch` 用来在无界面模式下执行 ParaView Python 脚本。
- 脚本中的 `ColorBy(rep, ("POINTS", "vtkProcessId"))` 会让不同并行进程负责的数据块显示为不同颜色。

## 结果

运行成功后会在本目录生成 `parasphere.png`。ParaView 可能会短暂弹出窗口，也可能不会；无论哪种情况，最终都应看到输出图片。

这张图的球体会按 `vtkProcessId` 着色，因此不同并行进程负责的部分会显示成不同颜色，这就是教程里要验证的结果。

运行前将 `PARAVIEW_BIN` 设为 ParaView 安装目录下的 `bin`，或将 `mpiexec`、`pvbatch` 加入 PATH。脚本不依赖某个固定的本机安装路径。
