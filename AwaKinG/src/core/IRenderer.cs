using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AwaKinG.src.core
{
    interface IRenderer
    {
        void Render();
        bool Initialize(int width, int height, bool fullscreen, IntPtr window);
        void ResizeBuffer(System.Drawing.Size s);
    }
}
