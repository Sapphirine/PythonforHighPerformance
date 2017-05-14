from ctypes import *
sumfunction_lib = CDLL('./sumfunction.so')

sumfunction_lib.sum1.restype = c_double
s = sumfunction_lib.sum1(c_double(1), c_double(3.14159))
print(s, type(s))

#Convert arguments from Python to Ctypes
sumfunction_lib.sum1.argtypes = [c_double, c_double]
s = sumfunction_lib.sum1(1, 3.14159)
print(s, type(s))

sumfunction_lib.sum2.argtypes = [c_double, c_double]
sumfunction_lib.sum2(1, 3.14159)
