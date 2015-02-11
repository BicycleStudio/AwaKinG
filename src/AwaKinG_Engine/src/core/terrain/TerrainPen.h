#pragma once
#include "../../render/D3dRender.h"

class TerrainPen
{
public:
	const int maxSize = 10;
	const float sizeInCell = 10.0f;
	const float sizeOutCell = 5.0f;
	const float sizeHalfInCell = sizeInCell / 2.0f;
	const float sizeHalfOutCell = sizeOutCell / 2.0f;

	TerrainPen(){	}
	virtual void setSizeIn(int value){}
	virtual void update(){}
};
class TextureTerrainPen : public TerrainPen
{
public:
	~TextureTerrainPen(){ }
	TextureTerrainPen()
	{ 
		hard = 0.0f; 
		_sizeIn = 1; 
	}
	float hard;

	virtual void setSizeIn(int value)	{ _sizeIn = value; }
	int getSizeIn()	{ return _sizeIn; }
	virtual void update()	{ }
protected:
	int _sizeIn;
};
class HeightTerrainPen : public TextureTerrainPen
{
public:
	~HeightTerrainPen()
	{ 
		delete[]vertsIn_x; 
		delete[]vertsIn_y; 
		delete[]vertsIn_z; 
		delete[]vertsOut_x; 
		delete[]vertsOut_y; 
		delete[]vertsOut_z; 
		delete worldMatrixsIn;
		delete worldMatrixsOut;
	}
	HeightTerrainPen()
	{ 
		vertsIn_x = new float*[maxSize*maxSize * 4];
		vertsIn_y = new float*[maxSize*maxSize * 4];
		vertsIn_z = new float*[maxSize*maxSize * 4];
		vertsOut_x = new float*[maxSize*maxSize * 4];
		vertsOut_y = new float*[maxSize*maxSize * 4];
		vertsOut_z = new float*[maxSize*maxSize * 4];

		worldMatrixsIn = new XMFLOAT4X4[maxSize*maxSize * 4];
		worldMatrixsOut = new XMFLOAT4X4[maxSize*maxSize * 4];
		for(int i = 0; i < maxSize*maxSize * 4; i++)
		{
			XMStoreFloat4x4(&worldMatrixsIn[i], XMMatrixScaling(8.f, 8.f, 8.f));
			
			vertsIn_x[i] = new float;
			vertsIn_y[i] = new float;
			vertsIn_z[i] = new float;

			vertsOut_x[i] = new float;
			vertsOut_y[i] = new float;
			vertsOut_z[i] = new float;
			
			XMStoreFloat4x4(&worldMatrixsOut[i], XMMatrixScaling(5.f, 5.f, 5.f));
			D3dRender::getInstance().addTerrainPenInMatrix(&worldMatrixsIn[i]);
			D3dRender::getInstance().addTerrainPenOutMatrix(&worldMatrixsOut[i]);
		}
		countDrawSizeOut = countDrawSizeIn = 0; 
		shiftHeight = altHard = hard = 10.0f; 
		smoothKoeff = 1.0f;
		_sizeIn = _sizeOut = 1; 
		D3dRender::getInstance().setTerrainPenProps(&countDrawSizeIn, &countDrawSizeOut);
	}
	void setSizeOut(int value)	{if(value < _sizeIn) _sizeIn = value;_sizeOut = value;}
	void setSizeIn(int value)		{if(value > _sizeOut) _sizeOut = value;_sizeIn = value;}
	int getSizeOut()	{ return _sizeOut; }
	virtual void update()
	{
		for(int i = 0; i < countDrawSizeIn; i++)
		{
			worldMatrixsIn[i]._41 = vertsIn_x[i][0] - 4.f;
			worldMatrixsIn[i]._42 = vertsIn_y[i][0] - 4.f;
			worldMatrixsIn[i]._43 = vertsIn_z[i][0] - 4.f;
		}
		for(int i = 0; i < countDrawSizeOut; i++)
		{
			worldMatrixsOut[i]._41 = vertsOut_x[i][0] - 2.5f;
			worldMatrixsOut[i]._42 = vertsOut_y[i][0] - 2.5f;
			worldMatrixsOut[i]._43 = vertsOut_z[i][0] - 2.5f;
		}
	}

public:
	float altHard;
	float shiftHeight;
	float smoothKoeff;

	int countDrawSizeOut;
	float**	vertsOut_x;
	float**	vertsOut_y;
	float**	vertsOut_z;
	XMFLOAT4X4* worldMatrixsOut;
	int countDrawSizeIn;
	float** vertsIn_x;
	float** vertsIn_y;
	float** vertsIn_z;
	XMFLOAT4X4* worldMatrixsIn;

protected:
	int _sizeOut;
};

