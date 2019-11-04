#ifndef STRING_MATCHING_H
#define STRING_MATCHING_H

#include <string>

#include "../../../1_month/2_dynamic_arrays/dynamicArray/lists.h"
#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"

clsVector<int> findPrefixes(std::string str);
bool hasPrefix(std::string str, std::string prefix);
clsVector<int> goodSuffixTable(std::string str);
clsVector<int> calcPrefixes(std::string str);


clsVector<int> KMP(std::string &text, std::string &pattern);

#endif // STRING_MATCHING_H
