#pragma once
// here I place all my include libraries
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <chrono>
#include <future>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <strstream>
#include <windows.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace sf;
using namespace std;

string get_current_dir();

namespace engine_math {
	template <class T>
	T* copy(T* to_copy) {
		T* to_return;
		to_return = new T(*to_copy);
		return to_return;
	}
}

using namespace engine_math;
