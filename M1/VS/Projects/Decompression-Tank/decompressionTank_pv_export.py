from pathlib import Path
import json

from paraview.simple import *
from PIL import Image


ROOT = Path(__file__).resolve().parent
CASE_DIR = ROOT / "Data" / "OpenFOAM" / "decompressionTank"
OUT_DIR = ROOT / "report_assets"
FIG_DIR = OUT_DIR / "figures"
DATA_DIR = OUT_DIR / "data"
LEFT_FRAMES_DIR = OUT_DIR / "frames_left"

for path in (FIG_DIR, DATA_DIR, LEFT_FRAMES_DIR):
    path.mkdir(parents=True, exist_ok=True)


reader = OpenDataFile(str(CASE_DIR / "case.foam"))
reader.SkipZeroTime = 0  # 改这里：是否读取 t=0 的初始时刻
reader.MeshRegions = ["internalMesh"]
reader.CellArrays = ["U", "p", "rho"]  # 改这里：控制读取哪些物理量

scene = GetAnimationScene()
scene.UpdateAnimationUsingDataTimeSteps()
TIME_VALUES = list(reader.TimestepValues)


def nearest_time(target: float) -> float:
    return min(TIME_VALUES, key=lambda value: abs(value - target))


FOCUS_TIMES = {
    "early": TIME_VALUES[0],
    "mid": nearest_time(1.0e-4),
    "late": TIME_VALUES[-1],
}
FIGURE2_TIME = nearest_time(4.0e-5)  # 改这里：Figure 2 使用的时刻，当前为 40 us

with (DATA_DIR / "time_map.json").open("w", encoding="utf-8") as fh:
    json.dump(
        {
            "labels": list(range(len(TIME_VALUES))),
            "time_values": TIME_VALUES,
            "focus_times": FOCUS_TIMES,
        },
        fh,
        indent=2,
    )


def set_time(time_value: float) -> None:
    scene.AnimationTime = time_value
    UpdatePipeline(time_value, reader)


def base_render_view():
    # 所有 ParaView 导出图共用的基础视图设置。
    view = CreateView("RenderView")
    view.ViewSize = [3600, 2400]  # 改这里：控制 ParaView 原始导出分辨率，当前提高到高分辨率
    view.Background = [0.6, 0.6, 0.6]  # 改这里：背景颜色，当前是白底
    view.OrientationAxesVisibility = 0
    view.CenterAxesVisibility = 0
    view.UseColorPaletteForBackground = 0
    view.CameraParallelProjection = 1
    return view


point_data = CellDatatoPointData(Input=reader)

# 主要二维切片，大多数静态图和动画左图都基于它。
slice_xy = Slice(Input=point_data)
slice_xy.SliceType = "Plane"
slice_xy.SliceType.Origin = [0.075, 0.15, 0.0]  # 改这里：切片通过的位置
slice_xy.SliceType.Normal = [0.0, 0.0, 1.0]  # 改这里：切片法向，当前是 z=0 平面
slice_xy.Triangulatetheslice = 0

# 储罐整体视图里的速度箭头。
MAX_GLYPH_MAG = 20.0  # 改这里：左图/Figure 1 箭头按速度缩放时的最大上限

# 左图和 Figure 1 不使用原始 |U| 直接缩放，而是先把过大的值截断到上限。
velocity_glyph_scale = Calculator(Input=slice_xy)
velocity_glyph_scale.ResultArrayName = "glyphScale"
velocity_glyph_scale.Function = f"min(mag(U), {MAX_GLYPH_MAG})"

velocity_glyphs = Glyph(Input=velocity_glyph_scale, GlyphType="Arrow")
velocity_glyphs.OrientationArray = ["POINTS", "U"]
velocity_glyphs.ScaleArray = ["POINTS", "glyphScale"]
velocity_glyphs.ScaleFactor = 0.004  # 改这里：左图和 Figure 1 里的箭头整体缩放
velocity_glyphs.GlyphMode = "Every Nth Point"
velocity_glyphs.Stride = 25  # 改这里：箭头密度，越小越密

# 单独计算速度模长，供喷口局部放大图使用。
velocity_mag = Calculator(Input=slice_xy)
velocity_mag.ResultArrayName = "magU"
velocity_mag.Function = "mag(U)"

