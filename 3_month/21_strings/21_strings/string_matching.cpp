#include "string_matching.h"

std::string reverse(std::string str) {
    std::string res = str;
    int l = str.size();
    for(int i=0; i < l/2; ++i) {
        res[i] = str[l-i-1];
        res[l-i-1] = str[i];
    }
    return res;
}

clsVector<int> findPrefixes(std::string str)
{
    clsVector<int> vec;
    int l = str.size();
    for(int i=0; i < l; ++i) {
        int z = 0;
        for(z=0; z < l-i; ++z)
            if(str[z] != str[z+i])
                break;
        vec.add(z);
    }
    return vec;
}

bool hasPrefix(std::string str, std::string prefix)
{
    int l = str.size();
    int n = prefix.size();
    if(n > l)
        return 0;
    for(int i=0; i < n; ++i) {
        if(str[i] != prefix[i])
            return 0;
    }
    return 1;
}

int longestCommonSuffix(std::string str, std::string prefix)
{
    int suff = 0;
    int l = str.size();
    int n = prefix.size();
    if(n > l)
        return 0;
    for(int i=0; i < n; ++i) {
        if(str[i] != prefix[i])
            return 0;
    }
    return suff;
}

clsVector<int> goodSuffixTable(std::string str) {
    clsVector<int> vec;
    clsVector<int> suffs = findPrefixes(reverse(str));
    suffs.reverse();
    int _default = -1;
    int l = str.size();
    vec.add(_default);
    for(int i=1; i < l; ++i) {
        int suff = l - suffs[i];
        if((suffs[i] > 0) && (suff != l))
            vec.add(suff);
        else
            vec.add(_default);
    }
    return vec;
}

clsVector<int> calcPrefixes(std::string str) {
    clsVector<int> vec;
    int l = str.size();
    for(int i=0; i < l; ++i)
        vec.push_back(0);
    int k = 0;
    for(int i=1; i < l; ++i) {
        while((k > 0) && (str[k] != str[i]))
            k = vec[k-1];
        if(str[k] == str[i])
            k += 1;
        vec[i] = k;
    }
    return vec;
}

clsVector<int> KMP(std::string &text, std::string &pattern)
{
    clsVector<int> matches;
    int l = text.size();
    int n = pattern.size();
    clsVector<int> prefs = calcPrefixes(pattern);
    int q = 0;
    for(int i=0; i < l; ++i) {
        while((q > 0) && (pattern[q] != text[i]))
            q = prefs[q-1];
        if(pattern[q] == text[i])
            q += 1;
        if(q == n) {
            matches.push_back(i - n + 1);
            q = prefs[q-1];
        }
    }
    return matches;
}
