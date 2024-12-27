#ifndef _STRING_HANDLING_H_
#define _STRING_HANDLING_H_

#include <iostream>
#include <string>
using namespace std;

bool isDigit(const char &c);
bool isCapitalizedAlpha(const char &c);
bool isNotCapitalizedAlpha(const char &c);
bool isAlpha(const char &c);
float extractNumber(const string &data, int &i);

#endif