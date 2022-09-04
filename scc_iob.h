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

#define scc_iob_MIN_LEN 32
#define scc_iob_Reserved_Space 32

struct scc_iob {
    struct scc_iob *next;
    int idx;
    int len;
    int cap;
};

// 简单iob管理内核，外部应该再封装完整管理，涉及内存分配释放清理策略

// typedef struct scc_iob *scc_iob_node_t;
// typedef scc_iob_node_t *scc_iob_node_ptr_t;

typedef struct scc_iob *scc_iob_t;
typedef scc_iob_t *scc_iob_ptr_t;


// 两种策略
// 一种及时释放内存，采用一些高效处理内存的算法
// 一种惰性释放内存，使用全局表记录，清理的时候统一释放

scc_iob_t scc_iob_init(const char *s) {
    int len = strlen(s);
    int tol = scc_str_MIN_LEN + scc_str_Reserved_Space;

    if (len > scc_str_MIN_LEN) {
        tol = tableSizeFor(len + scc_str_Reserved_Space);
    }

    scc_iob_t ret = (scc_iob_t)malloc(tol);
    ret->cap = tol - scc_str_Reserved_Space;
    ret->idx = 0;
    ret->len = len;
    ret->next = nullptr;

    strcpy((char *)ret + scc_str_Reserved_Space, s);

    return ret;
}

// 释放单个节点的内存
void scc_str_node_free(scc_iob_t node) {}

// 释放整个iob的内存
void scc_str_free(scc_iob_t self);

// 清空
void scc_str_clean(scc_iob_t self);


// 整理，合并多个节点
void scc_str_tidy(scc_iob_ptr_t self);

void scc_str_print(const scc_iob_t s);
void scc_str_println(const scc_iob_t s);

void scc_iob_pop_front(scc_iob_ptr_t self, int size) {
    scc_iob_t iob = *self;

    if (iob->len <= size) {
        // 清空
        auto next = iob->next;
        auto remain = size - iob->len;
        // 释放单个节点的空间
        scc_str_node_free(iob);
        *self = nullptr;

        if (next != nullptr) {
            *self = next;
            scc_iob_pop_front(self, remain);
        }
    } else {
        iob->idx += size;
        iob->len -= size;
    }
}
void scc_iob_pop_back(scc_iob_ptr_t self, int size);

void scc_iob_push_front(scc_iob_ptr_t self, const char *s) {
    auto front = scc_iob_init(s);
    front->next = *self;
    *self = front;
}
void scc_iob_push_back(scc_iob_ptr_t self, const char *s) {}

void scc_iob_push_front(scc_iob_ptr_t self, scc_iob_ptr_t other){
    (*other)->next = *self;
    *self = *other;
}
void scc_iob_push_back(scc_iob_ptr_t self, scc_iob_ptr_t other) {
    (*self)->next = *other;
}

// 从self头部取出size字节，放入out尾部，如果out为空则创建
void scc_iob_cut_front(scc_iob_ptr_t self, scc_iob_ptr_t out, int size) {}

// 从self尾部取出size字节，放入out尾部，如果out为空则创建
void scc_iob_cut_back(scc_iob_ptr_t self, scc_iob_ptr_t out, int size){}

// 获取self前面size个字节的视图，不复制，内存管理取决于self，如果self被释放则out不能再使用
void scc_iob_view_front(scc_iob_ptr_t self, scc_iob_ptr_t out, int size);

// 获取self后面size个字节的视图，不复制，内存管理取决于self，如果self被释放则out不能再使用
void scc_iob_view_back(scc_iob_ptr_t self, scc_iob_ptr_t out, int size);