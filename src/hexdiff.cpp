/*
 *  Main file
 *  Written by Curtis Li
 */

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "hexdiff.h"
#include "colours.h"
#include "parsecli.h"

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
  ifstream f1, f2;

  // Parse the CLI
  parseCli(&arguments, argc, argv);

  // Open the files
  f1.open(arguments.arg1, ios::in | ios::binary);
  f2.open(arguments.arg2, ios::in | ios::binary);

  // Solve for the Greatest Common Subsequence (GCS)
  vector<vector<int> > lookup = vector<vector<int> >(getSize(&f1), vector<int>(getSize(&f2)));;
  gcs(&lookup, &f1, &f2);
  
  // Reset the streams and get the GCS result
  f1.clear();
  f1.seekg(0, f1.beg);
  f2.clear();
  f2.seekg(0, f2.beg);
  gcsSol(&lookup, &f1, &f2);
  
  // Clsoe the files
  f1.close();
  f2.close();
}


/*
 *  Get the size of a file opened by the stream
 *  Will reset the stream position to the original state
 */
size_t getSize(ifstream *str) {
  int pos = str->tellg();
  str->seekg(0, str->end);
  size_t size = str->tellg();
  str->seekg(pos);
  return size;
}


/*
 *  Solve for the greatest common subsequence given two streams
 *  Stores the result in a lookup/memoization table
 */
int gcs(vector< vector<int> > *lookup, ifstream *f1, ifstream *f2) {
  // Get iteration case
  int row = f1->tellg();
  int col = f2->tellg();

  // Base case
  char byte1, byte2;
  if (!f1->get(byte1) || !f2->get(byte2)) {
    return 0;
  }

  // Fetch memoized results
  assert(row < lookup->size() && col < (*lookup)[row].size());
  if ((*lookup)[row][col] != 0) {
    return (*lookup)[row][col];
  }

  // Match
  if (byte1 == byte2) {
    (*lookup)[row][col] = 1 + gcs(lookup, f1, f2);
    return (*lookup)[row][col];
  }

  // Branch and return max
  f1->clear();
  f1->seekg(row, f1->beg);
  f2->clear();
  f2->seekg(col+1, f2->beg);
  int a = gcs(lookup, f1, f2);

  f1->clear();
  f1->seekg(row+1, f1->beg);
  f2->clear();
  f2->seekg(col, f2->beg);
  int b = gcs(lookup, f1, f2);

  // Memoize result
  (*lookup)[row][col] = a > b ? a : b;
  return a > b ? a : b;
}


/*
 *  Retrieve the GCS solution from a lookup/memoization table
 */
void gcsSol(vector< vector<int> > *lookup, ifstream *f1, ifstream *f2) {
  // Get iteration case
  int row = f1->tellg();
  int col = f2->tellg();
  char byte1, byte2;
  DEBUG(cout << row << "-" << col << ": ");

  if (!f1->get(byte1) || !f2->get(byte2)) {
    DEBUG(cout << "ERROR" << endl);
    return;
  }

  // Match
  DEBUG(cout << byte1 << "-" << byte2 << ": ");
  if (byte1 == byte2) { 
    DEBUG(cout << "MATCH" << endl);
    cout << hex(byte1) << ": " << byte1 << endl;
    return gcsSol(lookup, f1, f2);
  }
  
  // Bounds checking if we hit the base case
  bool rowAtBase = row + 1 >= lookup->size();
  bool colAtBase = col + 1 >= (*lookup)[row].size();
  if (rowAtBase || colAtBase) {
    if (rowAtBase && colAtBase) {
      DEBUG(cout << lookup->size() << " " << (*lookup)[row].size() << ": ");
      DEBUG(cout << "BASE" << endl);
      return;
    } else if (rowAtBase) {
      DEBUG(cout << "BASE RIGHT" << endl);
      cout << RED << hex(byte2) << ": " << byte2 << END << endl;
      f1->clear();
      f1->seekg(row);
    } else if (byte2) {
      DEBUG(cout << "BASE DOWN" << endl);
      cout << GREEN << hex(byte1) << ": " << byte1 << END << endl;
      f2->clear();
      f2->seekg(col);
    }
    return gcsSol(lookup, f1, f2);
  }
  
  // Step case
  if ((*lookup)[row+1][col] > (*lookup)[row][col+1]) {
    // Go down
    DEBUG(cout << "GO DOWN" << endl);
    cout << GREEN << hex(byte1) << ": " << byte1 << END << endl;
    f2->seekg(col);
  } else {
    // Go right
    DEBUG(cout << "GO RIGHT" << endl);
    cout << RED << hex(byte2) << ": " << byte2 << END << endl;
    f1->seekg(row);
  }
  return gcsSol(lookup, f1, f2);
}

