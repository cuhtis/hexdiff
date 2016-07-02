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
  struct arguments arguments;
  arguments.quiet = 0;
  arguments.recursive = 0;
  arguments.verbose = 0;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);
}


static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;
  switch (key) {
    case 'q':
      arguments->quiet = 1;
      arguments->verbose = 0;
      break;
    case 'r':
      arguments->recursive = 1;
      break;
    case 'v':
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
