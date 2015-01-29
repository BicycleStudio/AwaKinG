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
        bool Initialize(System.Windows.Forms.Control control);
        void ResizeBuffer(System.Drawing.Size s);
        void AddStaticModelFromFile(String fpath);
        IInput Input { get; set; }

    }
}
