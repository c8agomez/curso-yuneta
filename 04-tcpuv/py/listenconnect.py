#!/usr/bin/env python
import argparse
import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 7000
BUFFER_SIZE = 1024


try:
   from . import __version__
except:  # pragma: no cover
   __version__ = '0.0.0'

##########################
#       Main
##########################
def main():
    # Variables
    TCP_IP = '127.0.0.1'
    TCP_PORT = 7000
    BUFFER_SIZE = 1024

    #  Parse arguments
    parser = argparse.ArgumentParser(
        description=" Program that connect to a tcp port and send data"
    )
    parser.version = 'listenconnect_1.0.0'

    group1 = parser.add_argument_group('options for execution')
    group1.add_argument(
        "-p",
        "--port",
        help="define port to use (default port=7000)",
        type=int,
        default=TCP_PORT
    )
    group1.add_argument(
        "-i",
        "--ip",
        help="define ip to use (default ip=127.0.0.1)",
        type=str,
        default=TCP_IP
    )
    group1.add_argument(
        "MESSAGE",
        help="MESSAGE to send",
        type=str
    )

    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=__version__,
        help="Version del programa"
    )

    args = parser.parse_args()

    if args.port:
        TCP_PORT = args.port
    if args.ip:
        TCP_IP= args.ip
    listenconnect(TCP_PORT, TCP_IP, args.MESSAGE)

##########################
#      Conection
##########################
def listenconnect(TCP_PORT, TCP_IP, MESSAGE):

    # Socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect
    s.connect((TCP_IP, TCP_PORT))

    # Send data
    s.sendall(MESSAGE.encode())

    # Close the socket
    s.close()

##########################
# main
##########################
if __name__ == "__main__":
    main()
