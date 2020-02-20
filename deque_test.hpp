#include <vector>
#include <assert.h>
#include <algorithm>
#include <list>
#include <random>

void test_deque() {
    std::vector<int> before;
    deque<int> q;
    std::list<int> l;

    std::cout << "Deque tests:\n-----------------\n";
    std::cout << "Test 1 (Empty input):\n";
    assert(q.empty() == l.empty());
    std::cout << "Passed!\n-----------------\n";

    std::cout << "Test 2 (Big input: size, add and operator=, delete):\n";
    deque<int> t;
    for (int i = 0; i < 50000; ++i) {
        int r = std::mt19937(std::random_device()())() % INT32_MAX;
        t.push_back(r);
        t.push_front(-r);
        l.push_back(r);
        l.push_front(-r);
    }
    assert(t.size() == l.size());
    std::cout << "Size test passed!\n";

    q = t;

    bool check = true;
    auto q_iterator = q.cbegin();
    auto l_iterator = l.begin();
    *l_iterator = *l.begin();
    while (q_iterator != q.cend() && l_iterator != l.cend()) {
        if (*q_iterator != *l_iterator) {
            check = false;
            break;
        }
        q_iterator++;
        l_iterator++;
    }
    assert(check);
    std::cout << "Add and operator= test passed!\n";
    for (int i = 0; i < 50000; ++i) {
        q.pop_back();
        l.pop_back();
    }
    assert(q.empty() == l.empty());
    std::cout << "Delete test passed!\n-----------------\n\n";
}