#include <algorithm>
#include <random>


template<class T>
class randomized_queue {
public:

    /*** Default constructor ***/
    randomized_queue () : size_randomized_queue(0),
                          capacity(2) {
        data = new T[2];
    }

    /*** Destructor ***/
    ~randomized_queue () {
        delete[] data;
    }

    /*** Copy constructor ***/
    randomized_queue (const randomized_queue &other) : data(new T[other.size_randomized_queue]),
                                                       size_randomized_queue(other.size_randomized_queue),
                                                       capacity(other.capacity) {
        data = new T[other.size_randomized_queue];
        std::copy(other.data, other.data + other.size_randomized_queue, data);
    }

    /*** Checks if RandomizedQueue is empty ***/
    bool empty () const {
        return (size_randomized_queue == 0);
    }

    /*** Returns number of elements in RandomizedQueue ***/
    int size () const {
        return size_randomized_queue;
    }


    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T *;
        using reference = T &;

        /*** Default constructor ***/
        iterator () {}

        /*** Destructor ***/
        ~iterator () { delete[] curr_permutation; }

        /*** Single argument constructor ***/
        iterator (int size) : position(size) {}

        iterator (T *&other, int size, bool end) : begin_(other),
                                                   position(end ? size : 0),
                                                   size_curr_permutation(size) {
            curr_permutation = create(size);
        }

        /*** Copy constructor ***/
        iterator (const iterator &other) : begin_(other.begin_),
                                           position(other.position),
                                           size_curr_permutation(other.size_curr_permutation) {
            curr_permutation = new int[other.size_curr_permutation];
            std::copy(other.curr_permutation, other.curr_permutation + other.size_curr_permutation, curr_permutation);
        }

        /*** Implementing operators ***/
        iterator &operator= (const iterator &other) {
            if (&other == this) {
                return *this;
            }
            delete[] curr_permutation;
            std::copy(other.curr_permutation, other.curr_permutation + other.size_curr_permutation, curr_permutation);
            begin_ = other.begin_;
            position = other.position;
            size_curr_permutation = other.size_curr_permutation;
            return *this;
        }

        iterator &operator++ () {
            ++position;
            return *this;
        }

        const iterator operator++ (int) {
            iterator save = *this;
            ++position;
            return save;
        }

        iterator &operator-- () {
            --position;
            return *this;
        }

        const iterator operator-- (int) {
            iterator save = *this;
            --position;
            return save;
        }

        bool operator== (const iterator &other) const { return position == other.position; }

        bool operator!= (const iterator &other) const { return position != other.position; }

        T &operator* () const {
            return *(begin_ + (position > size_curr_permutation ? position : curr_permutation[position]));
        }

        T *operator-> () const { return position; }

    private:
        int *curr_permutation, position, size_curr_permutation;
        T *begin_;

        int *create (const int size) {
            if (size == 0) {
                return nullptr;
            }
            int *help = new int[size];
            std::iota(help, help + size, 0);
            std::shuffle(help, help + size_curr_permutation, std::mt19937(std::random_device()()));
            return help;
        }
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T *;
        using reference = T &;

        /*** Default constructor ***/
        const_iterator () {}

        /*** Destructor ***/
        ~const_iterator () { delete[] curr_permutation; }

        /*** Single argument constructor ***/
        const_iterator (int size) : position(size) {}

        const_iterator (T *&other, int size, bool end) : begin_(other),
                                                   position(end ? size : 0),
                                                   size_curr_permutation(size) {
            curr_permutation = create(size);
        }

        /*** Copy constructor ***/
        const_iterator (const const_iterator &other) : begin_(other.begin_),
                                           position(other.position),
                                           size_curr_permutation(other.size_curr_permutation) {
            curr_permutation = new int[other.size_curr_permutation];
            std::copy(other.curr_permutation, other.curr_permutation + other.size_curr_permutation, curr_permutation);
        }

        /*** Implementing operators ***/
        const_iterator &operator= (const const_iterator &other) {
            if (&other == this) {
                return *this;
            }
            delete[] curr_permutation;
            std::copy(other.curr_permutation, other.curr_permutation + other.size_curr_permutation, curr_permutation);
            begin_ = other.begin_;
            position = other.position;
            size_curr_permutation = other.size_curr_permutation;
            return *this;
        }

        const_iterator &operator++ () {
            ++position;
            return *this;
        }

        const const_iterator operator++ (int) {
            const_iterator save = *this;
            ++position;
            return save;
        }

        const_iterator &operator-- () {
            --position;
            return *this;
        }

        const const_iterator operator-- (int) {
            const_iterator save = *this;
            --position;
            return save;
        }

        bool operator== (const const_iterator &other) const { return position == other.position; }

        bool operator!= (const const_iterator &other) const { return position != other.position; }

        T operator* () const {
            return *(begin_ + (position > size_curr_permutation ? position : curr_permutation[position]));
        }

        T *operator-> () const { return position; }

    private:
        int position;
        int *curr_permutation, size_curr_permutation;
        const T *begin_;

        int *create (const int size) {
            if (size == 0) {
                return nullptr;
            }
            int *help = new int[size];
            std::iota(help, help + size, 0);
            std::shuffle(help, help + size_curr_permutation, std::mt19937(std::random_device()()));
            return help;
        }
    };

    /*** Adds an element to the RandomizedQueue ***/
    void enqueue (const T &element) {
        if (size_randomized_queue == capacity) {
            resize(2 * capacity);
        }
        data[size_randomized_queue++] = element;
    }

    /*** Randomly removes and return an element from RandomizedQueue ***/
    T dequeue () {
        int r = std::mt19937(std::random_device()())() % size_randomized_queue;
        T ans = data[r];
        data[r] = data[--size_randomized_queue];
        if (size_randomized_queue > 0 && size_randomized_queue == capacity / 4) {
            resize(capacity / 2);
        }
        return ans;
    }

    /*** Returns a random element ***/
    T sample () const { return data[std::mt19937(std::random_device()())() % size_randomized_queue]; }

    iterator begin () { return iterator(data, size_randomized_queue, false); }

    iterator end () { return iterator(data, size_randomized_queue, true); }

    const_iterator cbegin () { return const_iterator(data, size_randomized_queue, false); }

    const_iterator cend () { return const_iterator(data, size_randomized_queue, true); }

    randomized_queue<T> &operator= (const randomized_queue &other) {
        if (&other == this) {
            return *this;
        }
        delete[] data;
        std::copy(other.curr_permutation, other.curr_permutation + other.size_curr_permutation, data);
        size_randomized_queue = other.size_randomized_queue;
        capacity = other.capacity;
        return *this;
    }

private:
    T *data;
    int capacity, size_randomized_queue;

    void resize (int new_capacity) {
        T *new_data = new T[new_capacity];
        std::copy(data, data + size_randomized_queue, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};