#pragma once
#include "..\engine_object_classes\mesh.h"
template <class T>
class mesh_loader
{
	
public:
	string dir_path_ = "";
	string file_name_ = "VideoShip";
	string extension_ = ".obj";

	mesh<T> load() {
		vector<point<T>*> points;
		points.reserve(1000);

		vector<triangle<T>> triangles;
		points.reserve(3000);

		vector<point<T>> normals;
		normals.reserve(3000);

		point<T>* vertice;
		size_t a, b, c;
		triangle<T> tr;
		string line;
		char type;

		ifstream in;
		in.open(dir_path_ + R"(\)" + file_name_ + extension_);
		if (!in.is_open())
			return mesh<T>();

		while (!in.eof())
		{

			stringstream s;

			getline(in, line);

			s << line;
			s >> type;

			switch (type)
			{
			case 'v':
				vertice = new point<T>();
				s >> vertice->x >> vertice->y >> vertice->z;
				points.push_back(vertice);
				break;
			case 'f':
				s >> a >> b >> c;
				a--;
				b--;
				c--;

				tr = triangle{
					points[a],
					points[b],
					points[c],
					a,
					b,
					c		
				};

				triangles.push_back(tr);

				normals.push_back(tr.normal());

				break;
			default:
				break;
			}
		}
		return mesh(points, triangles, normals);
	}

	mesh_loader(){
		dir_path_= get_current_dir() +  R"(\objects)";
	}

	mesh_loader(const string& dir_path_, const string& file_name_, const string& extension_)
		: dir_path_(dir_path_), file_name_(file_name_), extension_(extension_)
	{
	}
};

