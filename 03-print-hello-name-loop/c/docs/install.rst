Proceso instalación
===================

Si es la primera instalación y no existe el directorio build entonces lo creamos con los comandos::

    cd /home/yuneta/curso-yuneta/02-print-hello-world/c
    mkdir build

Dentro de build::

    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make clean
    make install

Para ejecutar el programa por defecto::

    cd /home/yuneta/curso-yuneta/bin/
    ./hello_world02

Para ejecutar el programa con un número de veces determinado(por ejemplo 20)::

    cd /home/yuneta/curso-yuneta/bin/
    ./hello_world02 20

