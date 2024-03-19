#include "strcmp.hpp"
#include <algorithm>
#include <bits/stdc++.h>

int myStrLen(const char* s) {
    int i = 0;
    while (s[i++]) {}
    return i;
}

int myStrCmp(const char* s1, const char* s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}