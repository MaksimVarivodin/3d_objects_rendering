#pragma once
#include "mesh_impl.h"

template <class T>
class mesh_loader {

private:
	string extension_ = ".obj";
	string dir_path_ = R"(C:\Users\maksy\Documents\Projects\c++\3DGraphics\SpaceTraveler\objects)";
	string file_name_ = "VideoShip";
public:
	string extension() const
	{
		return extension_;
	}

	void extension(const string& extension)
	{
		extension_ = extension;
	}


	string dir_path() const
	{
		return dir_path_;
	}

	void dir_path(const string& dir_path)
	{
		dir_path_ = dir_path;
	}


	string file_name() const
	{
		return file_name_;
	}

	void file_name(const string& file_name)
	{
		file_name_ = file_name;
	}

	mesh_loader() = default;

	inline mesh<T>* load() const
	{
		vector<point<T>*> points;
		vector<triangle<T>> triangles;

		points.reserve(1000);
		triangles.reserve(1500);

		point<T>* pointer;
		unsigned a, b, c;

		ifstream in;

		string line;

		char type;

		in.open(dir_path_ + R"(\)" + file_name_ + extension_);
		if (!in.is_open())
			return nullptr;

		while (!in.eof()) {
			stringstream s;
			getline(in, line);
			s << line.c_str();
			s >> type;

			switch (type) {
			case 'v':
				pointer = new point<T>();
				s >> pointer->get_ref_x() >> pointer->get_ref_y() >> pointer->get_ref_z();
				points.push_back(pointer);
				break;
			case 'f':
				s >> a >> b >> c;
				a--; b--; c--;
				triangles.push_back(triangle<T>(points[a], points[b], points[c]));
				break;
			default:
				break;
			}

		}
		return new mesh(points, triangles);
	}

};
