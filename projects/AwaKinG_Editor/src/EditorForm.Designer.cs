namespace AwaKinG_Editor
{
    partial class EditorForm
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditorForm));
      this.menuMain = new System.Windows.Forms.MenuStrip();
      this.menuFile = new System.Windows.Forms.ToolStripMenuItem();
      this.menuFileCreateMap = new System.Windows.Forms.ToolStripMenuItem();
      this.menuFileOpenMap = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.menuFileSaveMap = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
      this.menuFileExit = new System.Windows.Forms.ToolStripMenuItem();
      this.menuEdit = new System.Windows.Forms.ToolStripMenuItem();
      this.menuEditCamera = new System.Windows.Forms.ToolStripMenuItem();
      this.menuEditCameraFirstPerson = new System.Windows.Forms.ToolStripMenuItem();
      this.menuEditCameraRedactor = new System.Windows.Forms.ToolStripMenuItem();
      this.menuEditCameraLinked = new System.Windows.Forms.ToolStripMenuItem();
      this.pnlDown = new System.Windows.Forms.Panel();
      this.pnlLeft = new System.Windows.Forms.FlowLayoutPanel();
      this.pnlEntityTransformation = new GUI_elements.Panel_Ex();
      this.btnEntTransfRotation = new System.Windows.Forms.Button();
      this.btnEntTransfScaling = new System.Windows.Forms.Button();
      this.btnEntTransfObject = new System.Windows.Forms.Button();
      this.btnEntTransfPosition = new System.Windows.Forms.Button();
      this.panel_Ex1 = new GUI_elements.Panel_Ex();
      this.btnTerrainCreate = new GUI_elements.AWA_Button();
      this.label1 = new System.Windows.Forms.Label();
      this.vbtnTerrainSizeY = new GUI_elements.AWA_Value_Button();
      this.vbtnTerrainSizeX = new GUI_elements.AWA_Value_Button();
      this.pnlRight = new System.Windows.Forms.FlowLayoutPanel();
      this.pnlRender = new System.Windows.Forms.Panel();
      this.pnlTop = new System.Windows.Forms.FlowLayoutPanel();
      this.pnlTopMain = new System.Windows.Forms.Panel();
      this.btnTopWater = new System.Windows.Forms.Button();
      this.btnTopEntity = new System.Windows.Forms.Button();
      this.btnTopTerrain = new System.Windows.Forms.Button();
      this.menuMain.SuspendLayout();
      this.pnlLeft.SuspendLayout();
      this.pnlEntityTransformation.SuspendLayout();
      this.panel_Ex1.SuspendLayout();
      this.pnlTop.SuspendLayout();
      this.pnlTopMain.SuspendLayout();
      this.SuspendLayout();
      // 
      // menuMain
      // 
      this.menuMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFile,
            this.menuEdit});
      this.menuMain.Location = new System.Drawing.Point(0, 0);
      this.menuMain.Name = "menuMain";
      this.menuMain.Size = new System.Drawing.Size(784, 24);
      this.menuMain.TabIndex = 0;
      this.menuMain.Text = "menuStrip1";
      // 
      // menuFile
      // 
      this.menuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFileCreateMap,
            this.menuFileOpenMap,
            this.toolStripSeparator1,
            this.menuFileSaveMap,
            this.toolStripSeparator2,
            this.menuFileExit});
      this.menuFile.Name = "menuFile";
      this.menuFile.Size = new System.Drawing.Size(37, 20);
      this.menuFile.Text = "File";
      // 
      // menuFileCreateMap
      // 
      this.menuFileCreateMap.Name = "menuFileCreateMap";
      this.menuFileCreateMap.Size = new System.Drawing.Size(152, 22);
      this.menuFileCreateMap.Text = "New map";
      this.menuFileCreateMap.Click += new System.EventHandler(this.menuFileCreateMap_Click);
      // 
      // menuFileOpenMap
      // 
      this.menuFileOpenMap.Name = "menuFileOpenMap";
      this.menuFileOpenMap.Size = new System.Drawing.Size(152, 22);
      this.menuFileOpenMap.Text = "Open map...";
      this.menuFileOpenMap.Click += new System.EventHandler(this.menuFileOpenMap_Click);
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size(149, 6);
      // 
      // menuFileSaveMap
      // 
      this.menuFileSaveMap.Name = "menuFileSaveMap";
      this.menuFileSaveMap.Size = new System.Drawing.Size(152, 22);
      this.menuFileSaveMap.Text = "Save map...";
      this.menuFileSaveMap.Click += new System.EventHandler(this.menuFileSaveMap_Click);
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size(149, 6);
      // 
      // menuFileExit
      // 
      this.menuFileExit.Name = "menuFileExit";
      this.menuFileExit.Size = new System.Drawing.Size(152, 22);
      this.menuFileExit.Text = "Exit";
      this.menuFileExit.Click += new System.EventHandler(this.menuFileExit_Click);
      // 
      // menuEdit
      // 
      this.menuEdit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEditCamera});
      this.menuEdit.Name = "menuEdit";
      this.menuEdit.Size = new System.Drawing.Size(39, 20);
      this.menuEdit.Text = "Edit";
      // 
      // menuEditCamera
      // 
      this.menuEditCamera.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEditCameraFirstPerson,
            this.menuEditCameraRedactor,
            this.menuEditCameraLinked});
      this.menuEditCamera.Name = "menuEditCamera";
      this.menuEditCamera.Size = new System.Drawing.Size(115, 22);
      this.menuEditCamera.Text = "Camera";
      // 
      // menuEditCameraFirstPerson
      // 
      this.menuEditCameraFirstPerson.Checked = true;
      this.menuEditCameraFirstPerson.CheckState = System.Windows.Forms.CheckState.Checked;
      this.menuEditCameraFirstPerson.Name = "menuEditCameraFirstPerson";
      this.menuEditCameraFirstPerson.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
      this.menuEditCameraFirstPerson.Size = new System.Drawing.Size(175, 22);
      this.menuEditCameraFirstPerson.Tag = "1";
      this.menuEditCameraFirstPerson.Text = "First person";
      this.menuEditCameraFirstPerson.Click += new System.EventHandler(this.CameraType_Click);
      // 
      // menuEditCameraRedactor
      // 
      this.menuEditCameraRedactor.Name = "menuEditCameraRedactor";
      this.menuEditCameraRedactor.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
      this.menuEditCameraRedactor.Size = new System.Drawing.Size(175, 22);
      this.menuEditCameraRedactor.Tag = "2";
      this.menuEditCameraRedactor.Text = "Redactor";
      this.menuEditCameraRedactor.Click += new System.EventHandler(this.CameraType_Click);
      // 
      // menuEditCameraLinked
      // 
      this.menuEditCameraLinked.Name = "menuEditCameraLinked";
      this.menuEditCameraLinked.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.L)));
      this.menuEditCameraLinked.Size = new System.Drawing.Size(175, 22);
      this.menuEditCameraLinked.Tag = "0";
      this.menuEditCameraLinked.Text = "Linked";
      this.menuEditCameraLinked.Click += new System.EventHandler(this.CameraType_Click);
      // 
      // pnlDown
      // 
      this.pnlDown.BackColor = System.Drawing.SystemColors.ControlLight;
      this.pnlDown.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.pnlDown.Location = new System.Drawing.Point(0, 536);
      this.pnlDown.Name = "pnlDown";
      this.pnlDown.Size = new System.Drawing.Size(784, 25);
      this.pnlDown.TabIndex = 1;
      // 
      // pnlLeft
      // 
      this.pnlLeft.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
      this.pnlLeft.Controls.Add(this.pnlEntityTransformation);
      this.pnlLeft.Controls.Add(this.panel_Ex1);
      this.pnlLeft.Dock = System.Windows.Forms.DockStyle.Left;
      this.pnlLeft.Location = new System.Drawing.Point(0, 66);
      this.pnlLeft.Name = "pnlLeft";
      this.pnlLeft.Size = new System.Drawing.Size(176, 470);
      this.pnlLeft.TabIndex = 2;
      // 
      // pnlEntityTransformation
      // 
      this.pnlEntityTransformation._Checked = false;
      this.pnlEntityTransformation.BACKCOLOR = System.Drawing.Color.Transparent;
      this.pnlEntityTransformation.BORDERCOLOR = System.Drawing.Color.Black;
      this.pnlEntityTransformation.BORDERRADIUS = 5;
      this.pnlEntityTransformation.BORDERWIDTH = 1;
      this.pnlEntityTransformation.Controls.Add(this.btnEntTransfRotation);
      this.pnlEntityTransformation.Controls.Add(this.btnEntTransfScaling);
      this.pnlEntityTransformation.Controls.Add(this.btnEntTransfObject);
      this.pnlEntityTransformation.Controls.Add(this.btnEntTransfPosition);
      this.pnlEntityTransformation.Location = new System.Drawing.Point(3, 3);
      this.pnlEntityTransformation.Name = "pnlEntityTransformation";
      this.pnlEntityTransformation.Size = new System.Drawing.Size(167, 137);
      this.pnlEntityTransformation.TabIndex = 0;
      this.pnlEntityTransformation.Text = "Transformation";
      // 
      // btnEntTransfRotation
      // 
      this.btnEntTransfRotation.BackColor = System.Drawing.SystemColors.ControlLight;
      this.btnEntTransfRotation.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntTransfRotation.BackgroundImage")));
      this.btnEntTransfRotation.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntTransfRotation.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntTransfRotation.Location = new System.Drawing.Point(123, 31);
      this.btnEntTransfRotation.Name = "btnEntTransfRotation";
      this.btnEntTransfRotation.Size = new System.Drawing.Size(32, 32);
      this.btnEntTransfRotation.TabIndex = 2;
      this.btnEntTransfRotation.UseVisualStyleBackColor = false;
      // 
      // btnEntTransfScaling
      // 
      this.btnEntTransfScaling.BackColor = System.Drawing.SystemColors.ControlLight;
      this.btnEntTransfScaling.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntTransfScaling.BackgroundImage")));
      this.btnEntTransfScaling.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntTransfScaling.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntTransfScaling.Location = new System.Drawing.Point(87, 31);
      this.btnEntTransfScaling.Name = "btnEntTransfScaling";
      this.btnEntTransfScaling.Size = new System.Drawing.Size(32, 32);
      this.btnEntTransfScaling.TabIndex = 1;
      this.btnEntTransfScaling.UseVisualStyleBackColor = false;
      // 
      // btnEntTransfObject
      // 
      this.btnEntTransfObject.BackColor = System.Drawing.SystemColors.ControlLight;
      this.btnEntTransfObject.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntTransfObject.BackgroundImage")));
      this.btnEntTransfObject.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntTransfObject.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntTransfObject.Location = new System.Drawing.Point(14, 31);
      this.btnEntTransfObject.Name = "btnEntTransfObject";
      this.btnEntTransfObject.Size = new System.Drawing.Size(32, 32);
      this.btnEntTransfObject.TabIndex = 0;
      this.btnEntTransfObject.UseVisualStyleBackColor = false;
      // 
      // btnEntTransfPosition
      // 
      this.btnEntTransfPosition.BackColor = System.Drawing.SystemColors.ControlLight;
      this.btnEntTransfPosition.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntTransfPosition.BackgroundImage")));
      this.btnEntTransfPosition.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntTransfPosition.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntTransfPosition.Location = new System.Drawing.Point(51, 31);
      this.btnEntTransfPosition.Name = "btnEntTransfPosition";
      this.btnEntTransfPosition.Size = new System.Drawing.Size(32, 32);
      this.btnEntTransfPosition.TabIndex = 0;
      this.btnEntTransfPosition.UseVisualStyleBackColor = false;
      // 
      // panel_Ex1
      // 
      this.panel_Ex1._Checked = false;
      this.panel_Ex1.BACKCOLOR = System.Drawing.Color.Transparent;
      this.panel_Ex1.BORDERCOLOR = System.Drawing.Color.Black;
      this.panel_Ex1.BORDERRADIUS = 5;
      this.panel_Ex1.BORDERWIDTH = 1;
      this.panel_Ex1.Controls.Add(this.btnTerrainCreate);
      this.panel_Ex1.Controls.Add(this.label1);
      this.panel_Ex1.Controls.Add(this.vbtnTerrainSizeY);
      this.panel_Ex1.Controls.Add(this.vbtnTerrainSizeX);
      this.panel_Ex1.Location = new System.Drawing.Point(3, 146);
      this.panel_Ex1.Name = "panel_Ex1";
      this.panel_Ex1.Size = new System.Drawing.Size(167, 104);
      this.panel_Ex1.TabIndex = 1;
      this.panel_Ex1.Text = "Terrain";
      // 
      // btnTerrainCreate
      // 
      this.btnTerrainCreate.BackColor = System.Drawing.Color.Transparent;
      this.btnTerrainCreate.BACKCOLOR = System.Drawing.Color.Transparent;
      this.btnTerrainCreate.BORDERCOLOR = System.Drawing.Color.Black;
      this.btnTerrainCreate.BORDERRADIUS = 5;
      this.btnTerrainCreate.BORDERWIDTH = 1;
      this.btnTerrainCreate.Image = null;
      this.btnTerrainCreate.Location = new System.Drawing.Point(12, 71);
      this.btnTerrainCreate.Name = "btnTerrainCreate";
      this.btnTerrainCreate.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.btnTerrainCreate.SCALEBORD = true;
      this.btnTerrainCreate.Size = new System.Drawing.Size(143, 23);
      this.btnTerrainCreate.TabIndex = 2;
      this.btnTerrainCreate.Text = "Create";
      this.btnTerrainCreate.UseVisualStyleBackColor = false;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(77, 42);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(14, 13);
      this.label1.TabIndex = 1;
      this.label1.Text = "X";
      // 
      // vbtnTerrainSizeY
      // 
      this.vbtnTerrainSizeY.ARROWHEIGHT = 0;
      this.vbtnTerrainSizeY.ARROWTOOLSH = 1;
      this.vbtnTerrainSizeY.ARRWIDTH = 20;
      this.vbtnTerrainSizeY.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerrainSizeY.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerrainSizeY.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerrainSizeY.BORDERRADIUS = 5;
      this.vbtnTerrainSizeY.BORDERWIDTH = 1;
      this.vbtnTerrainSizeY.Image = null;
      this.vbtnTerrainSizeY.Location = new System.Drawing.Point(95, 29);
      this.vbtnTerrainSizeY.MaxValue = 100F;
      this.vbtnTerrainSizeY.MinValue = 1F;
      this.vbtnTerrainSizeY.Name = "vbtnTerrainSizeY";
      this.vbtnTerrainSizeY.Size = new System.Drawing.Size(60, 39);
      this.vbtnTerrainSizeY.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
      this.vbtnTerrainSizeY.TabIndex = 0;
      this.vbtnTerrainSizeY.Text = "awA_Value_Button1";
      this.vbtnTerrainSizeY.UseVisualStyleBackColor = false;
      this.vbtnTerrainSizeY.VALUEV = 1F;
      // 
      // vbtnTerrainSizeX
      // 
      this.vbtnTerrainSizeX.ARROWHEIGHT = 0;
      this.vbtnTerrainSizeX.ARROWTOOLSH = 1;
      this.vbtnTerrainSizeX.ARRWIDTH = 20;
      this.vbtnTerrainSizeX.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerrainSizeX.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerrainSizeX.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerrainSizeX.BORDERRADIUS = 5;
      this.vbtnTerrainSizeX.BORDERWIDTH = 1;
      this.vbtnTerrainSizeX.Image = null;
      this.vbtnTerrainSizeX.Location = new System.Drawing.Point(12, 29);
      this.vbtnTerrainSizeX.MaxValue = 100F;
      this.vbtnTerrainSizeX.MinValue = 1F;
      this.vbtnTerrainSizeX.Name = "vbtnTerrainSizeX";
      this.vbtnTerrainSizeX.Size = new System.Drawing.Size(60, 39);
      this.vbtnTerrainSizeX.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
      this.vbtnTerrainSizeX.TabIndex = 0;
      this.vbtnTerrainSizeX.Text = "awA_Value_Button1";
      this.vbtnTerrainSizeX.UseVisualStyleBackColor = false;
      this.vbtnTerrainSizeX.VALUEV = 1F;
      // 
      // pnlRight
      // 
      this.pnlRight.BackColor = System.Drawing.SystemColors.InactiveBorder;
      this.pnlRight.Dock = System.Windows.Forms.DockStyle.Right;
      this.pnlRight.Location = new System.Drawing.Point(610, 66);
      this.pnlRight.Name = "pnlRight";
      this.pnlRight.Size = new System.Drawing.Size(174, 470);
      this.pnlRight.TabIndex = 3;
      // 
      // pnlRender
      // 
      this.pnlRender.BackColor = System.Drawing.Color.RoyalBlue;
      this.pnlRender.Dock = System.Windows.Forms.DockStyle.Fill;
      this.pnlRender.Location = new System.Drawing.Point(176, 66);
      this.pnlRender.Name = "pnlRender";
      this.pnlRender.Size = new System.Drawing.Size(434, 470);
      this.pnlRender.TabIndex = 4;
      this.pnlRender.SizeChanged += new System.EventHandler(this.pnlRender_SizeChanged);
      // 
      // pnlTop
      // 
      this.pnlTop.BackColor = System.Drawing.SystemColors.ButtonFace;
      this.pnlTop.Controls.Add(this.pnlTopMain);
      this.pnlTop.Dock = System.Windows.Forms.DockStyle.Top;
      this.pnlTop.Location = new System.Drawing.Point(0, 24);
      this.pnlTop.Name = "pnlTop";
      this.pnlTop.Size = new System.Drawing.Size(784, 42);
      this.pnlTop.TabIndex = 5;
      // 
      // pnlTopMain
      // 
      this.pnlTopMain.Controls.Add(this.btnTopWater);
      this.pnlTopMain.Controls.Add(this.btnTopEntity);
      this.pnlTopMain.Controls.Add(this.btnTopTerrain);
      this.pnlTopMain.Location = new System.Drawing.Point(0, 0);
      this.pnlTopMain.Margin = new System.Windows.Forms.Padding(0);
      this.pnlTopMain.Name = "pnlTopMain";
      this.pnlTopMain.Size = new System.Drawing.Size(176, 42);
      this.pnlTopMain.TabIndex = 0;
      // 
      // btnTopWater
      // 
      this.btnTopWater.BackColor = System.Drawing.SystemColors.ControlLight;
      this.btnTopWater.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnTopWater.BackgroundImage")));
      this.btnTopWater.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTopWater.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTopWater.Location = new System.Drawing.Point(82, 2);
      this.btnTopWater.Name = "btnTopWater";
      this.btnTopWater.Size = new System.Drawing.Size(38, 38);
      this.btnTopWater.TabIndex = 2;
      this.btnTopWater.UseVisualStyleBackColor = false;
      // 
      // btnTopEntity
      // 
      this.btnTopEntity.BackColor = System.Drawing.SystemColors.ControlLight;
      this.btnTopEntity.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnTopEntity.BackgroundImage")));
      this.btnTopEntity.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTopEntity.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTopEntity.Location = new System.Drawing.Point(42, 2);
      this.btnTopEntity.Name = "btnTopEntity";
      this.btnTopEntity.Size = new System.Drawing.Size(38, 38);
      this.btnTopEntity.TabIndex = 1;
      this.btnTopEntity.UseVisualStyleBackColor = false;
      // 
      // btnTopTerrain
      // 
      this.btnTopTerrain.BackColor = System.Drawing.SystemColors.ControlLight;
      this.btnTopTerrain.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnTopTerrain.BackgroundImage")));
      this.btnTopTerrain.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTopTerrain.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTopTerrain.Location = new System.Drawing.Point(2, 2);
      this.btnTopTerrain.Name = "btnTopTerrain";
      this.btnTopTerrain.Size = new System.Drawing.Size(38, 38);
      this.btnTopTerrain.TabIndex = 0;
      this.btnTopTerrain.UseVisualStyleBackColor = false;
      // 
      // EditorForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(784, 561);
      this.Controls.Add(this.pnlRender);
      this.Controls.Add(this.pnlRight);
      this.Controls.Add(this.pnlLeft);
      this.Controls.Add(this.pnlTop);
      this.Controls.Add(this.pnlDown);
      this.Controls.Add(this.menuMain);
      this.MainMenuStrip = this.menuMain;
      this.MinimumSize = new System.Drawing.Size(800, 600);
      this.Name = "EditorForm";
      this.ShowIcon = false;
      this.Text = "AwaKinG Engine Editor";
      this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
      this.Activated += new System.EventHandler(this.EditorForm_Activated);
      this.Deactivate += new System.EventHandler(this.EditorForm_Deactivate);
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.redactorForm_FormClosing);
      this.Load += new System.EventHandler(this.EditorForm_Load);
      this.SizeChanged += new System.EventHandler(this.EditorForm_SizeChanged);
      this.menuMain.ResumeLayout(false);
      this.menuMain.PerformLayout();
      this.pnlLeft.ResumeLayout(false);
      this.pnlEntityTransformation.ResumeLayout(false);
      this.panel_Ex1.ResumeLayout(false);
      this.panel_Ex1.PerformLayout();
      this.pnlTop.ResumeLayout(false);
      this.pnlTopMain.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuMain;
        private System.Windows.Forms.ToolStripMenuItem menuFile;
        private System.Windows.Forms.ToolStripMenuItem menuFileExit;
        private System.Windows.Forms.Panel pnlDown;
        private System.Windows.Forms.FlowLayoutPanel pnlLeft;
        private System.Windows.Forms.FlowLayoutPanel pnlRight;
        private System.Windows.Forms.Panel pnlRender;
        private System.Windows.Forms.ToolStripMenuItem menuEdit;
        private System.Windows.Forms.ToolStripMenuItem menuEditCamera;
        private System.Windows.Forms.ToolStripMenuItem menuEditCameraFirstPerson;
        private System.Windows.Forms.ToolStripMenuItem menuEditCameraRedactor;
        private System.Windows.Forms.ToolStripMenuItem menuEditCameraLinked;
        private System.Windows.Forms.ToolStripMenuItem menuFileCreateMap;
        private System.Windows.Forms.ToolStripMenuItem menuFileOpenMap;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem menuFileSaveMap;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.FlowLayoutPanel pnlTop;
        private System.Windows.Forms.Panel pnlTopMain;
        private GUI_elements.Panel_Ex pnlEntityTransformation;
        private System.Windows.Forms.Button btnEntTransfRotation;
        private System.Windows.Forms.Button btnEntTransfScaling;
        private System.Windows.Forms.Button btnEntTransfPosition;
        private System.Windows.Forms.Button btnTopWater;
        private System.Windows.Forms.Button btnTopEntity;
        private System.Windows.Forms.Button btnTopTerrain;
        private System.Windows.Forms.Button btnEntTransfObject;
        private GUI_elements.Panel_Ex panel_Ex1;
        private GUI_elements.AWA_Button btnTerrainCreate;
        private System.Windows.Forms.Label label1;
        private GUI_elements.AWA_Value_Button vbtnTerrainSizeY;
        private GUI_elements.AWA_Value_Button vbtnTerrainSizeX;
    }
}