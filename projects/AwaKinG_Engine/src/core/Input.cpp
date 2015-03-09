#include "Input.h"

Input::Input(){
	errorMessage = ED_UNDEFINED;
  _device = 0;
  _keyboard = 0;
  _mouse = 0;
}

bool Input::initialize(HWND hwnd){
  _hwnd = hwnd;

  CHECK_RESULT(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&_device, NULL), EDI_CREATE);

  CHECK_RESULT(_device->CreateDevice(GUID_SysMouse, &_mouse, NULL), EDI_MOUSE_CREATE);
  CHECK_RESULT(_mouse->SetDataFormat(&c_dfDIMouse),EDI_SET_DATA_FORMAT);
  CHECK_RESULT(_mouse->SetCooperativeLevel(_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND),EDI_SET_COOPERATIVE_LEVEL);

  CHECK_RESULT(_device->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL),EDI_KEYBOARD_CREATE);
  CHECK_RESULT(_keyboard->SetDataFormat(&c_dfDIKeyboard),EDI_SET_DATA_FORMAT);
  CHECK_RESULT(_keyboard->SetCooperativeLevel(_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND),EDI_SET_COOPERATIVE_LEVEL);

  return true;
}
void Input::shutdown(){
  SAFE_RELEASE(_mouse);
  SAFE_RELEASE(_keyboard);
  SAFE_RELEASE(_device);
}
bool Input::update(){
  CHECK_RESULT(_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&_mouseState), EDI_GET_DEVICE_STATE);
  CHECK_RESULT(_keyboard->GetDeviceState(sizeof(_keyState), (LPVOID)&_keyState), EDI_GET_DEVICE_STATE);

  return true;
}
bool Input::acquire() {
  CHECK_RESULT(_mouse->Acquire(), EDI_ACQUIRE);
  CHECK_RESULT(_keyboard->Acquire(), EDI_ACQUIRE);
  return true;
}
bool Input::LControl() {
  return _keyState[DIK_LCONTROL];
}
bool Input::LShift() {
  return _keyState[DIK_LSHIFT];
}
bool Input::W() {
  return _keyState[DIK_W];
}
bool Input::A() {
  return _keyState[DIK_A];
}
bool Input::S() {
  return _keyState[DIK_S];
}
bool Input::D() {
  return _keyState[DIK_D];
}
float Input::MouseX() {
  return ((float)_mouseState.lX) / 500.0f;
}
float Input::MouseY() {
  return ((float)_mouseState.lY) / 500.0f;
}
float Input::MouseZ() {
  return ((float)_mouseState.lZ) / 500.0f;
}