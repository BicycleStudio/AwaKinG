using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace AwaKinG_Redactor.src.engine
{
    public class EngineWrap
    {
        const String _dllPath = "../../../../dll/AwaKinG_Engine.dll";
        #region dll import
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineSetCameraManagerType")]
        public static extern void EngineSetCameraManagerType(IntPtr pointer, int type);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineGetActive")]
        public static extern bool EngineGetActive(IntPtr pointer);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineSetActive")]
        public static extern int EngineSetActive(IntPtr pointer, int value);
        
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineCreateMapFromFile")]
        public static extern void EngineCreateMapFromFile(IntPtr pointer, String fileName, int len);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineGetPointer")]
        public static extern IntPtr EngineGetPointer();

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineInitialize")]
        public static extern bool EngineInitialize(IntPtr pointer, IntPtr mainHwnd, IntPtr hwnd, int sizeX, int sizeY);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineRelease")]
        public static extern void EngineRelease(IntPtr pointer);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineUpdate")]
        public static extern bool EngineUpdate(IntPtr pointer);
        #endregion
        public bool Done { get { return _done; } set { _done = value; } }
        bool _done = false;
        IntPtr _engine;
        bool _active;
        public EngineWrap(IntPtr mainWindow, IntPtr window, System.Drawing.Size size) 
        {
            _engine = EngineGetPointer();
            bool init = EngineInitialize(_engine, mainWindow, window, size.Width, size.Height);
        }
        public void Update()
        {
            Done = EngineUpdate(_engine);
        }
        public void Shutdown()
        {
            EngineRelease(_engine);
        }
        public void CreateMapFromFile(String fileName)
        {
            EngineCreateMapFromFile(_engine, fileName, fileName.Length);
        }
        public void SetActive(bool setValue)
        {
            _active = setValue;
            if (_active)
                EngineSetActive(_engine, 1);
        }
        public bool GetActive()
        {
            return _active;
        }
        public void SetCameraManagerType(int type)
        {
            EngineSetCameraManagerType(_engine, type);
        }
    }
}
