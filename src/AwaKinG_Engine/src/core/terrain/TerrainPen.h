#pragma once

class TerrainPen
{
public:
	const int maxSize = 10;

	TerrainPen(){	}
	virtual void setSizeIn(int value){}
};
class TextureTerrainPen : public TerrainPen
{
public:
	TextureTerrainPen()
	{ 
		hard = 0.0f; 
		_sizeIn = 1; 
		countDrawSizeIn = 0; 
		vertsIn_x = new float*[maxSize*maxSize * 4];
		vertsIn_y = new float*[maxSize*maxSize * 4];
		vertsIn_z = new float*[maxSize*maxSize * 4];
		for(int i = 0; i < maxSize*maxSize * 4; i++)
		{
			XMFLOAT4X4 matr_;
			XMStoreFloat4x4(&matr_,XMMatrixIdentity());
			worldMatrixsIn.push_back(matr_);
			vertsIn_x[i] = &worldMatrixsIn[i]._41;
			vertsIn_y[i] = &worldMatrixsIn[i]._41;
			vertsIn_z[i] = &worldMatrixsIn[i]._41;
		}
	}
	float hard;
	int countDrawSizeIn;
	float** vertsIn_x;
	float** vertsIn_y;
	float** vertsIn_z;
	vector<XMFLOAT4X4> worldMatrixsIn;

	virtual void setSizeIn(int value)	{ _sizeIn = value; }
	int getSizeIn()	{ return _sizeIn; }
protected:
	int _sizeIn;
};
class HeightTerrainPen : public TextureTerrainPen
{
public:
	HeightTerrainPen()
	{ 
		vertsIn_x = new float*[maxSize*maxSize * 4];
		vertsIn_y = new float*[maxSize*maxSize * 4];
		vertsIn_z = new float*[maxSize*maxSize * 4];
		vertsOut_x = new float*[maxSize*maxSize * 4];
		vertsOut_y = new float*[maxSize*maxSize * 4];
		vertsOut_z = new float*[maxSize*maxSize * 4];
		for(int i = 0; i < maxSize*maxSize * 4; i++)
		{
			XMFLOAT4X4 matr_;
			XMStoreFloat4x4(&matr_, XMMatrixIdentity());
			worldMatrixsIn.push_back(matr_);
			vertsIn_x[i] = &worldMatrixsIn[i]._41;
			vertsIn_y[i] = &worldMatrixsIn[i]._41;
			vertsIn_z[i] = &worldMatrixsIn[i]._41;

			worldMatrixsOut.push_back(matr_);
			vertsOut_x[i] = &worldMatrixsOut[i]._41;
			vertsOut_y[i] = &worldMatrixsOut[i]._41;
			vertsOut_z[i] = &worldMatrixsOut[i]._41;
		}
		countDrawSizeOut = countDrawSizeIn = 0; 
		shiftHeight = altHard = hard = 10.0f; 
		_sizeIn = _sizeOut = 2; 
	}
	void setSizeOut(int value)	{if(value < _sizeIn) _sizeIn = value;_sizeOut = value;}
	void setSizeIn(int value)		{if(value > _sizeOut) _sizeOut = value;_sizeIn = value;}
	int getSizeOut()	{ return _sizeOut; }

public:
	int altHard;
	int shiftHeight;
	int countDrawSizeOut;
	float**	vertsOut_x;
	float**	vertsOut_y;
	float**	vertsOut_z;
	vector<XMFLOAT4X4> worldMatrixsOut;

protected:
	int _sizeOut;
};

