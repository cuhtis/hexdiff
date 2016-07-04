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

#define DEBUG(a) 

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

  vector<vector<int> > lookup = vector<vector<int> >(getSize(&f1), vector<int>(getSize(&f2)));;
  
  f1.clear();
  f1.seekg(0, f1.beg);
  f2.clear();
  f2.seekg(0, f2.beg);
  gcsSol(&lookup, &f1, &f2);
  
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


void gcsSol(vector< vector<int> > *lookup, ifstream *f1, ifstream *f2) {
  // Get iteration case
  int i = f1->tellg();
  int j = f2->tellg();
  char c1, c2;
  DEBUG(cout << i << "-" << j << ": ");

  if (!f1->get(c1) || !f2->get(c2)) {
    DEBUG(cout << "ERROR" << endl);
    return;
  }

  // Char match
  DEBUG(cout << c1 << "-" << c2 << ": ");
  if (c1 == c2) { 
    DEBUG(cout << "MATCH" << endl);
    cout << hex(c1) << ": " << c1 << endl;
    gcsSol(lookup, f1, f2);
    return;
  }
  
  // Bounds checking if we hit the limit
  bool b1 = i + 1 >= lookup->size();
  bool b2 = j + 1 >= (*lookup)[i].size();
  if (b1 || b2) {
    if (b1 && b2) {
      DEBUG(cout << lookup->size() << " " << (*lookup)[i].size() << ": ");
      DEBUG(cout << "BASE" << endl);
      return;
    } else if (b1) {
      DEBUG(cout << "BASE RIGHT" << endl);
      cout << RED << hex(c1) << ": " << c2 << END << endl;
      f1->clear();
      f1->seekg(i);
    } else if (b2) {
      DEBUG(cout << "BASE DOWN" << endl);
      cout << GREEN << hex(c1) << ": " << c1 << END << endl;
      f2->clear();
      f2->seekg(j);
    }
    gcsSol(lookup, f1, f2);
    return;
  }
  
  if ((*lookup)[i+1][j] == (*lookup)[i][j+1]) {
    // Same regardless of which way we go, just take a random path...
    DEBUG(cout << "GO RAND" << endl);
    cout << RED << hex(c1) << ": " << c2 << END << endl;
    f1->seekg(i);
  } else if ((*lookup)[i+1][j] > (*lookup)[i][j+1]) {
    // Go down
    DEBUG(cout << "GO DOWN" << endl);
    cout << GREEN << hex(c1) << ": " << c1 << END << endl;
    f2->seekg(j);
  } else {
    DEBUG(cout << "GO RIGHT" << endl);
    cout << RED << hex(c1) << ": " << c2 << END << endl;
    // Go right
    f1->seekg(i);
  }
  gcsSol(lookup, f1, f2);
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
