template<class T>
class deque {
    struct Node;
public:

    /*** Default constructor ***/
    deque () : first(nullptr), last(nullptr), size_deque(0) {}

    /*** Destructor ***/
    ~deque () {
        cleaner(first);
    }

    /*** Copy constructor ***/
    deque (const deque &other) : size_deque(0), first(nullptr), last(nullptr) {
        copy_deque(other);
    }

    /*** Checks if deque is empty ***/
    const bool empty () const {
        return (size_deque == 0);
    }

    /*** Returns number of elements in deque ***/
    const int size () const {
        return size_deque;
    }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T *;
        using reference = T &;

        /*** Default constructor ***/
        iterator () :
                p(nullptr) {}

        /*** Single argument constructor ***/
        iterator (Node *pointer) :
                p(pointer) {}

        /*** Copy constructor ***/
        iterator (const iterator &other) :
                p(other.p) {}

        /*** Implementing operators ***/
        iterator &operator= (const iterator &other) {
            p = other.p;
            return *this;
        }

        iterator &operator++ () {
            p = p->next;
            return *this;
        }

        const iterator operator++ (int) {
            Node *save = p;
            p = p->next;
            return iterator(save);
        }

        iterator &operator-- () {
            p = p->prev;
            return *this;
        }

        const iterator operator-- (int) {
            Node *save = p;
            p = p->prev;
            return iterator(save);
        }

        bool operator== (const iterator &other) const {
            return p == other.p;
        }

        bool operator!= (const iterator &other) const {
            return p != other.p;
        }

        T &operator* () const { return p->element; }

        T *operator-> () const {
            iterator help = *this;
            T &value = *help;
            return (&value);
        }

    private:
        Node *p;
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T *;
        using reference = T &;

        /*** Default constructor ***/
        const_iterator () : p(nullptr) {}

        /*** Single argument constructor ***/
        const_iterator (const Node *pointer) : p(pointer) {}

        /*** Copy constructor ***/
        const_iterator (const const_iterator &other) : p(other.p) {}

        /*** Implementing operators ***/
        const_iterator &operator= (const const_iterator &other) {
            p = other.p;
            return *this;
        }

        const_iterator &operator++ () {
            p = p->next;
            return *this;
        }

        const const_iterator operator++ (int) {
            const Node *save = p;
            p = p->next;
            return const_iterator(save);
        }

        const_iterator &operator-- () {
            p = p->prev;
            return *this;
        }

        const const_iterator operator-- (int) {
            const Node *save = p;
            p = p->prev;
            return const_iterator(save);
        }

        bool operator== (const const_iterator &other) const {
            return p == other.p;
        }

        T operator* () const { return p->element; }

        T *operator-> () const {
            const_iterator help = *this;
            T &value = *help;
            return (&value);
        }

        bool operator!= (const const_iterator &other) const {
            return p != other.p;
        }

    private:
        const Node *p;
    };

    /*** Adds an element to the beginning of the deque ***/
    void push_front (const T &element) {
        Node *new_node = new Node(element);
        new_node->next = first;
        if (!empty()) {
            first->prev = new_node;
        } else {
            last = new_node;
        }
        first = new_node;
        ++size_deque;
    }

    /*** Adds an element to the end of the deque ***/
    void push_back (const T &element) {
        Node *new_node = new Node(element);

        new_node->prev = last;
        if (!empty()) {
            last->next = new_node;
        } else {
            first = new_node;
        }

        last = new_node;
        ++size_deque;
    }

    /*** Returns and removes an element from the beginning of the deque ***/
    T pop_front () {
        T save_element = first->element;
        Node *save_next = first->next;
        delete first;
        first = save_next;
        if (empty()) {
            last = nullptr;
        } else {
            first->prev = nullptr;
        }
        --size_deque;
        return save_element;
    }

    /*** Returns and removes an element from the end of the deque ***/
    T pop_back () {
        T save_element = last->element;
        Node *save_prev = last->prev;
        delete last;
        last = save_prev;
        if (size_deque == 0) {
            first = nullptr;
        } else {
            last->next = nullptr;
        }
        --size_deque;
        return save_element;
    }

    iterator begin () { return iterator(first); }

    iterator end () { return iterator(last); }

    const_iterator cbegin () { return const_iterator(first); }

    const_iterator cend () { return const_iterator(last); }

    deque<T> &operator= (const deque &other) {
        if (this == &other) {
            return *this;
        }
        cleaner(first);
        copy_deque(other);
        return *this;
    }

private:
    int size_deque;

    struct Node {
        Node () : next(nullptr), prev(nullptr) {}

        Node (T element) : next(nullptr), prev(nullptr), element(element) {}

        T element;
        Node *next, *prev;
    };

    void cleaner (Node *&v) {
        Node *curr;
        while (first != nullptr) {
            curr = first;
            first = first->next;
            delete curr;
        }
        size_deque = 0;
        last = nullptr;
    }

    void copy_deque (const deque &other) {
        Node *current;
        current = other.first;
        while (current != nullptr) {
            push_back(current->element);
            current = current->next;
        }
    }

    Node *first, *last;
};