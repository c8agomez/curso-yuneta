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
        description=" Program that connect to a tcp port and send file."
    )
    parser.version = 'listenconnect_1.0.0'

    group1 = parser.add_argument_group('options for execution')
    group1.add_argument(
        "-p",
        "--port",
        help="Define port to use (default port=7000)",
        type=int,
        default=TCP_PORT
    )
    group1.add_argument(
        "-i",
        "--ip",
        help="Define ip to use (default ip=127.0.0.1)",
        type=str,
        default=TCP_IP
    )
    group1.add_argument(
        "FILES",
        help="List of files or file to send.(Example:file1.txt file2.txt file3.txt or file1.txt) ",
        nargs='+',
        type=str
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

    listenconnect(TCP_PORT, TCP_IP, args.FILES)

##########################
#      Conection
##########################
def listenconnect(port, ip, FILES):

    # Create a socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    s.connect((ip, port))

    # open list files to be sent
    for i, filepath in enumerate(FILES):

        if filepath !=  "":
            print("Send: ", filepath)

            try:
                # open the file to be sent and send
                with open(filepath, 'rb') as f:
                    file_data = (filepath+'\0').encode() + f.read()
                    s.sendall(file_data)
                # receive confirmation
                if(i < len(FILES)):
                    confirmation = s.recv(1024)

            except FileNotFoundError:
                print("The file is not found\n")

    # close the socket and file
    s.close()

##########################
# main
##########################
if __name__ == "__main__":
    main()
