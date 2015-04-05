using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace AwaKinG_Editor {
  public static class EngineDll {
    const String _dllPath = "../../../../dll/AwaKinG_Engine.dll";
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl,EntryPoint = "initialize")]
    public extern static bool Initialize(IntPtr mainHandle,IntPtr renderHandle);
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "update")]
    public extern static void Update();
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "release")]
    public extern static void Release();
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "setActive")]
    public extern static void SetActive(bool value);
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "resizeBuffer")]
    public extern static void ResizeBuffer(int sizeX, int sizeY);
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "setCameraType")]
    public extern static bool SetCameraType(int type);
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "openMap")]
    public extern static bool OpenMap(String fileName, int lenght);
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "saveMap")]
    public extern static bool SaveMap(String fileName, int lenght);
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "newMap")]
    public extern static void newMap();
  }
  public static class TerrainDll {
    const String _dllPath = "../../../../dll/AwaKinG_Engine.dll";
    [DllImport(_dllPath, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "createTerrain")]
    public extern static int createTerrain(int sizeX, int sizeY);
  }
  public class Engine {
    public bool Done { get { return _done; } set { _done = value; if (_done) EngineDll.Release(); } }
    private bool _done = false;
    private bool _active = false;
    private bool _initialized = false;
    static Engine _engine = new Engine();

    private Engine() {
    }
    public static Engine GetInstance() {
      return _engine;
    }
    public bool Initialize(IntPtr mainHandle, IntPtr renderHandle) {
      _initialized = EngineDll.Initialize(mainHandle, renderHandle);
      return _initialized;
    }
    public void Update() {
      EngineDll.Update();
    }
    public void SetActive(bool set) {
      EngineDll.SetActive(set);
      _active = set;
    }
    public void Resize(System.Drawing.Size size) {
      if (_initialized)
        EngineDll.ResizeBuffer(size.Width, size.Height);
    }
  }
}
