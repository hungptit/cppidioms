// call_once example
#include <chrono>    // std::chrono::milliseconds
#include <iostream>  // std::cout
#include <mutex>     // std::call_once, std::once_flag
#include <thread>    // std::thread, std::this_thread::sleep_for

int winner;
void set_winner(int x) { winner = x; }
std::once_flag winner_flag;

void wait_1000ms(int id) {
  for (int i = 0; i < 1000; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  // claim to be the winner (only the first such call is executed):
  std::call_once(winner_flag, set_winner, id);
}

int main() {
  constexpr int number_of_threads = 10;
  std::thread threads[number_of_threads];
  for (int i = 0; i < number_of_threads; ++i)
    threads[i] = std::thread(wait_1000ms, i + 1);

  std::cout << "waiting for the first among 10 threads to count 1000 ms...\n";

  for (auto& th : threads) {
    th.join();
  }

  std::cout << "winner thread: " << winner << '\n';

  return 0;
}
