using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AwaKinG.src.core;

namespace AwaKinG.src
{
    public partial class Redactor : Form
    {
        bool gLoop = true;
        IRenderer Renderer;
        IEngine Engine;
        Input Input;
        public Redactor(Engine engine, Renderer renderer, Input input)
        {
            Renderer = renderer;
            Engine = engine;
            Input = input;

            InitializeComponent();

            Renderer.Initialize(PNL_Render);
            Input.Initialize(Handle);
            Renderer.Input = Input;

            Application.Idle += Application_Idle;
        }

        void Application_Idle(object sender, EventArgs e)
        {
            Renderer.ResizeBuffer(PNL_Render.Size);
            while(gLoop)
            {
                Input.Frame();
                Engine.Update();
                Renderer.Render();
                Application.DoEvents();
            }
        }
        private void PNL_Render_SizeChanged(object sender, EventArgs e)
        {
            Renderer.ResizeBuffer(PNL_Render.Size);
        }

        private void Redactor_FormClosing(object sender, FormClosingEventArgs e)
        {
            gLoop = false;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gLoop = false;
        }
    }
}
