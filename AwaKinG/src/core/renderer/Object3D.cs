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
    public struct Vertex
    {
        public Vector3 Position;
        public Vector2 TexCoords;
        public Vector3 Normal;
        public Vertex(Vector3 pos, Vector2 texs, Vector3 nor)
        {
            Position = pos;
            TexCoords = texs;
            Normal = nor;
        }
        public Vertex(Vector3 pos, Vector2 texs)
        {
            Position = pos;
            TexCoords = texs;
            Normal = new Vector3(0.0f, 1.0f, 0.0f);
        }
    }
    public struct CB_World_Pick
    {
        public Matrix World;
    }
    public class Object3D : IObject3D
    {
        protected Vertex[] _Verts = null;
        protected uint[] _Inds = null;
        protected String _FileName = "";
        protected int _CountVerts;
        protected Matrix _Transform;

        public CB_World_Pick CBWorldPick;
        public ShaderResourceView Texture;
        public Buffer VBuffer = null;
        public Buffer IBuffer = null;
        public Buffer CBufferWorld = null;
        public int CountInds;
        public String ErrorMessage = "";

        public void SetFileName(String fname)
        {
            _FileName = fname;
        }
        public virtual void Render()
        {

        }
        public virtual bool Initialize(Device device)
        {
            return true;
        }
    }
}