velocity_mag_glyphs = Glyph(Input=velocity_mag, GlyphType="Arrow")
velocity_mag_glyphs.OrientationArray = ["POINTS", "U"]
velocity_mag_glyphs.ScaleArray = ["POINTS", "U"]
velocity_mag_glyphs.ScaleFactor = 0.003  # 改这里：Figure 2 喷口局部箭头大小
velocity_mag_glyphs.GlyphMode = "Every Nth Point"
velocity_mag_glyphs.Stride = 10  # 改这里：Figure 2 局部箭头密度

pressure_contours = Contour(Input=slice_xy)
pressure_contours.ContourBy = ["POINTS", "p"]
pressure_contours.Isosurfaces = [0.0] * 9  # 先占位，后面会按统一范围重设等值线
pressure_contours.PointMergeMethod = "Uniform Binning"


def pressure_range(time_value: float):
    set_time(time_value)
    UpdatePipeline(time_value, slice_xy)
    info = slice_xy.GetDataInformation().GetPointDataInformation().GetArrayInformation("p")
    return info.GetComponentRange(0)


def magu_range(time_value: float):
    set_time(time_value)
    UpdatePipeline(time_value, velocity_mag)
    info = velocity_mag.GetDataInformation().GetPointDataInformation().GetArrayInformation("magU")
    return info.GetComponentRange(0)


pressure_min = min(pressure_range(time_value)[0] for time_value in FOCUS_TIMES.values())
pressure_max = max(pressure_range(time_value)[1] for time_value in FOCUS_TIMES.values())
magu_reference_times = list(FOCUS_TIMES.values()) + [FIGURE2_TIME]
magu_min = min(magu_range(time_value)[0] for time_value in magu_reference_times)
magu_max = max(magu_range(time_value)[1] for time_value in magu_reference_times)

pressure_values = [
    pressure_min + (pressure_max - pressure_min) * i / 8.0 for i in range(9)
]
pressure_contours.Isosurfaces = pressure_values


def configure_pressure_view(view):
    # 这里控制动画左图，以及 Figure 1 的三张总览图。
    slice_display = Show(slice_xy, view, "GeometryRepresentation")
    ColorBy(slice_display, ("POINTS", "p"))
    slice_display.RescaleTransferFunctionToDataRange(False, True)
    slice_display.SetScalarBarVisibility(view, True)

    lut = GetColorTransferFunction("p")
    lut.RescaleTransferFunction(pressure_min, pressure_max)
    pwf = GetOpacityTransferFunction("p")
    pwf.RescaleTransferFunction(pressure_min, pressure_max)
    pressure_bar = GetScalarBar(lut, view)
    pressure_bar.Title = "Pression p"
    pressure_bar.ComponentTitle = ""
    pressure_bar.WindowLocation = "Any Location"
    pressure_bar.Orientation = "Vertical"
    # 如果左图布局还不舒服，优先在这里改颜色条的位置和大小。
    pressure_bar.Position = [0.65, 0.40]  # 改这里：颜色条左下角位置，[横向, 纵向]
    pressure_bar.ScalarBarLength = 0.30  # 改这里：颜色条长度
    pressure_bar.TitleFontSize = 45  # 改这里：颜色条标题字号
    pressure_bar.LabelFontSize = 32  # 改这里：颜色条刻度字号
    pressure_bar.LabelColor = [1.0, 1.0, 1.0]  # 改这里：颜色条刻度标签颜色，当前是黑色
    pressure_bar.TitleColor = [1.0, 1.0, 1.0]  # 改这里：颜色条标题颜色


    glyph_display = Show(velocity_glyphs, view, "GeometryRepresentation")
    glyph_display.DiffuseColor = [0.1, 0.1, 0.1]  # 改这里：箭头颜色
    glyph_display.AmbientColor = [0.1, 0.1, 0.1]  # 改这里：箭头颜色
    ColorBy(glyph_display, None)

    return slice_display, glyph_display


