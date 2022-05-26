#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>

void print(int n, const std::string& str) {
    std::string msg = std::to_string(n) + ":" + str;
    std::cout << msg << std::endl;
}

int main(int argc, char** argv) {
    std::vector<std::string> s = {
        "Jack",
        "Automhate",
        "Syzy",
        "Skrillex",
        "LeotriXx0xX"
    };
    std::vector<std::thread> threads;

    for (int i = 0; i < s.size(); i++) {
        threads.push_back(std::thread(print, i, s[i]));
    }

    for (auto& thread: threads) {
        thread.join();
    }

    return 0;
}
