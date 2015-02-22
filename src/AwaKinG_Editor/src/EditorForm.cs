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
    public EditorForm() {
      InitializeComponent();
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
      Engine.GetInstance().Resize(pnlRender.Size);
    }
  }
}
