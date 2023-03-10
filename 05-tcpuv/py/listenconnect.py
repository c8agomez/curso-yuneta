#!/usr/bin/env python3
import argparse
import socket
import os

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
        description=" Program that connect to a tcp port and send file."
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
        help="File content to send",
        type=str
    )

    parser.add_argument(
        "--repeat",
        type=int,
        default=2,
        help="Number of times to repeat the file to send")

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

    listenconnect(TCP_PORT, TCP_IP, args.FILE, args.repeat)

##########################
#      Conection
##########################
def listenconnect(TCP_PORT, TCP_IP, FILE,repeat):
    for i in range(repeat):
        # Socket object
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect
        s.connect((TCP_IP, TCP_PORT))

        # Get the local address of the socket
        local_name = s.getsockname()
        print("Local socket name:", local_name)

        # Get the remote address of the socket
        peer_name = s.getpeername()
        print("Remote address:", peer_name)

        # Fichero a enviar
        print("Send file:", FILE)

        file_name_len = len(FILE)
        # Send the bytes to the remote endpoint
        s.sendall(file_name_len.to_bytes(4, byteorder='big'))

        # Env??a longitud fichero
        file_size = os.path.getsize(FILE)
        print("file_size:", file_size)
        s.sendall(file_size.to_bytes(4, byteorder='big'))

        s.sendall(FILE.encode())

        with open(FILE, 'rb') as f:
            s.sendall(f.read())
        # Close the socket
        s.close()

##########################
# main
##########################
if __name__ == "__main__":
    main()
