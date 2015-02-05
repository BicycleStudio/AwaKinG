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
           EntryPoint = "EngineTerrainSetWorkType")]
        private static extern void _setTerrainWorkType(IntPtr pointer, int type);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainPick")]
        private static extern int _pickTerrain(IntPtr pointer, int posX, int posY);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainLoad")]
        private static extern void _loadTerrain(IntPtr pointer, String fileName, int len);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainSave")]
        private static extern IntPtr _saveTerrain(IntPtr pointer, String fileName, int len);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainRandomize")]
        private static extern bool _randomizeTerrain(IntPtr pointer, int diapazon);
      
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainBlur")]
        private static extern bool _blurTerrain(IntPtr pointer, int value);
      
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainGenerate")]
        private static extern bool _generateTerrain(IntPtr pointer, int sizeX, int sizeY);
        
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineRenderResizeBuffer")]
        private static extern bool _resizeBuffers(IntPtr pointer, int sizeX, int sizeY);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineSetCameraManagerType")]
        private static extern void _setCameraManagerType(IntPtr pointer, int type);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineGetActive")]
        private static extern bool _getActive(IntPtr pointer);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineSetActive")]
        private static extern int _setActive(IntPtr pointer, int value);
        
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineCreateMapFromFile")]
        private static extern void _createMapFromFile(IntPtr pointer, String fileName, int len);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineGetPointer")]
        private static extern IntPtr _getPointer();

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineInitialize")]
        private static extern bool _initialize(IntPtr pointer, IntPtr mainHwnd, IntPtr hwnd, int sizeX, int sizeY);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineRelease")]
        private static extern void _release(IntPtr pointer);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineUpdate")]
        private static extern bool _update(IntPtr pointer);
        #endregion
        public bool Done { get { return _done; } set { _done = value; } }
        bool _done = false;
        bool _initialized;
        IntPtr _engine;
        bool _active;
        public EngineWrap(IntPtr mainWindow, IntPtr window, System.Drawing.Size size) 
        {
            _engine = _getPointer();
            _initialize(_engine, mainWindow, window, size.Width, size.Height);
            _initialized = true;
        }
        public void Update()
        {
            Done = _update(_engine);
        }
        public void Shutdown()
        {
            _release(_engine);
        }
        public void CreateMapFromFile(String fileName)
        {
            _createMapFromFile(_engine, fileName, fileName.Length);
        }
        public void SetActive(bool setValue)
        {
            _active = setValue;
            if (_active)
                _setActive(_engine, 1);
        }
        public bool GetActive()
        {
            return _active;
        }
        public void SetCameraManagerType(int type)
        {
            _setCameraManagerType(_engine, type);
        }
        public void ResizeRenderBuffers(System.Drawing.Size size)
        {
            if(_initialized)
            {
                bool b = _resizeBuffers(_engine, size.Width, size.Height);
            }
        }
        public void GenerateTerrain(int gridX, int gridY)
        {
            _generateTerrain(_engine, gridX, gridY);
        }
        public void RandomizeTerrain(int diapazon)
        {
            _randomizeTerrain(_engine, diapazon);
        }
        public void BlurTerrain(int value)
        {
            _blurTerrain(_engine, value);
        }
        public void LoadTerrain(String fileName)
        {
            _loadTerrain(_engine, fileName, fileName.Length);
        }
        public void SaveTerrain(String fileName)
        {
            IntPtr str = _saveTerrain(_engine, fileName, fileName.Length);

            string sttt =Marshal.PtrToStringAnsi(str);
        }
        public int PickTerrain(System.Drawing.Point pt)
        {

            return _pickTerrain(_engine, pt.X, pt.Y);
        }
        public void SetTerrainWorkType(int type)
        {
            _setTerrainWorkType(_engine, type);
        }
    }
}
