using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using AwaKinG.src.core;

namespace AwaKinG.src
{
    static class Program
    {

        [STAThread]
        static void Main()
        {
            Engine Engine = new core.Engine();
            Renderer Renderer = new core.Renderer();

            Engine.Initialize();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1(Engine, Renderer));

            Engine.Shutdown();
            Renderer.Shutdown();
        }
    }
}
