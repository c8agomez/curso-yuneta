#!/usr/bin/env python3

#----------------------------------------------------------------#
#  Hello world loop 02
#----------------------------------------------------------------#
version = "1.0.0"

#---------------------------------------#
#       Code
#---------------------------------------#
import time
import argparse

#-----------------------------------------------#
# Mide tiempo
#-----------------------------------------------#
def mide_tiempo(funcion):
    def funcion_medida(*args, **kwargs):
        inicio = time.time()
        c = funcion(*args, **kwargs)
        elapsed_time=time.time()-inicio
        print("Spent time: %.10f s. to print" % elapsed_time)
        return c
    return funcion_medida

#-----------------------------------------------#
# Hello loop con parámetro
#-----------------------------------------------#
@mide_tiempo
def hello_loop_t(repeat):
    repeat=int(repeat)
    for x in range(1,repeat+1):
        print(x ,'Hello World')

#-----------------------------------------------#
# Hello loop default
#-----------------------------------------------#
@mide_tiempo
def hello_loop_d():
    num=100
    for x in range(1,num+1):
        print(x ,'Hello World')



#-----------------------------------------------#
#   Main
#-----------------------------------------------#
if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description="Hello world loop"
    )
    parser.version = 'Hello_word02_1.0.0'

    parser.add_argument(
        '-r',
        '--repeat',
        help="N times repeat Hello world. (Default=100)"
    )

    parser.add_argument(
        '-v',
        '--version',
        action='version',
        help="Version del programa"
    )

    args = parser.parse_args()

    if not args.repeat:
        hello_loop_d()

    else:
        hello_loop_t(
            repeat=args.repeat,
        )
