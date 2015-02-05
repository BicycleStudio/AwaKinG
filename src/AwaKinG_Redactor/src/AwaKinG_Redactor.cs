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
        OpenFileDialog _terrainOFD = new OpenFileDialog();
        SaveFileDialog _terrainSFD = new SaveFileDialog();
    #endregion
        public AwaKinG_Redactor()
        {
            InitializeComponent();

            _engine = new EngineWrap(Handle, pnlRender.Handle, new System.Drawing.Size(2000,1500));
            _engine.ResizeRenderBuffers(pnlRender.Size);
            _engine.SetCameraManagerType(0);

            _terrainSFD.InitialDirectory = _terrainOFD.InitialDirectory = System.IO.Path.GetFullPath(@"../../../../resources/map/terrain/");
            _terrainSFD.Filter = _terrainOFD.Filter = "ter files (*.ter)|*.ter";
            _terrainSFD.FilterIndex = _terrainOFD.FilterIndex = 1;

            _mapOFD.InitialDirectory = System.IO.Path.GetFullPath(@"../../../../resources/map/");
            _mapOFD.Filter = "map files (*.map)|*.map";
            _mapOFD.FilterIndex = 1;

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
                        if (_mapOFD.FileName != "")
                            _engine.CreateMapFromFile(_mapOFD.FileName);
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
        private void awA_Button1_Click(object sender, EventArgs e)
        {
            _engine.GenerateTerrain((int)awA_Value_Button1.Value, (int)awA_Value_Button2.Value);
        }

        private void awA_Button2_Click(object sender, EventArgs e)
        {
            _engine.RandomizeTerrain((int)awA_Value_Button3.Value);
        }
        private void awA_Button3_Click(object sender, EventArgs e)
        {
            _engine.BlurTerrain(1);
        }
        private void loadFromFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (_terrainOFD.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if (_terrainOFD.OpenFile() != null)
                        if (_terrainOFD.FileName != "")
                            _engine.LoadTerrain(_terrainOFD.FileName);
                }
                catch (Exception ex)
                { 
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        }
        private void saveToFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (_terrainSFD.ShowDialog() == DialogResult.OK)
            {
                if (_terrainSFD.FileName != "")
                    _engine.SaveTerrain(_terrainSFD.FileName);
            }
        }
        private void awA_Button5_Click(object sender, EventArgs e)
        {
            _engine.SetTerrainWorkType(2);
        }
        private void awA_Button6_Click(object sender, EventArgs e)
        {
            _engine.SetTerrainWorkType(0);
        }
        private void awA_Button4_Click(object sender, EventArgs e)
        {
            _engine.SetTerrainWorkType(1);
        }
        private void pnlRender_MouseDown(object sender, MouseEventArgs e)
        {
            int id = _engine.PickTerrain(e.Location);
            label1.Text = "Log: " + id.ToString();
        }
    }
}
