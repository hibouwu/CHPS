# 储罐减压可视化

利用 ParaView 观察高压储罐向喷嘴释放流体时的压力、速度与密度变化。报告、可视化结果、处理脚本与输入数据保存在同一目录。

[返回科学可视化课程](../../README.md)

## 阅读与结果

- [报告 PDF](exemple.pdf) · [LaTeX 源码](exemple.tex)
- [完整演示视频](decompressionTank.mp4)
- [流场动画](decompressionTank_left.mp4)
- [图表与导出数据](report_assets/)

## 输入数据

- [OpenFOAM 算例](Data/OpenFOAM/decompressionTank/)：`decompressionTank_pv_export.py` 使用这一份数据，入口为 `case.foam`。
- [VTK 时间序列](Data/VTK/evaluations/decompressionTank/decompressionTank.vtm.series)：课程考核数据的另一种组织形式，可在 ParaView 中打开。

两份数据保留各自的时间值和文件结构，不假定其时间采样完全一致。

## 重新生成图表与视频

需要 ParaView 的 Python 环境、Pillow、pandas、matplotlib 和 FFmpeg。先在已安装 ParaView 的环境中执行：

```bash
pvpython decompressionTank_pv_export.py
python3 build_decompression_report_assets.py
```

第一步读取 OpenFOAM 数据并生成图像与 CSV；第二步使用导出结果生成图表和视频。脚本以自身目录定位数据，无需依赖旧的 Note 路径。ParaView 软件本身不包含在此项目中。

LaTeX 报告通过 `report_assets/` 中的图片排版，可使用现有 LaTeX 环境编译 `exemple.tex`。
