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

En esta tarea se exige poner nombre además de la repetición por defecto que es 100 o el número de veces que nosotros le pasemos. Por tanto sería::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/bin/
    ./hello_world03 Carlos

Para ejecutar el programa con un número de veces determinado(por ejemplo 20) y el nombre que es obligatorio::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/bin/
    ./hello_world03 -t 20 Carlos

Para mostrar la ayuda::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/bin/
    ./hello_world03 --help

En la ayuda veremos::

    Usage: hello_world03 [OPTION...] ARG1
    Hello name 03 -- a program with options and arguments using argp. Greets the
    name you enter n times

    Options:
    -t, --repeat=TIMES         Repeat execution 'Hello Name!'. Default
                            repeat=100

    -?, --help                 Give this help list
    --usage                Give a short usage message
    -V, --version              Print program version

    Mandatory or optional arguments to long options are also mandatory or optional
    for any corresponding short options.

    Report bugs to <cochoa@mulesol.es>.



