using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AwaKinG.src.core.renderer;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using Device = SharpDX.Direct3D11.Device;
using Resource = SharpDX.Direct3D11.Resource;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.D3DCompiler;

namespace AwaKinG.src.core
{
    public class Renderer : IRenderer
    {
    #region varibles
        float ScreenNear = 0.1f;
        float ScreenDepth = 100000.0f;
        public float ConstOrtho = 1.0f;
        private bool VerticalSyncEnabled = true;
    #endregion

    #region varibles
        private List<Object3D> Models = new List<Object3D>();
        private SwapChain SwapChain;
        public Device Device { get; private set; }
        public DeviceContext DeviceContext { get; private set; }
        private RenderTargetView RenderTargetView;
        private DepthStencilView DepthStencilView;
        public DepthStencilState DepthStencilState;
        private RasterizerState RasterState;
        private Texture2D DepthStencilBuffer;
        private ViewportF View_Port;
        private System.Drawing.Size Size;

        public Matrix ProjectionMatrix;
        public Matrix OrthoMatrix;
        public Matrix WorldMatrix;

        private Color4 SceneColor = new Color4(1.0f,0.0f,0.0f,1.0f);
    #endregion

    #region Initialize methods
        public bool Initialize(int width, int height, bool fullscreen, IntPtr window)
        {
            try
            {
                var factory = new Factory();
                var adapter = factory.GetAdapter(0);
                var monitor = adapter.GetOutput(0);
                var modes = monitor.GetDisplayModeList(Format.R8G8B8A8_UNorm, DisplayModeEnumerationFlags.Interlaced);
                var rational = new Rational(0, 1);
                if (VerticalSyncEnabled)
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
                    OutputHandle = window,
                    SampleDescription = new SampleDescription(1, 0),
                    IsWindowed = !fullscreen,
                    Flags = SwapChainFlags.None,
                    SwapEffect = SwapEffect.Discard
                };
                Device device;
                SwapChain swapChain;
                Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, swapChainDesc, out device, out swapChain);

                Device = device;
                DeviceContext = Device.ImmediateContext;
                SwapChain = swapChain;

                var Back_1 = Texture2D.FromSwapChain<Texture2D>(SwapChain, 0);
                RenderTargetView = new RenderTargetView(device, Back_1);
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
                DepthStencilBuffer = new Texture2D(device, depthBufferDesc);
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
                DepthStencilState = new DepthStencilState(Device, depthStencilDesc);
                DeviceContext.OutputMerger.SetDepthStencilState(DepthStencilState, 1);
                var depthStencilViewDesc = new DepthStencilViewDescription()
                {
                    Format = Format.D24_UNorm_S8_UInt,
                    Dimension = DepthStencilViewDimension.Texture2D,
                    Texture2D = new DepthStencilViewDescription.Texture2DResource()
                    {
                        MipSlice = 0
                    }
                };
                DepthStencilView = new DepthStencilView(Device, DepthStencilBuffer, depthStencilViewDesc);
                DeviceContext.OutputMerger.SetTargets(DepthStencilView, RenderTargetView);
                var rasterDesc = new RasterizerStateDescription()
                {
                    IsAntialiasedLineEnabled = false,
                    CullMode = CullMode.Back,
                    DepthBias = 0,
                    DepthBiasClamp = .0f,
                    IsDepthClipEnabled = true,
                    FillMode = FillMode.Solid,
                    IsFrontCounterClockwise = false,
                    IsMultisampleEnabled = false,
                    IsScissorEnabled = false,
                    SlopeScaledDepthBias = .0f
                };
                RasterState = new RasterizerState(Device, rasterDesc);
                DeviceContext.Rasterizer.State = RasterState;
                DeviceContext.Rasterizer.SetViewport(0, 0, width, height, 0, 1);

                ProjectionMatrix = Matrix.PerspectiveFovLH((float)(Math.PI / 4), (float)((float)width / (float)height), ScreenNear, ScreenDepth);
                WorldMatrix = Matrix.Identity;
                OrthoMatrix = Matrix.OrthoLH(width, height, -ScreenDepth, ScreenDepth);

                InitializeShaders();

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        private bool InitializeShaders()
        {
            return true;
        }
    #endregion
    
    #region Update methods
        public void Render()
        {
            DeviceContext.OutputMerger.SetTargets(DepthStencilView, RenderTargetView);
            DeviceContext.Rasterizer.SetViewport(View_Port);
            DeviceContext.ClearDepthStencilView(DepthStencilView, DepthStencilClearFlags.Depth, 1, 0);
            DeviceContext.ClearRenderTargetView(RenderTargetView, SceneColor);
            foreach (Object3D mdl in Models)
                mdl.Render();

            if (VerticalSyncEnabled) SwapChain.Present(1, 0);
            else SwapChain.Present(0, 0);
        }
        public void ResizeBuffer(System.Drawing.Size s)
        {
            Size = s;

            DeviceContext.OutputMerger.ResetTargets();
            RenderTargetView.Dispose();

            SwapChain.ResizeBuffers(1, s.Width, s.Height, Format.Unknown, 0);

            var Back_1 = Texture2D.FromSwapChain<Texture2D>(SwapChain, 0);
            RenderTargetView = new RenderTargetView(Device, Back_1);
            Back_1.Dispose();
            
            View_Port = new ViewportF(0.0f, 0.0f, Size.Width, Size.Height, 0.0f, 1.0f);

            ProjectionMatrix = Matrix.PerspectiveFovLH((float)(Math.PI / 4), (float)((float)s.Width / (float)s.Height), ScreenNear, ScreenDepth);
            OrthoMatrix = Matrix.OrthoLH(s.Width * ConstOrtho, s.Height * ConstOrtho, -ScreenDepth, ScreenDepth);
        }
    #endregion

    #region Shutdown methods
        public void Shutdown()
        {

        }
    #endregion
    }
}
