#include "test_matching.h"

#include "string_matching.h"

#define calcPrefixes_(str)  \
{   \
    clsVector<int> prefs = findPrefixes(str);  \
    printf("\"%s\" prefixes is:\n", str.c_str());   \
    prefs.printArray(stdout);   \
    printf("\n");   \
}

#define checkPrefix(str, pref)  \
{   \
    bool res = hasPrefix(str, pref);  \
    printf("%s.hasPrefix("#pref") = %d\n", str.c_str(), res);   \
}

#define checkSuffTable(str)  \
{   \
    clsVector<int> res = goodSuffixTable(str);  \
    printf("\"%s\" good suffixes is:\n", str.c_str());   \
    res.printArray(stdout);   \
}

void test_matching()
{
    std::string str1("coconut");
    std::string str2("aaaaaaa");
    std::string str3("EXAMPLE");
    std::string str4("GAAGCAAG");
    std::string str5("GATGCAAG");
    std::string str6("GAGAGGAG");

    std::string pat1("AAG");

//    calcPrefixes_(str1);
//    calcPrefixes_(str2);

//    checkPrefix(str1, "co");
//    checkPrefix(str1, "oc");
//    checkPrefix(str1, "cocon");

//    checkSuffTable(str3);
//    checkSuffTable(str4);
//    checkSuffTable(str5);

//    clsVector<int> prefs = calcPrefixes(str6);
//    printf("\"%s\" prefixes is:\n", str6.c_str());
//    prefs.printArray(stdout);
//    printf("\n");

    clsVector<int> matches = KMP(str4, pat1);
    printf("\"%s\" matches pattern \"%s\" is:\n",
           str4.c_str(), pat1.c_str());
    matches.printArray(stdout);
    printf("\n");



}
