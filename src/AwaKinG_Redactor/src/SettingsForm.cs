using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI_elements;

namespace AwaKinG_Redactor.src
{
    public partial class SettingsForm : Form
    {
        public SettingsForm()
        {
            InitializeComponent();
        }
        private void btnOk_Click(object sender, EventArgs e)
        {
            Close();
        }
        private void SettingsForm_Activated(object sender, EventArgs e)
        {
            rbtnSlow.Checked = false;   rbtnFast.Checked = false;  rbtnNormal.Checked = false;
            rbtnRedactor.Checked = false; rbtnRedactorFree.Checked = false;

            switch(src.engine.Camera.GetInstance().Type)
            {
                case engine.CameraType.Redactor: rbtnRedactor.Checked = true; break;
                case engine.CameraType.RedactorFree: rbtnRedactorFree.Checked = true; break;
                default: break;
            }

            if (src.engine.Camera.GetInstance().Speed == 1.0f) { rbtnSlow.Checked = true; return; }
            if (src.engine.Camera.GetInstance().Speed <= 5.0f) { rbtnNormal.Checked = true; return; }
            rbtnFast.Checked = true;

            rbtnWireframe.Checked = src.engine.Terrain.GetInstance().Wireframe;
            rbtnQuadTreeVisible.Checked = src.engine.Terrain.GetInstance().QuadTreeVisible;
        }
        private void rbtnCameraSpeed_Click(object sender, EventArgs e)
        {
            ((RadioButton)sender).Checked = true;
            if (sender != rbtnSlow) rbtnSlow.Checked = false;
            if (sender != rbtnFast) rbtnFast.Checked = false;
            if (sender != rbtnNormal) rbtnNormal.Checked = false;
        }

        private void rbtnCameraType_Click(object sender, EventArgs e)
        {
            ((RadioButton)sender).Checked = true;
            if (sender != rbtnRedactor) rbtnRedactor.Checked = false;
            if (sender != rbtnRedactorFree) rbtnRedactorFree.Checked = false;
        }

        private void rbtnQuadTreeVisible_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
