namespace AwaKinG_Redactor.src
{
    partial class SettingsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnOk = new GUI_elements.AWA_Button();
            this.btnCancel = new GUI_elements.AWA_Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.panel1 = new System.Windows.Forms.Panel();
            this.rbtnRedactor = new System.Windows.Forms.RadioButton();
            this.rbtnRedactorFree = new System.Windows.Forms.RadioButton();
            this.label3 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.rbtnFast = new System.Windows.Forms.RadioButton();
            this.rbtnNormal = new System.Windows.Forms.RadioButton();
            this.rbtnSlow = new System.Windows.Forms.RadioButton();
            this.label4 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.panel4 = new System.Windows.Forms.Panel();
            this.rbtnWireframe = new System.Windows.Forms.RadioButton();
            this.panel3 = new System.Windows.Forms.Panel();
            this.rbtnQuadTreeVisible = new System.Windows.Forms.RadioButton();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnOk
            // 
            this.btnOk.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnOk.BackColor = System.Drawing.Color.Transparent;
            this.btnOk.BACKCOLOR = System.Drawing.Color.Transparent;
            this.btnOk.BORDERCOLOR = System.Drawing.Color.Black;
            this.btnOk.BORDERRADIUS = 5;
            this.btnOk.BORDERWIDTH = 1;
            this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOk.Image = null;
            this.btnOk.Location = new System.Drawing.Point(125, 193);
            this.btnOk.Name = "btnOk";
            this.btnOk.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.btnOk.SCALEBORD = true;
            this.btnOk.Size = new System.Drawing.Size(68, 23);
            this.btnOk.TabIndex = 0;
            this.btnOk.Text = "Ok";
            this.btnOk.UseVisualStyleBackColor = false;
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnCancel.BackColor = System.Drawing.Color.Transparent;
            this.btnCancel.BACKCOLOR = System.Drawing.Color.Transparent;
            this.btnCancel.BORDERCOLOR = System.Drawing.Color.Black;
            this.btnCancel.BORDERRADIUS = 5;
            this.btnCancel.BORDERWIDTH = 1;
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Image = null;
            this.btnCancel.Location = new System.Drawing.Point(51, 193);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.btnCancel.SCALEBORD = true;
            this.btnCancel.Size = new System.Drawing.Size(68, 23);
            this.btnCancel.TabIndex = 0;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(8, 8);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.Padding = new System.Drawing.Point(10, 3);
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(186, 183);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.panel1);
            this.tabPage1.Controls.Add(this.panel2);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(178, 157);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Camera";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.rbtnRedactor);
            this.panel1.Controls.Add(this.rbtnRedactorFree);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(3, 65);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(172, 45);
            this.panel1.TabIndex = 3;
            // 
            // rbtnRedactor
            // 
            this.rbtnRedactor.AutoSize = true;
            this.rbtnRedactor.Location = new System.Drawing.Point(79, 5);
            this.rbtnRedactor.Name = "rbtnRedactor";
            this.rbtnRedactor.Size = new System.Drawing.Size(69, 17);
            this.rbtnRedactor.TabIndex = 2;
            this.rbtnRedactor.Text = "Redactor";
            this.rbtnRedactor.UseVisualStyleBackColor = true;
            this.rbtnRedactor.Click += new System.EventHandler(this.rbtnCameraType_Click);
            // 
            // rbtnRedactorFree
            // 
            this.rbtnRedactorFree.AutoSize = true;
            this.rbtnRedactorFree.Location = new System.Drawing.Point(79, 22);
            this.rbtnRedactorFree.Name = "rbtnRedactorFree";
            this.rbtnRedactorFree.Size = new System.Drawing.Size(46, 17);
            this.rbtnRedactorFree.TabIndex = 2;
            this.rbtnRedactorFree.Text = "Free";
            this.rbtnRedactorFree.UseVisualStyleBackColor = true;
            this.rbtnRedactorFree.Click += new System.EventHandler(this.rbtnCameraType_Click);
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(31, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(34, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Type:";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.rbtnFast);
            this.panel2.Controls.Add(this.rbtnNormal);
            this.panel2.Controls.Add(this.rbtnSlow);
            this.panel2.Controls.Add(this.label4);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel2.Location = new System.Drawing.Point(3, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(172, 62);
            this.panel2.TabIndex = 2;
            // 
            // rbtnFast
            // 
            this.rbtnFast.AutoSize = true;
            this.rbtnFast.Location = new System.Drawing.Point(79, 39);
            this.rbtnFast.Name = "rbtnFast";
            this.rbtnFast.Size = new System.Drawing.Size(45, 17);
            this.rbtnFast.TabIndex = 2;
            this.rbtnFast.TabStop = true;
            this.rbtnFast.Text = "Fast";
            this.rbtnFast.UseVisualStyleBackColor = true;
            this.rbtnFast.Click += new System.EventHandler(this.rbtnCameraSpeed_Click);
            // 
            // rbtnNormal
            // 
            this.rbtnNormal.AutoSize = true;
            this.rbtnNormal.Location = new System.Drawing.Point(79, 22);
            this.rbtnNormal.Name = "rbtnNormal";
            this.rbtnNormal.Size = new System.Drawing.Size(58, 17);
            this.rbtnNormal.TabIndex = 2;
            this.rbtnNormal.TabStop = true;
            this.rbtnNormal.Text = "Normal";
            this.rbtnNormal.UseVisualStyleBackColor = true;
            this.rbtnNormal.Click += new System.EventHandler(this.rbtnCameraSpeed_Click);
            // 
            // rbtnSlow
            // 
            this.rbtnSlow.AutoSize = true;
            this.rbtnSlow.Location = new System.Drawing.Point(79, 5);
            this.rbtnSlow.Name = "rbtnSlow";
            this.rbtnSlow.Size = new System.Drawing.Size(48, 17);
            this.rbtnSlow.TabIndex = 2;
            this.rbtnSlow.TabStop = true;
            this.rbtnSlow.Text = "Slow";
            this.rbtnSlow.UseVisualStyleBackColor = true;
            this.rbtnSlow.Click += new System.EventHandler(this.rbtnCameraSpeed_Click);
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(27, 24);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "Speed:";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.panel4);
            this.tabPage2.Controls.Add(this.panel3);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(10, 3, 3, 3);
            this.tabPage2.Size = new System.Drawing.Size(178, 157);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Terrain";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.rbtnWireframe);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(10, 29);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(165, 28);
            this.panel4.TabIndex = 5;
            // 
            // rbtnWireframe
            // 
            this.rbtnWireframe.AutoCheck = false;
            this.rbtnWireframe.AutoSize = true;
            this.rbtnWireframe.Location = new System.Drawing.Point(13, 6);
            this.rbtnWireframe.Name = "rbtnWireframe";
            this.rbtnWireframe.Size = new System.Drawing.Size(73, 17);
            this.rbtnWireframe.TabIndex = 2;
            this.rbtnWireframe.Text = "Wireframe";
            this.rbtnWireframe.UseVisualStyleBackColor = true;
            this.rbtnWireframe.Click += new System.EventHandler(this.rbtnWireframe_Click);
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.rbtnQuadTreeVisible);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(10, 3);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(165, 26);
            this.panel3.TabIndex = 4;
            // 
            // rbtnQuadTreeVisible
            // 
            this.rbtnQuadTreeVisible.AutoCheck = false;
            this.rbtnQuadTreeVisible.AutoSize = true;
            this.rbtnQuadTreeVisible.Location = new System.Drawing.Point(13, 5);
            this.rbtnQuadTreeVisible.Name = "rbtnQuadTreeVisible";
            this.rbtnQuadTreeVisible.Size = new System.Drawing.Size(105, 17);
            this.rbtnQuadTreeVisible.TabIndex = 2;
            this.rbtnQuadTreeVisible.Text = "QuadTree visible";
            this.rbtnQuadTreeVisible.UseVisualStyleBackColor = true;
            this.rbtnQuadTreeVisible.CheckedChanged += new System.EventHandler(this.rbtnQuadTreeVisible_CheckedChanged);
            this.rbtnQuadTreeVisible.Click += new System.EventHandler(this.rbtnWireframe_Click);
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(202, 221);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOk);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "SettingsForm";
            this.Padding = new System.Windows.Forms.Padding(8, 8, 8, 30);
            this.Text = "Settings";
            this.Activated += new System.EventHandler(this.SettingsForm_Activated);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private GUI_elements.AWA_Button btnOk;
        private GUI_elements.AWA_Button btnCancel;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label4;
        public System.Windows.Forms.RadioButton rbtnRedactor;
        public System.Windows.Forms.RadioButton rbtnRedactorFree;
        public System.Windows.Forms.RadioButton rbtnFast;
        public System.Windows.Forms.RadioButton rbtnNormal;
        public System.Windows.Forms.RadioButton rbtnSlow;
        private System.Windows.Forms.Panel panel3;
        public System.Windows.Forms.RadioButton rbtnQuadTreeVisible;
        private System.Windows.Forms.Panel panel4;
        public System.Windows.Forms.RadioButton rbtnWireframe;
    }
}