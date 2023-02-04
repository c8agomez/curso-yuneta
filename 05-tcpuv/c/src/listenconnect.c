#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <fcntl.h>

uv_tcp_t server;
uv_loop_t *loop;


/***************************************************************************
 *      Structures
 ***************************************************************************/
#define MIN_ARGS 0
#define MAX_ARGS 0

struct arguments
{
    char *args[MAX_ARGS + 1]; /* positional args */
    int port;
    char *ip;
};

const char *argp_program_version =
    "listenconnect_1.0.0";

const char *argp_program_bug_address =
    "<cochoa@mulesol.es>";

static error_t parse_opt (int key, char *arg, struct argp_state *state);

/***************************************************************************
 *      Data
 ***************************************************************************/
/* Program documentation. */
static char doc[] =
    "Listen in a tcp port and receive data using libuv library.";

/* A description of the arguments we accept. */
static char args_doc[] = "";

static struct argp_option options[] = {
    {0, 0, 0, 0, "Options:"},
    {"port", 'p', "PORT", 0, "Set port to listen.(default: 7000)", 1},
    {"ip", 'i', "IP", 0, "Set ip to listen.(default: 127.0.0.1)", 1},
    {0},
};

/* Our argp parser. */
static struct argp argp = {
    options,
    parse_opt,
    args_doc,
    doc,
};

/********************************************************************
 *  Parse a single option
 ********************************************************************/
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    /*
     *  Get the input argument from argp_parse,
     *  which we know is a pointer to our arguments structure.
     */
    struct arguments *arguments = state->input;

    switch(key) {
        case 'p':
            if(arg) {
                arguments->port = atoi(arg);
            }
            break;
        case 'i':
            if(arg) {
                arguments->ip = arg;
            }
            break;

        case ARGP_KEY_ARG:
            if(state->arg_num >= MAX_ARGS) {
                /* Too many arguments. */
                argp_usage(state);
            }
            arguments->args[state->arg_num] = arg;
            break;

        case ARGP_KEY_END:
            if(state->arg_num < MIN_ARGS) {
                /* Not enough arguments. */
                argp_usage(state);
            }
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/*****************************************************************
 *  Close
 *****************************************************************/
void on_close(uv_handle_t* handle) {
    free(handle);
}

/*******************************************************************
 *  Read data
 *******************************************************************/
void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    static int file_name_len = 0;
    static int file_len = 0;
    static char file_name[100];

    if(nread == UV_EOF) {
        /* El final de los datos se ha alcanzado */
        uv_read_stop(client);
        return;
    }

    if(nread < 0) {
        if(nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t *)client, NULL);
        return;
    }

    if(nread > 0) {

        if(file_name_len == 0) {
            memcpy(&file_name_len, buf->base, 4);
            file_name_len = ntohl(file_name_len);
            memcpy(file_name, buf->base + 4, file_name_len);
            file_name[file_name_len] = '\0';
            /* Verificacion de existencia de archivo*/
            if(access(file_name, F_OK) == 0) {
                printf("File %s exists. \n", file_name);
                /* Send Confirmation. */
                uv_write_t *req = malloc(sizeof(uv_write_t));
                uv_buf_t buf = uv_buf_init("createError\n", 13);
                uv_write(req, (uv_stream_t *)client, &buf, 1, NULL);
                file_name_len = 0;
                file_len = 0;
            } else {
                printf("El archivo %s no existe\n", file_name);
                uv_write_t *req = malloc(sizeof(uv_write_t));
                uv_buf_t buf = uv_buf_init("createOK\n", 8);
                uv_write(req, (uv_stream_t *)client, &buf, 1, NULL);
            }
        } else if(file_len == 0) {
            memcpy(&file_len, buf->base, 4);
            file_len = ntohl(file_len);
        }

        if(file_len != 0) {
            FILE *file = fopen(file_name, "a");
            fwrite(buf->base, 1, nread, file);
            fclose(file);
        }

        if(file_len != 0 && buf->len > nread) {
            printf("File receive: %s\n", file_name);

            /* Send Confirmation. */
            uv_write_t *req = malloc(sizeof(uv_write_t));
            uv_buf_t buf = uv_buf_init("OK\n", 4);
            uv_write(req, (uv_stream_t *)client, &buf, 1, NULL);
            /* Clean up */
            file_name_len = 0;
            file_len = 0;
        }
    }
    free(buf->base);
}

/*****************************************************************
 *  alloc buffer
 *****************************************************************/
void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    char *base;
    base = (char *)calloc(1, suggested_size);
    if(!base)
        *buf = uv_buf_init(NULL, 0);
    else
        *buf = uv_buf_init(base, suggested_size);
}

/*****************************************************************
 *  Get peername and socketname
 *****************************************************************/
void get_peer_and_sock(uv_tcp_t *client)
{
    struct sockaddr_in peer_addr, sock_addr;
    int peer_addr_len = sizeof(peer_addr);
    int sock_addr_len = sizeof(sock_addr);
    char peer_ip[INET_ADDRSTRLEN];
    char sock_ip[INET_ADDRSTRLEN];

    uv_tcp_getpeername(client, (struct sockaddr*) &peer_addr, &peer_addr_len);
    uv_tcp_getsockname(client, (struct sockaddr*) &sock_addr, &sock_addr_len);

    /*Remote*/
    uv_ip4_name(&peer_addr, peer_ip, sizeof(peer_ip));
    printf("Remote IP: %s\n", peer_ip);
    printf("Remote Port: %d\n", ntohs(peer_addr.sin_port));

    /*Local*/
    uv_ip4_name(&sock_addr, sock_ip, sizeof(sock_ip));
    printf("Local IP: %s\n", sock_ip);
    printf("Local Port: %d\n", ntohs(sock_addr.sin_port));
}

/*****************************************************************
 *  Conection
 *****************************************************************/
void on_connect(uv_stream_t *server, int status)
{
    if(status < 0) {
        fprintf(stderr, "Connect error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);

    if(uv_accept(server, (uv_stream_t *)client) == 0) {
        get_peer_and_sock(client);
        uv_read_start((uv_stream_t *)client, alloc_buffer, on_read);
    } else {
        uv_close((uv_handle_t *)client, on_close);
    }
}

/*****************************************************************
 *                      Main
 *****************************************************************/
int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    struct arguments arguments;

    /*Default values*/
    memset(&arguments, 0, sizeof(arguments));
    arguments.port = 7000;
    arguments.ip = "127.0.0.1";

    /*Parse arguments*/
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    uv_ip4_addr(arguments.ip, arguments.port, &addr);

    uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
    int r = uv_listen((uv_stream_t *)&server, 128, on_connect);
    if(r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}
