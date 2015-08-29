
#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> &split(const string &s, const char delim, vector<string> &elems);
vector<string> split(const string &s, const char delim);

void parseFloats(string str, float *values);
void parseInts(string str, int *values);

char *itoa(int value);
char *ftoi(float value);
char *dtoa(double value);

#endif
