# Installation de MPI sur votre ordinateur（在你的电脑上安装 MPI）

Télécharger `mpich-4.3.0.tar.gz` à l'adresse http://www.mpich.org/static/downloads/4.3.0/mpich-4.3.0.tar.gz（从该地址下载 `mpich-4.3.0.tar.gz`）
```
cd /tmp
tar xvzf /votre/repertoire/de/telechargement/mpich-4.3.0.tar.gz 
```

Le dossier créé est le répertoire de compilation que l'on pourra détruire après installation définitive.（生成的文件夹是编译目录，完成最终安装后可以删除）

Configuration :（配置：）

```
cd mpich-4.3.0
./configure --prefix=/usr/local/mpich-4.3.0 --disable-cxx --disable-fortran --disable-romio --enable-threads=runtime --with-device=ch3
```

Le répertoire désigné par `--prefix=` sera le répertoire d'installation définitive, le chemin donné ici n'est qu'un exemple.（`--prefix=` 指定的目录是最终安装目录，这里的路径只是示例）

Compilation (plusieurs minutes) :（编译，需数分钟：）

```
make
```

Installation (en fonction du répertoire final d'installation peut nécessiter les droits root) :（安装，取决于最终安装目录可能需要 root 权限：）

```
sudo make install
```

# Environnement, compilation, exécution（环境、编译、执行）

Préparation environnement (à exécuter dans chaque nouveau shell ou à mettre dans votre `.bashrc`) :（环境准备：每次新开 shell 执行，或加入你的 `.bashrc`）
```
export PATH=/usr/local/mpich-4.3.0/bin:$PATH
```

Après avoir écrit votre premier programme MPI `monprog.c`, compilez-le avec `mpicc` (`mpicc` se comporte comme un compilateur classique) :（写好第一个 MPI 程序 `monprog.c` 后，用 `mpicc` 编译，它的行为与普通编译器类似：）
```
prompt> mpicc monprog.c -o monprog.exe
```

On execute autant de fois que nécessaire le programme MPI avec `mpiexec` ou `mpirun` :（使用 `mpiexec` 或 `mpirun` 按需多次运行 MPI 程序：）
```
prompt> mpiexec -n 4 ./monprog.exe
prompt> mpirun -n 2 ./monprog.exe
prompt> etc ...
```
