#ifndef HEXDIFF_H
#define HEXDIFF_H

/*
 *  Header file for hexdiff.c
 */

const char *argp_program_version = "Hexdiff v0.1";
const char *argp_program_bug_address = "curtis.li@nyu.edu";
static char doc[] = "Get the diff of binary files.";
static char args_doc[] = "FILE1 FILE2";
static struct argp_option options[] = {
  { "quiet", 'q', 0, 0, "Run in quiet mode."},
  { "recursive", 'r', 0, 0, "Run in recursive mode."},
  { "verbose", 'v', 0, 0, "Run in verbose mode."},
  { 0 }
};

struct arguments {
  char *arg1;
  char *arg2;
  char **args;
  int quiet, recursive, verbose;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state);
static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

#endif
