#pragma once
#include <vector>
#include <map>
#include <string>
#include "../../../../include/D3DX11.h"
#include "../../../../include/d3dcompiler.h"
#include "Model.h"

//using namespace DirectX;
using namespace std;

#pragma comment(lib, "../../lib/x86/D3DX11.lib")
#pragma comment(lib, "../../lib/x86/D3D11.lib")

#define checkResult(hres, msg) if(FAILED(hres)){ErrorMessage = msg;return false; }
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}
struct int2
{
	int2(){}
	int2(int x_, int y_){ x = x_; y = y_; }
	int x;
	int y;
};
struct int3 : int2
{
	int3(){}
	int3(int x_, int y_, int z_){ x = x_; y = y_; z = z_; }

	int z;
};
struct int4 : int3
{
	int4(){}
	int4(int x_, int y_, int z_, int w_){ x = x_; y = y_; z = z_; w = w_; }

	int w;
};
struct precomputeRay
{
	float3 origin;
	float3 direction;
	float3 invDirection;
	int sign[3];

	bool intersect(float3** ps, float t0, float t1)
	{
		float tmin, tmax, tymin, tymax, tzmin, tzmax;

		tmin = (ps[sign[0]]->x - origin.x) * invDirection.x;
		tmax = (ps[1 - sign[0]]->x - origin.x) * invDirection.x;
		tymin = (ps[sign[1]]->y - origin.y) * invDirection.y;
		tymax = (ps[1 - sign[1]]->y - origin.y) * invDirection.y;
		if((tmin > tymax) || (tymin > tmax))
			return false;
		if(tymin > tmin)
			tmin = tymin;
		if(tymax < tmax)
			tmax = tymax;
		tzmin = (ps[sign[2]]->z - origin.z) * invDirection.z;
		tzmax = (ps[1 - sign[2]]->z - origin.z) * invDirection.z;
		if((tmin > tzmax) || (tzmin > tmax))
			return false;
		if(tzmin > tmin)
			tmin = tzmin;
		if(tzmax < tmax)
			tmax = tzmax;
		return ((tmin < t1) && (tmax > t0));
		return false;
	}
	void makeRay(float3 pickOrig, float3 pickDir)
	{
		origin = pickOrig;
		direction = pickDir;
		invDirection = float3(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);
		sign[0] = (invDirection.x < 0);
		sign[1] = (invDirection.y < 0);
		sign[2] = (invDirection.z < 0);
	}
};
class IRTerrain
{
public:
};

