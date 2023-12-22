#include "mesh_loader.h"

mesh* mesh_loader::load() const
{

	vector<Vector3f> points;
	vector<triangle> triangles;
	Vector3f vertice;
	triangle tr;
	string line;
	char type;

	ifstream in;
	in.open(dir_path_ + R"(\)" + file_name_ + extension_);
	if (!in.is_open())
		return nullptr;
	
	while(! in.eof())
	{

		stringstream s;

		getline(in, line);
		
		s << line;		
		s >> type;

		switch (type)
		{
			case 'v':
				s >> vertice.x >> vertice.y >> vertice.z;
				points.push_back(vertice);
				break;
			case 'f':
				s >> *tr.a_pointer() >> *tr.b_pointer() >> *tr.c_pointer();
				*(tr.a_pointer()) = tr.a() - 1;
				*(tr.b_pointer()) = tr.b() - 1;
				*(tr.c_pointer()) = tr.c() - 1;
				triangles.push_back(tr);
				break;
			default:
				break;
		}		
	}
	return new mesh(points, triangles);
}
