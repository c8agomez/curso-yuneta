/***********************************************************************
*       Third task: Print "Hello Name loop in C
***********************************************************************/
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <argp.h>

/***************************************************************************
 *              Constants
 ***************************************************************************/
#define MIN_ARGS 1
#define MAX_ARGS 1

/* Used by main to communicate with parse_opt. */
struct arguments
{
    char *args[MAX_ARGS + 1];
    int silent, verbose, repeat;
};

const char *argp_program_version =
    "Hello_word03_1.0.0";

const char *argp_program_bug_address =
    "<cochoa@mulesol.es>";

static error_t parse_opt (int key, char *arg, struct argp_state *state);

/* Program documentation. */
static char doc[] =
    "Hello name 03 -- a program with options and arguments using argp. Greets the name you enter n times";

/* A description of the arguments we accept. */
static char args_doc[] = "NAME";  /*Nombre que vamos a pasar*/

/* The options */
static struct argp_option options[] = {
    {0, 0, 0, 0, "Options:"},
    {"repeat",    't', "TIMES",   0,  "Repeat execution 'Hello Name!'. Default repeat=100", 1},
    { 0 }
};

/* Our argp parser. */
static struct argp argp = {
    options,
    parse_opt,
    args_doc,
    doc
};

/***************************************************************************
 *              Parse a single option
 ***************************************************************************/
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    /*
    * Get the input argument from argp_parse, which we
    * know is a pointer to our arguments structure.
    */
    struct arguments *arguments = state->input;

    switch (key)
    {
    case 't':
        if(arg) {
            arguments->repeat = atoi(arg);
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

/***************************************************************************
 *              Diferencia (a-b) entre dos tiempos en segundos
 ***************************************************************************/
double timeval_diff(struct timeval *a, struct timeval *b) {
        return
        (double)(a->tv_sec + (double)a->tv_usec/1000000) -
        (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

/***************************************************************************
 *                      Loop
 ***************************************************************************/
static inline void make_loop(int count_loop, char *name)
{
    double seconds;

    struct timeval t_ini, t_fin;

    gettimeofday(&t_ini, NULL);

    for(int i=1; i <= count_loop; i++) {
        printf("Hello %s!\n", name);
    };

    gettimeofday(&t_fin, NULL);

    seconds = timeval_diff(&t_fin, &t_ini);
    printf("\n Spent time: %f s. to print %d repeat \n\n",seconds, (count_loop));
}

/***************************************************************************
 *              Main
 ***************************************************************************/
int main(int argc, char *argv[])
{
    struct arguments arguments;

    memset(&arguments, 0, sizeof(arguments));
    arguments.repeat=100;

    /* Parse our arguments; every option seen by parse_opt will
    be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    make_loop(arguments.repeat,arguments.args[0]);

    return 0;
}
