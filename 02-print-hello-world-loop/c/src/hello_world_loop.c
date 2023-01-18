/***********************************************************************
*       Second task: Print "Hello World loop in C
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <argp.h>

/***************************************************************************
 *              Constants
 ***************************************************************************/
#define LONGITUD_CADENA 1000

const char *argp_program_version =
  "Hello_word02_1.0.0";
const char *argp_program_bug_address =
  "<cochoa@mulesol.es>";

/* Program documentation. */
static char doc[] =
  "Hello World 02 -- a program with options and arguments using argp";

/* A description of the arguments we accept. */
static char args_doc[] = "ARG1";

/* The options */
static struct argp_option options[] = {
	{"verbose",  'v', 0,      0,  "Produce verbose output" },
	{"quiet",    'q', 0,      0,  "Don't produce any output" },
	{"silent",   's', 0,      OPTION_ALIAS },
	{ 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
	char *args[1];                /* arg1 */
	int silent, verbose;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
	struct arguments *arguments = state->input;

	switch (key)
	{
		case 'q': case 's':
			arguments->silent = 1;
			break;

		case 'v':
			arguments->verbose = 1;
			break;

		case ARGP_KEY_ARG:
			if (state->arg_num >= 1)
			/* Too many arguments. */
			argp_usage (state);
			arguments->args[state->arg_num] = arg;
			break;

		case ARGP_KEY_END:
			if (state->arg_num < 1)
			/* Not enough arguments. */
			argp_usage (state);
			break;

		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

/* Devuelve "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b) {
	return
		(double)(a->tv_sec + (double)a->tv_usec/1000000) -
		(double)(b->tv_sec + (double)b->tv_usec/1000000);
}

/***************************************************************************
 *              Para verificar que es un entero
 ***************************************************************************/
int esEnteroValido(char cadena[LONGITUD_CADENA]) {
	int longitud = strlen(cadena);

	/* Quitar espacios, saltos de línea, etcétera*/
	while (longitud > 0 && isspace(cadena[longitud - 1]))
		longitud--;

	if (longitud <= 0) {
		return 0;
	}

	int i;

	for (i = 0; i < longitud; ++i) {
		/* En caso de que sea un guión, y que no esté al inicio, no es válido */
		if (cadena[i] == '-' && i > 0) {
			return 0;
		}

		/* Si no es dígito, tampoco es válido */
		if (!isdigit(cadena[i]) && cadena[i] != '-') {
			return 0;
		}
	}
	return 1;
}

/***************************************************************************
 *              main
 ***************************************************************************/

int main(int argc, char *argv[])
{
	struct arguments arguments;

	struct timeval t_ini, t_fin;
	double seconds;

	gettimeofday(&t_ini, NULL);

	int count_loop;

	/* Default values. */
	arguments.silent = 0;
	arguments.verbose = 0;

	/* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
	argp_parse (&argp, argc, argv, 0, 0, &arguments);

	printf ("ARG1 = %s\n"
		"VERBOSE = %s\nSILENT = %s\n",
		arguments.args[0],
		arguments.verbose ? "yes" : "no",
		arguments.silent ? "yes" : "no");

// 	if(argc < 2) { TODO No tiene sentido ahora la opción por defecto. Se pasa siempre un argunmento
// 		count_loop=100;
// 	} else {
	if(esEnteroValido(argv[1]) ) {
		count_loop = atoi(argv[1]);
	} else {
		printf("Numbers only\n");
		return 1;
	}

	for(int i=0; i <= count_loop; i++) {
		printf("%d Hello World\n", i);
	};

	gettimeofday(&t_fin, NULL);

	seconds = timeval_diff(&t_fin, &t_ini);
	printf("\n Spent time: %f s. to print %d times \n\n",seconds, (count_loop));

	return 0;
}
