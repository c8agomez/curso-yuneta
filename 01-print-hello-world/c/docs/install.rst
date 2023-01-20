Proceso instalación
===================

Si es la primera instalación y no existe el directorio build entonces lo creamos con los comandos::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa
    mkdir build

Dentro de build::

    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make clean
    make install

En esta tarea se imprime Hello World in C::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/bin/
    ./hello_world01
