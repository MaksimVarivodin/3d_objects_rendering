#include "lighting.h"

mesh lighting::color_filtering(const mesh& m) const
{
	vector<Vector3f> normals = m.normals_to_triangles();
	vector<triangle> trians = m.get_triangles();

	for(size_t i = 0; i< normals.size(); i++)
	{
		const float dot_product = em_dot_product_point(normals[i], direction_);

		trians[i].fill({
			static_cast<Uint8>((float)	trians[i].fill().r * dot_product),
			static_cast<Uint8>((float)	trians[i].fill().g * dot_product),
			static_cast<Uint8>((float)	trians[i].fill().b * dot_product)
		});

	}
	return mesh(m.get_points(), trians);


}
