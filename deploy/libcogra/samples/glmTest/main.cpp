#include <iostream>
#include <cogra/types.h>

int main()
{
	cogra::f32vec3 v1(1.0f, 2.0f, 0.5f);
	cogra::f32vec3 v2(0.5f, 2.5f, 5.0f);
	cogra::f32vec3 res = v1 + v2;

	for (cogra::int32 i = 0; i < res.length(); i++)
	{
		std::cout << res[i] << "; ";
	}
	

	return 0;
}