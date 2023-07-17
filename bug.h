#include <atomic>

using namespace std;

void thread1(int N, atomic<int>& a, atomic<int>& b, atomic<int>& c, atomic<int>& d, atomic<int*>* x, int iter);
void thread2(int N, atomic<int>& a, atomic<int>& b, atomic<int>& c, atomic<int>& d, atomic<int*>* x, int* ret, int iter);
int check(int* ret, int iter);
