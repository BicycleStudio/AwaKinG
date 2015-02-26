#ifndef __ADDITIONAL_H
#define __ADDITIONAL_H

#include <Windows.h>
#include <vector>
#include <string>
#include "../../../../include/d3d11.h"
#include "../../../../include/D3DX11.h"
#include "../../../../include/d3dcompiler.h"
#include "../../../../include/xnamath.h"

using namespace std;

#pragma comment(lib, "../../lib/x86/D3DX11.lib")
#pragma comment(lib, "../../lib/x86/D3D11.lib")

#define CHECK_RESULT(hres, msg) if(FAILED(hres)){errorMessage = msg;return false; }
#define SAFE_RELEASE(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

namespace Shader  {
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
			for(int i = 0; i < Buffers.size(); i++)
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
#endif // __ADDITIONAL_H 