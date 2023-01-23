Proceso
=======
La primera vez tendremos que tener instalado la dependencia commander:

    npm i commander


En esta tarea se imprime por defecto 100 veces o el número de veces que le pasemos por comando. Por defecto sería::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/02-print-hello-world-loop/javascript/src
    node hello_world_loop_02.js

Para ejecutar el programa con un número de veces determinado(por ejemplo 20)::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/02-print-hello-world-loop/javascript/src
    node hello_world_loop_02.js -r 20

Para mostrar la ayuda con --help o -h::

    cd /yuneta/development/projects/curso-yuneta/carlos-ochoa/02-print-hello-world-loop/javascript/src
    node hello_world_loop_02.js --help

En la ayuda veremos::

        Usage: string-util [-h] [-v] [-r REPEAT]

        Hello world loop

        Options:
        -V, --version          output the version number
        -r, --repeat <REPEAT>  N times repeat "Hello world". (Default=100
        -h, --help             display help for command




