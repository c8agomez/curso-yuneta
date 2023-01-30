#!/usr/bin/env python
import argparse
import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 7000
BUFFER_SIZE = 1024

version = "1.0.0"

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
        "FILE",
        help="File content to send"
    )

    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=version,
        help="Version del programa"
    )

    args = parser.parse_args()

    if args.port:
        TCP_PORT = args.port
    if args.ip:
        TCP_IP= args.ip

    # Fichero
    with open(args.FILE, "rb") as f:
        file_content = f.read()

    listenconnect(TCP_PORT, TCP_IP, file_content)

##########################
#      Conection
##########################
def listenconnect(TCP_PORT, TCP_IP, file_content):
    # Socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect
    s.connect((TCP_IP, TCP_PORT))

    # Send data
    s.sendall(file_content)

    # Close the socket
    s.close()

##########################
# main
##########################
if __name__ == "__main__":
    main()
