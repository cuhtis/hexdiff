/*
 *  Main file
 *  Written by Curtis Li
 */

#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "hexdiff.h"

/**************************************************
 *                                                *
 *    Functions                                   *
 *                                                *
 **************************************************/

using namespace std;

/*
 *  Main function
 */
int main(int argc, char** argv) {
  struct arguments arguments;

  arguments.quiet = 0;
  arguments.recursive = 0;
  arguments.verbose = 0;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  ifstream f1, f2;
  f1.open(arguments.arg1, ios::in | ios::binary);
  f2.open(arguments.arg2, ios::in | ios::binary);

  cout << "SIZE1: " << getSize(&f1) << endl;
  cout << "SIZE2: " << getSize(&f2) << endl;
  
  vector<vector<int> > lookup = vector<vector<int> >(getSize(&f1), vector<int>(getSize(&f2)));;
  
  int max = gcs(&lookup, &f1, &f2);
  printf("MAX: %d\n", max);

  for (int i = 0; i < lookup.size(); i++) {
    for (int j = 0; j < lookup[i].size(); j++) {
      cout << lookup[i][j] << " ";
    }
    cout << endl;
  }

  f1.close();
  f2.close();
}


size_t getSize(ifstream *str) {
  int pos = str->tellg();
  str->seekg(0, str->end);
  size_t size = str->tellg();
  str->seekg(pos);
  return size;
}

int gcs(vector< vector<int> > *lookup, ifstream *f1, ifstream *f2) {
  // Get iteration case
  int i = f1->tellg();
  int j = f2->tellg();

  // Base case
  char c1, c2;
  if (!f1->get(c1) || !f2->get(c2)) {
    return 0;
  }

  // Fetch memoized results
  assert(i < lookup->size() && j < (*lookup)[i].size());
  if ((*lookup)[i][j] != 0) {
    return (*lookup)[i][j];
  }

  // Match
  if (c1 == c2) {
    (*lookup)[i][j] = 1 + gcs(lookup, f1, f2);
    return (*lookup)[i][j];
  }

  // Branch and return max
  f1->clear();
  f1->seekg(i, f1->beg);
  f2->clear();
  f2->seekg(j+1, f2->beg);
  int a = gcs(lookup, f1, f2);

  f1->clear();
  f1->seekg(i+1, f1->beg);
  f2->clear();
  f2->seekg(j, f2->beg);
  int b = gcs(lookup, f1, f2);

  (*lookup)[i][j] = a > b ? a : b;
  return a > b ? a : b;
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
