#include "..\header.h"
string get_current_dir() {
	string result;
	char* output = new char[500];
	WCHAR path[500];
	GetModuleFileName(NULL, path, 500);
	sprintf(output, "%ws", path);
	result = output;
	result = result.substr(0, result.find_last_of("\\/"));
	delete[] output;
	return result;
}
