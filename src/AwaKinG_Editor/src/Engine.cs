using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AwaKinG_Editor
{
    public static class EngineDll
    {

    }
    public class Engine
    {
        public bool done { get { return _done; } set { _done = value; } }
        private bool _done = false;
        static Engine _engine = new Engine();

        private Engine() { }
        public static Engine getInstance()
        {
            return _engine;
        }
        public void update()
        {

        }
        public void setActive(bool set)
        {

        }
        public void resize(System.Drawing.Size size)
        {

        }
    }
}
