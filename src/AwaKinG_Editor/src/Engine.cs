using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace AwaKinG_Editor
{
    public static class EngineDll
    {
        const String _dllPath = "../../../../dll/AwaKinG_Engine.dll";
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "getEnginePointer")]
        public extern static IntPtr getEnginePointer();
    }
    public class Engine
    {
        public bool done { get { return _done; } set { _done = value; } }
        private bool _done = false;
        static Engine _engine = new Engine();
        private IntPtr _enginePointer;

        private Engine() 
        {
            _enginePointer = EngineDll.getEnginePointer();
        }
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
