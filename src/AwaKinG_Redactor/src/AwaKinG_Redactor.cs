using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AwaKinG_Redactor.src.engine;

namespace AwaKinG_Redactor
{
    public partial class AwaKinG_Redactor : Form
    {
    #region private vars
        EngineWrap _engine;
        OpenFileDialog _mapOFD = new OpenFileDialog();
    #endregion
        public AwaKinG_Redactor()
        {
            InitializeComponent();

            _engine = new EngineWrap(Handle, pnlRender.Handle, new System.Drawing.Size(2000,1500));
            _engine.ResizeRenderBuffers(pnlRender.Size);
            _engine.SetCameraManagerType(0);

            _mapOFD.InitialDirectory = System.IO.Path.GetFullPath(@"../../../../resources/map/");
            _mapOFD.Filter = "map files (*.map)|*.map";
            _mapOFD.FilterIndex = 1;
            _mapOFD.RestoreDirectory = true;

            Application.Idle += Application_Idle;
        }
        void Application_Idle(object sender, EventArgs e)
        {
            while (!_engine.Done)
            {
                if (_engine.GetActive())
                    _engine.Update();
                Application.DoEvents();
            }
        }
        private void AwaKinG_Redactor_Load(object sender, EventArgs e)
        {
            _engine.SetActive(true);
        }
        private void AwaKinG_Redactor_Activated(object sender, EventArgs e)
        {
            if (WindowState != FormWindowState.Minimized)
                _engine.SetActive(true);
        }
        private void AwaKinG_Redactor_Deactivate(object sender, EventArgs e)
        {
            _engine.SetActive(false);
        }
        private void AwaKinG_Redactor_SizeChanged(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized)
            {
                _engine.SetActive(false);
            }
            else
                _engine.SetActive(true);
        }
        private void AwaKinG_Redactor_FormClosing(object sender, FormClosingEventArgs e)
        {
            _engine.Done = true;
            _engine.Shutdown();
        }
        private void freeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _engine.SetCameraManagerType(Convert.ToInt32(((ToolStripMenuItem)sender).Tag));
            foreach (ToolStripMenuItem it in cameraToolStripMenuItem.DropDownItems)
            {
                if(it != sender) it.Checked = false;
            }
            ((ToolStripMenuItem)sender).Checked = true;

        }
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _engine.Done = true;
            _engine.Shutdown();
            Close();
        }
        private void openMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (_mapOFD.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if (_mapOFD.OpenFile() != null)
                    {
                        if (_mapOFD.FileName != "")
                            _engine.CreateMapFromFile(_mapOFD.FileName);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        }
        private void pnlRender_SizeChanged(object sender, EventArgs e)
        {
            _engine.ResizeRenderBuffers(pnlRender.Size);
        }
    }
}
