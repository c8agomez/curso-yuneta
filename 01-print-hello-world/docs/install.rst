Proceso instalación
===================

Si es la primera instalación y no existe el directorio build entonces lo creamos con los comandos::

    cd /home/yuneta/curso-yuneta/01-print-hello-world/
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make install

Para ejecutar el programa::

    cd /home/yuneta/curso-yuneta/01-print-hello-world/build/
    ./hello_world




