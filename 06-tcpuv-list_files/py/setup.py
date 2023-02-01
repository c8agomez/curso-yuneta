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

setup(
    name='listenconnect',
    version="1.0.0",
    description='Listen in a tcp port and send file',
    author='c8agomez',
    author_email='carlos8agomez@gmail.com',
    packages=find_packages(),
    install_requires= [],
    tests_require=[],
    entry_points={
        'console_scripts': [
            'listenconnect = listenconnect:main'
        ]
    },
)
