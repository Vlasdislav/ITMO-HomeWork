#include "find_nearest_same.hpp"
#include <algorithm>

int myStrLen(const char* s) {
    int i = 0;
    while (s[i++]) {}
    return i;
}

ptrdiff_t findNearestSame(const char* s, const char* c) {
    ptrdiff_t c_ind = c - s;
    ptrdiff_t before = -1;
    ptrdiff_t after = -1;
    for (int i = 0; i < c_ind; ++i) {
        if (s[i] == *c) {
            before = i;
        }
    }
    for (int i = c_ind + 1; s[i] != '\0'; ++i) {
        if (s[i] == *c) {
            after = i;
            break;
        }
    }
    if (after == -1 && before == -1) {
        return 0;
    }
    if (after == -1) {
        return before - c_ind;
    }
    if (before == -1) {
        return after - c_ind;
    }
    return (after - c_ind <= c_ind - before ? after - c_ind : before - c_ind);
}