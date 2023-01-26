# -*- encoding: utf-8 -*-

import os
import sys

from setuptools import setup, find_packages
from os.path import exists

if sys.version_info[:2] < (3, 5):
   raise RuntimeError('Requires Python 3.5 or better')

here = os.path.abspath(os.path.dirname(__file__))
try:
    README = open(os.path.join(here, 'README.rst')).read()
    CHANGES = open(os.path.join(here, 'CHANGES.txt')).read()
except IOError:
    README = CHANGES = ''

from web_skeleton3 import __version__

setup(
    name='hello_world_loop_02',
    version="1.0.0",
    description='N times repeat Hello world. (Default=100)',
    author='c8agomez',
    author_email='carlos8agomez@gmail.com',
    url='https://github.com/c8agomez/curso-yuneta/tree/main/02-print-hello-world-loop/python',
    packages=find_packages(),
    install_requires= [],
    tests_require=[],
    entry_points={
        'console_scripts': [
            'hello_world_loop_02 = hello_world_loop_02.__main__:main'
        ]
    },
)
