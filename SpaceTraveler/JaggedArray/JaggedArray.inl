#include <stdexcept>

namespace SpaceEngine
{
    template <class T>
    size_t getAllocationSize(const DynamicArray<T>& arr)
    {
        return std::get<1>(arr);
    }

    template <class T>
    T* getAllocatedMemory(const DynamicArray<T>& arr)
    {
        return std::get<0>(arr).get();
    }

    template <class T>
    DynamicArray<T> createDynamicArray(size_t size)
    {
        return DynamicArray<T>{
            std::shared_ptr<T[]>(
                new T[size](),
                std::default_delete<T[]>()),
            size
        };
    }

    template <class T>
    const T& JaggedArray<T>::operator()(size_t index) const
    {
        if (index >= this->dataSize_)
        {
            throw std::out_of_range("index out of range");
        }
        const T* found = nullptr;
        size_t prefix = 0;
        for (const auto& [jIndex, jSize] : indices_)
        {
            if (index < prefix + jSize)
            {
                found = ptr + (index - prefix);
                break;
            }
            prefix += jSize;
        }
        if (found == nullptr)
        {
            // Defensive: inconsistent indices_ vs dataSize_
            throw std::out_of_range("index not mapped into subarrays");
        }
        return *found;
    }

    template <class T>
    void JaggedArray<T>::push_back(const T& element)
    {
    }
}
