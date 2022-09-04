#include <alloca.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "scc_str.h"

// 用于32位大小
// 求最接近的大于等于cap的 2^n
static int tableSizeFor(int cap) {
    int n = cap - 1;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

scc_str_t scc_str_init(const char *s) {
    int len = strlen(s);
    int tol = scc_str_MIN_LEN + scc_str_Reserved_Space;

    if (len > scc_str_MIN_LEN) {
        tol = tableSizeFor(len + scc_str_Reserved_Space);
    }

    scc_str_t ret = (scc_str_t)malloc(tol);
    ret->cap = tol - scc_str_Reserved_Space;
    ret->idx = 0;
    ret->len = len;
    ret->next = nullptr;

    strcpy((char *)ret + scc_str_Reserved_Space, s);

    return ret;
}

scc_str_t scc_str_pop_front(scc_str_t str, int size) {
    scc_str_t ret;
    if (str->len <= size) {
        // 清空
        if (str->next != nullptr) {
            auto next = str->next;
            // 释放单个节点的空间
            scc_str_free(str);
            return scc_str_pop_front(next, size - str->len);
        }
        return nullptr;
    } else {
        str->idx += size;
        str->len -= size;

        return str;
    }
}
void scc_str_pop_back(scc_str_t str, int size) {

}

//
scc_str_t scc_str_push_front(scc_str_t str, const char *s) {
    auto front = scc_str_init(s);
    front->next = str;

    return front;
}

void scc_str_push_front2(scc_str_t *str, const char *s) {
    auto front = scc_str_init(s);
    front->next = *str;

    *str = front;
}

// bug
void scc_str_push_back(scc_str_t str, const char *s) {
    int len = strlen(s);
    auto base = (char *)str + scc_str_Reserved_Space;
    base += str->len;

    if (str->len + len > str->cap) {
        auto remain = str->cap - str->len;
        // 复制remain个字节到base
        strncpy(base, s, remain);
        str->len += remain;

        auto ne = scc_str_init(s + remain);
        str->next = ne;
    } else {
        // 复制len个字节到base
        strncpy(base, s, len);
        str->len += len;
    }
}

scc_str_t scc_str_cut_front(scc_str_t str, int size) {
    
}
scc_str_t scc_str_cut_back(scc_str_t str, int size) {

}

void scc_str_free(scc_str_t str) {
    free((void *)str);
}
void scc_str_clean(scc_str_t str) {}

void scc_str_tidy(scc_str_t str) {}

void scc_str_print(const scc_str_t s) {
    auto base = (char *)s + scc_str_Reserved_Space;
    for (int i = 0; i < s->len; ++i) {
        putchar(base[s->idx + i]);
    }
    if (s->next != nullptr) {
        scc_str_print(s->next);
    }
}
void scc_str_println(const scc_str_t s) {
    scc_str_print(s);
    putchar('\n');
}
