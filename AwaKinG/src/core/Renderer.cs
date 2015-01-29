using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AwaKinG.src.core.renderer;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using Effect = AwaKinG.src.core.renderer.Effect;
using Buffer = SharpDX.Direct3D11.Buffer;
using Device = SharpDX.Direct3D11.Device;
using Resource = SharpDX.Direct3D11.Resource;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.D3DCompiler;

namespace AwaKinG.src.core
{
    struct Props
    {
        public static float ScreenNear = 0.1f;
        public static float ScreenFar = 100000.0f;
        public static bool VerticalSyncEnabled = true;
        public static Color4 SceneColor = new Color4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    public class Renderer : IRenderer
    {
        static Effect _colorMap = new Effect();
        static Effect _textureMapPick = new Effect();
        static Effect _textureMap = new Effect();

        public IInput Input { get; set; }
    #region private_varibles
        float _constOrtho = 1.0f;
        Matrix _projectionMatrix;
        Matrix _orthoMatrix;
        Matrix _worldMatrix;
    #endregion
    #region varibles
        Device _device;
        DeviceContext _deviceContext;
        SwapChain _swapChain;

        ViewportF _viewPort;
        RenderTargetView _rTView;
        DepthStencilView _dSView;
        DepthStencilState _dSState;
        Texture2D _dSBuffer;

        RS _RS;
        BS _BS;
        SS _SS;

        Buffer _cBufferViewProj;
        List<Object3D> _models = new List<Object3D>();
    #endregion
    #region Initialize methods
        public Renderer()
        {
        }
        public bool Initialize(System.Windows.Forms.Control control)
        {
            try
            {
                var width = control.Width;
                var height = control.Height;
                var factory = new Factory();
                var adapter = factory.GetAdapter(0);
                var monitor = adapter.GetOutput(0);
                var modes = monitor.GetDisplayModeList(Format.R8G8B8A8_UNorm, DisplayModeEnumerationFlags.Interlaced);
                var rational = new Rational(0, 1);
                if (Props.VerticalSyncEnabled)
                {
                    foreach (var mode in modes)
                    {
                        if (mode.Width == width && mode.Height == height)
                        {
                            rational = new Rational(mode.RefreshRate.Numerator, mode.RefreshRate.Denominator);
                            break;
                        }
                    }
                }
                var adapterDescription = adapter.Description;
                var VideoCardMemory = adapterDescription.DedicatedVideoMemory >> 10 >> 10;
                var VideoCardDescription = adapterDescription.Description;
                var swapChainDesc = new SwapChainDescription()
                {
                    BufferCount = 1,
                    ModeDescription = new ModeDescription(width, height, rational, Format.R8G8B8A8_UNorm),
                    Usage = Usage.RenderTargetOutput,
                    OutputHandle = control.Handle,
                    SampleDescription = new SampleDescription(1, 0),
                    IsWindowed = true,
                    Flags = SwapChainFlags.None,
                    SwapEffect = SwapEffect.Discard
                };
                Device device;
                SwapChain swapChain;
                Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, swapChainDesc, out device, out swapChain);

                _device = device;
                _deviceContext = _device.ImmediateContext;
                _swapChain = swapChain;

                var Back_1 = Texture2D.FromSwapChain<Texture2D>(_swapChain, 0);
                _rTView = new RenderTargetView(device, Back_1);
                Back_1.Dispose();

                monitor.Dispose();
                adapter.Dispose();
                factory.Dispose();

                var depthBufferDesc = new Texture2DDescription()
                {
                    Width = width,
                    Height = height,
                    MipLevels = 1,
                    ArraySize = 1,
                    Format = Format.D24_UNorm_S8_UInt,
                    SampleDescription = new SampleDescription(1, 0),
                    Usage = ResourceUsage.Default,
                    BindFlags = BindFlags.DepthStencil,
                    CpuAccessFlags = CpuAccessFlags.None,
                    OptionFlags = ResourceOptionFlags.None
                };
                _dSBuffer = new Texture2D(device, depthBufferDesc);
                var depthStencilDesc = new DepthStencilStateDescription()
                {
                    IsDepthEnabled = true,
                    DepthWriteMask = DepthWriteMask.All,
                    DepthComparison = Comparison.Less,
                    IsStencilEnabled = true,
                    StencilReadMask = 0xFF,
                    StencilWriteMask = 0xFF,
                    FrontFace = new DepthStencilOperationDescription()
                    {
                        FailOperation = StencilOperation.Keep,
                        DepthFailOperation = StencilOperation.Increment,
                        PassOperation = StencilOperation.Keep,
                        Comparison = Comparison.Always
                    },
                    BackFace = new DepthStencilOperationDescription()
                    {
                        FailOperation = StencilOperation.Keep,
                        DepthFailOperation = StencilOperation.Decrement,
                        PassOperation = StencilOperation.Keep,
                        Comparison = Comparison.Always
                    }
                };
                _dSState = new DepthStencilState(_device, depthStencilDesc);
                _deviceContext.OutputMerger.SetDepthStencilState(_dSState, 1);
                var depthStencilViewDesc = new DepthStencilViewDescription()
                {
                    Format = Format.D24_UNorm_S8_UInt,
                    Dimension = DepthStencilViewDimension.Texture2D,
                    Texture2D = new DepthStencilViewDescription.Texture2DResource()
                    {
                        MipSlice = 0
                    }
                };
                _dSView = new DepthStencilView(_device, _dSBuffer, depthStencilViewDesc);
                _deviceContext.OutputMerger.SetTargets(_dSView, _rTView);
                _deviceContext.Rasterizer.SetViewport(0, 0, width, height, 0, 1);

                _projectionMatrix = Matrix.PerspectiveFovLH((float)(Math.PI / 4), (float)((float)width / (float)height), Props.ScreenNear, Props.ScreenFar);
                _worldMatrix = Matrix.Identity;
                _orthoMatrix = Matrix.OrthoLH(width, height, -Props.ScreenFar, Props.ScreenFar);

                InitializeShaders();

                _cBufferViewProj = new Buffer(_device, Utilities.SizeOf<Matrix>(), ResourceUsage.Default, BindFlags.ConstantBuffer, CpuAccessFlags.None, ResourceOptionFlags.None, 0);

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        private bool InitializeShaders()
        {
            try
            {
                if (!_textureMap.Initialize(_device, "fx/Texture_Mapping.hlsl", "VS", "PS")) return false;
                if (!_textureMapPick.Initialize(_device, "fx/Texture_Mapping.hlsl", "VS_PICK", "PS_PICK")) return false;

                var sSLinear_ = new SamplerState(_device, new SamplerStateDescription()
                {
                    Filter = Filter.MinMagMipLinear, AddressU = TextureAddressMode.Wrap, AddressV = TextureAddressMode.Wrap, AddressW = TextureAddressMode.Wrap,
                    BorderColor = SharpDX.Color.Black, ComparisonFunction = Comparison.Never,
                    MaximumAnisotropy = 16, MipLodBias = 0, MinimumLod = 0, MaximumLod = 16,
                });
                _SS = new SS(sSLinear_);

                var rasterDesc_ = new RasterizerStateDescription()
                {
                    IsAntialiasedLineEnabled = false, CullMode = CullMode.Back, DepthBias = 0,
                    DepthBiasClamp = .0f, IsDepthClipEnabled = true, FillMode = FillMode.Solid,
                    IsFrontCounterClockwise = false, IsMultisampleEnabled = false,
                    IsScissorEnabled = false, SlopeScaledDepthBias = .0f
                };
                var rSDefault_ = new RasterizerState(_device, rasterDesc_);
                rasterDesc_.CullMode = CullMode.None;
                _RS = new RS(rSDefault_, new RasterizerState(_device, rasterDesc_));
                _deviceContext.Rasterizer.State = _RS.Default;

                BlendStateDescription bsd_ = new BlendStateDescription();
                bsd_.AlphaToCoverageEnable = false;
                bsd_.IndependentBlendEnable = false;
                bsd_.RenderTarget[0].IsBlendEnabled = true;
                bsd_.RenderTarget[0].SourceBlend = BlendOption.SourceAlpha;
                bsd_.RenderTarget[0].DestinationBlend = BlendOption.InverseSourceAlpha;
                bsd_.RenderTarget[0].BlendOperation = BlendOperation.Add;
                bsd_.RenderTarget[0].SourceAlphaBlend = BlendOption.One;
                bsd_.RenderTarget[0].DestinationAlphaBlend = BlendOption.Zero;
                bsd_.RenderTarget[0].AlphaBlendOperation = BlendOperation.Add;
                bsd_.RenderTarget[0].RenderTargetWriteMask = ColorWriteMaskFlags.All;
                var bSBlend_ = new BlendState(_device, bsd_);
                bsd_.RenderTarget[0].IsBlendEnabled = false;
                _BS = new BS(new BlendState(_device, bsd_), bSBlend_);

                _deviceContext.OutputMerger.SetBlendState(_BS.Default, _BS.BlendFactor, 0xffffffff);

                return true;
            }
            catch(Exception ex)
            {
                return false;
            }
        }
    #endregion
    
    #region Update methods
        public void AddStaticModelFromFile(String fpath)
        {
            StaticObject so_ = new StaticObject();
            so_.SetFileName(fpath);
            if (!so_.Initialize(_device))
                MessageBox.Show(so_.ErrorMessage);
            else
                _models.Add(so_);
        }
        public void Render(/*ref Matrix view*/)
        {
            _deviceContext.OutputMerger.SetTargets(_dSView, _rTView);
            _deviceContext.Rasterizer.SetViewport(_viewPort);
            _deviceContext.ClearDepthStencilView(_dSView, DepthStencilClearFlags.Depth, 1, 0);
            _deviceContext.ClearRenderTargetView(_rTView, Props.SceneColor);

            var view_ = Matrix.Identity;//Camera.ViewMatrix;

            view_ = Matrix.Multiply(view_, _projectionMatrix);
            _deviceContext.UpdateSubresource(ref view_, _cBufferViewProj);
            _deviceContext.GeometryShader.SetConstantBuffer(0, _cBufferViewProj);
            _deviceContext.VertexShader.SetConstantBuffer(0, _cBufferViewProj);
            _deviceContext.Rasterizer.State = _RS.Default;

            _deviceContext.InputAssembler.InputLayout = _textureMap.IL;
            _deviceContext.VertexShader.Set(_textureMap.VS);
            _deviceContext.PixelShader.Set(_textureMap.PS);
            _deviceContext.PixelShader.SetSampler(0, _SS.Linear);

            _deviceContext.InputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;
            foreach (Object3D mdl in _models)
            {
                _deviceContext.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(mdl.VBuffer, 32, 0));
                _deviceContext.InputAssembler.SetIndexBuffer(mdl.IBuffer, Format.R32_UInt, 0);
                mdl.Render();

                _deviceContext.UpdateSubresource(ref mdl.CBWorldPick, mdl.CBufferWorld);
                _deviceContext.VertexShader.SetConstantBuffer(1, mdl.CBufferWorld);
                _deviceContext.PixelShader.SetShaderResource(0, mdl.Texture);

                _deviceContext.DrawIndexed(mdl.CountInds, 0, 0);
            }

            if (Props.VerticalSyncEnabled) _swapChain.Present(1, 0);
            else _swapChain.Present(0, 0);
        }
        public void ResizeBuffer(System.Drawing.Size s)
        {
            _deviceContext.OutputMerger.ResetTargets();
            _rTView.Dispose();

            _swapChain.ResizeBuffers(1, s.Width, s.Height, Format.Unknown, 0);

            var Back_ = Texture2D.FromSwapChain<Texture2D>(_swapChain, 0);
            _rTView = new RenderTargetView(_device, Back_);
            Back_.Dispose();
            
            _viewPort = new ViewportF(0.0f, 0.0f, s.Width, s.Height, 0.0f, 1.0f);

            _projectionMatrix = Matrix.PerspectiveFovLH((float)(Math.PI / 4), (float)((float)s.Width / (float)s.Height), Props.ScreenNear, Props.ScreenFar);
            _orthoMatrix = Matrix.OrthoLH(s.Width * _constOrtho, s.Height * _constOrtho, -Props.ScreenFar, Props.ScreenFar);
        }
    #endregion

    #region Shutdown methods
        public void Shutdown()
        {

        }
    #endregion
    }
}
