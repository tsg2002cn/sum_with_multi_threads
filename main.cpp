#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

void partial_sum(const std::vector<int> &data, size_t begin, size_t end,
                 long long &result) {
  result = std::accumulate(data.begin() + begin, data.begin() + end, 0LL);
}

int main() {
  std::vector<int> data(200'000'000, 1);
  {
    auto start = std::chrono::steady_clock::now();
    long long total = std::accumulate(data.begin(), data.end(), 0LL);
    auto end = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "total = " << total
              << ", time (without threading) = " << duration << std::endl;
  }

  {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "hardware_concurrency = " << n << "\n";
    if (n == 0)
      n = 4;
    std::vector<long long> partial(n);
    std::vector<std::thread> threads;

    size_t block = data.size() / n;
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
      size_t begin = i * block;
      size_t end = (i == n - 1 ? data.size() : (i + 1) * block);
      threads.emplace_back(partial_sum, std::cref(data), begin, end,
                           std::ref(partial[i]));
    }
    for (auto &t : threads)
      t.join();

    long long total = std::accumulate(partial.begin(), partial.end(), 0LL);
    auto end = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "total = " << total << ", time (with threading) = " << duration
              << std::endl;
  }
}