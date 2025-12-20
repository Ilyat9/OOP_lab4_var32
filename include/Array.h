#pragma once
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "Figure.h"

template<class T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t capacity;
    size_t size;
    
    void resize(size_t newCapacity) {
        std::shared_ptr<T[]> newData(new T[newCapacity]);
        for (size_t i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        
        data = std::move(newData);
        capacity = newCapacity;
    }
    
public:
    Array() : data(nullptr), capacity(0), size(0) {}
    
    Array(size_t initialCapacity) : capacity(initialCapacity), size(0) {
        data = std::shared_ptr<T[]>(new T[initialCapacity]);
    }
    
    ~Array() = default;
    
    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }
    
    void push_back(T&& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = std::move(value);
    }
    
    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }
    
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    
    void clear() {
        data.reset();
        size = 0;
        capacity = 0;
    }
};
