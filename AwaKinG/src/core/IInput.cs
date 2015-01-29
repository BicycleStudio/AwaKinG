using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AwaKinG.src.core
{
    public interface IInput
    {
        float MX { get; set; }
        float MY { get; set; }
        float MZ { get; set; }

        bool W { get; set; }
        bool A { get; set; }
        bool S { get; set; }
        bool D { get; set; }

        bool RightShift { get; set; }
        bool LeftShift { get; set; }
        bool LeftControl { get; set; }
        bool LeftAlt { get; set; }

        bool F { get; set; }
        bool R { get; set; }
    }
}
