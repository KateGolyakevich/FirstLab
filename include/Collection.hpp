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
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Collection(size_t initial_capacity = 4)
        : capacity(initial_capacity), size(0) {
        if (capacity == 0) capacity = 1;
        data = new T[capacity];
    }

    // Деструктор
    ~Collection() {
        delete[] data;
    }

    // Конструктор копирования (Deep Copy)
    Collection(const Collection& other)
        : capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }


    Collection& operator=(const Collection& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Конструктор перемещения
    Collection(Collection&& other) noexcept
        : data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    // Оператор присваивания перемещением
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

    // 1. Добавление объекта
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

    // 2. Получение количества элементов и проверка на пустоту
    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }
    bool is_empty() const { return size == 0; }

    // 3. Получение объекта по индексу (оператор [])
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // Получение по индексу с контролем выхода за границы
    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за пределы коллекции! (Index: "
                                    + std::to_string(index) + ", Size: " + std::to_string(size) + ")");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за пределы коллекции!");
        }
        return data[index];
    }

    // 4. Поиск индекса элемента по значению
    int find_index(const T& item) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == item) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // 5. Удаление объекта по индексу
    bool remove_at(size_t index) {
        if (index >= size) return false;
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
        return true;
    }

    // Удаление объекта по значению
    bool remove(const T& item) {
        int indx = find_index(item);
        if (indx != -1) {
            return remove_at(static_cast<size_t>(indx));
        }
        return false;
    }

    // 6. Очистка коллекции
    void clear() {
        size = 0;
    }

    // 7. Вывод содержимого коллекции
    void print(std::ostream& os = std::cout) const {
        if (is_empty()) {
            os << "[Коллекция пуста]\n";
            return;
        }
        for (size_t i = 0; i < size; ++i) {
            os << "  [" << i << "] ";
            print_element(os, data[i]);
            os << "\n";
        }
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Collection<U>& col);

private:

    template <typename Val>
    static void print_element(std::ostream& os, const Val& val) {
        os << val;
    }

    template <typename Ptr>
    static void print_element(std::ostream& os, Ptr* ptr) {
        if (ptr) os << *ptr;
        else os << "nullptr";
    }
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const Collection<U>& col) {
    col.print(os);
    return os;
}

// Шаблонная функция 1: Поиск индекса элемента по предикату
template <typename T, typename Predicate>
int find_if(const Collection<T>& col, Predicate pred) {
    for (size_t i = 0; i < col.get_size(); ++i) {
        if (pred(col[i])) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

//Фильтрация элементов коллекции в новую коллекцию
template <typename T, typename Predicate>
Collection<T> filter_collection(const Collection<T>& source, Predicate pred) {
    Collection<T> result;
    for (size_t i = 0; i < source.get_size(); ++i) {
        if (pred(source[i])) {
            result.add(source[i]);
        }
    }
    return result;
}

//Подсчет суммы числовых характеристик элементов
template <typename T, typename Extractor>
double calculate_sum(const Collection<T>& col, Extractor ext) {
    double total = 0.0;
    for (size_t i = 0; i < col.get_size(); ++i) {
        total += ext(col[i]);
    }
    return total;
}

#endif // COLLECTION_HPP