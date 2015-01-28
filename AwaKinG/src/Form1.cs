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
using GUI_elements;

namespace AwaKinG
{
    public partial class Form1 : Form
    {
        bool Loop = true;
        IEngine Engine;
        IRenderer Renderer;
        public Form1(Engine engine, Renderer renderer)
        {
            Engine = engine;
            Renderer = renderer;
            InitializeComponent();

            Renderer.Initialize(PNL_RenderWindow.Width, PNL_RenderWindow.Height, false, PNL_RenderWindow.Handle);
            Application.Idle += Application_Idle;
        }

        void Application_Idle(object sender, EventArgs e)
        {
            while (Loop)
            {
                Engine.Update();
                Renderer.Render();
                Application.DoEvents();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Loop = false;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Loop = false;
            Close();
        }

        private void PNL_RenderWindow_SizeChanged(object sender, EventArgs e)
        {
            Renderer.ResizeBuffer(PNL_RenderWindow.Size);
        }
        
    }
}
