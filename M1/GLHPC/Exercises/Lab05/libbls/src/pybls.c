#ifndef PYBLS_H
  #define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
  #include <Python.h>
  #include <numpy/arrayobject.h>

  #include "../include/bls.h"

static PyObject *py_bls(PyObject *self, PyObject *args) {
  PyArrayObject *t_arr, *f_arr;
  double Pmin, Pmax, qmin, qmax;
  int Np, Nq;

  if (!PyArg_ParseTuple(args, "O!O!ddiddi", &PyArray_Type, &t_arr, &PyArray_Type, &f_arr, &Pmin,
                        &Pmax, &Np, &qmin, &qmax, &Nq))
    return NULL;

  int N = (int)PyArray_DIM(t_arr, 0);
  double *t = (double *)PyArray_DATA(t_arr);
  double *f = (double *)PyArray_DATA(f_arr);

  BLSResult res = bls(t, f, N, Pmin, Pmax, Np, qmin, qmax, Nq);

  return Py_BuildValue("{s:d,s:d,s:d,s:d,s:d}", "period", res.period, "duration", res.duration,
                       "phase", res.phase, "depth", res.depth, "power", res.power);
}

static PyObject *py_periodogram_bls(PyObject *self, PyObject *args) {
  PyArrayObject *t_arr, *f_arr;
  double Pmin, Pmax, qmin, qmax;
  int Np, Nq;

  if (!PyArg_ParseTuple(args, "O!O!ddiddi", &PyArray_Type, &t_arr, &PyArray_Type, &f_arr, &Pmin,
                        &Pmax, &Np, &qmin, &qmax, &Nq))
    return NULL;

  int N = (int)PyArray_DIM(t_arr, 0);
  double *t = (double *)PyArray_DATA(t_arr);
  double *f = (double *)PyArray_DATA(f_arr);

  int out_Nf;
  double *periodogram = bls_periodogram(t, f, N, Pmin, Pmax, Np, qmin, qmax, Nq, &out_Nf);

  npy_intp dims[2] = {out_Nf, 2};
  PyObject *result = PyArray_SimpleNewFromData(2, dims, NPY_DOUBLE, periodogram);
  // The numpy array now owns the data and will free it when done
  // So we don't free periodogram here

  return result;
}

static PyMethodDef BlsMethods[] = {
    {"bls", py_bls, METH_VARARGS, "Run the BLS algorithm."},
    {"bls_periodogram", py_periodogram_bls, METH_VARARGS, "Compute the BLS periodogram."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef blsmodule = {PyModuleDef_HEAD_INIT, "pybls", NULL, -1, BlsMethods};

PyMODINIT_FUNC PyInit_bls(void) {
  import_array();
  return PyModule_Create(&blsmodule);
}
#endif  // PYBLS_H