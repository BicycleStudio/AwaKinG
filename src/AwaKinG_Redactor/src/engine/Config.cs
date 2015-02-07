using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AwaKinG_Redactor.src.engine
{
    public enum CameraType { Undefined, Redactor, RedactorFree }
    public class Config
    {
        public enum SystemStringType 
        {   
            Undefined, OpenBlock, CloseBlock,
            Camera, CameraSpeed, CameraType, 
            Terrain
        }
        private struct SystemStrings
        {
            public const string OpenBlock = "{";
            public const string CloseBlock = "}";
            public const string Camera = "camera";
            public const string CameraSpeed = "speed";
            public const string CameraType = "type";
            public const string Terrain = "terrain";
        }
        static Config _config = new Config();
        public static Config GetInstance()
        {
            return _config;
        }
        private Config()
        { 

        }
        private SystemStringType GetSystemStringType(String dirtyString)
        {
            if (dirtyString.Contains(SystemStrings.OpenBlock)) return SystemStringType.OpenBlock;
            if (dirtyString.Contains(SystemStrings.CloseBlock)) return SystemStringType.CloseBlock;
            if (dirtyString.Contains(SystemStrings.Camera)) return SystemStringType.Camera;
            if (dirtyString.Contains(SystemStrings.CameraType)) return SystemStringType.CameraType;
            if (dirtyString.Contains(SystemStrings.CameraSpeed)) return SystemStringType.CameraSpeed;
            if (dirtyString.Contains(SystemStrings.Terrain)) return SystemStringType.Terrain;
            return SystemStringType.Undefined;
        }
        private int GetInt(String dirtyString, int defaulValue)
        {
            int ret_ = defaulValue;
            string[] sts = dirtyString.Split(' ');
            for (int i = 0; i < sts.Count(); i++)
            {
                try
                {
                    ret_ = Convert.ToInt32(sts[i]);
                    break;
                }
                catch (Exception)
                {
                    continue;
                }
            }
            return ret_;
        }
        private float GetFloat(String dirtyString, float defaulValue)
        {
            float ret_ = defaulValue;
            string[] sts = dirtyString.Split(' ');
            for(int i=0; i<sts.Count(); i++)
            {
                try
                {
                    ret_ = Convert.ToSingle(sts[i].Replace('.',','));
                    break;
                }
                catch(Exception)
                {
                    continue;
                }
            }
            return ret_;
        }
        public void Load(String fileName)
        {
            StreamReader sr = null;
            try
            {
                sr = new StreamReader(fileName);
            }
            catch (Exception ex)
            {
                return;
            }
            SystemStringType type_ = SystemStringType.Undefined;
            while (!sr.EndOfStream)
            {
                try
                {
                    String str_ = sr.ReadLine();
                    type_ = GetSystemStringType(str_);
                    ReadSystemBlock(type_, sr);
                }
                catch(Exception ex)
                {
                    if (sr.EndOfStream) break;
                    return;
                }
            }
            sr.Close();
        }
        public void Save(String fileName)
        {
            StreamWriter sw = new StreamWriter(fileName);

            sw.Write(SystemStrings.Camera + Environment.NewLine);
            sw.Write(SystemStrings.OpenBlock + Environment.NewLine);
            sw.Write("\t" + SystemStrings.CameraSpeed + " = " + Camera.GetInstance().Speed.ToString() + Environment.NewLine);
            sw.Write("\t" + SystemStrings.CameraType + " = " + Camera.GetInstance().GetTypeString() + Environment.NewLine);
            sw.Write(SystemStrings.CloseBlock + Environment.NewLine);

            sw.Write(SystemStrings.Terrain + Environment.NewLine);
            sw.Write(SystemStrings.OpenBlock + Environment.NewLine);
            sw.Write(SystemStrings.CloseBlock);
            sw.Close();
        }
        private void ReadSystemBlock(SystemStringType type_, StreamReader sr)
        {
            String str_ = "";
            switch (type_)
            {
                case SystemStringType.Camera:
                    try { str_ = sr.ReadLine(); } catch (Exception ex) { return; }
                    type_ = GetSystemStringType(str_);
                    while (type_ != SystemStringType.CloseBlock)
                    {
                        switch(type_)
                        {
                            case SystemStringType.OpenBlock: break;
                            case SystemStringType.CameraSpeed: Camera.GetInstance().Speed = GetFloat(str_, Camera.GetInstance().Speed); break;
                            case SystemStringType.CameraType:Camera.GetInstance().setType(str_);break;
                        }
                        try { str_ = sr.ReadLine(); } catch (Exception ex) { return; }
                        type_ = GetSystemStringType(str_);
                    }
                    break;
                case SystemStringType.Terrain:
                    try { str_ = sr.ReadLine(); } catch (Exception ex) { return; }
                    type_ = GetSystemStringType(str_);
                    while (type_ != SystemStringType.CloseBlock)
                    {
                        switch(type_)
                        {
                            case SystemStringType.OpenBlock: break;
                        }
                        try { str_ = sr.ReadLine(); } catch (Exception ex) { return; }
                        type_ = GetSystemStringType(str_);
                    }
                    break;
                default: break;
            }
        }
    }
    public class Terrain
    {
        public static Terrain GetInstance()
        {
            return _terrain;
        }
        private static Terrain _terrain = new Terrain();
        private Terrain(){}
    }
    public class Camera
    {
        public float Speed { get { return _speed; } set { _speed = value; } }
        private float _speed = 1.0f;
        public CameraType Type { get { return _type; } set { _type = value; } }
        private CameraType _type = CameraType.Redactor;

        private enum SystemStringType { Undefined, TypeRedactor, TypeRedactorFree }
        public struct SystemStrings
        {
            public const string CameraTypeRedactor = "redactor";
            public const string CameraTypeRedactorFree = "redFree";
        }
        public String GetTypeString()
        {
            switch(_type)
            {
                case CameraType.Redactor: return SystemStrings.CameraTypeRedactor;
                case CameraType.RedactorFree: return SystemStrings.CameraTypeRedactorFree;
            }
            return SystemStrings.CameraTypeRedactor;
        }
        private SystemStringType GetSystemStringType(String dirtyString)
        {
            if (dirtyString.Contains(SystemStrings.CameraTypeRedactor)) 
                return SystemStringType.TypeRedactor;
            if (dirtyString.Contains(SystemStrings.CameraTypeRedactorFree)) 
                return SystemStringType.TypeRedactorFree;
            return SystemStringType.Undefined;
        }
        public void setType(String set)
        {
            switch (GetSystemStringType(set))
            {
                case SystemStringType.TypeRedactor:
                    _type = CameraType.Redactor; break;
                case SystemStringType.TypeRedactorFree:
                    _type = CameraType.RedactorFree; break;
                default: break;
            }
        }
        public static Camera GetInstance()
        {
            return _camera;
        }
        private static Camera _camera = new Camera();
        private Camera() { }
    }
}
