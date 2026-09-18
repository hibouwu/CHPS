from paraview.simple import *


_DisableFirstRenderCameraReset()

render_view = GetActiveViewOrCreate("RenderView")
render_view.ViewSize = [1280, 960]
render_view.Background = [1.0, 1.0, 1.0]

sphere = Sphere()
sphere.ThetaResolution = 32
sphere.PhiResolution = 32

rep = Show(sphere, render_view)
rep.Representation = "Surface"
ColorBy(rep, ("POINTS", "vtkProcessId"))

render_view.ResetCamera()
Render()
rep.RescaleTransferFunctionToDataRange(True)
Render()

SaveScreenshot("parasphere.png", render_view)
