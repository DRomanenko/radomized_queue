#include <iostream>
#include <fstream>
#include <string_view>

#include "deque.hpp"

#include "deque_test.hpp"

#include "randomized_queue.hpp"

#include "randomized_queue_test.hpp"

#include "subset.hpp"

static bool is_number (const std::string &line) {
    char *p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

int main (int argc, char **argv) {
    test_deque();
    test_randomized_queue();

    int k = 0;
    std::string_view file_input_name = nullptr;
    for (int i = 1; i < argc; ++i) {
        //*** проверка на пустую строку ***//*
        if (argv[i][0] == '\0') {
            continue;
        }

        if (is_number(argv[i])) {
            k = std::stoi(argv[i]);
        } else {
            file_input_name = std::string_view(argv[i]);
            break;
        }
    }

    std::ifstream file_in(file_input_name.data());
    subset_stream(!file_input_name.empty() ? file_in : std::cin, k);
    return 0;
}
