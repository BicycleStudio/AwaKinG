using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Windows.Forms;
using SharpDX;
using SharpDX.Win32;
using System.IO;
using SharpDX.Multimedia;
using SharpDX.DirectInput;

namespace AwaKinG.src.core
{
    public class Input : IInput
    {
        #region Variables / Properties
        DirectInput _DirectInput;
        Keyboard _Keyboard;
        Mouse _Mouse;

        public KeyboardState _KeyboardState;
        MouseState _MouseState;
        public float MX
        {
            get { return _MouseState.X; }
            set { }
        }
        public float MY
        {
            get { return _MouseState.Y; }
            set { }
        }
        public float MZ
        {
            get { return _MouseState.Z; }
            set { }
        }
        public bool W
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.W); }
            set { }
        }
        public bool A
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.A); }
            set { }
        }
        public bool S
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.S); }
            set { }
        }
        public bool D
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.D); }
            set { }
        }
        public bool F
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.F); }
            set { }
        }
        public bool R
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.R); }
            set { }
        }
        public bool LeftShift
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.LeftShift); }
            set { }
        }
        public bool LeftControl
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.LeftControl); }
            set { }
        }
        public bool LeftAlt
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.LeftAlt); }
            set { }
        }
        public bool RightShift
        {
            get { return _KeyboardState.PressedKeys.Contains(Key.RightShift); }
            set { }
        }
        #endregion

        #region Methods
        internal String Initialize(IntPtr main_hwnd)
        {
            _DirectInput = new DirectInput();

            _Mouse = new Mouse(_DirectInput);
            _Mouse.Properties.AxisMode = DeviceAxisMode.Relative;
            _Mouse.SetCooperativeLevel(main_hwnd, CooperativeLevel.Background | CooperativeLevel.NonExclusive);
            try
            {
                _Mouse.Acquire();
            }
            catch (SharpDX.SharpDXException ex)
            {
                return ex.Message;
            }

            _Keyboard = new Keyboard(_DirectInput);
            _Keyboard.Properties.BufferSize = 256;

            _Keyboard.SetCooperativeLevel(main_hwnd, CooperativeLevel.Background | CooperativeLevel.NonExclusive);

            try
            {
                _Keyboard.Acquire();
            }
            catch (SharpDX.SharpDXException ex)
            {
                return ex.Message;
            }
            return "OK";
        }
        public void GetMouseButtons(out bool bt_1, out bool bt_2, out bool w)
        {
            bt_1 = _MouseState.Buttons[0];
            bt_2 = _MouseState.Buttons[1];
            w = _MouseState.Buttons[2];
        }
        public void Dispose()
        {
            // Release the mouse.
            if (_Mouse != null)
            {
                _Mouse.Unacquire();
                _Mouse.Dispose();
                _Mouse = null;
            }

            // Release the keyboard.
            if (_Keyboard != null)
            {
                _Keyboard.Unacquire();
                _Keyboard.Dispose();
                _Keyboard = null;
            }

            // Release the main interface to direct input.
            if (_DirectInput != null)
            {
                _DirectInput.Dispose();
                _DirectInput = null;
            }
        }
        public bool Frame()
        {
            if (!ReadKeyboard())
                return false;
            if (!ReadMouse())
                return false;
            return true;
        }
        private bool ReadKeyboard()
        {
            var resultCode = ResultCode.Ok;

            _KeyboardState = new KeyboardState();

            try
            {
                // Read the keyboard device.
                _Keyboard.GetCurrentState(ref _KeyboardState);
            }
            catch (SharpDX.SharpDXException ex)
            {
                resultCode = ex.Descriptor;
            }

            try
            {
                // If the keyboard lost focus or was not acquired then try to get control back.
                if (resultCode == ResultCode.InputLost || resultCode == ResultCode.NotAcquired)
                    _Keyboard.Acquire();
                else if (resultCode != ResultCode.Ok)
                    return false;
            }
            catch (SharpDX.SharpDXException ex)
            {
                if (ex.Descriptor == ResultCode.ReadOnly)
                    return true;
                resultCode = ex.Descriptor;
            }
            catch (Exception)
            {
                return false;
            }

            // If the keyboard lost focus or was not acquired then try to get control back.
            if (resultCode == ResultCode.InputLost || resultCode == ResultCode.NotAcquired)
                _Keyboard.Acquire();
            else if (resultCode != ResultCode.Ok)
                return false;

            return true;
        }
        private bool ReadMouse()
        {
            var resultCode = ResultCode.Ok;

            _MouseState = new MouseState();

            try
            {
                // Read the mouse device.
                _Mouse.GetCurrentState(ref _MouseState);
            }
            catch (SharpDX.SharpDXException ex)
            {
                resultCode = ex.Descriptor;
            }
            try
            {
                // If the mouse lost focus or was not acquired then try to get control back.
                if (resultCode == ResultCode.InputLost || resultCode == ResultCode.NotAcquired)
                    _Mouse.Acquire();
                else if (resultCode != ResultCode.Ok)
                    return false;
            }
            catch (SharpDX.SharpDXException ex)
            {
                if (ex.Descriptor == ResultCode.ReadOnly)
                    return true;
                resultCode = ex.Descriptor;
            }
            catch (Exception)
            {
                return false;
            }

            // If the mouse lost focus or was not acquired then try to get control back.
            if (resultCode == ResultCode.InputLost || resultCode == ResultCode.NotAcquired)
                _Mouse.Acquire();
            else if (resultCode != ResultCode.Ok)
                return false;

            return true;
        }
        public bool IsEscapePressed()
        {
            return _KeyboardState != null && _KeyboardState.PressedKeys.Contains(Key.Escape);
        }
        public bool IsWPressed()
        {
            return _KeyboardState != null && _KeyboardState.PressedKeys.Contains(Key.W);
        }
        public bool IsAPressed()
        {
            return _KeyboardState != null && _KeyboardState.PressedKeys.Contains(Key.A);
        }
        public bool IsSPressed()
        {
            return _KeyboardState != null && _KeyboardState.PressedKeys.Contains(Key.S);
        }
        public bool IsDPressed()
        {
            return _KeyboardState != null && _KeyboardState.PressedKeys.Contains(Key.D);
        }
        #endregion
    }
}
