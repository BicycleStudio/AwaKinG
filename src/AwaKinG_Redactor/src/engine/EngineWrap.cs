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
            EntryPoint = "EngineTerrainSetTerraPenSmoothKoeff")]
        private static extern void _terraPenSetSmoothKoeff(IntPtr pointer, float value);

        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainDiamondSquare")]
        private static extern void _terraDiamondSquare(IntPtr pointer);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainSetPenVisible")]
        private static extern void _setTerraPenVisible(IntPtr pointer, bool set);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainSetTerraPenSize")]
        private static extern void _setTerraPenSize(IntPtr pointer,  int in_, int out_);
        [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
           EntryPoint = "EngineTerrainSetTerraPenHard")]
        private static extern void _setTerraPenHard(IntPtr pointer, float hard);
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
        public PickWorker pickTerrainWorker = new PickWorker();
        public PickWorker defaultTerrainWorker = new PickWorker();
        public HeightPickWorker heightShowWorker = new HeightPickWorker();
        public ApplyHeightPickWorker applyHeightWorker = new ApplyHeightPickWorker();
        public ApplySmoothInHeightPickWorker applySmoothInHeightWorker = new ApplySmoothInHeightPickWorker();
        public ApplySmoothOutHeightPickWorker applySmoothOutHeightWorker = new ApplySmoothOutHeightPickWorker();
        public ApplySmoothInOutHeightPickWorker applySmoothInOutHeightWorker = new ApplySmoothInOutHeightPickWorker();

        public TexturePickWorker textureTerrainWorker = new TexturePickWorker();
        public void SetTerraPenHeightVisible(bool set)
        {
            _setTerraPenVisible(_engine, set);
        }
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
            _terraDiamondSquare(_engine);
            //_blurTerrain(_engine, 12);
            //_randomizeTerrain(_engine, diapazon);
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
                pickTerrainWorker.Pick(_engine, pt);
        }
        public void SetTerrainWorkType(int type)
        {
            switch(type)
            {
                case 0: pickTerrainWorker = defaultTerrainWorker; break;
                case 1: pickTerrainWorker = heightShowWorker; break;
                case 2: pickTerrainWorker = applyHeightWorker; break;
                case 3: pickTerrainWorker = applySmoothInHeightWorker; break;
                case 4: pickTerrainWorker = applySmoothOutHeightWorker; break;
                case 5: pickTerrainWorker = applySmoothInOutHeightWorker; break;
                case 10: pickTerrainWorker = textureTerrainWorker; break;
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
        public void SetTerraPenHard(float value)
        {
            _setTerraPenHard(_engine, value);
        }
        public void SetTerraPenSize(int in_, int out_)
        {
            _setTerraPenSize(_engine, in_, out_);
        }
        public void SetTerraPenSmoothKoeff(float value)
        {
            _terraPenSetSmoothKoeff(_engine, value);
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
            EntryPoint = "EngineTerrainTerraformingShow")]
        private static extern int _terraformingShow(IntPtr pointer, int posX, int posY);
        public override void Pick(IntPtr engine, System.Drawing.Point mouse)
        {
            _terraformingShow(engine, mouse.X, mouse.Y);
        }
    }
    public class ApplyHeightPickWorker : PickWorker
    {
        [DllImport("../../../../dll/AwaKinG_Engine.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "EngineTerrainTerraformingApply")]
        private static extern int _terraformingApply(IntPtr pointer, int posX, int posY);
        public override void Pick(IntPtr engine, System.Drawing.Point mouse)
        {
            _terraformingApply(engine, mouse.X, mouse.Y);
        }
    }
    public class ApplySmoothInHeightPickWorker : PickWorker
    {
         [DllImport("../../../../dll/AwaKinG_Engine.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
             EntryPoint = "EngineTerrainTerraformApplySmIn")]
         private static extern int _terraformingApplySmoothIn(IntPtr pointer, int posX, int posY);
         public override void Pick(IntPtr engine, System.Drawing.Point mouse)
         {
             _terraformingApplySmoothIn(engine, mouse.X, mouse.Y);
         }
    }
    public class ApplySmoothOutHeightPickWorker : PickWorker
    {
         [DllImport("../../../../dll/AwaKinG_Engine.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
             EntryPoint = "EngineTerrainTerraformApplySmOut")]
         private static extern int _terraformingApplySmoothOut(IntPtr pointer, int posX, int posY);
         public override void Pick(IntPtr engine, System.Drawing.Point mouse)
         {
             _terraformingApplySmoothOut(engine, mouse.X, mouse.Y);
         }
    }
    public class ApplySmoothInOutHeightPickWorker : PickWorker
    {
         [DllImport("../../../../dll/AwaKinG_Engine.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,
             EntryPoint = "EngineTerrainTerraformApplySmInOut")]
         private static extern int _terraformingApplySmoothInOut(IntPtr pointer, int posX, int posY);
         public override void Pick(IntPtr engine, System.Drawing.Point mouse)
         {
             _terraformingApplySmoothInOut(engine, mouse.X, mouse.Y);
         }
    }
    public class TexturePickWorker: PickWorker
    {
        public override void Pick(IntPtr engine, System.Drawing.Point mouse)
        {
            //_textureWorkTerrain(engine, mouse.X, mouse.Y);
        }
    }
}
