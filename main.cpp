#include <alloca.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
// #include <iostream>

#include "scc_str.h"


int main() {
    auto s = scc_str_init("hello, \0");

    scc_str_println(s);

    printf("%lu\n", sizeof(scc_str));

    return 0;
}
