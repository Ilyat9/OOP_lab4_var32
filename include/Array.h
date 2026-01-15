#pragma once
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> _items; 
    size_t _capacity;
    size_t _count;
    
    void expand_storage(size_t target_capacity) {
        std::unique_ptr<T[]> new_items(new T[target_capacity]);
        
        for (size_t i = 0; i < _count; ++i) {
            new_items[i] = std::move(_items[i]);
        }
        
        _items = std::move(new_items);
        _capacity = target_capacity;
    }
    
public:
    Array() : _items(nullptr), _capacity(0), _count(0) {}
    
    explicit Array(size_t start_capacity) : _capacity(start_capacity), _count(0) {
        _items = std::unique_ptr<T[]>(new T[start_capacity]);
    }
    
    ~Array() = default;
    
    void add_element(T value) { 
        if (_count >= _capacity) {
            expand_storage(_capacity == 0 ? 2 : _capacity * 2);
        }
        _items[_count++] = std::move(value);
    }
    
    void erase_at(size_t idx) {
        if (idx >= _count) {
            throw std::out_of_range("Array Error: Accessing element beyond total count");
        }
        
        for (size_t i = idx; i < _count - 1; ++i) {
            _items[i] = std::move(_items[i + 1]);
        }
        --_count;
    }
    
    T& operator[](size_t idx) {
        if (idx >= _count) throw std::out_of_range("Array Error: Index out of bounds");
        return _items[idx];
    }
    
    const T& operator[](size_t idx) const {
        if (idx >= _count) throw std::out_of_range("Array Error: Index out of bounds");
        return _items[idx];
    }
    
    size_t length() const { return _count; }
    size_t current_capacity() const { return _capacity; }
    
    void reset() {
        _items.reset();
        _count = 0;
        _capacity = 0;
    }
};
