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
        string _configPath = System.IO.Path.GetFullPath(@"../../../../config/redactor.cfg");
        src.SettingsForm _settings = new src.SettingsForm();
        EngineWrap _engine;
        OpenFileDialog _mapOFD = new OpenFileDialog();
        OpenFileDialog _terrainOFD = new OpenFileDialog();
        SaveFileDialog _terrainSFD = new SaveFileDialog();
    #endregion
        enum TexturingWorkType { None, Texture}
        enum TerraformingWorkType { None, Height, SInHeight, SOutHeight, SInOutHeight }
        TexturingWorkType _texwtType = TexturingWorkType.None;
        TexturingWorkType _texwtSaved = TexturingWorkType.Texture;
        TerraformingWorkType _twtType = TerraformingWorkType.None;
        TerraformingWorkType _twtTypeSaved = TerraformingWorkType.Height;
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

            Config.GetInstance().Load(_configPath);
            _engine.SetConfig();
            setFileCameraType();
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
            Config.GetInstance().Save(_configPath);
        }
        private void freeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _engine.SetCameraManagerType(Convert.ToInt32(((ToolStripMenuItem)sender).Tag));
            mtsiCameraRedactor.Checked = false;
            mtsiCameraFree.Checked = false;

            ((ToolStripMenuItem)sender).Checked = true;
            if (mtsiCameraRedactor.Checked) Camera.GetInstance().Type = CameraType.Redactor;
            if (mtsiCameraFree.Checked) Camera.GetInstance().Type = CameraType.RedactorFree;
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
            if (btnTPTexture.CHECKED)
            {
                btnTPHeight.CHECKED = false;
                _engine.SetTerraPenHeightVisible(false);
                _twtType = TerraformingWorkType.None;
                _engine.SetTerrainWorkType(0);
                _texwtType = _texwtSaved;
            }
            else
            {
                _texwtSaved = _texwtType;
                _texwtType = TexturingWorkType.None;
            }
        }
        private void awA_Button6_Click(object sender, EventArgs e)
        {
            _engine.SetTerrainWorkType(0);
            _engine.SetTerraPenHeightVisible(btnTPHeight.CHECKED);
        }
        private void SetTerrainPenWorkType()
        {
            switch(_twtType)
            {
                case TerraformingWorkType.Height: _engine.SetTerrainWorkType(1); break;
                case TerraformingWorkType.SInHeight: _engine.SetTerrainWorkType(1); break;
                case TerraformingWorkType.SOutHeight: _engine.SetTerrainWorkType(1); break;
                case TerraformingWorkType.SInOutHeight: _engine.SetTerrainWorkType(1); break;
            }
            _engine.SetTerraPenHard(vbtnTPHardness.Value / 100.0f);
        }
        private void awA_Button4_Click(object sender, EventArgs e)
        {
            if (btnTPHeight.CHECKED)
            {
                _twtType = _twtTypeSaved;
                btnTPTexture.CHECKED = false;
                SetTerrainPenWorkType();
            }
            else
            {
                _twtTypeSaved = _twtType;
                _twtType = TerraformingWorkType.None;
                _engine.SetTerrainWorkType(0);
            }
            _engine.SetTerraPenHeightVisible(btnTPHeight.CHECKED);
        }
        private void pnlRender_MouseDown(object sender, MouseEventArgs e)
        {
            switch(_twtType)
            {
                case TerraformingWorkType.Height:
                    _engine.SetTerrainWorkType(2);
                    _engine.PickTerrain(e.Location);
                    break;
                case TerraformingWorkType.SInHeight:
                    _engine.SetTerrainWorkType(3);
                    _engine.PickTerrain(e.Location);
                    break;
                case TerraformingWorkType.SOutHeight:
                    _engine.SetTerrainWorkType(4);
                    _engine.PickTerrain(e.Location);
                    break;
                case TerraformingWorkType.SInOutHeight:
                    _engine.SetTerrainWorkType(5);
                    _engine.PickTerrain(e.Location);
                    break;
            }
        }
        private void setFileCameraType()
        {
            mtsiCameraFree.Checked = false;
            mtsiCameraRedactor.Checked = false;
            switch (Camera.GetInstance().Type)
            {
                case CameraType.Redactor: mtsiCameraRedactor.Checked = true; break;
                case CameraType.RedactorFree: mtsiCameraFree.Checked = true; break;
            }
        }
        private void settingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _engine.SetActive(false);
            Application.Idle -= Application_Idle;
            if (_settings.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (_settings.rbtnFast.Checked) Camera.GetInstance().Speed = 10.0f;
                if (_settings.rbtnNormal.Checked) Camera.GetInstance().Speed = 5.0f;
                if (_settings.rbtnSlow.Checked) Camera.GetInstance().Speed = 1.0f;

                if (_settings.rbtnRedactor.Checked) Camera.GetInstance().setType(Camera.SystemStrings.CameraTypeRedactor);
                if (_settings.rbtnRedactorFree.Checked) Camera.GetInstance().setType(Camera.SystemStrings.CameraTypeRedactorFree);

                Terrain.GetInstance().Wireframe = _settings.rbtnWireframe.Checked;
                Terrain.GetInstance().QuadTreeVisible = _settings.rbtnQuadTreeVisible.Checked;

                _engine.SetConfig();
                setFileCameraType();
            }
            _engine.SetActive(true);
            Application.Idle += Application_Idle;
        }

        private void pnlRender_MouseMove(object sender, MouseEventArgs e)
        {
            _engine.PickTerrain(e.Location);
        }

        private void pnlRender_MouseUp(object sender, MouseEventArgs e)
        {
            switch (_twtType)
            {
                case TerraformingWorkType.Height:
                    _engine.SetTerrainWorkType(1);
                    break;
                case TerraformingWorkType.SInHeight:
                    _engine.SetTerrainWorkType(1);
                    break;
                case TerraformingWorkType.SOutHeight:
                    _engine.SetTerrainWorkType(1);
                    break;
                case TerraformingWorkType.SInOutHeight:
                    _engine.SetTerrainWorkType(1);
                    break;
            }
        }
        private void avbPenHardness_MouseUp(object sender, MouseEventArgs e)
        {
            _engine.SetTerraPenHard(vbtnTPHardness.Value/100.0f);
        }
        private void avbPenSizeOuter_OnValueChanged(object sender, EventArgs e)
        {
            if (vbtnPenSizeOuter.Value < vbtnPenSizeInner.Value) vbtnPenSizeInner.Value = vbtnPenSizeOuter.Value;
            vbtnPenSizeInner.Refresh();
        }
        private void avbPenSizeInner_OnValueChanged(object sender, EventArgs e)
        {
            if (vbtnPenSizeOuter.Value < vbtnPenSizeInner.Value) vbtnPenSizeOuter.Value = vbtnPenSizeInner.Value;
            vbtnPenSizeOuter.Refresh();
        }
        private void avbPenHardness_OnValueChanged(object sender, EventArgs e)
        {
        }
        private void avbPenSizeOuter_MouseUp(object sender, MouseEventArgs e)
        {
            _engine.SetTerraPenSize((int)vbtnPenSizeInner.Value, (int)vbtnPenSizeOuter.Value);
        }
        private void btnTPSmoothInOut_Click(object sender, EventArgs e)
        {
            if (!btnTPSmoothIn.CHECKED && !btnTPSmoothOut.CHECKED)
            {
                _twtType = TerraformingWorkType.Height;
                return;
            }
            if (btnTPSmoothIn.CHECKED && btnTPSmoothOut.CHECKED)
            {
                _twtType = TerraformingWorkType.SInOutHeight;
                return;
            }
            if (btnTPSmoothIn.CHECKED && !btnTPSmoothOut.CHECKED)
            {
                _twtType = TerraformingWorkType.SInHeight;
                return;
            }
            if (!btnTPSmoothIn.CHECKED && btnTPSmoothOut.CHECKED)
            {
                _twtType = TerraformingWorkType.SOutHeight;
                return;
            }
        }
        private void vbtnTPSmoothKoeff_MouseUp(object sender, MouseEventArgs e)
        {
            _engine.SetTerraPenSmoothKoeff(vbtnTPSmoothKoeff.Value);
        }
    }
}
