#ifndef __ADDITIONAL_H
#define __ADDITIONAL_H

#pragma warning(push)
#pragma warning(disable:4005)

#include <Windows.h>
#include <vector>
#include "../../../../include/D3DX11.h"
#include "../../../../include/d3dcompiler.h"
#include "../../../../include/xnamath.h"

using namespace std;

#ifdef __x86
#pragma comment(lib, "../../lib/x86/D3DX11.lib")
#pragma comment(lib, "../../lib/x86/D3D11.lib")
#endif

#ifdef __x64
#pragma comment(lib, "../../lib/x64/D3DX11.lib")
#pragma comment(lib, "../../lib/x64/D3D11.lib")
#endif

#define CHECK_RESULT(hres, msg) if(FAILED(hres)){errorMessage = msg;return false; }
#define SAFE_RELEASE(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}
#define PI_180  0.0174532925f

enum ModelRenderTechnique { MRT_TEXTURE_MAP = 0 };
typedef unsigned int uint;

struct int3 {
  int3() {}
  int3(int value) { x = value; y = value; z = value; }
  int3(int x_, int y_, int z_) { x = x_; y = y_; z = z_; }
  int x;
  int y; 
  int z;
};
namespace Vertex {
	struct Default {
    Default() {}
    Default(XMFLOAT3 pos, XMFLOAT2 tutv, XMFLOAT3 nor) { 
      position = pos;
      texCoords = tutv;
      normal = nor;
    }
		XMFLOAT3 position;
		XMFLOAT2 texCoords;
		XMFLOAT3 normal;
	};
}
namespace Shader {
	struct SystemConfiguration {
		SystemConfiguration() {}
		const float Zfar = 100000.0f;
		const float Znear = 0.01f;
	};
	struct Technique {
		Technique() { VertexShader = 0; PixelShader = 0; InputLayout = 0; VertexStride = 0; }
		virtual void release() {
			SAFE_RELEASE(VertexShader);
			SAFE_RELEASE(PixelShader);
			SAFE_RELEASE(InputLayout);
		}
		ID3D11VertexShader* VertexShader;
		ID3D11PixelShader* PixelShader;
		ID3D11InputLayout* InputLayout;
		unsigned int VertexStride;
	};
	struct TechniqueBuffers : Technique {
		TechniqueBuffers() { VertexShader = 0; PixelShader = 0; InputLayout = 0; VertexStride = 0; }
		void release() {
			SAFE_RELEASE(VertexShader);
			SAFE_RELEASE(PixelShader);
			SAFE_RELEASE(InputLayout);
			for(uint i = 0; i < Buffers.size(); i++)
				SAFE_RELEASE(Buffers[i]);
			Buffers.clear();
			IndexsOfBuffers.clear();
		}
		vector<ID3D11Buffer*>	Buffers;
		vector<int>	IndexsOfBuffers;
	};
	struct RasterizerState {
		RasterizerState() { Solid = 0; SolidNonCull = 0; Wireframe = 0; }
		virtual void release() {
			SAFE_RELEASE(Solid);
			SAFE_RELEASE(SolidNonCull);
			SAFE_RELEASE(Wireframe);
		}
		ID3D11RasterizerState* Solid;
		ID3D11RasterizerState* SolidNonCull;
		ID3D11RasterizerState* Wireframe;
	};
	struct SamplerState {
		SamplerState() { Linear = 0; }
		virtual void release() {
			SAFE_RELEASE(Linear);
		}
		ID3D11SamplerState* Linear;
	};
}
#pragma warning(pop)
#endif // __ADDITIONAL_H 