def configure_magu_view(view):
    # Figure 2 专用设置：这里颜色表示 |U|，不是 p。
    mag_display = Show(velocity_mag, view, "GeometryRepresentation")
    ColorBy(mag_display, ("POINTS", "magU"))
    mag_display.RescaleTransferFunctionToDataRange(False, True)
    mag_display.SetScalarBarVisibility(view, True)

    lut = GetColorTransferFunction("magU")
    lut.RescaleTransferFunction(magu_min, magu_max)
    pwf = GetOpacityTransferFunction("magU")
    pwf.RescaleTransferFunction(magu_min, magu_max)

    glyph_display = Show(velocity_mag_glyphs, view, "GeometryRepresentation")
    glyph_display.DiffuseColor = [0.1, 0.1, 0.1] # 改这里：Figure 2 局部箭头颜色
    glyph_display.AmbientColor = [0.1, 0.1, 0.1] # 改这里：Figure 2 局部箭头颜色
    ColorBy(glyph_display, None)

    return mag_display, glyph_display


def configure_contour_view(view):
    # Figure 3 专用设置：半透明底图上叠加压力等值线。
    slice_display = Show(slice_xy, view, "GeometryRepresentation")
    ColorBy(slice_display, ("POINTS", "p"))
    slice_display.Opacity = 0.55
    slice_display.SetScalarBarVisibility(view, True)
    lut = GetColorTransferFunction("p")
    lut.RescaleTransferFunction(pressure_min, pressure_max)
    pwf = GetOpacityTransferFunction("p")
    pwf.RescaleTransferFunction(pressure_min, pressure_max)

    contour_display = Show(pressure_contours, view, "GeometryRepresentation")
    ColorBy(contour_display, ("POINTS", "p"))
    contour_display.LineWidth = 8.0  # 改这里：等值线粗细
    contour_display.SetScalarBarVisibility(view, False)


