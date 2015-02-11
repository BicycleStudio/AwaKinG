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
            this.pnlLeft = new System.Windows.Forms.Panel();
            this.pnlTerrainPen = new GUI_elements.Panel_Ex();
            this.pnlPositionLock = new System.Windows.Forms.Panel();
            this.btnTPPositionLock = new GUI_elements.AWA_Button();
            this.pnlTerrainPenSmoothIn = new System.Windows.Forms.Panel();
            this.btnTPSmoothIn = new GUI_elements.AWA_Button();
            this.pnlTerrainPenSmoothOut = new System.Windows.Forms.Panel();
            this.btnTPSmoothOut = new GUI_elements.AWA_Button();
            this.pnlTerrainPenSmoothLoeff = new System.Windows.Forms.Panel();
            this.vbtnTPSmoothKoeff = new GUI_elements.AWA_Value_Button();
            this.label5 = new System.Windows.Forms.Label();
            this.panel5 = new System.Windows.Forms.Panel();
            this.vbtnTPShiftHeight = new GUI_elements.AWA_Value_Button();
            this.label7 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.vbtnTPAltHard = new GUI_elements.AWA_Value_Button();
            this.label6 = new System.Windows.Forms.Label();
            this.pnlTerrainPenHard = new System.Windows.Forms.Panel();
            this.vbtnTPHardness = new GUI_elements.AWA_Value_Button();
            this.label4 = new System.Windows.Forms.Label();
            this.pnlTerrainPenSizeOuter = new System.Windows.Forms.Panel();
            this.vbtnPenSizeOuter = new GUI_elements.AWA_Value_Button();
            this.label3 = new System.Windows.Forms.Label();
            this.pnlTerrainPenSizeInner = new System.Windows.Forms.Panel();
            this.vbtnPenSizeInner = new GUI_elements.AWA_Value_Button();
            this.label2 = new System.Windows.Forms.Label();
            this.panel4 = new System.Windows.Forms.Panel();
            this.btnTPTexture = new GUI_elements.AWA_Button();
            this.btnTPHeight = new GUI_elements.AWA_Button();
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
            this.pnlLeft.SuspendLayout();
            this.pnlTerrainPen.SuspendLayout();
            this.pnlPositionLock.SuspendLayout();
            this.pnlTerrainPenSmoothIn.SuspendLayout();
            this.pnlTerrainPenSmoothOut.SuspendLayout();
            this.pnlTerrainPenSmoothLoeff.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel3.SuspendLayout();
            this.pnlTerrainPenHard.SuspendLayout();
            this.pnlTerrainPenSizeOuter.SuspendLayout();
            this.pnlTerrainPenSizeInner.SuspendLayout();
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
            // pnlLeft
            // 
            this.pnlLeft.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pnlLeft.Controls.Add(this.pnlTerrainPen);
            this.pnlLeft.Controls.Add(this.panel_Ex1);
            this.pnlLeft.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlLeft.Location = new System.Drawing.Point(0, 52);
            this.pnlLeft.Name = "pnlLeft";
            this.pnlLeft.Padding = new System.Windows.Forms.Padding(2);
            this.pnlLeft.Size = new System.Drawing.Size(173, 481);
            this.pnlLeft.TabIndex = 3;
            // 
            // pnlTerrainPen
            // 
            this.pnlTerrainPen._Checked = false;
            this.pnlTerrainPen.BACKCOLOR = System.Drawing.Color.Transparent;
            this.pnlTerrainPen.BORDERCOLOR = System.Drawing.Color.Black;
            this.pnlTerrainPen.BORDERRADIUS = 5;
            this.pnlTerrainPen.BORDERWIDTH = 1;
            this.pnlTerrainPen.Controls.Add(this.pnlPositionLock);
            this.pnlTerrainPen.Controls.Add(this.pnlTerrainPenSmoothIn);
            this.pnlTerrainPen.Controls.Add(this.pnlTerrainPenSmoothOut);
            this.pnlTerrainPen.Controls.Add(this.pnlTerrainPenSmoothLoeff);
            this.pnlTerrainPen.Controls.Add(this.panel5);
            this.pnlTerrainPen.Controls.Add(this.panel3);
            this.pnlTerrainPen.Controls.Add(this.pnlTerrainPenHard);
            this.pnlTerrainPen.Controls.Add(this.pnlTerrainPenSizeOuter);
            this.pnlTerrainPen.Controls.Add(this.pnlTerrainPenSizeInner);
            this.pnlTerrainPen.Controls.Add(this.panel4);
            this.pnlTerrainPen.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTerrainPen.Location = new System.Drawing.Point(2, 150);
            this.pnlTerrainPen.Name = "pnlTerrainPen";
            this.pnlTerrainPen.Padding = new System.Windows.Forms.Padding(3, 25, 3, 5);
            this.pnlTerrainPen.Size = new System.Drawing.Size(169, 306);
            this.pnlTerrainPen.TabIndex = 10;
            this.pnlTerrainPen.Text = "Pen";
            // 
            // pnlPositionLock
            // 
            this.pnlPositionLock.Controls.Add(this.btnTPPositionLock);
            this.pnlPositionLock.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlPositionLock.Location = new System.Drawing.Point(3, 276);
            this.pnlPositionLock.Name = "pnlPositionLock";
            this.pnlPositionLock.Padding = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.pnlPositionLock.Size = new System.Drawing.Size(163, 25);
            this.pnlPositionLock.TabIndex = 7;
            this.pnlPositionLock.Visible = false;
            // 
            // btnTPPositionLock
            // 
            this.btnTPPositionLock.BackColor = System.Drawing.Color.Transparent;
            this.btnTPPositionLock.BACKCOLOR = System.Drawing.Color.Transparent;
            this.btnTPPositionLock.BORDERCOLOR = System.Drawing.Color.Black;
            this.btnTPPositionLock.BORDERRADIUS = 10;
            this.btnTPPositionLock.BORDERWIDTH = 0;
            this.btnTPPositionLock.CHECKABLE = true;
            this.btnTPPositionLock.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnTPPositionLock.Image = null;
            this.btnTPPositionLock.Location = new System.Drawing.Point(4, 2);
            this.btnTPPositionLock.Name = "btnTPPositionLock";
            this.btnTPPositionLock.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.btnTPPositionLock.SCALEBORD = true;
            this.btnTPPositionLock.Size = new System.Drawing.Size(155, 21);
            this.btnTPPositionLock.TabIndex = 5;
            this.btnTPPositionLock.Text = "Position lock";
            this.btnTPPositionLock.UseVisualStyleBackColor = false;
            // 
            // pnlTerrainPenSmoothIn
            // 
            this.pnlTerrainPenSmoothIn.Controls.Add(this.btnTPSmoothIn);
            this.pnlTerrainPenSmoothIn.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTerrainPenSmoothIn.Location = new System.Drawing.Point(3, 251);
            this.pnlTerrainPenSmoothIn.Name = "pnlTerrainPenSmoothIn";
            this.pnlTerrainPenSmoothIn.Padding = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.pnlTerrainPenSmoothIn.Size = new System.Drawing.Size(163, 25);
            this.pnlTerrainPenSmoothIn.TabIndex = 5;
            // 
            // btnTPSmoothIn
            // 
            this.btnTPSmoothIn.BackColor = System.Drawing.Color.Transparent;
            this.btnTPSmoothIn.BACKCOLOR = System.Drawing.Color.Transparent;
            this.btnTPSmoothIn.BORDERCOLOR = System.Drawing.Color.Black;
            this.btnTPSmoothIn.BORDERRADIUS = 10;
            this.btnTPSmoothIn.BORDERWIDTH = 0;
            this.btnTPSmoothIn.CHECKABLE = true;
            this.btnTPSmoothIn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnTPSmoothIn.Image = null;
            this.btnTPSmoothIn.Location = new System.Drawing.Point(4, 2);
            this.btnTPSmoothIn.Name = "btnTPSmoothIn";
            this.btnTPSmoothIn.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.btnTPSmoothIn.SCALEBORD = true;
            this.btnTPSmoothIn.Size = new System.Drawing.Size(155, 21);
            this.btnTPSmoothIn.TabIndex = 5;
            this.btnTPSmoothIn.Text = "Smooth in";
            this.btnTPSmoothIn.UseVisualStyleBackColor = false;
            this.btnTPSmoothIn.Click += new System.EventHandler(this.btnTPSmoothInOut_Click);
            // 
            // pnlTerrainPenSmoothOut
            // 
            this.pnlTerrainPenSmoothOut.Controls.Add(this.btnTPSmoothOut);
            this.pnlTerrainPenSmoothOut.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTerrainPenSmoothOut.Location = new System.Drawing.Point(3, 226);
            this.pnlTerrainPenSmoothOut.Name = "pnlTerrainPenSmoothOut";
            this.pnlTerrainPenSmoothOut.Padding = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.pnlTerrainPenSmoothOut.Size = new System.Drawing.Size(163, 25);
            this.pnlTerrainPenSmoothOut.TabIndex = 4;
            // 
            // btnTPSmoothOut
            // 
            this.btnTPSmoothOut.BackColor = System.Drawing.Color.Transparent;
            this.btnTPSmoothOut.BACKCOLOR = System.Drawing.Color.Transparent;
            this.btnTPSmoothOut.BORDERCOLOR = System.Drawing.Color.Black;
            this.btnTPSmoothOut.BORDERRADIUS = 10;
            this.btnTPSmoothOut.BORDERWIDTH = 0;
            this.btnTPSmoothOut.CHECKABLE = true;
            this.btnTPSmoothOut.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnTPSmoothOut.Image = null;
            this.btnTPSmoothOut.Location = new System.Drawing.Point(4, 2);
            this.btnTPSmoothOut.Name = "btnTPSmoothOut";
            this.btnTPSmoothOut.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.btnTPSmoothOut.SCALEBORD = true;
            this.btnTPSmoothOut.Size = new System.Drawing.Size(155, 21);
            this.btnTPSmoothOut.TabIndex = 5;
            this.btnTPSmoothOut.Text = "Smooth out";
            this.btnTPSmoothOut.UseVisualStyleBackColor = false;
            this.btnTPSmoothOut.Click += new System.EventHandler(this.btnTPSmoothInOut_Click);
            // 
            // pnlTerrainPenSmoothLoeff
            // 
            this.pnlTerrainPenSmoothLoeff.Controls.Add(this.vbtnTPSmoothKoeff);
            this.pnlTerrainPenSmoothLoeff.Controls.Add(this.label5);
            this.pnlTerrainPenSmoothLoeff.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTerrainPenSmoothLoeff.Location = new System.Drawing.Point(3, 201);
            this.pnlTerrainPenSmoothLoeff.Name = "pnlTerrainPenSmoothLoeff";
            this.pnlTerrainPenSmoothLoeff.Size = new System.Drawing.Size(163, 25);
            this.pnlTerrainPenSmoothLoeff.TabIndex = 6;
            // 
            // vbtnTPSmoothKoeff
            // 
            this.vbtnTPSmoothKoeff.ARROWHEIGHT = 1;
            this.vbtnTPSmoothKoeff.ARROWTOOLSH = 1;
            this.vbtnTPSmoothKoeff.ARRWIDTH = 20;
            this.vbtnTPSmoothKoeff.BackColor = System.Drawing.Color.Transparent;
            this.vbtnTPSmoothKoeff.BACKCOLOR = System.Drawing.Color.Transparent;
            this.vbtnTPSmoothKoeff.BORDERCOLOR = System.Drawing.Color.Black;
            this.vbtnTPSmoothKoeff.BORDERRADIUS = 5;
            this.vbtnTPSmoothKoeff.BORDERWIDTH = 0;
            this.vbtnTPSmoothKoeff.Image = null;
            this.vbtnTPSmoothKoeff.Location = new System.Drawing.Point(78, 2);
            this.vbtnTPSmoothKoeff.MaxValue = 1F;
            this.vbtnTPSmoothKoeff.MinValue = 0F;
            this.vbtnTPSmoothKoeff.Name = "vbtnTPSmoothKoeff";
            this.vbtnTPSmoothKoeff.Size = new System.Drawing.Size(75, 20);
            this.vbtnTPSmoothKoeff.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Very_Slow;
            this.vbtnTPSmoothKoeff.TabIndex = 1;
            this.vbtnTPSmoothKoeff.Text = "awA_Value_Button6";
            this.vbtnTPSmoothKoeff.UseVisualStyleBackColor = false;
            this.vbtnTPSmoothKoeff.VALUEV = 1F;
            this.vbtnTPSmoothKoeff.MouseUp += new System.Windows.Forms.MouseEventHandler(this.vbtnTPSmoothKoeff_MouseUp);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 6);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(73, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "Smooth koeff:";
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.vbtnTPShiftHeight);
            this.panel5.Controls.Add(this.label7);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel5.Location = new System.Drawing.Point(3, 176);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(163, 25);
            this.panel5.TabIndex = 9;
            // 
            // vbtnTPShiftHeight
            // 
            this.vbtnTPShiftHeight.ARROWHEIGHT = 1;
            this.vbtnTPShiftHeight.ARROWTOOLSH = 1;
            this.vbtnTPShiftHeight.ARRWIDTH = 20;
            this.vbtnTPShiftHeight.BackColor = System.Drawing.Color.Transparent;
            this.vbtnTPShiftHeight.BACKCOLOR = System.Drawing.Color.Transparent;
            this.vbtnTPShiftHeight.BORDERCOLOR = System.Drawing.Color.Black;
            this.vbtnTPShiftHeight.BORDERRADIUS = 5;
            this.vbtnTPShiftHeight.BORDERWIDTH = 0;
            this.vbtnTPShiftHeight.Image = null;
            this.vbtnTPShiftHeight.Location = new System.Drawing.Point(78, 2);
            this.vbtnTPShiftHeight.MaxValue = 10000F;
            this.vbtnTPShiftHeight.MinValue = -10000F;
            this.vbtnTPShiftHeight.Name = "vbtnTPShiftHeight";
            this.vbtnTPShiftHeight.Size = new System.Drawing.Size(75, 20);
            this.vbtnTPShiftHeight.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
            this.vbtnTPShiftHeight.TabIndex = 1;
            this.vbtnTPShiftHeight.Text = "awA_Value_Button6";
            this.vbtnTPShiftHeight.UseVisualStyleBackColor = false;
            this.vbtnTPShiftHeight.VALUEV = 0F;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 6);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(63, 13);
            this.label7.TabIndex = 0;
            this.label7.Text = "Shift-height:";
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.vbtnTPAltHard);
            this.panel3.Controls.Add(this.label6);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(3, 151);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(163, 25);
            this.panel3.TabIndex = 8;
            this.panel3.Visible = false;
            // 
            // vbtnTPAltHard
            // 
            this.vbtnTPAltHard.ARROWHEIGHT = 1;
            this.vbtnTPAltHard.ARROWTOOLSH = 1;
            this.vbtnTPAltHard.ARRWIDTH = 20;
            this.vbtnTPAltHard.BackColor = System.Drawing.Color.Transparent;
            this.vbtnTPAltHard.BACKCOLOR = System.Drawing.Color.Transparent;
            this.vbtnTPAltHard.BORDERCOLOR = System.Drawing.Color.Black;
            this.vbtnTPAltHard.BORDERRADIUS = 5;
            this.vbtnTPAltHard.BORDERWIDTH = 0;
            this.vbtnTPAltHard.Image = null;
            this.vbtnTPAltHard.Location = new System.Drawing.Point(78, 2);
            this.vbtnTPAltHard.MaxValue = 1000F;
            this.vbtnTPAltHard.MinValue = -1000F;
            this.vbtnTPAltHard.Name = "vbtnTPAltHard";
            this.vbtnTPAltHard.Size = new System.Drawing.Size(75, 20);
            this.vbtnTPAltHard.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
            this.vbtnTPAltHard.TabIndex = 1;
            this.vbtnTPAltHard.Text = "awA_Value_Button6";
            this.vbtnTPAltHard.UseVisualStyleBackColor = false;
            this.vbtnTPAltHard.VALUEV = 0F;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 6);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(68, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "Alt-hardness:";
            // 
            // pnlTerrainPenHard
            // 
            this.pnlTerrainPenHard.Controls.Add(this.vbtnTPHardness);
            this.pnlTerrainPenHard.Controls.Add(this.label4);
            this.pnlTerrainPenHard.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTerrainPenHard.Location = new System.Drawing.Point(3, 126);
            this.pnlTerrainPenHard.Name = "pnlTerrainPenHard";
            this.pnlTerrainPenHard.Size = new System.Drawing.Size(163, 25);
            this.pnlTerrainPenHard.TabIndex = 3;
            this.pnlTerrainPenHard.Visible = false;
            // 
            // vbtnTPHardness
            // 
            this.vbtnTPHardness.ARROWHEIGHT = 1;
            this.vbtnTPHardness.ARROWTOOLSH = 1;
            this.vbtnTPHardness.ARRWIDTH = 20;
            this.vbtnTPHardness.BackColor = System.Drawing.Color.Transparent;
            this.vbtnTPHardness.BACKCOLOR = System.Drawing.Color.Transparent;
            this.vbtnTPHardness.BORDERCOLOR = System.Drawing.Color.Black;
            this.vbtnTPHardness.BORDERRADIUS = 5;
            this.vbtnTPHardness.BORDERWIDTH = 0;
            this.vbtnTPHardness.Image = null;
            this.vbtnTPHardness.Location = new System.Drawing.Point(78, 2);
            this.vbtnTPHardness.MaxValue = 1000F;
            this.vbtnTPHardness.MinValue = -1000F;
            this.vbtnTPHardness.Name = "vbtnTPHardness";
            this.vbtnTPHardness.Size = new System.Drawing.Size(75, 20);
            this.vbtnTPHardness.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
            this.vbtnTPHardness.TabIndex = 1;
            this.vbtnTPHardness.Text = "awA_Value_Button6";
            this.vbtnTPHardness.UseVisualStyleBackColor = false;
            this.vbtnTPHardness.VALUEV = 1F;
            this.vbtnTPHardness.OnValueChanged += new System.EventHandler<System.EventArgs>(this.avbPenHardness_OnValueChanged);
            this.vbtnTPHardness.MouseUp += new System.Windows.Forms.MouseEventHandler(this.avbPenHardness_MouseUp);
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
            // pnlTerrainPenSizeOuter
            // 
            this.pnlTerrainPenSizeOuter.Controls.Add(this.vbtnPenSizeOuter);
            this.pnlTerrainPenSizeOuter.Controls.Add(this.label3);
            this.pnlTerrainPenSizeOuter.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTerrainPenSizeOuter.Location = new System.Drawing.Point(3, 101);
            this.pnlTerrainPenSizeOuter.Name = "pnlTerrainPenSizeOuter";
            this.pnlTerrainPenSizeOuter.Size = new System.Drawing.Size(163, 25);
            this.pnlTerrainPenSizeOuter.TabIndex = 2;
            // 
            // vbtnPenSizeOuter
            // 
            this.vbtnPenSizeOuter.ARROWHEIGHT = 1;
            this.vbtnPenSizeOuter.ARROWTOOLSH = 1;
            this.vbtnPenSizeOuter.ARRWIDTH = 20;
            this.vbtnPenSizeOuter.BackColor = System.Drawing.Color.Transparent;
            this.vbtnPenSizeOuter.BACKCOLOR = System.Drawing.Color.Transparent;
            this.vbtnPenSizeOuter.BORDERCOLOR = System.Drawing.Color.Black;
            this.vbtnPenSizeOuter.BORDERRADIUS = 5;
            this.vbtnPenSizeOuter.BORDERWIDTH = 0;
            this.vbtnPenSizeOuter.Image = null;
            this.vbtnPenSizeOuter.Location = new System.Drawing.Point(78, 2);
            this.vbtnPenSizeOuter.MaxValue = 9F;
            this.vbtnPenSizeOuter.MinValue = 1F;
            this.vbtnPenSizeOuter.Name = "vbtnPenSizeOuter";
            this.vbtnPenSizeOuter.Size = new System.Drawing.Size(75, 20);
            this.vbtnPenSizeOuter.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
            this.vbtnPenSizeOuter.TabIndex = 1;
            this.vbtnPenSizeOuter.Text = "awA_Value_Button5";
            this.vbtnPenSizeOuter.UseVisualStyleBackColor = false;
            this.vbtnPenSizeOuter.VALUEV = 1F;
            this.vbtnPenSizeOuter.OnValueChanged += new System.EventHandler<System.EventArgs>(this.avbPenSizeOuter_OnValueChanged);
            this.vbtnPenSizeOuter.MouseUp += new System.Windows.Forms.MouseEventHandler(this.avbPenSizeOuter_MouseUp);
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
            // pnlTerrainPenSizeInner
            // 
            this.pnlTerrainPenSizeInner.Controls.Add(this.vbtnPenSizeInner);
            this.pnlTerrainPenSizeInner.Controls.Add(this.label2);
            this.pnlTerrainPenSizeInner.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTerrainPenSizeInner.Location = new System.Drawing.Point(3, 76);
            this.pnlTerrainPenSizeInner.Name = "pnlTerrainPenSizeInner";
            this.pnlTerrainPenSizeInner.Size = new System.Drawing.Size(163, 25);
            this.pnlTerrainPenSizeInner.TabIndex = 1;
            // 
            // vbtnPenSizeInner
            // 
            this.vbtnPenSizeInner.ARROWHEIGHT = 1;
            this.vbtnPenSizeInner.ARROWTOOLSH = 1;
            this.vbtnPenSizeInner.ARRWIDTH = 20;
            this.vbtnPenSizeInner.BackColor = System.Drawing.Color.Transparent;
            this.vbtnPenSizeInner.BACKCOLOR = System.Drawing.Color.Transparent;
            this.vbtnPenSizeInner.BORDERCOLOR = System.Drawing.Color.Black;
            this.vbtnPenSizeInner.BORDERRADIUS = 5;
            this.vbtnPenSizeInner.BORDERWIDTH = 0;
            this.vbtnPenSizeInner.Image = null;
            this.vbtnPenSizeInner.Location = new System.Drawing.Point(78, 2);
            this.vbtnPenSizeInner.MaxValue = 9F;
            this.vbtnPenSizeInner.MinValue = 1F;
            this.vbtnPenSizeInner.Name = "vbtnPenSizeInner";
            this.vbtnPenSizeInner.Size = new System.Drawing.Size(75, 20);
            this.vbtnPenSizeInner.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
            this.vbtnPenSizeInner.TabIndex = 1;
            this.vbtnPenSizeInner.Text = "awA_Value_Button4";
            this.vbtnPenSizeInner.UseVisualStyleBackColor = false;
            this.vbtnPenSizeInner.VALUEV = 1F;
            this.vbtnPenSizeInner.OnValueChanged += new System.EventHandler<System.EventArgs>(this.avbPenSizeInner_OnValueChanged);
            this.vbtnPenSizeInner.MouseUp += new System.Windows.Forms.MouseEventHandler(this.avbPenSizeOuter_MouseUp);
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
            this.panel4.Controls.Add(this.btnTPTexture);
            this.panel4.Controls.Add(this.btnTPHeight);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(3, 25);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(163, 51);
            this.panel4.TabIndex = 0;
            // 
            // btnTPTexture
            // 
            this.btnTPTexture.BackColor = System.Drawing.Color.Transparent;
            this.btnTPTexture.BACKCOLOR = System.Drawing.Color.Transparent;
            this.btnTPTexture.BORDERCOLOR = System.Drawing.Color.Black;
            this.btnTPTexture.BORDERRADIUS = 5;
            this.btnTPTexture.BORDERWIDTH = 1;
            this.btnTPTexture.CHECKABLE = true;
            this.btnTPTexture.Image = null;
            this.btnTPTexture.Location = new System.Drawing.Point(87, 4);
            this.btnTPTexture.Name = "btnTPTexture";
            this.btnTPTexture.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.btnTPTexture.SCALEBORD = true;
            this.btnTPTexture.Size = new System.Drawing.Size(42, 44);
            this.btnTPTexture.TabIndex = 7;
            this.btnTPTexture.Text = "T";
            this.btnTPTexture.UseVisualStyleBackColor = false;
            this.btnTPTexture.Click += new System.EventHandler(this.awA_Button5_Click);
            // 
            // btnTPHeight
            // 
            this.btnTPHeight.BackColor = System.Drawing.Color.Transparent;
            this.btnTPHeight.BACKCOLOR = System.Drawing.Color.Transparent;
            this.btnTPHeight.BORDERCOLOR = System.Drawing.Color.Black;
            this.btnTPHeight.BORDERRADIUS = 5;
            this.btnTPHeight.BORDERWIDTH = 1;
            this.btnTPHeight.CHECKABLE = true;
            this.btnTPHeight.Image = null;
            this.btnTPHeight.Location = new System.Drawing.Point(35, 4);
            this.btnTPHeight.Name = "btnTPHeight";
            this.btnTPHeight.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
            this.btnTPHeight.SCALEBORD = true;
            this.btnTPHeight.Size = new System.Drawing.Size(42, 44);
            this.btnTPHeight.TabIndex = 6;
            this.btnTPHeight.Text = "H";
            this.btnTPHeight.UseVisualStyleBackColor = false;
            this.btnTPHeight.Click += new System.EventHandler(this.awA_Button4_Click);
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
            this.Controls.Add(this.pnlLeft);
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
            this.pnlLeft.ResumeLayout(false);
            this.pnlTerrainPen.ResumeLayout(false);
            this.pnlPositionLock.ResumeLayout(false);
            this.pnlTerrainPenSmoothIn.ResumeLayout(false);
            this.pnlTerrainPenSmoothOut.ResumeLayout(false);
            this.pnlTerrainPenSmoothLoeff.ResumeLayout(false);
            this.pnlTerrainPenSmoothLoeff.PerformLayout();
            this.panel5.ResumeLayout(false);
            this.panel5.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.pnlTerrainPenHard.ResumeLayout(false);
            this.pnlTerrainPenHard.PerformLayout();
            this.pnlTerrainPenSizeOuter.ResumeLayout(false);
            this.pnlTerrainPenSizeOuter.PerformLayout();
            this.pnlTerrainPenSizeInner.ResumeLayout(false);
            this.pnlTerrainPenSizeInner.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.panel_Ex1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel pnlLeft;
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
        private GUI_elements.AWA_Button btnTPTexture;
        private GUI_elements.AWA_Button btnTPHeight;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem;
        private GUI_elements.Panel_Ex pnlTerrainPen;
        private System.Windows.Forms.Panel pnlTerrainPenHard;
        private GUI_elements.AWA_Value_Button vbtnTPHardness;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel pnlTerrainPenSizeOuter;
        private GUI_elements.AWA_Value_Button vbtnPenSizeOuter;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel pnlTerrainPenSizeInner;
        private GUI_elements.AWA_Value_Button vbtnPenSizeInner;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel panel4;
        private GUI_elements.Panel_Ex panel_Ex1;
        private System.Windows.Forms.Panel pnlTerrainPenSmoothOut;
        private GUI_elements.AWA_Button btnTPSmoothOut;
        private System.Windows.Forms.Panel pnlTerrainPenSmoothIn;
        private GUI_elements.AWA_Button btnTPSmoothIn;
        private System.Windows.Forms.Panel pnlTerrainPenSmoothLoeff;
        private GUI_elements.AWA_Value_Button vbtnTPSmoothKoeff;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Panel pnlPositionLock;
        private GUI_elements.AWA_Button btnTPPositionLock;
        private System.Windows.Forms.Panel panel5;
        private GUI_elements.AWA_Value_Button vbtnTPShiftHeight;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Panel panel3;
        private GUI_elements.AWA_Value_Button vbtnTPAltHard;
        private System.Windows.Forms.Label label6;
    }
}

