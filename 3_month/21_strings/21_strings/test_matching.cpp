#include "test_matching.h"

#include <stdio.h>
#include <string>
#include <stdlib.h>

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

#define calcKMP(str, patt)  \
{   \
    clsVector<int> matches = KMP(str, patt);   \
    printf("\"%s\" matches pattern \"%s\" is:\n",   \
           str.c_str(), patt.c_str()); \
    matches.printArray(stdout); \
    printf("\n");   \
}

size_t charPos(const char *str, char ch){
    size_t pos = 0;
    while(str[pos] != '\0') {
        if(str[pos] == ch)
            break;
        pos++;
    }
    return pos;
}

void testKMP(const char * testFilename)
{
    FILE *file = fopen(testFilename, "r");
    if(!file) {
        printf("Can not open the file %s!\n", testFilename);
        return;
    }
    int amount = 0;
    int good = 0;
    int bad = 0;
    fscanf(file, "%d\n", &amount);
    printf("Matching test KMP algoriyhm of %s file ...\n", testFilename);
    for(int i=0; (i < amount) && !feof(file); ++i) {
        char str_[4096];
        fgets(str_, 4096, file);
        std::string str(str_);
        size_t length = str.length();
        const char tab = '\t';
        const char space = ' ';
        size_t textEnd = str.find(&tab, 0, 1);
        char text_[4096];
        memset(text_, 0, 4096);
        str.copy(text_, textEnd);
        std::string text(text_);

        memset(str_, 0, 4096);
        str.copy(str_, length - textEnd - 1, textEnd+1);
        str.erase();
        str = std::string(str_);
        length = str.length();

        size_t patternEnd = str.find(&tab, 0, 1);
        bool isHasResults = 1;
        if(patternEnd > length) {
            patternEnd = length;
            isHasResults = 0;
        }
        char pattern_[1024];
        memset(pattern_, 0, 1024);
        str.copy(pattern_, patternEnd);
        std::string pattern(pattern_);

        char res_[1024];
        memset(res_, 0, 1024);
        size_t res_length = 0;
        if(isHasResults) {
            res_length = length - patternEnd - 1;
            str.copy(res_, res_length, patternEnd+1);
        }
        size_t wasRead = 1;
        clsVector<int> results;
        char *pos = &res_[0];
        while(wasRead < res_length) {
            int cnt = 0;
//            cnt = strcspn(pos, &space);
            cnt = charPos(pos, space);
            if(cnt < 1)
                break;
            char val_[32];
            memset(val_, 0, 32);
            strncpy(val_, pos, cnt);
            results.push_back(atoi(val_));
            pos += cnt + 1;
            wasRead += cnt + 1;
        }

        clsVector<int> matches = KMP(text, pattern);
        bool isGood = 0;
        if(matches.size() == results.size()) {
            isGood = 1;
            for(int j = results.size()-1; j >= 0; --j)
                if(matches[j] != results[j]) {
                    isGood = 0;
                    break;
                }
        }

        if(isHasResults) {
            res_length = length - patternEnd - 1;
            str.copy(res_, res_length, patternEnd+1);
        }
        if(isGood) {
            printf("test %d is sucsess, ", i+1);
            good++;
        }
        else {
            printf("test %d is failed, ", i+1);
            bad++;
        }
        printf(" matches[%lu]: ", matches.size());
        matches.printArray(stdout);
    }

    printf("test report:\n");
    printf("all cases is %d\n", amount);
    printf("success is %d (%f%%)\n", good, 100.0*(double)good / (double)amount);
    printf("failed is %d (%f%%)\n\n", bad, 100.0*(double)bad / (double)amount);
    fclose(file);
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

//    calcKMP(str4, pat1);
//    calcKMP(str5, pat1);

#if 1
    // autotests
    testKMP("../21_strings/string_matching_test_cases.tsv");
    testKMP("../21_strings/test1.tsv");
#endif

}
