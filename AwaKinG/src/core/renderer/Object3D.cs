using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpDX;
using SharpDX.Direct3D11;
using Buffer = SharpDX.Direct3D11.Buffer;

namespace AwaKinG.src.core.renderer
{
    public class Object3D : IObject3D
    {
        Buffer VBuffer;
        Buffer IBuffer;

        public virtual void Render()
        {

        }
        public virtual bool Initialize()
        {
            return true;
        }
    }
}
