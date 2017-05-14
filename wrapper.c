#include "Python.h"
#include "wrapper.h"

static PyObject *_wrap_calculate_sin(PyObject *self, PyObject *args) {

  PyObject *resultobj;
  double r1, r2, result;

  PyArg_ParseTuple(args, (char *)"dd:calculate_sin", &r1, &r2);

  calculate_sin(r1, r2, &result);

  resultobj = PyFloat_FromDouble(result);
  return resultobj;
}
static PyMethodDef HwMethods[] = {
    {"calculate_sin", _wrap_calculate_sin, METH_VARARGS, "Hello world."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef hwmodule = {
   PyModuleDef_HEAD_INIT,
   "code",   /* name of module */
   NULL,   /* module documentation, may be NULL */
   -1,
   HwMethods
};


PyMODINIT_FUNC
PyInit_hw(void)
{
    return PyModule_Create(&hwmodule);
}
