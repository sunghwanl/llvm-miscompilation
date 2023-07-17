#include <atomic>
#include <iostream>

using namespace std;

void foo(int i, int j, atomic<int>& a, atomic<int>& b) {
  a.store(i + j, memory_order_release);
  while (b.load(memory_order_acquire) < i);
}
