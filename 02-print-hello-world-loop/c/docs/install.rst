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

En esta tarea se imprime por defecto 100 veces o el número de veces que le pasemos por comando. Por defecto sería::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/bin/
    ./hello_world02

Para ejecutar el programa con un número de veces determinado(por ejemplo 20)::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/bin/
    ./hello_world02 -t 20

Para mostrar la ayuda::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/bin/
    ./hello_world02 --help

En la ayuda veremos::
    Usage: hello_world02 [OPTION...]
    Hello World 02 -- a program with options and arguments using argp

    -t, --repeat=TIMES         Repeat execution 'Hello World'. Default
                                repeat=100
    -?, --help                 Give this help list
        --usage                Give a short usage message
    -V, --version              Print program version

    Mandatory or optional arguments to long options are also mandatory or optional
    for any corresponding short options.

    Report bugs to <cochoa@mulesol.es>.


