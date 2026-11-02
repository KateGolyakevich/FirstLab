#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Collection {
    private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; i++) {new_data[i] = data[i];}
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    public:
    Collection(size_t initial_capacity = 4) : capacity(initial_capacity) {
        if (capacity == 0) capacity = 1; data = new T[capacity];
    }
    ~Collection() {delete[] data;}

    Collection(const Collection& other) : capacity(other.capacity), size(other.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {data[i] = other.data[i];}
    }

    Collection& operator=(const Collection& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; i++) {data[i] = other.data[i];}
        }
        return *this;
    }

    Collection(Collection&& other) noexcept : data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    Collection& operator=(Collection&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            size = other.size;
            other.data = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    void add(const T& item) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        data[size++] = item;
    }

    Collection& operator+=(const T& item) {
        add(item);
        return *this;
    }

    size_t get_size() const {return size;}
    size_t get_capacity() const {return capacity;}
    bool is_empty() const {return size == 0;}

    T& operator[](size_t index) {return data[index];}
    const T& operator[](size_t index) const {return data[index];}

    T& at(size_t index) {
        if (index >= size)
            throw std::out_of_range("Индекс выходит за границы интервала!");
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы интервала!");
        }
        return data[index];
        }

    int find_index(const T& item) const {
        for (size_t i = 0; i < size; i++) {
            if (data[i] == item) return static_cast<int>(i);
        }
        return -1;
    }

    bool remove_by_index(size_t index) {
        if (index >= size) return false;
        for (size_t i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        --size;
        return true;
    }

    bool remove_by_num(const T& item) {
        int num = find_num(item);
        if (num != -1) {return remove_by_index(static_cast<size_t>(num));}
        return false;
    }

    void clear() {size = 0;}

    void print(std::ostream& os = std::cout) const {
        if (is_empty()){os << "Коллекция пуста\n"; return;}
    }
};

#endif