def save_overview(time_value: float, output_name: str):
    view = base_render_view()
    configure_pressure_view(view)
    set_time(time_value)
    # 这组相机参数决定 Figure 1 能看到多少完整储罐区域。
    view.CameraPosition = [0.075, 0.15, 1.0]  # 改这里：相机位置
    view.CameraFocalPoint = [0.075, 0.15, 0.0]  # 改这里：相机看向哪里
    view.CameraParallelScale = 0.17  # 改这里：缩放范围，越大看到越多
    Render(view)
    output_path = FIG_DIR / output_name
    SaveScreenshot(str(output_path), view, ImageResolution=view.ViewSize)
    # Figure 1 左右留白较多，这里在导出后立刻裁掉左右各 1/4。
    image = Image.open(output_path).convert("RGB")
    width, height = image.size
    cropped = image.crop((width // 4, 0, width - width // 4, height))  # 改这里：Figure 1 左右裁剪范围
    cropped.save(output_path)
    Delete(view)


def save_nozzle_zoom(time_value: float, output_name: str):
    view = base_render_view()
    configure_magu_view(view)
    set_time(time_value)
    # Figure 2 的喷口局部放大取景。
    view.CameraPosition = [0.145, 0.055, 1.0]  # 改这里：Figure 2 相机位置
    view.CameraFocalPoint = [0.145, 0.055, 0.0]  # 改这里：Figure 2 对准喷口
    view.CameraParallelScale = 0.03  # 改这里：Figure 2 放大倍数
    Render(view)
    SaveScreenshot(str(FIG_DIR / output_name), view, ImageResolution=view.ViewSize)
    Delete(view)


def save_contours(time_value: float, output_name: str):
    view = base_render_view()
    configure_contour_view(view)
    set_time(time_value)
    # Figure 3 的取景，重点放在压力梯度更明显的区域。
    view.CameraPosition = [0.12, 0.055, 1.0]  # 改这里：Figure 3 相机位置
    view.CameraFocalPoint = [0.12, 0.055, 0.0]  # 改这里：Figure 3 视线中心
    view.CameraParallelScale = 0.08  # 改这里：Figure 3 视野范围
    Render(view)
    SaveScreenshot(str(FIG_DIR / output_name), view, ImageResolution=view.ViewSize)
    Delete(view)


save_overview(FOCUS_TIMES["early"], "figure1_early.png")
save_overview(FOCUS_TIMES["mid"], "figure1_mid.png")
save_overview(FOCUS_TIMES["late"], "figure1_late.png")
save_nozzle_zoom(FIGURE2_TIME, "figure2_nozzle_magu.png")
save_contours(FOCUS_TIMES["mid"], "figure3_contours.png")

line = PlotOverLine(Input=point_data)
# Figure 4 使用的轴线采样线。
line.Point1 = [0.0, 0.055, 0.0]  # 改这里：采样线起点
line.Point2 = [0.15, 0.055, 0.0]  # 改这里：采样线终点
line.Resolution = 300  # 改这里：采样点数量

for tag, time_value in FOCUS_TIMES.items():
    set_time(time_value)
    UpdatePipeline(time_value, line)
    SaveData(str(DATA_DIR / f"line_{tag}.csv"), proxy=line, Precision=10)


probe_tank = ProbeLocation(Input=point_data, ProbeType="Fixed Radius Point Source")
# Figure 5 和动画右图里使用的储罐内部采样点。
probe_tank.ProbeType.Center = [0.03, 0.055, 0.0]  # 改这里：内部采样点坐标
probe_tank.ProbeType.Radius = 0.0
probe_tank.ProbeType.NumberOfPoints = 1

probe_nozzle = ProbeLocation(Input=point_data, ProbeType="Fixed Radius Point Source")
# 靠近喷口的采样点；和内部点叠加比较就是统计图的核心。
probe_nozzle.ProbeType.Center = [0.145, 0.055, 0.0]  # 改这里：喷口采样点坐标
probe_nozzle.ProbeType.Radius = 0.0
probe_nozzle.ProbeType.NumberOfPoints = 1

tank_over_time = PlotDataOverTime(Input=probe_tank)
nozzle_over_time = PlotDataOverTime(Input=probe_nozzle)

UpdatePipeline(TIME_VALUES[-1], tank_over_time)
UpdatePipeline(TIME_VALUES[-1], nozzle_over_time)

SaveData(str(DATA_DIR / "tank_over_time.csv"), proxy=tank_over_time, Precision=10)
SaveData(str(DATA_DIR / "nozzle_over_time.csv"), proxy=nozzle_over_time, Precision=10)


animation_view = base_render_view()
configure_pressure_view(animation_view)

# 导出动画左图时显示的标题。
title = Text()
title.Text = "Decompression du reservoir"
title_display = Show(title, animation_view, "TextSourceRepresentation")
title_display.WindowLocation = "Upper Center"
title_display.FontSize = 72  # 改这里：动画左图标题字号
title_display.Color = [0.0, 0.0, 0.0] # 改这里：动画左图标题颜色，当前是黑色

time_text = AnnotateTimeFilter(Input=reader)
time_text.Format = "Temps = %.2f us"  # 改这里：时间显示格式，当前改成微秒
time_display = Show(time_text, animation_view, "TextSourceRepresentation")
time_display.WindowLocation = "Any Location"  # 改这里：时间文字是否固定在角落
time_display.Position = [0.55, 0.82]  # 改这里：时间文字位置 [横向, 纵向]
time_display.FontSize = 45  # 改这里：时间注释字号
time_display.Color = [0.0, 0.0, 0.0]

# 左图里的简短说明，解释颜色和箭头各表示什么。
legend_text = Text()
legend_text.Text = "Couleur : pression p\nFleches : vitesse U"
legend_display = Show(legend_text, animation_view, "TextSourceRepresentation")
legend_display.WindowLocation = "Any Location"
legend_display.Position = [0.55, 0.84]  # 改这里：颜色/箭头说明的位置 第一个值控制横向，第二个值控制纵向
legend_display.FontSize = 45  # 改这里：颜色/箭头说明字号
legend_display.Color = [0.0, 0.0, 0.0]

# 动画左图主取景。想改左图范围时，优先改这里，再考虑后面的裁剪。
animation_view.CameraPosition = [0.075, 0.15, 1.0]  # 改这里：动画左图相机位置
animation_view.CameraFocalPoint = [0.075, 0.15, 0.0]  # 改这里：动画左图看向中心
animation_view.CameraParallelScale = 0.17  # 改这里：动画左图视野范围

for idx, time_value in enumerate(TIME_VALUES):
    set_time(time_value)
    time_text.Format = f"Temps = {time_value * 1.0e6:.2f} us"  # 改这里：每一帧直接写入微秒数值，避免空白
    Render(animation_view)
    SaveScreenshot(
        str(LEFT_FRAMES_DIR / f"frame_{idx:03d}.png"),
        animation_view,
        ImageResolution=animation_view.ViewSize,
    )
