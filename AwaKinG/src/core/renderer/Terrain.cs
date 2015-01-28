using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AwaKinG.src.core.renderer
{
    public class Terrain : Object3D
    {
        public override bool Initialize()
        {
            if (!VertexBufferInit()) return false;
            if (!IndexBufferInit()) return false;

            return true;
        }
        private bool VertexBufferInit()
        { 
            
            return true;
        }
        private bool IndexBufferInit()
        {
            return true; 
        }
    }
}
