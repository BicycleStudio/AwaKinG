using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using SharpDX.Windows;

using Buffer = SharpDX.Direct3D11.Buffer;
using Device = SharpDX.Direct3D11.Device;
using Resource = SharpDX.Direct3D11.Resource;

namespace AwaKinG.src.core.renderer
{
    public class Terrain : Object3D
    {
        int _countVsLocal = 64;
        float _cellSpace = 10.0f;

        public override bool Initialize(Device device)
        {
            if (!VertexBufferInit(device)) return false;
            if (!IndexBufferInit(device)) return false;

            return true;
        }
        private bool VertexBufferInit(Device device)
        {
            _CountVerts = _countVsLocal * _countVsLocal;
            float texs = (float)10 / (float)(_countVsLocal - 1);
            _Verts = new Vertex[_CountVerts];
            int number = 0;
            for (int i = 0; i < _countVsLocal; i++)
            {
                for (int j = 0; j < _countVsLocal; j++)
                {

                    _Verts[number] = new Vertex(
                        new Vector3(_cellSpace * i, 0.0f, _cellSpace * j),
                        new Vector2(texs * i, texs * j));
                    number++;
                }
            }
            VBuffer = Buffer.Create(device, BindFlags.VertexBuffer, _Verts, 0, ResourceUsage.Dynamic, CpuAccessFlags.Write);

            return true;
        }
        private bool IndexBufferInit(Device device)
        {
            _Inds = new uint[CountInds];

            uint index = 0;
            for (int i = 0; i < CountInds - 1; i++)
            {
                for (int j = 0; j < CountInds - 1; j++)
                {
                    _Inds[index] = (uint)(i * CountInds + j);
                    _Inds[index + 1] = (uint)(i * CountInds + j + 1);
                    _Inds[index + 2] = (uint)((i + 1) * CountInds + j);

                    _Inds[index + 3] = (uint)(i * CountInds + j + 1);
                    _Inds[index + 4] = (uint)((i + 1) * CountInds + j + 1);
                    _Inds[index + 5] = (uint)((i + 1) * CountInds + j);

                    index += 6;
                }

            }
            IBuffer = Buffer.Create(device, BindFlags.IndexBuffer, _Inds);
            return true; 
        }
    }
}
