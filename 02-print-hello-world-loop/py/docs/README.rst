Proceso
=======

En esta tarea se imprime por defecto 100 veces o el número de veces que le pasemos por comando.
Por defecto sería::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/02-print-hello-world-loop/python/src
    ./hello_world_loop_02.py

Para ejecutar el programa con un número de veces determinado(por ejemplo 20)::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/02-print-hello-world-loop/python/src
    ./hello_world_loop_02.py -r 20

Para mostrar la ayuda con --help o -h::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/02-print-hello-world-loop/python/src
    ./hello_world_loop_02.py --help

En la ayuda veremos::
    usage: hello_world_loop_02.py [-h] [-r REPEAT] [-v]

    Hello world loop

    options:
    -h, --help            show this help message and exit
    -r REPEAT, --repeat REPEAT
                            N times repeat Hello world. (Default=100)
    -v, --version         Version del programa

