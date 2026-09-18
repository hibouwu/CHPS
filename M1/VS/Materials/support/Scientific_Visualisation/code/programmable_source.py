import numpy as np
data = np.genfromtxt("data.csv",
                     dtype=None,
                     names=True,
                     delimiter=',',
                     autostrip=True)
for name in data.dtype.names:
    array = data[name]
    output.RowData.append(array, name)