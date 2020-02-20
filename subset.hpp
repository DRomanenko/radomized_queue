#include <iostream>

void subset_stream (std::istream &input, const int size) {
    randomized_queue<std::string> RQ;
    std::string line;
    while (std::getline(input, line)) {
        RQ.enqueue(line);
    }
    for (int i = 0; i < size; ++i) {
        std::cout << RQ.dequeue()<< std::endl;
    }
}