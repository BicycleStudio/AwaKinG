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
    bool[] btnsTop = new bool[3];
    bool[] btnsTransform = new bool[4];
    bool[] btnsTexturing = new bool[4];
    Color setColor = SystemColors.GradientActiveCaption;
    Color defaultColor = SystemColors.ControlLightLight;
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
      pnlRender_SizeChanged(sender,e);
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
    private void btnTopMain_Click(object sender, EventArgs e) {
      switch (Convert.ToInt32(((Button)sender).Tag)) {
        case 0:
        btnsTop[0] = !btnsTop[0];
        btnsTop[1] = false; 
        btnsTop[2] = false;
        SetTopBtns();
        break;
        case 1:
        btnsTop[0] = false;
        btnsTop[1] = !btnsTop[1];
        btnsTop[2] = false;
        SetTopBtns();
        break;
        case 2:
        btnsTop[0] = false;
        btnsTop[1] = false;
        btnsTop[2] = !btnsTop[2];
        SetTopBtns();
        break;
      }
    }
    private void SetTopBtns() {
      if (btnsTop[0]) {
        btnTopTerrain.BackColor = setColor;
        pnlLeftTerrain.Visible = true;
      }
      else {
        btnTopTerrain.BackColor = defaultColor;
        pnlLeftTerrain.Visible = false;
      }
      if (btnsTop[1]) {
        btnTopEntity.BackColor = setColor;
        pnlLeftEntity.Visible = true;
      }
      else {
        btnTopEntity.BackColor = defaultColor;
        pnlLeftEntity.Visible = false;
      }
      if (btnsTop[2]) {
        btnTopWater.BackColor = setColor;
        pnlLeftWater.Visible = true;
      }
      else {
        btnTopWater.BackColor = defaultColor;
        pnlLeftWater.Visible = false;
      }
    }
    private void SetTerrainTexturingBtns() {
      if (btnsTexturing[0]) btnTexturingQuad.BackColor = setColor;
      else btnTexturingQuad.BackColor = defaultColor;
      if (btnsTexturing[1]) btnTexturingCirc.BackColor = setColor;
      else btnTexturingCirc.BackColor = defaultColor;
      if (btnsTexturing[2]) btnTexturingRhomb.BackColor = setColor;
      else btnTexturingRhomb.BackColor = defaultColor;
      if (btnsTexturing[3]) btnTexturingCustom.BackColor = setColor;
      else btnTexturingCustom.BackColor = defaultColor;
    }
    private void SetEntityTransformBtns() {
      if (btnsTransform[0]) btnEntityObject.BackColor = setColor;
      else btnEntityObject.BackColor = defaultColor;
      if (btnsTransform[1]) btnEntityPos.BackColor = setColor;
      else btnEntityPos.BackColor = defaultColor;
      if (btnsTransform[2]) btnEntityScl.BackColor = setColor;
      else btnEntityScl.BackColor = defaultColor;
      if (btnsTransform[3]) btnEntityRot.BackColor = setColor;
      else btnEntityRot.BackColor = defaultColor;
    }
    private void btnEntityTransform_Click(object sender, EventArgs e) {
      switch (Convert.ToInt32(((Button)sender).Tag)) {
        case 0:
        btnsTransform[0] = !btnsTransform[0]; btnsTransform[1] = false; btnsTransform[2] = false; btnsTransform[3] = false;
        SetEntityTransformBtns();
        break;
        case 1:
        btnsTransform[0] = false; btnsTransform[1] = !btnsTransform[1]; btnsTransform[2] = false; btnsTransform[3] = false;
        SetEntityTransformBtns();
        break;
        case 2:
        btnsTransform[0] = false; btnsTransform[1] = false; btnsTransform[2] = !btnsTransform[2]; btnsTransform[3] = false;
        SetEntityTransformBtns();
        break;
        case 3:
        btnsTransform[0] = false; btnsTransform[1] = false; btnsTransform[2] = false;btnsTransform[3] = !btnsTransform[3]; 
        SetEntityTransformBtns();
        break;
      }
    }
    private void btnTerrainTexturingBtns_Click(object sender, EventArgs e) {
      switch (Convert.ToInt32(((Button)sender).Tag)) {
        case 0:
        btnsTexturing[0] = !btnsTexturing[0]; btnsTexturing[1] = false; btnsTexturing[2] = false; btnsTexturing[3] = false;
        SetTerrainTexturingBtns();
        break;
        case 1:
        btnsTexturing[0] = false; btnsTexturing[1] = !btnsTexturing[1]; btnsTexturing[2] = false; btnsTexturing[3] = false;
        SetTerrainTexturingBtns();
        break;
        case 2:
        btnsTexturing[0] = false; btnsTexturing[1] = false; btnsTexturing[2] = !btnsTexturing[2]; btnsTexturing[3] = false;
        SetTerrainTexturingBtns();
        break;
        case 3:
        btnsTexturing[0] = false; btnsTexturing[1] = false; btnsTexturing[2] = false; btnsTexturing[3] = !btnsTexturing[3];
        SetTerrainTexturingBtns();
        break;
      }
    }
    private void btnTerrainCreate_Click(object sender, EventArgs e) {
      if (TerrainDll.createTerrain((int)vbtnTerrainSizeX.Value, (int)vbtnTerrainSizeY.Value) == -1) {
        MessageBox.Show("Engine does't support Terrain. Try another day :)","Terrain error", MessageBoxButtons.OK);
        return;
      }
      pnlTerrainTerraforming.Visible = true;
      pnlTerrainTexturing.Visible = true;
      pnlTerrainTexturePacks.Visible = true;
    }
  }
}
