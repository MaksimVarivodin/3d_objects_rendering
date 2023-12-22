#pragma once
#include "mesh.h"
class mesh_loader
{
public:
	
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

	mesh* load() const;

	mesh_loader() = default;

};

