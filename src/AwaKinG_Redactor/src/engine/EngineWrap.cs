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
        #region dll import
        const String _dllPath = "../../../../dll/AwaKinG_Engine.dll";

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainQuadTreeSetVisible")]
        private static extern void _setTerrainQuadTreeVisible(IntPtr pointer, bool set);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainSetWireframe")]
        private static extern void _setTerrainWireframe(IntPtr pointer, bool set);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineCameraManagerSetSpeed")]
        private static extern void _setCameraSpeed(IntPtr pointer, float speed);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainLoad")]
        private static extern void _loadTerrain(IntPtr pointer, String fileName, int len);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainSave")]
        private static extern void _saveTerrain(IntPtr pointer, String fileName, int len);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainRandomize")]
        private static extern void _randomizeTerrain(IntPtr pointer, int diapazon);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainBlur")]
        private static extern void _blurTerrain(IntPtr pointer, int value);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainGenerate")]
        private static extern bool _generateTerrain(IntPtr pointer, int sizeX, int sizeY);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineRenderResizeBuffer")]
        private static extern bool _resizeBuffers(IntPtr pointer, int sizeX, int sizeY);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineCameraManagerSetType")]
        private static extern void _setCameraManagerType(IntPtr pointer, int type);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineGetActive")]
        private static extern bool _getActive(IntPtr pointer);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineSetActive")]
        private static extern void _setActive(IntPtr pointer, int value);
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
        bool _active;
        bool _initialized;
        bool _haveTerrain = false;

        IntPtr _engine;
        PickWorker _pickTerrainWorker = new PickWorker();
        PickWorker _defaultTerrainWorker = new PickWorker();
        HeightPickWorker _heightTerrainWorker = new HeightPickWorker();
        TexturePickWorker _textureTerrainWorker = new TexturePickWorker();
        public void SetConfig()
        {
            float camSpeed = Camera.GetInstance().Speed;
            CameraType camType = Camera.GetInstance().Type;

            int type = 0;
            switch(camType)
            {
                case CameraType.Redactor: type = 0; break;
                case CameraType.RedactorFree: type = 1; break;
            }
            SetCameraManagerType(type);
            _setCameraSpeed(_engine, camSpeed);
            SetTerrainQuadTreeVisible(Terrain.GetInstance().QuadTreeVisible);
            SetTerrainWireframe(Terrain.GetInstance().Wireframe);
        }
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
            _haveTerrain = true;
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
            _haveTerrain = true;
        }
        public void SaveTerrain(String fileName)
        {
            _saveTerrain(_engine, fileName, fileName.Length);
        }
        public void PickTerrain(System.Drawing.Point pt)
        {
            if (_initialized & _active & _haveTerrain)
                _pickTerrainWorker.Pick(_engine, pt);
        }
        public void SetTerrainWorkType(int type)
        {
            switch(type)
            {
                case 0: _pickTerrainWorker = _defaultTerrainWorker; break;
                case 1: _pickTerrainWorker = _heightTerrainWorker; break;
                case 2: _pickTerrainWorker = _textureTerrainWorker; break;
            }
        }
        public void SetTerrainWireframe(bool set)
        {
            _setTerrainWireframe(_engine, set);
        }
        public void SetTerrainQuadTreeVisible(bool set)
        {
            _setTerrainQuadTreeVisible(_engine, set);
        }
    }
    public class PickWorker
    {
        virtual public void Pick(IntPtr engine, System.Drawing.Point mouse)
        {

        }
    }
    public class HeightPickWorker: PickWorker
    {
        [DllImport("../../../../dll/AwaKinG_Engine.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainHeightWork")]
        private static extern int _heightWorkTerrain(IntPtr pointer, int posX, int posY);
        public override void Pick(IntPtr engine, System.Drawing.Point mouse)
        {
            _heightWorkTerrain(engine, mouse.X, mouse.Y);
        }
    }
    public class TexturePickWorker: PickWorker
    {
        [DllImport("../../../../dll/AwaKinG_Engine.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainTextureWork")]
        private static extern int _textureWorkTerrain(IntPtr pointer, int posX, int posY);
        public override void Pick(IntPtr engine, System.Drawing.Point mouse)
        {
            _textureWorkTerrain(engine, mouse.X, mouse.Y);
        }
    }
}
