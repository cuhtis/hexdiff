/*
 *  Command line parser functions
 *  Written by Curtis Li
 */

#include <stdlib.h>
#include <argp.h>
#include "parsecli.h"

const char *argp_program_version = "Hexdiff v0.1";
const char *argp_program_bug_address = "curtis.li@nyu.edu";

void parseCli(struct arguments *arguments, int argc, char **argv) {
  arguments->format = DEFAULT_FORMAT;
  arguments->match = false;
  arguments->quiet = false;
  arguments->recursive = false;
  arguments->simple = false;
  arguments->verbose = false;

  argp_parse(&argp, argc, argv, 0, 0, arguments);
}

error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments =  (struct arguments *) state->input;
  switch (key) {
    case ARG_KEY_FORMAT:
      arguments->format = arg ? atoi(arg) : DEFAULT_FORMAT;
      break;
    case ARG_KEY_MATCH:
      arguments->match = true;
      break;
    case ARG_KEY_QUIET:
      arguments->quiet = true;
      arguments->verbose = false;
      break;
    case ARG_KEY_RECURSIVE:
      arguments->recursive = true;
      break;
    case ARG_KEY_SIMPLE:
      arguments->simple = true;
      break;
    case ARG_KEY_VERBOSE:
      arguments->quiet = false;
      arguments->verbose = true;
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
