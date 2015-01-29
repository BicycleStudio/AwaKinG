using System;
using System.IO;
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
    public class StaticObject : Object3D
    {
        public override void Render()
        {
            CBWorldPick.World = _Transform;
        }
        public override bool Initialize(Device device)
        {
            if (!File.Exists(_FileName)) return false;
            try
            {
                _Transform = Matrix.Identity;
                Texture = ShaderResourceView.FromFile(device, _FileName.Substring(0, _FileName.Length - 3) + "dds");
                ReadFromFile(_FileName);

                VertexBufferInit(device);
                IndexBufferInit(device);

                CBufferWorld = new Buffer(device, Utilities.SizeOf<CB_World_Pick>(), ResourceUsage.Default, BindFlags.ConstantBuffer, CpuAccessFlags.None, ResourceOptionFlags.None, 0);
            }
            catch(Exception ex)
            {
                ErrorMessage = ex.Message;
                return false;
            }
            return true;
        }
        private void ReadFromFile(String path)
        {
            StreamReader sr = new StreamReader(path);

            String st = sr.ReadLine();
            String[] sts = st.Split(' ');
            int num_v = Convert.ToInt32(sts[0]);
            int num_f = Convert.ToInt32(sts[1]);
            int num_tv = Convert.ToInt32(sts[2]);

            List<Vector3> Vertexs = new List<Vector3>();
            List<Vector3> Normals = new List<Vector3>();
            List<Vector2> TVertexs = new List<Vector2>();

            List<Int3> VertexsFaces = new List<Int3>();
            List<Int3> TVertexsFaces = new List<Int3>();

            for (int i = 0; i < num_v; i++)
            {
                st = sr.ReadLine();
                sts = st.Split(' ');

                float v_1 = Convert.ToSingle(sts[0].Replace('.',','));
                float v_2 = Convert.ToSingle(sts[1].Replace('.', ','));
                float v_3 = Convert.ToSingle(sts[2].Replace('.', ','));

                Vertexs.Add(new Vector3(v_1, v_3, v_2));
                st = sr.ReadLine();
                sts = st.Split(' ');

                v_1 = Convert.ToSingle(sts[0].Replace('.', ','));
                v_2 = Convert.ToSingle(sts[1].Replace('.', ','));
                v_3 = Convert.ToSingle(sts[2].Replace('.', ','));
                Normals.Add(new Vector3(v_1, v_3, v_2));
            }
            for (int i = 0; i < num_tv; i++)
            {
                st = sr.ReadLine();
                sts = st.Split(' ');

                float v_1 = Convert.ToSingle(sts[0].Replace('.', ','));
                float v_2 = Convert.ToSingle(sts[1].Replace('.', ','));

                TVertexs.Add(new Vector2(v_1, 1.0f - v_2));
            }
            for (int i = 0; i < num_f; i++)
            {
                st = sr.ReadLine();
                sts = st.Split(' ');

                int v_1 = Convert.ToInt32(sts[0]);
                int v_2 = Convert.ToInt32(sts[1]);
                int v_3 = Convert.ToInt32(sts[2]);

                VertexsFaces.Add(new Int3(v_1, v_3, v_2));
                st = sr.ReadLine();
                sts = st.Split(' ');

                v_1 = Convert.ToInt32(sts[0]);
                v_2 = Convert.ToInt32(sts[1]);
                v_3 = Convert.ToInt32(sts[2]);
                TVertexsFaces.Add(new Int3(v_1, v_3, v_2));
            }
            sr.Close();

            List<Vertex> VERTS = new List<Vertex>();
            int count_v = 0;
            for (int i = 0; i < num_f; i++)
            {
                VERTS.Add(new Vertex(Vertexs[VertexsFaces[i].X], TVertexs[TVertexsFaces[i].X], Normals[VertexsFaces[i].X]));
                VERTS.Add(new Vertex(Vertexs[VertexsFaces[i].Y], TVertexs[TVertexsFaces[i].Y], Normals[VertexsFaces[i].Y]));
                VERTS.Add(new Vertex(Vertexs[VertexsFaces[i].Z], TVertexs[TVertexsFaces[i].Z], Normals[VertexsFaces[i].Z]));
                count_v += 3;
            }
            Vertexs.Clear(); Normals.Clear(); TVertexs.Clear(); TVertexsFaces.Clear(); VertexsFaces.Clear();

            _Inds = new uint[count_v];
            List<Vertex> Optimized_VERTS = new List<Vertex>();
            for (uint i = 0; i < count_v; i++)
                _Inds[i] = i;

            bool write = true;

            Optimized_VERTS.Add(VERTS[0]);

            for (int i = 1; i < count_v; i++)
            {
                write = true;

                for (int j = 0; j < Optimized_VERTS.Count; j++)
                {
                    if (VERTS[i].Position == Optimized_VERTS[j].Position && VERTS[i].TexCoords == Optimized_VERTS[j].TexCoords)
                    {
                        write = false;
                        _Inds[i] = (uint)j;
                    }
                }
                if (write)
                {
                    Optimized_VERTS.Add(VERTS[i]);
                    _Inds[i] = (uint)(Optimized_VERTS.Count - 1);
                }
            }
            _Verts = new Vertex[Optimized_VERTS.Count];
            CountInds = count_v;
            for (int i = 0; i < Optimized_VERTS.Count; i++)
                _Verts[i] = Optimized_VERTS[i];
        }
        private bool VertexBufferInit(Device device)
        {
            VBuffer = Buffer.Create(device, BindFlags.VertexBuffer, _Verts, 0, ResourceUsage.Dynamic, CpuAccessFlags.Write);

            return true;
        }
        private bool IndexBufferInit(Device device)
        {
            IBuffer = Buffer.Create(device, BindFlags.IndexBuffer, _Inds);
            return true;
        }
    }
}
