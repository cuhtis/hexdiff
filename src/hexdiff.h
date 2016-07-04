#ifndef HEXDIFF_H
#define HEXDIFF_H

/*
 *  Header file for hexdiff.cpp
 */
#include <iostream>
#include <iomanip>
#include <vector>

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
