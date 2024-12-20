# KSPWLO with Pre-processing

本项目采用https://github.com/tchond/kspwlos的svpplus算法，并在此基础上增加了对图文件的预处理，即在执行算法前删除图中度为一的顶点，以减少算法时间复杂度。实验证明算法的效率取得显著提升。

参考文献：Theodoros Chondrogiannis, Panagiotis Bouros, Johann Gamper, Ulf Leser, and David B. Blumenthal, Finding k-shortest paths with limited overlap. The VLDB Journal 29(5) (2020)

## 环境

操作系统：ubuntu 22.04

编译器：g++ 11.4.0

## 运行

在编译代码前，需要改变Makefile中编译器的路径：

`CC      =  /usr/bin/g++`   更改为你的编译器路径

构建代码需要进入项目文件夹，在终端中输入以下命令：

```sh
$ make
```

之后，会生成执行文件run.exec   为运行此文件，输入以下命令：

```sh
$ ./run.exec -f [SAMPLE] -k [PATHS] -t [THRESHOLD] -s [SOURCE] -d [DESTINATION]
```
表格提供了对各参数的解释，以及参数值的范围

| 参数 | 描述 | 值 |
| --- | --- | --- |
| SAMPLE | 图文件路径 | /sample/filename.gr |
| PATHS | 期望获得的路径查询数量 | [0,+inf] |
| THRESHOLD | 相似度阈值 | [0,1] |
| SOURCE | 源查询节点 | [0,NUM_NODES] |
| DESTINATION | 目标查询节点 | [0,NUM_NODES] |
