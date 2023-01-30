#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

uv_tcp_t server;
uv_loop_t *loop;


/***************************************************************************
 *      Structures
 ***************************************************************************/

/*
 *  Used by main to communicate with parse_opt.
 */
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
    if(nread < 0) {
        if(nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t *)client, on_close);
        free(buf->base);
        return;
    }

    if (nread > 0) {
    // Do something with the received data
    printf("Received %ld bytes of data: %s\n", nread, buf->base);
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
