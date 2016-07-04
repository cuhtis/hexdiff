#ifndef HEXDIFF_H
#define HEXDIFF_H

/*
 *  Header file for hexdiff.c
 */
#include <iostream>
#include <iomanip>
#include <vector>

#define ARG_KEY_QUIET     'q'
#define ARG_KEY_RECURSIVE 'r'
#define ARG_KEY_VERBOSE   'v'

#define RED "\033[31m"
#define GREEN "\033[32m"
#define END "\033[0m"

const char *argp_program_version = "Hexdiff v0.1";
const char *argp_program_bug_address = "curtis.li@nyu.edu";
static char doc[] = "Get the diff of binary files.";
static char args_doc[] = "FILE1 FILE2";
static struct argp_option options[] = {
  { "quiet", ARG_KEY_QUIET, 0, 0, "Run in quiet mode."},
  { "recursive", ARG_KEY_RECURSIVE, 0, 0, "Run in recursive mode."},
  { "verbose", ARG_KEY_VERBOSE, 0, 0, "Run in verbose mode."},
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

struct HexCharStruct {
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs) {
  return (o << std::hex << std::setw(2) << (int)hs.c << std::setfill('0'));
}

inline HexCharStruct hex(unsigned char _c) {
  return HexCharStruct(_c);
}

size_t getSize(std::ifstream *str);

int gcs(std::vector< std::vector<int> > *lookup, std::ifstream *f1, std::ifstream *f2);
void gcsSol(std::vector< std::vector<int> > *lookup, std::ifstream *f1, std::ifstream *f2);

#endif
