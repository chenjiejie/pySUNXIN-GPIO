from distutils.core import setup, Extension

setup(
    name                = 'pySUNXI',
    version             = '1.0',
    author              = 'cjiejie',
    author_email        = 'cjiejie1993@gmail.com',
    description         = 'reaning form pySUNXI-0.1.12',
    ext_modules         = [Extension('SUNXI_GPIO', ['source/gpio_lib.c', 'source/pysunxi.c'])],
    package_dir={'': 'source'},
    packages=[''],                          
)
