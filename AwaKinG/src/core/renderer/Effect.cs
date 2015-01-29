using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AwaKinG.src.core.renderer;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using Buffer = SharpDX.Direct3D11.Buffer;
using Device = SharpDX.Direct3D11.Device;
using Resource = SharpDX.Direct3D11.Resource;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.D3DCompiler;


namespace AwaKinG.src.core.renderer
{
    public struct SS
    {
        public SS(SamplerState linear) { Linear = linear; }
        public SamplerState Linear;
    }
    public struct BS
    {
        public BS(BlendState def, BlendState blend) { Default = def; Blend = blend; BlendFactor = new Color4(0.0f, 0.0f, 0.0f, 0.0f); }
        public BlendState Default;
        public BlendState Blend;
        public Color4 BlendFactor;
    }
    public struct RS
    {
        public RS(RasterizerState def, RasterizerState nbc) { Default = def; NoBackCull = nbc; }
        public RasterizerState Default;
        public RasterizerState NoBackCull;
    }
    public class Effect
    {
        public InputLayout IL = null;
        public VertexShader VS = null;
        public PixelShader PS = null;
        public bool Initialize(Device device, String fname, String vSName, String pSName)
        {
            try
            {
                var vertexShaderByteCode = ShaderBytecode.CompileFromFile(fname, vSName, "vs_4_0", ShaderFlags.PackMatrixRowMajor, EffectFlags.None);
                VS = new VertexShader(device, vertexShaderByteCode);
                var pixelShaderByteCode = ShaderBytecode.CompileFromFile(fname, pSName, "ps_4_0", ShaderFlags.PackMatrixRowMajor, EffectFlags.None);
                PS = new PixelShader(device, pixelShaderByteCode);

                IL = new InputLayout(device, ShaderSignature.GetInputSignature(vertexShaderByteCode), new[]
                        {   new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0),
                            new InputElement("TEXCOORD", 0, Format.R32G32_Float, 12, 0),
                            new InputElement("NORMAL", 0, Format.R32G32B32_Float, 20, 0),
                        });

                vertexShaderByteCode.Dispose();
                pixelShaderByteCode.Dispose();

                return true;
            }
            catch(Exception ex)
            {
                return false;
            }
        }
    }
}
