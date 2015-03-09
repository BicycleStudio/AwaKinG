using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AwaKinG_Editor {
  public partial class EditorForm : Form {
    OpenFileDialog ofdMap = new OpenFileDialog();
    SaveFileDialog sfdMap = new SaveFileDialog();
    public EditorForm() {
      InitializeComponent();
      ofdMap.InitialDirectory = System.IO.Path.GetFullPath(@"..\..\..\..\resources\map");
      ofdMap.Filter = "amp files (*.amp)|*.amp";
      ofdMap.FilterIndex = 1;
      ofdMap.RestoreDirectory = true;
      ofdMap.InitialDirectory = System.IO.Path.GetFullPath(@"..\..\..\..\resources\map");
      sfdMap.Filter = "amp files (*.amp)|*.amp";
      sfdMap.FilterIndex = 1;
      sfdMap.RestoreDirectory = true;
      Engine.GetInstance().Initialize(Handle, pnlRender.Handle); 
      Application.Idle += Application_Idle;
    }
    void Application_Idle(object sender, EventArgs e) {
      while (!Engine.GetInstance().Done) {
        Engine.GetInstance().Update();
        Application.DoEvents();
      }
    }
    private void menuFileExit_Click(object sender, EventArgs e) {
      Engine.GetInstance().Done = true;
      Close();
    }
    private void redactorForm_FormClosing(object sender, FormClosingEventArgs e) {
      Engine.GetInstance().Done = true;
    }
    private void pnlRender_SizeChanged(object sender, EventArgs e) {
      if (WindowState != FormWindowState.Minimized) { 
        Engine.GetInstance().SetActive(true);
        Engine.GetInstance().Resize(pnlRender.Size);
      }
    }
    private void EditorForm_Load(object sender, EventArgs e) {
      Engine.GetInstance().SetActive(true);
    }
    private void EditorForm_SizeChanged(object sender, EventArgs e) {
      if (WindowState == FormWindowState.Minimized) 
        Engine.GetInstance().SetActive(false);
      else
        Engine.GetInstance().SetActive(true);
    }
    private void EditorForm_Activated(object sender, EventArgs e) {
      if (WindowState != FormWindowState.Minimized)
        Engine.GetInstance().SetActive(true);
    }
    private void EditorForm_Deactivate(object sender, EventArgs e) {
      Engine.GetInstance().SetActive(false);
    }
    private void CameraType_Click(object sender, EventArgs e) {
      int type_ = Convert.ToInt32(((ToolStripMenuItem)sender).Tag);
      EngineDll.SetCameraType(type_);
      foreach (ToolStripMenuItem ts in menuEditCamera.DropDownItems)
        ts.Checked = false;
      ((ToolStripMenuItem)sender).Checked = true;
    }
    private void menuFileCreateMap_Click(object sender, EventArgs e) {
      DialogResult dr = MessageBox.Show("You sure? You may lost all your progress","Create new map", MessageBoxButtons.OKCancel);
      if (dr == System.Windows.Forms.DialogResult.OK) {
        EngineDll.newMap();
      }
    }
    private void menuFileOpenMap_Click(object sender, EventArgs e) {
      if (ofdMap.ShowDialog() == DialogResult.OK) {
        try {
          if (ofdMap.FileName != null) {
            EngineDll.OpenMap(ofdMap.FileName, ofdMap.FileName.Length);
          }
        }
        catch (Exception ex) {
          MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
        }
      }
    }
    private void menuFileSaveMap_Click(object sender, EventArgs e) {
        if (sfdMap.ShowDialog() == DialogResult.OK) {
        try {
          if (sfdMap.FileName != null) {
            EngineDll.SaveMap(sfdMap.FileName, sfdMap.FileName.Length);
          }
        }
        catch (Exception ex) {
          MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
        }
      }
    }
  }
}
