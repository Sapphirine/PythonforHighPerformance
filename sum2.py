import ctypes

_sum2 = ctypes.CDLL('libsum.so')
_sum2.our_function.argtypes = (ctypes.c_int, ctypes.POINTER(ctypes.c_int))

def our_function(numbers):
    global _sum2
    num_numbers = len(numbers)
    array_type = ctypes.c_int * num_numbers
    result = _sum2.our_function(ctypes.c_int(num_numbers), array_type(*numbers))
    return int(result)
