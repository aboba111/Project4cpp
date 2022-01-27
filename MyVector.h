#include <iterator>
#include <memory>
#include <stdexcept>
#include <exception>

template<typename T>
class MyVector {
private:
    T *m_elements = nullptr;
    size_t m_size = 0;
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        

    private:
        pointer m_ptr;

    public:
        Iterator() = default;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        Iterator(Iterator &&other) noexcept {
            //if (m_ptr != nullptr)
            //  delete m_ptr;
            m_ptr = std::exchange(other.m_ptr, nullptr);
        }

        Iterator(Iterator const &iterator) {
            m_ptr = iterator.m_ptr;
        }

        reference operator*() const { return *m_ptr; }

        pointer operator->() { return m_ptr; }

        Iterator &operator++() {
            m_ptr++;
            return *this;
        }

        int operator-(const Iterator &other) const {
            return m_ptr - other.m_ptr;
        }

        Iterator operator+(int i) {
            return Iterator(m_ptr + i);
        }

        const Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; };

        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };
    };

    Iterator begin() { return &m_elements[0]; }

    Iterator end() { return &m_elements[m_size]; }

    explicit MyVector(size_t size = 0) {
        resize(size);
    };

    // Copy
    MyVector(const MyVector &other) {
        resize(other.m_size);
        std::copy(other.m_elements, other.m_elements + other.m_size, m_elements);
    };

    //Move
    MyVector(MyVector<T> &&other) noexcept {
        if (this == &other)
            return;

        delete[] m_elements;
        m_elements = std::exchange(other.m_elements, nullptr);
        m_size = std::exchange(other.m_size, 0);
    }

    void push_back(T val) {
        resize(m_size + 1);
        m_elements[m_size - 1] = val;
    }

    void resize(size_t newSize) {
        if (newSize < 0)
            throw std::out_of_range("Size must be >= 0");

        T *tmp = new T[newSize + 1];

        if (m_elements != nullptr)
            std::copy(m_elements, m_elements + std::min(m_size, newSize), tmp);

        delete[] m_elements;

        m_elements = tmp;
        m_size = newSize;
    }

    Iterator find(T value) {
        for (auto it = begin(); it != end(); it++) {
            if (*it == value)
                return it;
        }
        return end();
    }

    Iterator erase(Iterator pos) {
        int index = pos - begin();
        for (int i = index; i < m_size - 1; i++)
            std::swap(m_elements[i], m_elements[i + 1]);
        resize(m_size - 1);
        return begin() + index;
    }

    Iterator erase(Iterator first, Iterator last) {
        for (auto it = first; it != last; it++)
            erase(it);
        return last;
    }

    Iterator erase(T value) {
        return erase(find(value));
    }

    size_t size() { return m_size; }

    bool empty() { return m_size == 0; }

    T &operator[](size_t i) { return m_elements[i]; }

    T &operator[](size_t i) const { return m_elements[i]; };

    // Copy
    MyVector &operator=(const MyVector<T> &other) {
        if (this == &other)
            return *this;

        resize(other.m_size);
        std::copy(other.m_elements, other.m_elements + other.m_size, m_elements);
        return *this;
    };

    // Move
    MyVector &operator=(MyVector<T> &&other) noexcept {
        if (this == &other)
            return *this;

        delete[] m_elements;
        m_elements = std::exchange(other.vector, nullptr);
        m_size = std::exchange(other.m_size, 0);
        return *this;
    };

    bool operator==(const MyVector &other) const {
        if (m_size != other.m_size)
            return false;

        for (int i = 0; i < m_size; i++) {
            if (this[i] != other[i])
                return false;
        }

        return true;
    };

    // --- Destructors --- ///
    ~MyVector() {
        delete[] m_elements;
    };

};
