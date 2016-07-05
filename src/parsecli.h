#ifndef PARSECLI_H
#define PARSECLI_H

/*
 *  Header file for parsecli.cpp
 */

#include <argp.h>

#define ARG_KEY_FORMAT    'f'
#define ARG_KEY_MATCH     'm'
#define ARG_KEY_QUIET     'q'
#define ARG_KEY_RECURSIVE 'r'
#define ARG_KEY_SIMPLE    's'
#define ARG_KEY_VERBOSE   'v'

#define DEFAULT_FORMAT    16

extern const char *argp_program_version;
extern const char *argp_program_bug_address;
static char doc[] = "Get the diff of binary files.";
static char args_doc[] = "FILE1 FILE2";
static struct argp_option options[] = {
  { "format", ARG_KEY_FORMAT, "BYTES", 0, "Number of bytes to display per row (Default: 16)."},
  { "match", ARG_KEY_MATCH, 0, 0, "Show the matching bytes."},
  { "quiet", ARG_KEY_QUIET, 0, 0, "Run in quiet mode."},
  { "recursive", ARG_KEY_RECURSIVE, 0, 0, "Run in recursive mode."},
  { "simple", ARG_KEY_SIMPLE, 0, 0, "Show only the number of bytes different."},
  { "verbose", ARG_KEY_VERBOSE, 0, 0, "Run in verbose mode."},
  { 0 }
};

struct arguments {
  char *arg1, *arg2;
  char **args;
  bool match, quiet, recursive, simple, verbose;
  int format;
};

void parseCli(struct arguments *arguments, int argc, char **argv);
error_t parse_opt(int key, char *arg, struct argp_state *state);
static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

#endif

