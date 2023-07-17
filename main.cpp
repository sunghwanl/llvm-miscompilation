#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <thread>
#include <cstdlib>

#include "bug.h"

using namespace std;
using msec = std::chrono::duration<double, std::milli>;


int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " number_of_iteration" << endl;
    exit(1);
  }

  int iter = stoi(argv[1]);

  if (iter <= 0) {
    cout << "positive number of iteration expected!" << endl;
    exit(1);
  }
  void* buf = malloc(sizeof(int) * 1000);

  atomic<int> a;
  atomic<int> b;
  atomic<int> c;
  atomic<int> d;
  atomic<int*>* x = (atomic<int*>*)buf;

  a.store(0, memory_order_relaxed);
  b.store(0, memory_order_relaxed);
  c.store(0, memory_order_relaxed);
  d.store(0, memory_order_relaxed);
  x->store(NULL, memory_order_relaxed);

  thread *th1, *th2;
  int* ret = (int*)malloc(iter * sizeof(int));

  const auto start = chrono::system_clock::now();

  th1 = new thread(thread1, 1, ref(a), ref(b), ref(c), ref(d), x, iter);
  th2 = new thread(thread2, 1, ref(a), ref(b), ref(c), ref(d), x, ret, iter);
  th1->join();
  th2->join();
  int chk = check(ret, iter);

  const auto end = chrono::system_clock::now();

  if(chk > 0) cout << "------------ WOW --------------" << endl;
  cout << fixed << setprecision(4);
  cout << "Execution time (msec): " << msec(end - start).count() << endl;
  cout << "Check: " << chk << "/" << iter << endl;
  if(chk > 0) cout << "-------------------------------" << endl;

  return 0;
}
