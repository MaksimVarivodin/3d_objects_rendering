#pragma once
namespace engine_math {
	template <class T>
	T* copy(T* to_copy) {
		T* to_return;
		to_return = new T(*to_copy);
		return to_return;
	}
}

