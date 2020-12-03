#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <numeric>

using namespace std;

void adder(int &sum, int start, int end) {
  sum = 0;
  for(int i = start; i < end; i++) {
    sum += i;
  }
}

int main() {

  const int numElem = 1000 * 1000 * 1000;

  for(int x = 1; x < 10; x++) {
    const int lowThread = x;
    int increment = numElem / lowThread;
    vector<thread> threads;
    vector<int> partialSums(lowThread);

    time_t start = time(0);
    for(int i = 0; i < lowThread; i++) {
      threads.push_back(thread(adder, ref(partialSums[i]), i * increment, (i + 1) * increment));
    }
    for(thread &t : threads) {
      //if(t.joinable()) {
        t.join();
      //}
    }
    int total = accumulate(partialSums.begin(), partialSums.end(), int(0));
    time_t end = time(0);
    int elapsed = end - start;
    for(int i = 0; i < partialSums.size(); i++) {
      cout << partialSums[i] << endl;
    }
    cout << "Total:" << total << "\nTime: " << elapsed << endl;
  }
}