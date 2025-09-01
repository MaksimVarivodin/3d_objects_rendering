#pragma once
#include <vector>
#include <tuple>
#include <memory>
#include <cstdint>

namespace SpaceEngine
{
    template <class T>
    using DynamicArray = std::tuple<std::shared_ptr<T[]>, size_t>;

    template <class T>
    size_t getAllocationSize(const DynamicArray<T>& arr);
    template <class T>
    T* getAllocatedMemory(const DynamicArray<T>& arr);
    template <class T>
    DynamicArray<T> createDynamicArray(size_t size);

    template <class T>
    using SubArray = std::tuple<T*, size_t>; // pointer, size
    template <class T>
    class JaggedArray
    {
        DynamicArray<T> allocatedMemory = {};
        size_t capacity_ = 0;
        size_t dataSize_ = 0;
        size_t freeSpace_ = 0;
        std::vector<SubArray<T>> indices_ = {};

    public:
        const T& operator()(size_t index) const;
        void push_back(const T& element);       
        size_t getCapacity() const;

    public:
        JaggedArray<T>() = default;
        JaggedArray<T>(
            DynamicArray<T> allocatedMemory,
            size_t capacity_,
            size_t dataSize_ = 0,            
            std::vector<SubArray<T>> indices_);
        JaggedArray<T>(            
            size_t capacity_,
            size_t dataSize_);
        JaggedArray<T>(size_t dataSize_);

    private:
        size_t getActualSize() const;
        T* getActualMemory() const;
    };
}

#include "JaggedArray.inl"
