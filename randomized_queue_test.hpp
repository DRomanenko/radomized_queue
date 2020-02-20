#include <vector>
#include <assert.h>
#include <algorithm>

void test_randomized_queue () {
    std::vector<int> before;
    randomized_queue<int> q;
    for (int i = 0; i < 50000; ++i) {
        int r = std::mt19937(std::random_device()())() % INT32_MAX;
        q.enqueue(r);
        before.push_back(r);
    }
    std::sort(before.begin(), before.end());

    auto b1 = q.cbegin();
    auto e1 = q.cend();

    auto b2 = q.cbegin();
    auto e2 = q.cend();


    std::cout << "Randomized queue test:\n-----------------\n";
    /*** Два прохода одним итератором дают одинаковую последовательность. ***/
    std::cout << "Test 1 (Two passes by one iterator):\n";
    std::vector<int> v11, v12;
    std::copy(b1, e1, std::back_inserter(v11));
    std::copy(b1, e1, std::back_inserter(v12));
    assert(v11 == v12);
    std::cout << "Passed!\n-----------------\n";

    std::vector<int> v21, v22;
    std::copy(b2, e2, std::back_inserter(v21));
    std::copy(b2, e2, std::back_inserter(v22));
    assert(v21 == v22);

    std::cout << "Test 2 (Two different iterators set different sequences):\n";
    /*** С высокой степенью вероятности, два разных итератора задают разные последовательности. ***/
    assert(v11 != v21);
    std::cout << "Passed!\n-----------------\n";

    std::cout << "Test 3 (Taking iterators did not affect the queue):\n";
    /*** Взятие итераторов не повлияло на очередь ***/
    std::vector<int> after;
    while (!q.empty()) {
        after.push_back(q.dequeue());
    }
    std::sort(after.begin(), after.end());
    assert(before == after);
    std::cout << "Passed!\n-----------------\n\n";
}