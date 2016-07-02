/*
 *  Main file
 *  Written by Curtis Li
 */

#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>

#include "hexdiff.h"

/**************************************************
 *                                                *
 *    Functions                                   *
 *                                                *
 **************************************************/

/*
 *  Main function
 */
int main(int argc, char** argv) {
  FILE *f1, *f2;
  struct arguments arguments;

  arguments.quiet = 0;
  arguments.recursive = 0;
  arguments.verbose = 0;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  f1 = fopen(arguments.arg1, "r");
  f2 = fopen(arguments.arg2, "r");
  
  fclose(f1);
  fclose(f2);
}


static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments =  (struct arguments *) state->input;
  switch (key) {
    case ARG_KEY_QUIET:
      arguments->quiet = 1;
      arguments->verbose = 0;
      break;
    case ARG_KEY_RECURSIVE:
      arguments->recursive = 1;
      break;
    case ARG_KEY_VERBOSE:
      arguments->quiet = 0;
      arguments->verbose = 1;
      break;
    case ARGP_KEY_ARG:
      if (!arguments->arg1) {
        arguments->arg1 = arg;
      } else if (!arguments->arg2) {
        arguments->arg2 = arg;
      }
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 2) {
        argp_usage(state);
      }
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
