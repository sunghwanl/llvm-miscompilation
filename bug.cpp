#include "foo.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

inline int* bug(int N, atomic<int>& a, atomic<int>& b, int i) {
  int* p = (int*)malloc(sizeof(int));
  
  for (int j = 1; j <= N; j++) {
    *p = j;
    foo(i, j, a, b);
  }

  return p;
}

void thread1(int N, atomic<int>& a, atomic<int>& b, atomic<int>& c, atomic<int>& d, atomic<int*>* x, int iter) {
  for (int i = 1; i <= iter; i++) {
    x->store(NULL, memory_order_relaxed);

    int* p = bug(N, a, b, i);
    x->store(p, memory_order_relaxed);

    c.store(i, memory_order_release);
    while (d.load(memory_order_acquire) < i);
  }
}

void thread2(int N, atomic<int>& a, atomic<int>& b, atomic<int>& c, atomic<int>& d, atomic<int*>* x, int* ret, int iter) {
  for (int i = 1; i <= iter; i++) {
    b.store(i, memory_order_release);
    while (a.load(memory_order_acquire) < i + N);

    int* p = x->load(memory_order_relaxed);
    if (p != NULL) {
      ret[i-1] = (*p != N);
    }
    else {
      ret[i-1] = 0;
    }

    d.store(i, memory_order_release);
    while (c.load(memory_order_acquire) < i);
  }
}

int check(int* ret, int iter) {
  int n = 0;
  for (int i = 0; i < iter; i++) {
    if (ret[i])
      n++;
  }

  return n;
}
