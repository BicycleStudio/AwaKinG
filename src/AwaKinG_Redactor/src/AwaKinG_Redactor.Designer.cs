namespace AwaKinG_Redactor
{
    partial class AwaKinG_Redactor
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openMapToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cameraToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mtsiCameraRedactor = new System.Windows.Forms.ToolStripMenuItem();
            this.mtsiCameraFree = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.terrainToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadFromFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel_Ex2 = new GUI_elements.Panel_Ex();
            this.panel7 = new System.Windows.Forms.Panel();
            this.avbPenHardness = new GUI_elements.AWA_Value_Button();
            this.label4 = new System.Windows.Forms.Label();
            this.panel6 = new System.Windows.Forms.Panel();
            this.avbPenSizeOuter = new GUI_elements.AWA_Value_Button();
            this.label3 = new System.Windows.Forms.Label();
            this.panel5 = new System.Windows.Forms.Panel();
            this.avbPenSizeInner = new GUI_elements.AWA_Value_Button();
            this.label2 = new System.Windows.Forms.Label();
            this.panel4 = new System.Windows.Forms.Panel();
            this.awA_Button6 = new GUI_elements.AWA_Button();
            this.awA_Button5 = new GUI_elements.AWA_Button();
            this.awA_Button4 = new GUI_elements.AWA_Button();
            this.panel_Ex1 = new GUI_elements.Panel_Ex();
            this.awA_Value_Button2 = new GUI_elements.AWA_Value_Button();
            this.awA_Value_Button1 = new GUI_elements.AWA_Value_Button();
            this.awA_Button1 = new GUI_elements.AWA_Button();
            this.awA_Button2 = new GUI_elements.AWA_Button();
            this.awA_Button3 = new GUI_elements.AWA_Button();
            this.awA_Value_Button3 = new GUI_elements.AWA_Value_Button();
            this.pnlRender = new System.Windows.Forms.Panel();
            this.menuStrip1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel_Ex2.SuspendLayout();
            this.panel7.SuspendLayout();
            this.panel6.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel_Ex1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.terrainToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(784, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openMapToolStripMenuItem,
            this.toolStripSeparator3,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openMapToolStripMenuItem
            // 
            this.openMapToolStripMenuItem.Name = "openMapToolStripMenuItem";
            this.openMapToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.openMapToolStripMenuItem.Text = "Open map...";
            this.openMapToolStripMenuItem.Click += new System.EventHandler(this.openMapToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(136, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cameraToolStripMenuItem,
            this.toolStripSeparator1,
            this.settingsToolStripMenuItem});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // cameraToolStripMenuItem
            // 
            this.cameraToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mtsiCameraRedactor,
            this.mtsiCameraFree});
            this.cameraToolStripMenuItem.Name = "cameraToolStripMenuItem";
            this.cameraToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.cameraToolStripMenuItem.Text = "Camera ";
            // 
            // mtsiCameraRedactor
            // 
            this.mtsiCameraRedactor.Checked = true;
            this.mtsiCameraRedactor.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mtsiCameraRedactor.Name = "mtsiCameraRedactor";
            this.mtsiCameraRedactor.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
            this.mtsiCameraRedactor.Size = new System.Drawing.Size(162, 22);
            this.mtsiCameraRedactor.Tag = "0";
            this.mtsiCameraRedactor.Text = "Redactor";
            this.mtsiCameraRedactor.Click += new System.EventHandler(this.freeToolStripMenuItem_Click);
            // 
            // mtsiCameraFree
            // 
            this.mtsiCameraFree.Name = "mtsiCameraFree";
            this.mtsiCameraFree.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
            this.mtsiCameraFree.Size = new System.Drawing.Size(162, 22);
            this.mtsiCameraFree.Tag = "1";
            this.mtsiCameraFree.Text = "Free";
            this.mtsiCameraFree.Click += new System.EventHandler(this.freeToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(122, 6);
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.settingsToolStripMenuItem.Text = "Settings...";
            this.settingsToolStripMenuItem.Click += new System.EventHandler(this.settingsToolStripMenuItem_Click);
            // 
            // terrainToolStripMenuItem
            // 
            this.terrainToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadFromFileToolStripMenuItem,
            this.saveToFileToolStripMenuItem});
            this.terrainToolStripMenuItem.Name = "terrainToolStripMenuItem";
            this.terrainToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.terrainToolStripMenuItem.Text = "Terrain";
            // 
            // loadFromFileToolStripMenuItem
            // 
            this.loadFromFileToolStripMenuItem.Name = "loadFromFileToolStripMenuItem";
            this.loadFromFileToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.loadFromFileToolStripMenuItem.Text = "Load from file...";
            this.loadFromFileToolStripMenuItem.Click += new System.EventHandler(this.loadFromFileToolStripMenuItem_Click);
            // 
            // saveToFileToolStripMenuItem
            // 
            this.saveToFileToolStripMenuItem.Name = "saveToFileToolStripMenuItem";
            this.saveToFileToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.saveToFileToolStripMenuItem.Text = "Save to file..";
            this.saveToFileToolStripMenuItem.Click += new System.EventHandler(this.saveToFileToolStripMenuItem_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 24);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(784, 28);
            this.panel1.TabIndex = 1;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panel2.Controls.Add(this.label1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel2.Location = new System.Drawing.Point(0, 533);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(784, 28);
            this.panel2.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Log:";
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.SystemColors.ControlDark;
            this.panel3.Controls.Add(this.panel_Ex2);
            this.panel3.Controls.Add(this.panel_Ex1);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel3.Location = new System.Drawing.Point(0, 52);
            this.panel3.Name = "panel3";
            this.panel3.Padding = new System.Windows.Forms.Padding(2);
            this.panel3.Size = new System.Drawing.Size(173, 481);
            this.panel3.TabIndex = 3;
            // 
            // panel_Ex2
            // 
            this.panel_Ex2._Checked = false;
            this.panel_Ex2.BACKCOLOR = System.Drawing.Color.Transparent;
            this.panel_Ex2.BORDERCOLOR = System.Drawing.Color.Black;
            this.panel_Ex2.BORDERRADIUS = 5;
            this.panel_Ex2.BORDERWIDTH = 1;
            this.panel_Ex2.Controls.Add(this.panel7);
            this.panel_Ex2.Controls.Add(this.panel6);
            this.panel_Ex2.Controls.Add(this.panel5);
            this.panel_Ex2.Controls.Add(this.panel4);
            this.panel_Ex2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel_Ex2.Location = new System.Drawing.Point(2, 150);
            this.panel_Ex2.Name = "panel_Ex2";
            this.panel_Ex2.Padding = new System.Windows.Forms.Padding(0, 25, 0, 0);
            this.panel_Ex2.Size = new System.Drawing.Size(169, 192);
            this.panel_Ex2.TabIndex = 10;
            this.panel_Ex2.Text = "Pen";
            // 
            // panel7
            // 
            this.panel7.Controls.Add(this.avbPenHardness);
            this.panel7.Controls.Add(this.label4);
            this.panel7.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel7.Location = new System.Drawing.Point(0, 126);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(169, 25);
            this.panel7.TabIndex = 3;
            // 
            // avbPenHardness
            // 
            this.avbPenHardness.ARROWHEIGHT = 1;
            this.avbPenHardness.ARROWTOOLSH = 1;
            this.avbPenHardness.ARRWIDTH = 20;
            this.avbPenHardness.BackColor = System.Drawing.Color.Transparent;
            this.avbPenHardness.BACKCOLOR = System.Drawing.Color.Transparent;
            this.avbPenHardness.BORDERCOLOR = System.Drawing.Color.Black;
            this.avbPenHardness.BORDERRADIUS = 5;
            this.avbPenHardness.BORDERWIDTH = 0;
            this.avbPenHardness.Image = null;
            this.avbPenHardness.Location = new System.Drawing.Point(78, 2);
            this.avbPenHardness.MaxValue = 1000F;
            this.avbPenHardness.MinValue = -1000F;
            this.avbPenHardness.Name = "avbPenHardness";
            this.avbPenHardness.Size = new System.Drawing.Size(75, 20);
            this.avbPenHardness.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
            this.avbPenHardness.TabIndex = 1;
            this.avbPenHardness.Text = "awA_Value_Button6";
            this.avbPenHardness.UseVisualStyleBackColor = false;
            this.avbPenHardness.VALUEV = 1F;
            this.avbPenHardness.OnValueChanged += new System.EventHandler<System.EventArgs>(this.avbPenHardness_OnValueChanged);
            this.avbPenHardness.MouseUp += new System.Windows.Forms.MouseEventHandler(this.avbPenHardness_MouseUp);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 6);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(55, 13);
            this.label4.TabIndex = 0;
            this.label4.Text = "Hardness:";
            // 
            // panel6
            // 
            this.panel6.Controls.Add(this.avbPenSizeOuter);
            this.panel6.Controls.Add(this.label3);
            this.panel6.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel6.Location = new System.Drawing.Point(0, 101);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(169, 25);
            this.panel6.TabIndex = 2;
            // 
            // avbPenSizeOuter
            // 
            this.avbPenSizeOuter.ARROWHEIGHT = 1;
            this.avbPenSizeOuter.ARROWTOOLSH = 1;
            this.avbPenSizeOuter.ARRWIDTH = 20;
            this.avbPenSizeOuter.BackColor = System.Drawing.Color.Transparent;
            this.avbPenSizeOuter.BACKCOLOR = System.Drawing.Color.Transparent;
            this.avbPenSizeOuter.BORDERCOLOR = System.Drawing.Color.Black;
            this.avbPenSizeOuter.BORDERRADIUS = 5;
            this.avbPenSizeOuter.BORDERWIDTH = 0;
            this.avbPenSizeOuter.Image = null;
            this.avbPenSizeOuter.Location = new System.Drawing.Point(78, 2);
            this.avbPenSizeOuter.MaxValue = 10F;
            this.avbPenSizeOuter.MinValue = 1F;
            this.avbPenSizeOuter.Name = "avbPenSizeOuter";
            this.avbPenSizeOuter.Size = new System.Drawing.Size(75, 20);
            this.avbPenSizeOuter.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
            this.avbPenSizeOuter.TabIndex = 1;
            this.avbPenSizeOuter.Text = "awA_Value_Button5";
            this.avbPenSizeOuter.UseVisualStyleBackColor = false;
            this.avbPenSizeOuter.VALUEV = 1F;
            this.avbPenSizeOuter.OnValueChanged += new System.EventHandler<System.EventArgs>(this.avbPenSizeOuter_OnValueChanged);
            this.avbPenSizeOuter.MouseUp += new System.Windows.Forms.MouseEventHandler(this.avbPenSizeOuter_MouseUp);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(14, 6);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Size outer:";
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.avbPenSizeInner);
            this.panel5.Controls.Add(this.label2);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel5.Location = new System.Drawing.Point(0, 76);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(169, 25);
            this.panel5.TabIndex = 1;
            // 
            // avbPenSizeInner
            // 
            this.avbPenSizeInner.ARROWHEIGHT = 1;
            this.avbPenSizeInner.ARROWTOOLSH = 1;
            this.avbPenSizeInner.ARRWIDTH = 20;
            this.avbPenSizeInner.BackColor = System.Drawing.Color.Transparent;
            this.avbPenSizeInner.BACKCOLOR = System.Drawing.Color.Transparent;
            this.avbPenSizeInner.BORDERCOLOR = System.Drawing.Color.Black;
            this.avbPenSizeInner.BORDERRADIUS = 5;
            this.avbPenSizeInner.BORDERWIDTH = 0;
            this.avbPenSizeInner.Image = null;
            this.avbPenSizeInner.Location = new System.Drawing.Point(78, 2);
            this.avbPenSizeInner.MaxValue = 10F;
            this.avbPenSizeInner.MinValue = 1F;
            this.avbPenSizeInner.Name = "avbPenSizeInner";
            this.avbPenSizeInner.Size = new System.Drawing.Size(75, 20);
            this.avbPenSizeInner.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
            this.avbPenSizeInner.TabIndex = 1;
            this.avbPenSizeInner.Text = "awA_Value_Button4";
            this.avbPenSizeInner.UseVisualStyleBackColor = false;
            this.avbPenSizeInner.VALUEV = 1F;
            this.avbPenSizeInner.OnValueChanged += new System.EventHandler<System.EventArgs>(this.avbPenSizeInner_OnValueChanged);
            this.avbPenSizeInner.MouseUp += new System.Windows.Forms.MouseEventHandler(this.avbPenSizeOuter_MouseUp);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 6);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Size inner:";
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.awA_Button6);
            this.panel4.Controls.Add(this.awA_Button5);
            this.panel4.Controls.Add(this.awA_Button4);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(0, 25);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(169, 51);
            this.panel4.TabIndex = 0;
            // 
            // awA_Button6
            // 
            this.awA_Button6.BackColor = System.Drawing.Color.Transparent;
            this.awA_Button6.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Button6.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Button6.BORDERRADIUS = 5;
            this.awA_Button6.BORDERWIDTH = 1;
            this.awA_Button6.Image = null;
            this.awA_Button6.Location = new System.Drawing.Point(114, 3);
            this.awA_Button6.Name = "awA_Button6";
            this.awA_Button6.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.awA_Button6.SCALEBORD = true;
            this.awA_Button6.Size = new System.Drawing.Size(42, 44);
            this.awA_Button6.TabIndex = 8;
            this.awA_Button6.Text = "N";
            this.awA_Button6.UseVisualStyleBackColor = false;
            this.awA_Button6.Click += new System.EventHandler(this.awA_Button6_Click);
            // 
            // awA_Button5
            // 
            this.awA_Button5.BackColor = System.Drawing.Color.Transparent;
            this.awA_Button5.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Button5.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Button5.BORDERRADIUS = 5;
            this.awA_Button5.BORDERWIDTH = 1;
            this.awA_Button5.Image = null;
            this.awA_Button5.Location = new System.Drawing.Point(63, 3);
            this.awA_Button5.Name = "awA_Button5";
            this.awA_Button5.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.awA_Button5.SCALEBORD = true;
            this.awA_Button5.Size = new System.Drawing.Size(42, 44);
            this.awA_Button5.TabIndex = 7;
            this.awA_Button5.Text = "T";
            this.awA_Button5.UseVisualStyleBackColor = false;
            this.awA_Button5.Click += new System.EventHandler(this.awA_Button5_Click);
            // 
            // awA_Button4
            // 
            this.awA_Button4.BackColor = System.Drawing.Color.Transparent;
            this.awA_Button4.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Button4.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Button4.BORDERRADIUS = 5;
            this.awA_Button4.BORDERWIDTH = 1;
            this.awA_Button4.CHECKABLE = true;
            this.awA_Button4.Image = null;
            this.awA_Button4.Location = new System.Drawing.Point(11, 3);
            this.awA_Button4.Name = "awA_Button4";
            this.awA_Button4.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.awA_Button4.SCALEBORD = true;
            this.awA_Button4.Size = new System.Drawing.Size(42, 44);
            this.awA_Button4.TabIndex = 6;
            this.awA_Button4.Text = "H";
            this.awA_Button4.UseVisualStyleBackColor = false;
            this.awA_Button4.Click += new System.EventHandler(this.awA_Button4_Click);
            // 
            // panel_Ex1
            // 
            this.panel_Ex1._Checked = false;
            this.panel_Ex1.BACKCOLOR = System.Drawing.Color.Transparent;
            this.panel_Ex1.BORDERCOLOR = System.Drawing.Color.Black;
            this.panel_Ex1.BORDERRADIUS = 5;
            this.panel_Ex1.BORDERWIDTH = 1;
            this.panel_Ex1.Controls.Add(this.awA_Value_Button2);
            this.panel_Ex1.Controls.Add(this.awA_Value_Button1);
            this.panel_Ex1.Controls.Add(this.awA_Button1);
            this.panel_Ex1.Controls.Add(this.awA_Button2);
            this.panel_Ex1.Controls.Add(this.awA_Button3);
            this.panel_Ex1.Controls.Add(this.awA_Value_Button3);
            this.panel_Ex1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel_Ex1.Location = new System.Drawing.Point(2, 2);
            this.panel_Ex1.Name = "panel_Ex1";
            this.panel_Ex1.Size = new System.Drawing.Size(169, 148);
            this.panel_Ex1.TabIndex = 9;
            this.panel_Ex1.Text = "Main settings";
            // 
            // awA_Value_Button2
            // 
            this.awA_Value_Button2.ARROWHEIGHT = 0;
            this.awA_Value_Button2.ARROWTOOLSH = 1;
            this.awA_Value_Button2.ARRWIDTH = 20;
            this.awA_Value_Button2.BackColor = System.Drawing.Color.Transparent;
            this.awA_Value_Button2.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Value_Button2.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Value_Button2.BORDERRADIUS = 5;
            this.awA_Value_Button2.BORDERWIDTH = 1;
            this.awA_Value_Button2.Image = null;
            this.awA_Value_Button2.Location = new System.Drawing.Point(90, 29);
            this.awA_Value_Button2.MaxValue = 32F;
            this.awA_Value_Button2.MinValue = 1F;
            this.awA_Value_Button2.Name = "awA_Value_Button2";
            this.awA_Value_Button2.Size = new System.Drawing.Size(60, 31);
            this.awA_Value_Button2.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
            this.awA_Value_Button2.TabIndex = 1;
            this.awA_Value_Button2.Text = "awA_Value_Button2";
            this.awA_Value_Button2.UseVisualStyleBackColor = false;
            this.awA_Value_Button2.VALUEV = 1F;
            // 
            // awA_Value_Button1
            // 
            this.awA_Value_Button1.ARROWHEIGHT = 0;
            this.awA_Value_Button1.ARROWTOOLSH = 1;
            this.awA_Value_Button1.ARRWIDTH = 20;
            this.awA_Value_Button1.BackColor = System.Drawing.Color.Transparent;
            this.awA_Value_Button1.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Value_Button1.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Value_Button1.BORDERRADIUS = 5;
            this.awA_Value_Button1.BORDERWIDTH = 1;
            this.awA_Value_Button1.Image = null;
            this.awA_Value_Button1.Location = new System.Drawing.Point(15, 29);
            this.awA_Value_Button1.MaxValue = 32F;
            this.awA_Value_Button1.MinValue = 1F;
            this.awA_Value_Button1.Name = "awA_Value_Button1";
            this.awA_Value_Button1.Size = new System.Drawing.Size(60, 31);
            this.awA_Value_Button1.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
            this.awA_Value_Button1.TabIndex = 0;
            this.awA_Value_Button1.Text = "awA_Value_Button1";
            this.awA_Value_Button1.UseVisualStyleBackColor = false;
            this.awA_Value_Button1.VALUEV = 1F;
            // 
            // awA_Button1
            // 
            this.awA_Button1.BackColor = System.Drawing.Color.Transparent;
            this.awA_Button1.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Button1.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Button1.BORDERRADIUS = 5;
            this.awA_Button1.BORDERWIDTH = 1;
            this.awA_Button1.Image = null;
            this.awA_Button1.Location = new System.Drawing.Point(30, 66);
            this.awA_Button1.Name = "awA_Button1";
            this.awA_Button1.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.awA_Button1.SCALEBORD = true;
            this.awA_Button1.Size = new System.Drawing.Size(107, 20);
            this.awA_Button1.TabIndex = 2;
            this.awA_Button1.Text = "create";
            this.awA_Button1.UseVisualStyleBackColor = false;
            this.awA_Button1.Click += new System.EventHandler(this.awA_Button1_Click);
            // 
            // awA_Button2
            // 
            this.awA_Button2.BackColor = System.Drawing.Color.Transparent;
            this.awA_Button2.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Button2.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Button2.BORDERRADIUS = 5;
            this.awA_Button2.BORDERWIDTH = 1;
            this.awA_Button2.Image = null;
            this.awA_Button2.Location = new System.Drawing.Point(76, 92);
            this.awA_Button2.Name = "awA_Button2";
            this.awA_Button2.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.awA_Button2.SCALEBORD = true;
            this.awA_Button2.Size = new System.Drawing.Size(88, 20);
            this.awA_Button2.TabIndex = 4;
            this.awA_Button2.Text = "randomize";
            this.awA_Button2.UseVisualStyleBackColor = false;
            this.awA_Button2.Click += new System.EventHandler(this.awA_Button2_Click);
            // 
            // awA_Button3
            // 
            this.awA_Button3.BackColor = System.Drawing.Color.Transparent;
            this.awA_Button3.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Button3.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Button3.BORDERRADIUS = 5;
            this.awA_Button3.BORDERWIDTH = 1;
            this.awA_Button3.Image = null;
            this.awA_Button3.Location = new System.Drawing.Point(76, 118);
            this.awA_Button3.Name = "awA_Button3";
            this.awA_Button3.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.awA_Button3.SCALEBORD = true;
            this.awA_Button3.Size = new System.Drawing.Size(88, 20);
            this.awA_Button3.TabIndex = 5;
            this.awA_Button3.Text = "blur";
            this.awA_Button3.UseVisualStyleBackColor = false;
            this.awA_Button3.Click += new System.EventHandler(this.awA_Button3_Click);
            // 
            // awA_Value_Button3
            // 
            this.awA_Value_Button3.ARROWHEIGHT = 0;
            this.awA_Value_Button3.ARROWTOOLSH = 1;
            this.awA_Value_Button3.ARRWIDTH = 20;
            this.awA_Value_Button3.BackColor = System.Drawing.Color.Transparent;
            this.awA_Value_Button3.BACKCOLOR = System.Drawing.Color.Transparent;
            this.awA_Value_Button3.BORDERCOLOR = System.Drawing.Color.Black;
            this.awA_Value_Button3.BORDERRADIUS = 5;
            this.awA_Value_Button3.BORDERWIDTH = 1;
            this.awA_Value_Button3.Image = null;
            this.awA_Value_Button3.Location = new System.Drawing.Point(10, 92);
            this.awA_Value_Button3.MaxValue = 100F;
            this.awA_Value_Button3.MinValue = 1F;
            this.awA_Value_Button3.Name = "awA_Value_Button3";
            this.awA_Value_Button3.Size = new System.Drawing.Size(60, 46);
            this.awA_Value_Button3.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
            this.awA_Value_Button3.TabIndex = 3;
            this.awA_Value_Button3.Text = "awA_Value_Button3";
            this.awA_Value_Button3.UseVisualStyleBackColor = false;
            this.awA_Value_Button3.VALUEV = 1F;
            // 
            // pnlRender
            // 
            this.pnlRender.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlRender.Location = new System.Drawing.Point(173, 52);
            this.pnlRender.Name = "pnlRender";
            this.pnlRender.Size = new System.Drawing.Size(611, 481);
            this.pnlRender.TabIndex = 4;
            this.pnlRender.SizeChanged += new System.EventHandler(this.pnlRender_SizeChanged);
            this.pnlRender.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnlRender_MouseDown);
            this.pnlRender.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnlRender_MouseMove);
            this.pnlRender.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pnlRender_MouseUp);
            // 
            // AwaKinG_Redactor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 561);
            this.Controls.Add(this.pnlRender);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(500, 500);
            this.Name = "AwaKinG_Redactor";
            this.Text = "AwaKinG Redactor";
            this.Activated += new System.EventHandler(this.AwaKinG_Redactor_Activated);
            this.Deactivate += new System.EventHandler(this.AwaKinG_Redactor_Deactivate);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AwaKinG_Redactor_FormClosing);
            this.Load += new System.EventHandler(this.AwaKinG_Redactor_Load);
            this.SizeChanged += new System.EventHandler(this.AwaKinG_Redactor_SizeChanged);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel_Ex2.ResumeLayout(false);
            this.panel7.ResumeLayout(false);
            this.panel7.PerformLayout();
            this.panel6.ResumeLayout(false);
            this.panel6.PerformLayout();
            this.panel5.ResumeLayout(false);
            this.panel5.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.panel_Ex1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel pnlRender;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openMapToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cameraToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mtsiCameraRedactor;
        private System.Windows.Forms.ToolStripMenuItem mtsiCameraFree;
        private GUI_elements.AWA_Value_Button awA_Value_Button2;
        private GUI_elements.AWA_Value_Button awA_Value_Button1;
        private GUI_elements.AWA_Button awA_Button1;
        private GUI_elements.AWA_Button awA_Button3;
        private GUI_elements.AWA_Button awA_Button2;
        private GUI_elements.AWA_Value_Button awA_Value_Button3;
        private System.Windows.Forms.ToolStripMenuItem terrainToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadFromFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToFileToolStripMenuItem;
        private GUI_elements.AWA_Button awA_Button6;
        private GUI_elements.AWA_Button awA_Button5;
        private GUI_elements.AWA_Button awA_Button4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem;
        private GUI_elements.Panel_Ex panel_Ex2;
        private System.Windows.Forms.Panel panel7;
        private GUI_elements.AWA_Value_Button avbPenHardness;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel panel6;
        private GUI_elements.AWA_Value_Button avbPenSizeOuter;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel panel5;
        private GUI_elements.AWA_Value_Button avbPenSizeInner;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel panel4;
        private GUI_elements.Panel_Ex panel_Ex1;
    }
}

