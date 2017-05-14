/*
* Copyright (C) 1999 Michael P. Reilly, All rights reserved.
* Written by Michael P. Reilly.
*/
/* headers */
#include <Python.h>

/* Module globals */
static PyObject *counter_error = NULL;

/* Counter type */
staticforward PyTypeObject Counter_Type;

/* Counter object */
typedef struct {
  PyObject_HEAD
  long value;
} Counter;

#define Counter_Check(v)  ((v)->ob_type == &Counter_Type)
#define Counter_value(v)  (((Counter *)(v))->value)

/* helper functions */
static int
object2int(obj, value)
  PyObject *obj;
  long *value;
  { PyObject *temp;

    if (Counter_Check(obj))
      *value = Counter_value(obj);
    else if (PyInt_Check(obj))
      *value = PyInt_AsLong(obj);
    else {
      temp = PyNumber_Int(obj);
      if (temp == NULL) {
        PyErr_SetString(PyExc_TypeError, "expecting number");
        return 0;
      }
      *value = PyInt_AsLong(temp);
      Py_DECREF(temp);
    }
    return 1;
  }

/* constructor */
static PyObject *
Counter_NEW(initial_value)
  long initial_value;
  { Counter *object;

    object = PyObject_NEW(Counter, &Counter_Type);
    if (object != NULL)
      object->value = initial_value;
    return (PyObject *)object;
  }

static void
Counter_dealloc(self)
  PyObject *self;
  { PyMem_DEL(self);
  }

/* Numeric emulation routines */

/* In this case, it is easier to write a coercion routines than to
 * all the little add, subtract, multiply, etc. routines.
 */

static PyObject *
Counter_Neg(self)
  PyObject *self;
  { return Py_BuildValue("i", -Counter_value(self));
  }
static PyObject *
Counter_Pos(self)
  PyObject *self;
  { return Py_BuildValue("i", Counter_value(self));
  }
static PyObject *
Counter_Abs(self)
  PyObject *self;
  { register long value = Counter_value(self);
    return Py_BuildValue("i", (value < 0 ? -value : value));
  }
static int
Counter_Nonzero(self)
  PyObject *self;
  { return (Counter_value(self) != 0);
  }
static PyObject *
Counter_Invert(self)
  PyObject *self;
  { return PyInt_FromLong(~Counter_value(self));
  }

static PyObject *
Counter_Int(self)
  PyObject *self;
  {
    return PyInt_FromLong(Counter_value(self));
  }
static PyObject *
Counter_Long(self)
  PyObject *self;
  {
    return PyLong_FromLong(Counter_value(self));
  }
static PyObject *
Counter_Float(self)
  PyObject *self;
  {
    return PyFloat_FromDouble((double)Counter_value(self));
  }
static PyObject *
Counter_Oct(self)
  PyObject *self;
  { char buf[100];
    sprintf(buf, "0%o", Counter_value(self));
    return PyString_FromString(buf);
  }
static PyObject *
Counter_Hex(self)
  PyObject *self;
  { char buf[100];
    sprintf(buf, "0x%x", Counter_value(self));
    return PyString_FromString(buf);
  }

/* Convert them to integers if counters. */
static int
Counter_Coerce(v, w)
  PyObject **v, **w;
  { long i;

    *v = PyInt_FromLong(Counter_value(*v));
    if (object2int(*w, &i)) {
      *w = PyInt_FromLong(i);
    } else
      Py_INCREF(*w);
    return 0;
  }

static PyNumberMethods Counter_as_number = {
  0,                /* nb_add */
  0,                /* nb_subtract */
  0,                /* nb_multiply */
  0,                /* nb_divide */
  0,                /* nb_remainder */
  0,                /* nb_divmod */
  0,                /* nb_power */
  Counter_Neg,      /* nb_negative */
  Counter_Pos,      /* nb_positive */
  Counter_Abs,      /* nb_absolute */
  Counter_Nonzero,  /* nb_nonzero */
  Counter_Invert,   /* nb_invert */
  0,                /* nb_lshift */
  0,                /* nb_rshift */
  0,                /* nb_and */
  0,                /* nb_xor */
  0,                /* nb_or */
  Counter_Coerce,   /* nb_coerce */
  Counter_Int,      /* nb_int */
  Counter_Long,     /* nb_long */
  Counter_Float,    /* nb_float */
  Counter_Oct,      /* nb_oct */
  Counter_Hex,      /* nb_hex */
};

/* type methods */

static PyObject *
Counter_increment(self, args)
  PyObject *self, *args;
  { PyObject *result = NULL;
    long default_value = 1;

    if (PyArg_ParseTuple(args, "|i:incr", &default_value))
      if (Counter_value(self) + default_value < Counter_value(self))
        PyErr_SetString(counter_error, "overflow");
      else {
        Counter_value(self) += default_value;
        result = Py_None;
        Py_INCREF(result);
      }
    return result;
  }

static PyObject *
Counter_decrement(self, args)
  PyObject *self, *args;
  { PyObject *result = NULL;
    long default_value = 1;

    if (PyArg_ParseTuple(args, "|i:decr", &default_value))
      if (Counter_value(self) - default_value > Counter_value(self))
        PyErr_SetString(counter_error, "underflow");
      else {
        Counter_value(self) -= default_value;
        result = Py_None;
        Py_DECREF(result);
      }
    return result;
  }

/* Method table */
static PyMethodDef Counter_methods[] = {
  {"incr", Counter_increment, METH_VARARGS},
  {"decr", Counter_decrement, METH_VARARGS},
  {NULL, NULL},
};

/* Callback routines */

static PyObject *
Counter_GetAttr(self, attrname)
  PyObject *self;
  char *attrname;
  {
    return Py_FindMethod(Counter_methods, self, attrname);
  }

static PyObject *
Counter_Repr(self)
  PyObject *self;
  { PyObject *result = NULL;
    char buf[25];
    sprintf(buf, "%d", Counter_value(self));
    return PyString_FromString(buf);
  }

/* Type definition */
/* remember the forward declaration above, this is the real definition */
static PyTypeObject Counter_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,
  "counter",
  sizeof(Counter),
  0,
  (destructor)Counter_dealloc,
  0,
  (getattrfunc)Counter_GetAttr,
  0,
  0,
  (reprfunc)Counter_Repr,
  &Counter_as_number,
  /* the rest are NULLs */
};

/* Python constructor */

static PyObject *
Counter_new(self, args)
  PyObject *self, *args;
  { PyObject *result = NULL;
    long value = 0; /* default initial value */

    if (PyArg_ParseTuple(args, "|i", &value))
      result = Counter_NEW(value);
    return result;
  }

/* Module functions */

static PyMethodDef methods[] = {
  {"counter", Counter_new, METH_VARARGS},
  {NULL, NULL},
};

/* Module init function */

void initcounter()
  { PyObject *m, *d;

    m = Py_InitModule("counter", methods);
    d = PyModule_GetDict(m);

    /* initialize module variables/constants */

#if PYTHON_API_VERSION >= 1007
    counter_error = PyErr_NewException("counter.error", NULL, NULL);
#else
    counter_error = Py_BuildValue("s", "counter.error");
#endif
    PyDict_SetItemString(d, "error", counter_error);
  }
