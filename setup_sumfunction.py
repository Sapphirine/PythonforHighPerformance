from distutils.core import setup, Extension

name = "sumfunction"      # name of the module
version = "1.0"  # the module's version number

setup(name=name, version=version,
      ext_modules=[Extension(name='_sumfunction',
                             sources=["sumfunction.i", "sumfunction.c"],
    ])
