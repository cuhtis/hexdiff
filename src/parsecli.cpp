/*
 *  Command line parser functions
 *  Written by Curtis Li
 */

#include <argp.h>
#include "parsecli.h"

const char *argp_program_version = "Hexdiff v0.1";
const char *argp_program_bug_address = "curtis.li@nyu.edu";

void parseCli(struct arguments *arguments, int argc, char **argv) {
  arguments->quiet = 0;
  arguments->recursive = 0;
  arguments->verbose = 0;

  argp_parse(&argp, argc, argv, 0, 0, arguments);
}

error_t parse_opt(int key, char *arg, struct argp_state *state) {
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
