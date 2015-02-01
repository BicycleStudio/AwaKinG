#include "Parser.h"

Parser::Parser()
{

}
bool Parser::readFromFile(string str)
{
	// chack extension, make dicision what file ".amp", ".aml" etc
	// for now we only have ".aml"

	FILE* file_;
	fopen_s(&file_, str.c_str(), "r");

	int numV_ = 0; int numTV_ = 0; int numF_ = 0;
	fscanf_s(file_, "%d %d %d ", numV_, numF_, numTV_);

	vector<XMFLOAT3> verts_;		vector<XMFLOAT2> tVerts_; vector<XMFLOAT3> norms_;
	vector<XMINT3> vertFaces;	vector<XMINT3> tVertFaces;

	for(int i = 0; i < numV_; i++)
	{
		XMFLOAT3 float3_;
		fscanf_s(file_, "%f %f %f ", float3_.x, float3_.y, float3_.z);
		verts_.push_back(float3_);
		fscanf_s(file_, "%f %f %f ", float3_.x, float3_.y, float3_.z);
		norms_.push_back(float3_);
	}
	for(int i = 0; i < numTV_; i++)
	{
		XMFLOAT2 float2_;
		fscanf_s(file_, "%f %f ", float2_.x, float2_.y);
		tVerts_.push_back(float2_);
	}
	for(int i = 0; i < numF_; i++)
	{
		XMINT3 int3_;
		fscanf_s(file_, "%d %d %d ", int3_.x, int3_.y, int3_.z);
		vertFaces.push_back(int3_);
		fscanf_s(file_, "%d %d %d ", int3_.x, int3_.y, int3_.z);
		tVertFaces.push_back(int3_);
	}

	vector<Vertex::Simple> simpleVerts_;
	vector<Vertex::Simple> optimizedVerts_;
	unsigned int countV = 0;
	for(int i = 0; i < numF_; i++)
	{
		simpleVerts_.push_back(Vertex::Simple(verts_[vertFaces[i].x], tVerts_[tVertFaces[i].x], norms_[vertFaces[i].x]));
		simpleVerts_.push_back(Vertex::Simple(verts_[vertFaces[i].y], tVerts_[tVertFaces[i].y], norms_[vertFaces[i].y]));
		simpleVerts_.push_back(Vertex::Simple(verts_[vertFaces[i].z], tVerts_[tVertFaces[i].z], norms_[vertFaces[i].z]));
	}
	verts_.clear();	tVerts_.clear();	norms_.clear();	vertFaces.clear();	tVertFaces.clear();
	unsigned int* inds_ = new unsigned int[countV];

	for(unsigned int i = 0; i < countV; i++) inds_[i] = i;
	bool write = true;
	optimizedVerts_.push_back(simpleVerts_[0]);
	for(unsigned int i = 1; i < countV; i++)
	{
		write = true;
		for(unsigned int j = 0; j < optimizedVerts_.size(); j++)
		{
			if(simpleVerts_[i].position.x == optimizedVerts_[j].position.x && simpleVerts_[i].texCoord.x == optimizedVerts_[j].texCoord.x &&
				simpleVerts_[i].position.y == optimizedVerts_[j].position.y && simpleVerts_[i].texCoord.y == optimizedVerts_[j].texCoord.y &&
				simpleVerts_[i].position.z == optimizedVerts_[j].position.z)
			{
				write = false;
				inds_[i] = j;
			}
		}
		if(write)
		{
			optimizedVerts_.push_back(simpleVerts_[i]);
			inds_[i] = optimizedVerts_.size() - 1;
		}
	}

	Vertex::Simple* vertsForBuffer = new Vertex::Simple[optimizedVerts_.size()];
	//CountInds = count_v;
	for(unsigned int i = 0; i < optimizedVerts_.size(); i++) vertsForBuffer[i] = optimizedVerts_[i];

	fclose(file_);

	return true;
}
