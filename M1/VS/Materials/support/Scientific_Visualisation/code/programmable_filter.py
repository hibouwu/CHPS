input0 = inputs[0]
data = input0.PointData["volume_scalars"] / 2.0
output.PointData.append(data, "scalar_half") 