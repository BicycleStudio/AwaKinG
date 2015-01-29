using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;

using Buffer = SharpDX.Direct3D11.Buffer;
using Device = SharpDX.Direct3D11.Device;
using MapFlags = SharpDX.Direct3D11.MapFlags;
namespace AwaKinG.src.core
{
    public class Camera
    {
        public IInput IInput;

        public Vector3 Position {get { return _Pos; } private set { }}
        protected Vector3 _Pos;
        public Vector3 Look { get { return _Look; } private set { } }
        protected Vector3 _Look;
        protected Vector3 _Up;
        protected Vector3 _Right;

        public Matrix ViewMatrix;

        public Camera()
        {
            _Look = new Vector3(0.0f, 0.0f, 1.0f);
            _Right = new Vector3(1.0f, 0.0f, 0.0f);
            _Pos = new Vector3(0.0f, 0.0f, 0.0f);
        }
        public void Update()
        {
            
            float delta = 1.0f;
            if (IInput.LeftShift)
                delta = 4.0f;
            /*switch (_Camera_Type)
            {
                case Cam_type.Redactor:*/
        if (IInput.LeftControl)
        {
            Yaw(IInput.MX / 1000.0f);
            Pitch(IInput.MY / 1000.0f);
        }
        Walk(IInput.MZ * delta / 10.0f);
                 /*   break;
                case Cam_type.Free:
                    Yaw(IInput.MX / 1000.0f);
                    Pitch(IInput.MY / 1000.0f);
                    if (IInput.W)
                        Walk(1.1f * delta);
                    if (IInput.S)
                        Walk(-1.1f * delta);
                    if (IInput.A)
                        Strafe(-1.1f * delta);
                    if (IInput.D)
                        Strafe(1.1f * delta);
                    break;
            }
            if (IInput.R && IInput.LeftControl)
                _Camera_Type = Cam_type.Redactor;
            if (IInput.F && IInput.LeftControl)
                _Camera_Type = Cam_type.Free;
            */
            Frame();
        }
        private void Pitch(float angle)
        {
            Matrix T = Matrix.RotationAxis(_Right, angle);
            _Up = Vector3.TransformCoordinate(_Up, T);
            if (_Up.Y >= 0)
                _Look = Vector3.TransformCoordinate(_Look, T);
        }
        private void Yaw(float angle)
        {
            Matrix T = Matrix.RotationY(angle);
            _Right = Vector3.TransformCoordinate(_Right, T);
            _Look = Vector3.TransformCoordinate(_Look, T);
        }
        private void Walk(float units)
        {
            //if (type == CamType.First_Person)
            //_Pos += new Vector3(_Look.X, 0.0f, _Look.Z) * units;

            // if (type == CamType.Redaction)
            _Pos += _Look * units;
        }
        private void WalkLook(float units)
        {
            _Pos += _Look * units;
        }
        private void Strafe(float units)
        {
            /// case CamType.Redaction:
            _Pos += _Right * units;
            ///    break;
            /// case CamType.First_Person:
            ////  _Pos += new Vector3(_Right.X, 0.0f, _Right.Z) * units;
            ///   break;
        }
        private void Strafez(float units)
        {
            _Pos += _Up * units;
        }
        private void Frame()
        {
            Matrix V = new Matrix(0.0f);
            _Look = Vector3.Normalize(_Look);
            _Up = Vector3.Cross(_Look, _Right);
            _Up = Vector3.Normalize(_Up);

            //Right = Vector3.Cross(Up, Look);
            //Right = Vector3.Normalize(Right);

            float x = -Vector3.Dot(_Right, _Pos);
            float y = -Vector3.Dot(_Up, _Pos);
            float z = -Vector3.Dot(_Look, _Pos);

            V[0, 0] = _Right.X; V[0, 1] = _Up.X; V[0, 2] = _Look.X; V[0, 3] = 0.0f;
            V[1, 0] = _Right.Y; V[1, 1] = _Up.Y; V[1, 2] = _Look.Y; V[1, 3] = 0.0f;
            V[2, 0] = _Right.Z; V[2, 1] = _Up.Z; V[2, 2] = _Look.Z; V[2, 3] = 0.0f;
            V[3, 0] = x; V[3, 1] = y; V[3, 2] = z; V[3, 3] = 1.0f;
            ViewMatrix = V;
        }
    }
}
