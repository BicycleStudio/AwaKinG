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
      this.components = new System.ComponentModel.Container();
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
      this.pnlLeftTerrain = new System.Windows.Forms.FlowLayoutPanel();
      this.pnlTerrainMain = new GUI_elements.Panel_Ex();
      this.btnTerrainCreate = new GUI_elements.AWA_Button();
      this.label1 = new System.Windows.Forms.Label();
      this.vbtnTerrainSizeY = new GUI_elements.AWA_Value_Button();
      this.vbtnTerrainSizeX = new GUI_elements.AWA_Value_Button();
      this.pnlTerrainTerraforming = new GUI_elements.Panel_Ex();
      this.pnlTerrainTerraformingDummy = new System.Windows.Forms.Panel();
      this.panel9 = new System.Windows.Forms.Panel();
      this.btnTerraformingSmoothOut = new GUI_elements.AWA_Button();
      this.panel8 = new System.Windows.Forms.Panel();
      this.btnTerraformingSmoothIn = new GUI_elements.AWA_Button();
      this.panel7 = new System.Windows.Forms.Panel();
      this.label7 = new System.Windows.Forms.Label();
      this.vbtnTerraformingSmoothKoeff = new GUI_elements.AWA_Value_Button();
      this.panel6 = new System.Windows.Forms.Panel();
      this.label6 = new System.Windows.Forms.Label();
      this.vbtnTerraformingShiftHeight = new GUI_elements.AWA_Value_Button();
      this.panel5 = new System.Windows.Forms.Panel();
      this.label5 = new System.Windows.Forms.Label();
      this.vbtnTerraformingAltHard = new GUI_elements.AWA_Value_Button();
      this.panel4 = new System.Windows.Forms.Panel();
      this.label4 = new System.Windows.Forms.Label();
      this.vbtnTerraformingHard = new GUI_elements.AWA_Value_Button();
      this.panel3 = new System.Windows.Forms.Panel();
      this.label3 = new System.Windows.Forms.Label();
      this.vbtnTerraformingSizeOut = new GUI_elements.AWA_Value_Button();
      this.panel2 = new System.Windows.Forms.Panel();
      this.label2 = new System.Windows.Forms.Label();
      this.vbtnTerraformingSizeIn = new GUI_elements.AWA_Value_Button();
      this.pnlTerrainTexturing = new GUI_elements.Panel_Ex();
      this.pnlTerrainTexturingDummy = new System.Windows.Forms.Panel();
      this.panel15 = new System.Windows.Forms.Panel();
      this.label11 = new System.Windows.Forms.Label();
      this.vbtnTexturingHard = new GUI_elements.AWA_Value_Button();
      this.panel17 = new System.Windows.Forms.Panel();
      this.label13 = new System.Windows.Forms.Label();
      this.vbtnTexturingSize = new GUI_elements.AWA_Value_Button();
      this.panel12 = new System.Windows.Forms.Panel();
      this.btnTexturingCirc = new System.Windows.Forms.Button();
      this.btnTexturingCustom = new System.Windows.Forms.Button();
      this.btnTexturingQuad = new System.Windows.Forms.Button();
      this.btnTexturingRhomb = new System.Windows.Forms.Button();
      this.pnlTerrainTexturePacks = new GUI_elements.Panel_Ex();
      this.btnTerrainTexturePacksDel = new GUI_elements.AWA_Button();
      this.btnTerrainTexturePacksAdd = new GUI_elements.AWA_Button();
      this.tbxTerrainTexturePacks = new System.Windows.Forms.TextBox();
      this.lbxTerrainTexturePacks = new System.Windows.Forms.ListBox();
      this.pnlRight = new System.Windows.Forms.FlowLayoutPanel();
      this.pnlRender = new System.Windows.Forms.Panel();
      this.pnlTop = new System.Windows.Forms.FlowLayoutPanel();
      this.pnlTopMain = new System.Windows.Forms.Panel();
      this.btnTopWater = new System.Windows.Forms.Button();
      this.btnTopEntity = new System.Windows.Forms.Button();
      this.btnTopTerrain = new System.Windows.Forms.Button();
      this.pnlLeftEntity = new System.Windows.Forms.FlowLayoutPanel();
      this.pnlEntityTransformation = new GUI_elements.Panel_Ex();
      this.btnEntityStickToTerrain = new GUI_elements.AWA_Button();
      this.btnEntityRot = new System.Windows.Forms.Button();
      this.btnEntityScl = new System.Windows.Forms.Button();
      this.btnEntityObject = new System.Windows.Forms.Button();
      this.btnEntityPos = new System.Windows.Forms.Button();
      this.pnlEntityPacks = new GUI_elements.Panel_Ex();
      this.awA_Button2 = new GUI_elements.AWA_Button();
      this.textBox1 = new System.Windows.Forms.TextBox();
      this.awA_Button1 = new GUI_elements.AWA_Button();
      this.listBox1 = new System.Windows.Forms.ListBox();
      this.pnlLeftWater = new System.Windows.Forms.FlowLayoutPanel();
      this.cmsEntity = new System.Windows.Forms.ContextMenuStrip(this.components);
      this.transformationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.firstPersonFreeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.menuMain.SuspendLayout();
      this.pnlLeftTerrain.SuspendLayout();
      this.pnlTerrainMain.SuspendLayout();
      this.pnlTerrainTerraforming.SuspendLayout();
      this.pnlTerrainTerraformingDummy.SuspendLayout();
      this.panel9.SuspendLayout();
      this.panel8.SuspendLayout();
      this.panel7.SuspendLayout();
      this.panel6.SuspendLayout();
      this.panel5.SuspendLayout();
      this.panel4.SuspendLayout();
      this.panel3.SuspendLayout();
      this.panel2.SuspendLayout();
      this.pnlTerrainTexturing.SuspendLayout();
      this.pnlTerrainTexturingDummy.SuspendLayout();
      this.panel15.SuspendLayout();
      this.panel17.SuspendLayout();
      this.panel12.SuspendLayout();
      this.pnlTerrainTexturePacks.SuspendLayout();
      this.pnlTop.SuspendLayout();
      this.pnlTopMain.SuspendLayout();
      this.pnlLeftEntity.SuspendLayout();
      this.pnlEntityTransformation.SuspendLayout();
      this.pnlEntityPacks.SuspendLayout();
      this.cmsEntity.SuspendLayout();
      this.SuspendLayout();
      // 
      // menuMain
      // 
      this.menuMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFile,
            this.menuEdit});
      this.menuMain.Location = new System.Drawing.Point(0, 0);
      this.menuMain.Name = "menuMain";
      this.menuMain.Size = new System.Drawing.Size(1020, 24);
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
      this.menuFileCreateMap.Size = new System.Drawing.Size(139, 22);
      this.menuFileCreateMap.Text = "New map";
      this.menuFileCreateMap.Click += new System.EventHandler(this.menuFileCreateMap_Click);
      // 
      // menuFileOpenMap
      // 
      this.menuFileOpenMap.Name = "menuFileOpenMap";
      this.menuFileOpenMap.Size = new System.Drawing.Size(139, 22);
      this.menuFileOpenMap.Text = "Open map...";
      this.menuFileOpenMap.Click += new System.EventHandler(this.menuFileOpenMap_Click);
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size(136, 6);
      // 
      // menuFileSaveMap
      // 
      this.menuFileSaveMap.Name = "menuFileSaveMap";
      this.menuFileSaveMap.Size = new System.Drawing.Size(139, 22);
      this.menuFileSaveMap.Text = "Save map...";
      this.menuFileSaveMap.Click += new System.EventHandler(this.menuFileSaveMap_Click);
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size(136, 6);
      // 
      // menuFileExit
      // 
      this.menuFileExit.Name = "menuFileExit";
      this.menuFileExit.Size = new System.Drawing.Size(139, 22);
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
            this.menuEditCameraLinked,
            this.firstPersonFreeToolStripMenuItem});
      this.menuEditCamera.Name = "menuEditCamera";
      this.menuEditCamera.Size = new System.Drawing.Size(152, 22);
      this.menuEditCamera.Text = "Camera";
      // 
      // menuEditCameraFirstPerson
      // 
      this.menuEditCameraFirstPerson.Checked = true;
      this.menuEditCameraFirstPerson.CheckState = System.Windows.Forms.CheckState.Checked;
      this.menuEditCameraFirstPerson.Name = "menuEditCameraFirstPerson";
      this.menuEditCameraFirstPerson.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
      this.menuEditCameraFirstPerson.Size = new System.Drawing.Size(200, 22);
      this.menuEditCameraFirstPerson.Tag = "1";
      this.menuEditCameraFirstPerson.Text = "First person";
      this.menuEditCameraFirstPerson.Click += new System.EventHandler(this.CameraType_Click);
      // 
      // menuEditCameraRedactor
      // 
      this.menuEditCameraRedactor.Name = "menuEditCameraRedactor";
      this.menuEditCameraRedactor.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
      this.menuEditCameraRedactor.Size = new System.Drawing.Size(200, 22);
      this.menuEditCameraRedactor.Tag = "2";
      this.menuEditCameraRedactor.Text = "Redactor";
      this.menuEditCameraRedactor.Click += new System.EventHandler(this.CameraType_Click);
      // 
      // menuEditCameraLinked
      // 
      this.menuEditCameraLinked.Name = "menuEditCameraLinked";
      this.menuEditCameraLinked.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.L)));
      this.menuEditCameraLinked.Size = new System.Drawing.Size(200, 22);
      this.menuEditCameraLinked.Tag = "0";
      this.menuEditCameraLinked.Text = "Linked";
      this.menuEditCameraLinked.Click += new System.EventHandler(this.CameraType_Click);
      // 
      // pnlDown
      // 
      this.pnlDown.BackColor = System.Drawing.SystemColors.ControlLight;
      this.pnlDown.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.pnlDown.Location = new System.Drawing.Point(0, 716);
      this.pnlDown.Name = "pnlDown";
      this.pnlDown.Size = new System.Drawing.Size(1020, 25);
      this.pnlDown.TabIndex = 1;
      // 
      // pnlLeftTerrain
      // 
      this.pnlLeftTerrain.AutoScroll = true;
      this.pnlLeftTerrain.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
      this.pnlLeftTerrain.Controls.Add(this.pnlTerrainMain);
      this.pnlLeftTerrain.Controls.Add(this.pnlTerrainTerraforming);
      this.pnlLeftTerrain.Controls.Add(this.pnlTerrainTexturing);
      this.pnlLeftTerrain.Controls.Add(this.pnlTerrainTexturePacks);
      this.pnlLeftTerrain.Dock = System.Windows.Forms.DockStyle.Left;
      this.pnlLeftTerrain.Location = new System.Drawing.Point(0, 66);
      this.pnlLeftTerrain.Name = "pnlLeftTerrain";
      this.pnlLeftTerrain.Size = new System.Drawing.Size(175, 650);
      this.pnlLeftTerrain.TabIndex = 2;
      this.pnlLeftTerrain.Visible = false;
      // 
      // pnlTerrainMain
      // 
      this.pnlTerrainMain._Checked = false;
      this.pnlTerrainMain.BACKCOLOR = System.Drawing.Color.Transparent;
      this.pnlTerrainMain.BORDERCOLOR = System.Drawing.Color.Black;
      this.pnlTerrainMain.BORDERRADIUS = 5;
      this.pnlTerrainMain.BORDERWIDTH = 1;
      this.pnlTerrainMain.Controls.Add(this.btnTerrainCreate);
      this.pnlTerrainMain.Controls.Add(this.label1);
      this.pnlTerrainMain.Controls.Add(this.vbtnTerrainSizeY);
      this.pnlTerrainMain.Controls.Add(this.vbtnTerrainSizeX);
      this.pnlTerrainMain.Location = new System.Drawing.Point(3, 2);
      this.pnlTerrainMain.Margin = new System.Windows.Forms.Padding(3, 2, 3, 0);
      this.pnlTerrainMain.Name = "pnlTerrainMain";
      this.pnlTerrainMain.Size = new System.Drawing.Size(167, 104);
      this.pnlTerrainMain.TabIndex = 1;
      this.pnlTerrainMain.Text = "Terrain";
      // 
      // btnTerrainCreate
      // 
      this.btnTerrainCreate.BackColor = System.Drawing.Color.Transparent;
      this.btnTerrainCreate.BACKCOLOR = System.Drawing.Color.Transparent;
      this.btnTerrainCreate.BORDERCOLOR = System.Drawing.Color.Black;
      this.btnTerrainCreate.BORDERRADIUS = 5;
      this.btnTerrainCreate.BORDERWIDTH = 1;
      this.btnTerrainCreate.Image = null;
      this.btnTerrainCreate.Location = new System.Drawing.Point(12, 74);
      this.btnTerrainCreate.Name = "btnTerrainCreate";
      this.btnTerrainCreate.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.btnTerrainCreate.SCALEBORD = true;
      this.btnTerrainCreate.Size = new System.Drawing.Size(143, 23);
      this.btnTerrainCreate.TabIndex = 2;
      this.btnTerrainCreate.Text = "Create";
      this.btnTerrainCreate.UseVisualStyleBackColor = false;
      this.btnTerrainCreate.Click += new System.EventHandler(this.btnTerrainCreate_Click);
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
      this.vbtnTerrainSizeY.MaxValue = 32F;
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
      this.vbtnTerrainSizeX.MaxValue = 32F;
      this.vbtnTerrainSizeX.MinValue = 1F;
      this.vbtnTerrainSizeX.Name = "vbtnTerrainSizeX";
      this.vbtnTerrainSizeX.Size = new System.Drawing.Size(60, 39);
      this.vbtnTerrainSizeX.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
      this.vbtnTerrainSizeX.TabIndex = 0;
      this.vbtnTerrainSizeX.Text = "awA_Value_Button1";
      this.vbtnTerrainSizeX.UseVisualStyleBackColor = false;
      this.vbtnTerrainSizeX.VALUEV = 1F;
      // 
      // pnlTerrainTerraforming
      // 
      this.pnlTerrainTerraforming._Checked = false;
      this.pnlTerrainTerraforming.BACKCOLOR = System.Drawing.Color.Transparent;
      this.pnlTerrainTerraforming.BORDERCOLOR = System.Drawing.Color.Black;
      this.pnlTerrainTerraforming.BORDERRADIUS = 5;
      this.pnlTerrainTerraforming.BORDERWIDTH = 1;
      this.pnlTerrainTerraforming.Controls.Add(this.pnlTerrainTerraformingDummy);
      this.pnlTerrainTerraforming.Location = new System.Drawing.Point(3, 108);
      this.pnlTerrainTerraforming.Margin = new System.Windows.Forms.Padding(3, 2, 3, 0);
      this.pnlTerrainTerraforming.Name = "pnlTerrainTerraforming";
      this.pnlTerrainTerraforming.Size = new System.Drawing.Size(167, 201);
      this.pnlTerrainTerraforming.TabIndex = 2;
      this.pnlTerrainTerraforming.Text = "Terraforming";
      this.pnlTerrainTerraforming.Visible = false;
      // 
      // pnlTerrainTerraformingDummy
      // 
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel9);
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel8);
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel7);
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel6);
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel5);
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel4);
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel3);
      this.pnlTerrainTerraformingDummy.Controls.Add(this.panel2);
      this.pnlTerrainTerraformingDummy.Location = new System.Drawing.Point(3, 24);
      this.pnlTerrainTerraformingDummy.Name = "pnlTerrainTerraformingDummy";
      this.pnlTerrainTerraformingDummy.Size = new System.Drawing.Size(161, 171);
      this.pnlTerrainTerraformingDummy.TabIndex = 0;
      // 
      // panel9
      // 
      this.panel9.Controls.Add(this.btnTerraformingSmoothOut);
      this.panel9.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel9.Location = new System.Drawing.Point(0, 148);
      this.panel9.Name = "panel9";
      this.panel9.Size = new System.Drawing.Size(161, 22);
      this.panel9.TabIndex = 7;
      // 
      // btnTerraformingSmoothOut
      // 
      this.btnTerraformingSmoothOut.BackColor = System.Drawing.Color.Transparent;
      this.btnTerraformingSmoothOut.BACKCOLOR = System.Drawing.Color.Transparent;
      this.btnTerraformingSmoothOut.BORDERCOLOR = System.Drawing.Color.Black;
      this.btnTerraformingSmoothOut.BORDERRADIUS = 5;
      this.btnTerraformingSmoothOut.BORDERWIDTH = 0;
      this.btnTerraformingSmoothOut.CHECKABLE = true;
      this.btnTerraformingSmoothOut.Image = null;
      this.btnTerraformingSmoothOut.Location = new System.Drawing.Point(10, 1);
      this.btnTerraformingSmoothOut.Name = "btnTerraformingSmoothOut";
      this.btnTerraformingSmoothOut.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.btnTerraformingSmoothOut.SCALEBORD = true;
      this.btnTerraformingSmoothOut.Size = new System.Drawing.Size(141, 20);
      this.btnTerraformingSmoothOut.TabIndex = 4;
      this.btnTerraformingSmoothOut.Text = "Smooth out";
      this.btnTerraformingSmoothOut.UseVisualStyleBackColor = false;
      // 
      // panel8
      // 
      this.panel8.Controls.Add(this.btnTerraformingSmoothIn);
      this.panel8.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel8.Location = new System.Drawing.Point(0, 126);
      this.panel8.Name = "panel8";
      this.panel8.Size = new System.Drawing.Size(161, 22);
      this.panel8.TabIndex = 6;
      // 
      // btnTerraformingSmoothIn
      // 
      this.btnTerraformingSmoothIn.BackColor = System.Drawing.Color.Transparent;
      this.btnTerraformingSmoothIn.BACKCOLOR = System.Drawing.Color.Transparent;
      this.btnTerraformingSmoothIn.BORDERCOLOR = System.Drawing.Color.Black;
      this.btnTerraformingSmoothIn.BORDERRADIUS = 5;
      this.btnTerraformingSmoothIn.BORDERWIDTH = 0;
      this.btnTerraformingSmoothIn.CHECKABLE = true;
      this.btnTerraformingSmoothIn.Image = null;
      this.btnTerraformingSmoothIn.Location = new System.Drawing.Point(10, 1);
      this.btnTerraformingSmoothIn.Name = "btnTerraformingSmoothIn";
      this.btnTerraformingSmoothIn.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.btnTerraformingSmoothIn.SCALEBORD = true;
      this.btnTerraformingSmoothIn.Size = new System.Drawing.Size(141, 20);
      this.btnTerraformingSmoothIn.TabIndex = 4;
      this.btnTerraformingSmoothIn.Text = "Smooth in";
      this.btnTerraformingSmoothIn.UseVisualStyleBackColor = false;
      // 
      // panel7
      // 
      this.panel7.Controls.Add(this.label7);
      this.panel7.Controls.Add(this.vbtnTerraformingSmoothKoeff);
      this.panel7.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel7.Location = new System.Drawing.Point(0, 105);
      this.panel7.Name = "panel7";
      this.panel7.Size = new System.Drawing.Size(161, 21);
      this.panel7.TabIndex = 5;
      // 
      // label7
      // 
      this.label7.AutoSize = true;
      this.label7.Location = new System.Drawing.Point(3, 4);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(73, 13);
      this.label7.TabIndex = 1;
      this.label7.Text = "Smooth koeff:";
      // 
      // vbtnTerraformingSmoothKoeff
      // 
      this.vbtnTerraformingSmoothKoeff.ARROWHEIGHT = 1;
      this.vbtnTerraformingSmoothKoeff.ARROWTOOLSH = 1;
      this.vbtnTerraformingSmoothKoeff.ARRWIDTH = 20;
      this.vbtnTerraformingSmoothKoeff.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerraformingSmoothKoeff.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerraformingSmoothKoeff.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerraformingSmoothKoeff.BORDERRADIUS = 5;
      this.vbtnTerraformingSmoothKoeff.BORDERWIDTH = 0;
      this.vbtnTerraformingSmoothKoeff.Image = null;
      this.vbtnTerraformingSmoothKoeff.Location = new System.Drawing.Point(83, 1);
      this.vbtnTerraformingSmoothKoeff.MaxValue = 1F;
      this.vbtnTerraformingSmoothKoeff.MinValue = 0F;
      this.vbtnTerraformingSmoothKoeff.Name = "vbtnTerraformingSmoothKoeff";
      this.vbtnTerraformingSmoothKoeff.Size = new System.Drawing.Size(75, 19);
      this.vbtnTerraformingSmoothKoeff.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Very_Slow;
      this.vbtnTerraformingSmoothKoeff.TabIndex = 0;
      this.vbtnTerraformingSmoothKoeff.Text = "awA_Value_Button6";
      this.vbtnTerraformingSmoothKoeff.UseVisualStyleBackColor = false;
      this.vbtnTerraformingSmoothKoeff.VALUEV = 0F;
      // 
      // panel6
      // 
      this.panel6.Controls.Add(this.label6);
      this.panel6.Controls.Add(this.vbtnTerraformingShiftHeight);
      this.panel6.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel6.Location = new System.Drawing.Point(0, 84);
      this.panel6.Name = "panel6";
      this.panel6.Size = new System.Drawing.Size(161, 21);
      this.panel6.TabIndex = 4;
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(13, 4);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(63, 13);
      this.label6.TabIndex = 1;
      this.label6.Text = "Shift-height:";
      // 
      // vbtnTerraformingShiftHeight
      // 
      this.vbtnTerraformingShiftHeight.ARROWHEIGHT = 1;
      this.vbtnTerraformingShiftHeight.ARROWTOOLSH = 1;
      this.vbtnTerraformingShiftHeight.ARRWIDTH = 20;
      this.vbtnTerraformingShiftHeight.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerraformingShiftHeight.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerraformingShiftHeight.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerraformingShiftHeight.BORDERRADIUS = 5;
      this.vbtnTerraformingShiftHeight.BORDERWIDTH = 0;
      this.vbtnTerraformingShiftHeight.Image = null;
      this.vbtnTerraformingShiftHeight.Location = new System.Drawing.Point(83, 1);
      this.vbtnTerraformingShiftHeight.MaxValue = 1000F;
      this.vbtnTerraformingShiftHeight.MinValue = -1000F;
      this.vbtnTerraformingShiftHeight.Name = "vbtnTerraformingShiftHeight";
      this.vbtnTerraformingShiftHeight.Size = new System.Drawing.Size(75, 19);
      this.vbtnTerraformingShiftHeight.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
      this.vbtnTerraformingShiftHeight.TabIndex = 0;
      this.vbtnTerraformingShiftHeight.Text = "awA_Value_Button5";
      this.vbtnTerraformingShiftHeight.UseVisualStyleBackColor = false;
      this.vbtnTerraformingShiftHeight.VALUEV = 0F;
      // 
      // panel5
      // 
      this.panel5.Controls.Add(this.label5);
      this.panel5.Controls.Add(this.vbtnTerraformingAltHard);
      this.panel5.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel5.Location = new System.Drawing.Point(0, 63);
      this.panel5.Name = "panel5";
      this.panel5.Size = new System.Drawing.Size(161, 21);
      this.panel5.TabIndex = 3;
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(30, 4);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(46, 13);
      this.label5.TabIndex = 1;
      this.label5.Text = "Alt-hard:";
      // 
      // vbtnTerraformingAltHard
      // 
      this.vbtnTerraformingAltHard.ARROWHEIGHT = 1;
      this.vbtnTerraformingAltHard.ARROWTOOLSH = 1;
      this.vbtnTerraformingAltHard.ARRWIDTH = 20;
      this.vbtnTerraformingAltHard.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerraformingAltHard.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerraformingAltHard.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerraformingAltHard.BORDERRADIUS = 5;
      this.vbtnTerraformingAltHard.BORDERWIDTH = 0;
      this.vbtnTerraformingAltHard.Image = null;
      this.vbtnTerraformingAltHard.Location = new System.Drawing.Point(83, 1);
      this.vbtnTerraformingAltHard.MaxValue = 1000F;
      this.vbtnTerraformingAltHard.MinValue = -1000F;
      this.vbtnTerraformingAltHard.Name = "vbtnTerraformingAltHard";
      this.vbtnTerraformingAltHard.Size = new System.Drawing.Size(75, 19);
      this.vbtnTerraformingAltHard.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
      this.vbtnTerraformingAltHard.TabIndex = 0;
      this.vbtnTerraformingAltHard.Text = "awA_Value_Button4";
      this.vbtnTerraformingAltHard.UseVisualStyleBackColor = false;
      this.vbtnTerraformingAltHard.VALUEV = 0F;
      // 
      // panel4
      // 
      this.panel4.Controls.Add(this.label4);
      this.panel4.Controls.Add(this.vbtnTerraformingHard);
      this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel4.Location = new System.Drawing.Point(0, 42);
      this.panel4.Name = "panel4";
      this.panel4.Size = new System.Drawing.Size(161, 21);
      this.panel4.TabIndex = 2;
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(43, 4);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(33, 13);
      this.label4.TabIndex = 1;
      this.label4.Text = "Hard:";
      // 
      // vbtnTerraformingHard
      // 
      this.vbtnTerraformingHard.ARROWHEIGHT = 1;
      this.vbtnTerraformingHard.ARROWTOOLSH = 1;
      this.vbtnTerraformingHard.ARRWIDTH = 20;
      this.vbtnTerraformingHard.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerraformingHard.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerraformingHard.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerraformingHard.BORDERRADIUS = 5;
      this.vbtnTerraformingHard.BORDERWIDTH = 0;
      this.vbtnTerraformingHard.Image = null;
      this.vbtnTerraformingHard.Location = new System.Drawing.Point(83, 1);
      this.vbtnTerraformingHard.MaxValue = 1000F;
      this.vbtnTerraformingHard.MinValue = -1000F;
      this.vbtnTerraformingHard.Name = "vbtnTerraformingHard";
      this.vbtnTerraformingHard.Size = new System.Drawing.Size(75, 19);
      this.vbtnTerraformingHard.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
      this.vbtnTerraformingHard.TabIndex = 0;
      this.vbtnTerraformingHard.Text = "awA_Value_Button3";
      this.vbtnTerraformingHard.UseVisualStyleBackColor = false;
      this.vbtnTerraformingHard.VALUEV = 0F;
      // 
      // panel3
      // 
      this.panel3.Controls.Add(this.label3);
      this.panel3.Controls.Add(this.vbtnTerraformingSizeOut);
      this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel3.Location = new System.Drawing.Point(0, 21);
      this.panel3.Name = "panel3";
      this.panel3.Size = new System.Drawing.Size(161, 21);
      this.panel3.TabIndex = 1;
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(28, 4);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(48, 13);
      this.label3.TabIndex = 1;
      this.label3.Text = "Size out:";
      // 
      // vbtnTerraformingSizeOut
      // 
      this.vbtnTerraformingSizeOut.ARROWHEIGHT = 1;
      this.vbtnTerraformingSizeOut.ARROWTOOLSH = 1;
      this.vbtnTerraformingSizeOut.ARRWIDTH = 20;
      this.vbtnTerraformingSizeOut.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerraformingSizeOut.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerraformingSizeOut.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerraformingSizeOut.BORDERRADIUS = 5;
      this.vbtnTerraformingSizeOut.BORDERWIDTH = 0;
      this.vbtnTerraformingSizeOut.Image = null;
      this.vbtnTerraformingSizeOut.Location = new System.Drawing.Point(83, 1);
      this.vbtnTerraformingSizeOut.MaxValue = 10F;
      this.vbtnTerraformingSizeOut.MinValue = 1F;
      this.vbtnTerraformingSizeOut.Name = "vbtnTerraformingSizeOut";
      this.vbtnTerraformingSizeOut.Size = new System.Drawing.Size(75, 19);
      this.vbtnTerraformingSizeOut.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
      this.vbtnTerraformingSizeOut.TabIndex = 0;
      this.vbtnTerraformingSizeOut.Text = "awA_Value_Button2";
      this.vbtnTerraformingSizeOut.UseVisualStyleBackColor = false;
      this.vbtnTerraformingSizeOut.VALUEV = 1F;
      // 
      // panel2
      // 
      this.panel2.Controls.Add(this.label2);
      this.panel2.Controls.Add(this.vbtnTerraformingSizeIn);
      this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel2.Location = new System.Drawing.Point(0, 0);
      this.panel2.Name = "panel2";
      this.panel2.Size = new System.Drawing.Size(161, 21);
      this.panel2.TabIndex = 0;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(35, 4);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(41, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Size in:";
      // 
      // vbtnTerraformingSizeIn
      // 
      this.vbtnTerraformingSizeIn.ARROWHEIGHT = 1;
      this.vbtnTerraformingSizeIn.ARROWTOOLSH = 1;
      this.vbtnTerraformingSizeIn.ARRWIDTH = 20;
      this.vbtnTerraformingSizeIn.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTerraformingSizeIn.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTerraformingSizeIn.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTerraformingSizeIn.BORDERRADIUS = 5;
      this.vbtnTerraformingSizeIn.BORDERWIDTH = 0;
      this.vbtnTerraformingSizeIn.Image = null;
      this.vbtnTerraformingSizeIn.Location = new System.Drawing.Point(83, 1);
      this.vbtnTerraformingSizeIn.MaxValue = 10F;
      this.vbtnTerraformingSizeIn.MinValue = 1F;
      this.vbtnTerraformingSizeIn.Name = "vbtnTerraformingSizeIn";
      this.vbtnTerraformingSizeIn.Size = new System.Drawing.Size(75, 19);
      this.vbtnTerraformingSizeIn.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
      this.vbtnTerraformingSizeIn.TabIndex = 0;
      this.vbtnTerraformingSizeIn.Text = "awA_Value_Button1";
      this.vbtnTerraformingSizeIn.UseVisualStyleBackColor = false;
      this.vbtnTerraformingSizeIn.VALUEV = 1F;
      // 
      // pnlTerrainTexturing
      // 
      this.pnlTerrainTexturing._Checked = false;
      this.pnlTerrainTexturing.BACKCOLOR = System.Drawing.Color.Transparent;
      this.pnlTerrainTexturing.BORDERCOLOR = System.Drawing.Color.Black;
      this.pnlTerrainTexturing.BORDERRADIUS = 5;
      this.pnlTerrainTexturing.BORDERWIDTH = 1;
      this.pnlTerrainTexturing.Controls.Add(this.pnlTerrainTexturingDummy);
      this.pnlTerrainTexturing.Location = new System.Drawing.Point(3, 311);
      this.pnlTerrainTexturing.Margin = new System.Windows.Forms.Padding(3, 2, 3, 0);
      this.pnlTerrainTexturing.Name = "pnlTerrainTexturing";
      this.pnlTerrainTexturing.Size = new System.Drawing.Size(167, 110);
      this.pnlTerrainTexturing.TabIndex = 3;
      this.pnlTerrainTexturing.Text = "Texturing";
      this.pnlTerrainTexturing.Visible = false;
      // 
      // pnlTerrainTexturingDummy
      // 
      this.pnlTerrainTexturingDummy.Controls.Add(this.panel15);
      this.pnlTerrainTexturingDummy.Controls.Add(this.panel17);
      this.pnlTerrainTexturingDummy.Controls.Add(this.panel12);
      this.pnlTerrainTexturingDummy.Location = new System.Drawing.Point(3, 24);
      this.pnlTerrainTexturingDummy.Name = "pnlTerrainTexturingDummy";
      this.pnlTerrainTexturingDummy.Size = new System.Drawing.Size(161, 82);
      this.pnlTerrainTexturingDummy.TabIndex = 0;
      // 
      // panel15
      // 
      this.panel15.Controls.Add(this.label11);
      this.panel15.Controls.Add(this.vbtnTexturingHard);
      this.panel15.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel15.Location = new System.Drawing.Point(0, 60);
      this.panel15.Name = "panel15";
      this.panel15.Size = new System.Drawing.Size(161, 21);
      this.panel15.TabIndex = 2;
      // 
      // label11
      // 
      this.label11.AutoSize = true;
      this.label11.Location = new System.Drawing.Point(24, 4);
      this.label11.Name = "label11";
      this.label11.Size = new System.Drawing.Size(33, 13);
      this.label11.TabIndex = 1;
      this.label11.Text = "Hard:";
      // 
      // vbtnTexturingHard
      // 
      this.vbtnTexturingHard.ARROWHEIGHT = 1;
      this.vbtnTexturingHard.ARROWTOOLSH = 1;
      this.vbtnTexturingHard.ARRWIDTH = 20;
      this.vbtnTexturingHard.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTexturingHard.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTexturingHard.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTexturingHard.BORDERRADIUS = 5;
      this.vbtnTexturingHard.BORDERWIDTH = 0;
      this.vbtnTexturingHard.Image = null;
      this.vbtnTexturingHard.Location = new System.Drawing.Point(64, 1);
      this.vbtnTexturingHard.MaxValue = 1000F;
      this.vbtnTexturingHard.MinValue = -1000F;
      this.vbtnTexturingHard.Name = "vbtnTexturingHard";
      this.vbtnTexturingHard.Size = new System.Drawing.Size(75, 19);
      this.vbtnTexturingHard.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Slow;
      this.vbtnTexturingHard.TabIndex = 0;
      this.vbtnTexturingHard.Text = "awA_Value_Button3";
      this.vbtnTexturingHard.UseVisualStyleBackColor = false;
      this.vbtnTexturingHard.VALUEV = 0F;
      // 
      // panel17
      // 
      this.panel17.Controls.Add(this.label13);
      this.panel17.Controls.Add(this.vbtnTexturingSize);
      this.panel17.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel17.Location = new System.Drawing.Point(0, 39);
      this.panel17.Name = "panel17";
      this.panel17.Size = new System.Drawing.Size(161, 21);
      this.panel17.TabIndex = 0;
      // 
      // label13
      // 
      this.label13.AutoSize = true;
      this.label13.Location = new System.Drawing.Point(25, 4);
      this.label13.Name = "label13";
      this.label13.Size = new System.Drawing.Size(30, 13);
      this.label13.TabIndex = 1;
      this.label13.Text = "Size:";
      // 
      // vbtnTexturingSize
      // 
      this.vbtnTexturingSize.ARROWHEIGHT = 1;
      this.vbtnTexturingSize.ARROWTOOLSH = 1;
      this.vbtnTexturingSize.ARRWIDTH = 20;
      this.vbtnTexturingSize.BackColor = System.Drawing.Color.Transparent;
      this.vbtnTexturingSize.BACKCOLOR = System.Drawing.Color.Transparent;
      this.vbtnTexturingSize.BORDERCOLOR = System.Drawing.Color.Black;
      this.vbtnTexturingSize.BORDERRADIUS = 5;
      this.vbtnTexturingSize.BORDERWIDTH = 0;
      this.vbtnTexturingSize.Image = null;
      this.vbtnTexturingSize.Location = new System.Drawing.Point(64, 1);
      this.vbtnTexturingSize.MaxValue = 10F;
      this.vbtnTexturingSize.MinValue = 1F;
      this.vbtnTexturingSize.Name = "vbtnTexturingSize";
      this.vbtnTexturingSize.Size = new System.Drawing.Size(75, 19);
      this.vbtnTexturingSize.SVC = GUI_elements.AWA_Value_Button.SpeedOfValueChanging.Normal;
      this.vbtnTexturingSize.TabIndex = 0;
      this.vbtnTexturingSize.Text = "awA_Value_Button1";
      this.vbtnTexturingSize.UseVisualStyleBackColor = false;
      this.vbtnTexturingSize.VALUEV = 1F;
      // 
      // panel12
      // 
      this.panel12.Controls.Add(this.btnTexturingCirc);
      this.panel12.Controls.Add(this.btnTexturingCustom);
      this.panel12.Controls.Add(this.btnTexturingQuad);
      this.panel12.Controls.Add(this.btnTexturingRhomb);
      this.panel12.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel12.Location = new System.Drawing.Point(0, 0);
      this.panel12.Name = "panel12";
      this.panel12.Size = new System.Drawing.Size(161, 39);
      this.panel12.TabIndex = 5;
      // 
      // btnTexturingCirc
      // 
      this.btnTexturingCirc.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnTexturingCirc.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTexturingCirc.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTexturingCirc.Location = new System.Drawing.Point(46, 3);
      this.btnTexturingCirc.Name = "btnTexturingCirc";
      this.btnTexturingCirc.Size = new System.Drawing.Size(32, 32);
      this.btnTexturingCirc.TabIndex = 0;
      this.btnTexturingCirc.Tag = "1";
      this.btnTexturingCirc.Text = "C";
      this.btnTexturingCirc.UseVisualStyleBackColor = false;
      this.btnTexturingCirc.Click += new System.EventHandler(this.btnTerrainTexturingBtns_Click);
      // 
      // btnTexturingCustom
      // 
      this.btnTexturingCustom.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnTexturingCustom.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTexturingCustom.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTexturingCustom.Location = new System.Drawing.Point(118, 3);
      this.btnTexturingCustom.Name = "btnTexturingCustom";
      this.btnTexturingCustom.Size = new System.Drawing.Size(32, 32);
      this.btnTexturingCustom.TabIndex = 2;
      this.btnTexturingCustom.Tag = "3";
      this.btnTexturingCustom.Text = "...";
      this.btnTexturingCustom.UseVisualStyleBackColor = false;
      this.btnTexturingCustom.Click += new System.EventHandler(this.btnTerrainTexturingBtns_Click);
      // 
      // btnTexturingQuad
      // 
      this.btnTexturingQuad.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnTexturingQuad.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTexturingQuad.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTexturingQuad.Location = new System.Drawing.Point(9, 3);
      this.btnTexturingQuad.Name = "btnTexturingQuad";
      this.btnTexturingQuad.Size = new System.Drawing.Size(32, 32);
      this.btnTexturingQuad.TabIndex = 0;
      this.btnTexturingQuad.Tag = "0";
      this.btnTexturingQuad.Text = "Q";
      this.btnTexturingQuad.UseVisualStyleBackColor = false;
      this.btnTexturingQuad.Click += new System.EventHandler(this.btnTerrainTexturingBtns_Click);
      // 
      // btnTexturingRhomb
      // 
      this.btnTexturingRhomb.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnTexturingRhomb.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTexturingRhomb.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTexturingRhomb.Location = new System.Drawing.Point(82, 3);
      this.btnTexturingRhomb.Name = "btnTexturingRhomb";
      this.btnTexturingRhomb.Size = new System.Drawing.Size(32, 32);
      this.btnTexturingRhomb.TabIndex = 1;
      this.btnTexturingRhomb.Tag = "2";
      this.btnTexturingRhomb.Text = "R";
      this.btnTexturingRhomb.UseVisualStyleBackColor = false;
      this.btnTexturingRhomb.Click += new System.EventHandler(this.btnTerrainTexturingBtns_Click);
      // 
      // pnlTerrainTexturePacks
      // 
      this.pnlTerrainTexturePacks._Checked = false;
      this.pnlTerrainTexturePacks.BACKCOLOR = System.Drawing.Color.Transparent;
      this.pnlTerrainTexturePacks.BORDERCOLOR = System.Drawing.Color.Black;
      this.pnlTerrainTexturePacks.BORDERRADIUS = 5;
      this.pnlTerrainTexturePacks.BORDERWIDTH = 1;
      this.pnlTerrainTexturePacks.Controls.Add(this.btnTerrainTexturePacksDel);
      this.pnlTerrainTexturePacks.Controls.Add(this.btnTerrainTexturePacksAdd);
      this.pnlTerrainTexturePacks.Controls.Add(this.tbxTerrainTexturePacks);
      this.pnlTerrainTexturePacks.Controls.Add(this.lbxTerrainTexturePacks);
      this.pnlTerrainTexturePacks.Location = new System.Drawing.Point(3, 423);
      this.pnlTerrainTexturePacks.Margin = new System.Windows.Forms.Padding(3, 2, 3, 0);
      this.pnlTerrainTexturePacks.Name = "pnlTerrainTexturePacks";
      this.pnlTerrainTexturePacks.Size = new System.Drawing.Size(167, 167);
      this.pnlTerrainTexturePacks.TabIndex = 4;
      this.pnlTerrainTexturePacks.Text = "Texture packs";
      this.pnlTerrainTexturePacks.Visible = false;
      // 
      // btnTerrainTexturePacksDel
      // 
      this.btnTerrainTexturePacksDel.BackColor = System.Drawing.Color.Transparent;
      this.btnTerrainTexturePacksDel.BACKCOLOR = System.Drawing.Color.Transparent;
      this.btnTerrainTexturePacksDel.BORDERCOLOR = System.Drawing.Color.Red;
      this.btnTerrainTexturePacksDel.BORDERRADIUS = 5;
      this.btnTerrainTexturePacksDel.BORDERWIDTH = 1;
      this.btnTerrainTexturePacksDel.Font = new System.Drawing.Font("Bauhaus 93", 13F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.btnTerrainTexturePacksDel.ForeColor = System.Drawing.Color.Red;
      this.btnTerrainTexturePacksDel.Image = null;
      this.btnTerrainTexturePacksDel.Location = new System.Drawing.Point(143, 53);
      this.btnTerrainTexturePacksDel.Name = "btnTerrainTexturePacksDel";
      this.btnTerrainTexturePacksDel.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.btnTerrainTexturePacksDel.SCALEBORD = true;
      this.btnTerrainTexturePacksDel.Size = new System.Drawing.Size(20, 20);
      this.btnTerrainTexturePacksDel.TabIndex = 3;
      this.btnTerrainTexturePacksDel.Text = "-";
      this.btnTerrainTexturePacksDel.UseVisualStyleBackColor = false;
      // 
      // btnTerrainTexturePacksAdd
      // 
      this.btnTerrainTexturePacksAdd.BackColor = System.Drawing.Color.Transparent;
      this.btnTerrainTexturePacksAdd.BACKCOLOR = System.Drawing.Color.Transparent;
      this.btnTerrainTexturePacksAdd.BORDERCOLOR = System.Drawing.Color.Green;
      this.btnTerrainTexturePacksAdd.BORDERRADIUS = 5;
      this.btnTerrainTexturePacksAdd.BORDERWIDTH = 1;
      this.btnTerrainTexturePacksAdd.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.btnTerrainTexturePacksAdd.ForeColor = System.Drawing.Color.Green;
      this.btnTerrainTexturePacksAdd.Image = null;
      this.btnTerrainTexturePacksAdd.Location = new System.Drawing.Point(143, 31);
      this.btnTerrainTexturePacksAdd.Name = "btnTerrainTexturePacksAdd";
      this.btnTerrainTexturePacksAdd.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.btnTerrainTexturePacksAdd.SCALEBORD = true;
      this.btnTerrainTexturePacksAdd.Size = new System.Drawing.Size(20, 20);
      this.btnTerrainTexturePacksAdd.TabIndex = 2;
      this.btnTerrainTexturePacksAdd.Text = "+";
      this.btnTerrainTexturePacksAdd.UseVisualStyleBackColor = false;
      // 
      // tbxTerrainTexturePacks
      // 
      this.tbxTerrainTexturePacks.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.tbxTerrainTexturePacks.Location = new System.Drawing.Point(5, 31);
      this.tbxTerrainTexturePacks.Name = "tbxTerrainTexturePacks";
      this.tbxTerrainTexturePacks.Size = new System.Drawing.Size(135, 20);
      this.tbxTerrainTexturePacks.TabIndex = 1;
      // 
      // lbxTerrainTexturePacks
      // 
      this.lbxTerrainTexturePacks.FormattingEnabled = true;
      this.lbxTerrainTexturePacks.Location = new System.Drawing.Point(5, 53);
      this.lbxTerrainTexturePacks.Name = "lbxTerrainTexturePacks";
      this.lbxTerrainTexturePacks.Size = new System.Drawing.Size(135, 108);
      this.lbxTerrainTexturePacks.TabIndex = 0;
      // 
      // pnlRight
      // 
      this.pnlRight.BackColor = System.Drawing.SystemColors.InactiveBorder;
      this.pnlRight.Dock = System.Windows.Forms.DockStyle.Right;
      this.pnlRight.Location = new System.Drawing.Point(846, 66);
      this.pnlRight.Name = "pnlRight";
      this.pnlRight.Size = new System.Drawing.Size(174, 650);
      this.pnlRight.TabIndex = 3;
      this.pnlRight.Visible = false;
      // 
      // pnlRender
      // 
      this.pnlRender.BackColor = System.Drawing.Color.RoyalBlue;
      this.pnlRender.Dock = System.Windows.Forms.DockStyle.Fill;
      this.pnlRender.Location = new System.Drawing.Point(525, 66);
      this.pnlRender.Name = "pnlRender";
      this.pnlRender.Size = new System.Drawing.Size(321, 650);
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
      this.pnlTop.Size = new System.Drawing.Size(1020, 42);
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
      this.btnTopWater.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnTopWater.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnTopWater.BackgroundImage")));
      this.btnTopWater.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTopWater.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTopWater.Location = new System.Drawing.Point(82, 2);
      this.btnTopWater.Name = "btnTopWater";
      this.btnTopWater.Size = new System.Drawing.Size(38, 38);
      this.btnTopWater.TabIndex = 2;
      this.btnTopWater.Tag = "2";
      this.btnTopWater.UseVisualStyleBackColor = false;
      this.btnTopWater.Click += new System.EventHandler(this.btnTopMain_Click);
      // 
      // btnTopEntity
      // 
      this.btnTopEntity.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnTopEntity.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnTopEntity.BackgroundImage")));
      this.btnTopEntity.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTopEntity.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTopEntity.Location = new System.Drawing.Point(42, 2);
      this.btnTopEntity.Name = "btnTopEntity";
      this.btnTopEntity.Size = new System.Drawing.Size(38, 38);
      this.btnTopEntity.TabIndex = 1;
      this.btnTopEntity.Tag = "1";
      this.btnTopEntity.UseVisualStyleBackColor = false;
      this.btnTopEntity.Click += new System.EventHandler(this.btnTopMain_Click);
      // 
      // btnTopTerrain
      // 
      this.btnTopTerrain.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnTopTerrain.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnTopTerrain.BackgroundImage")));
      this.btnTopTerrain.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnTopTerrain.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnTopTerrain.Location = new System.Drawing.Point(2, 2);
      this.btnTopTerrain.Name = "btnTopTerrain";
      this.btnTopTerrain.Size = new System.Drawing.Size(38, 38);
      this.btnTopTerrain.TabIndex = 0;
      this.btnTopTerrain.Tag = "0";
      this.btnTopTerrain.UseVisualStyleBackColor = false;
      this.btnTopTerrain.Click += new System.EventHandler(this.btnTopMain_Click);
      // 
      // pnlLeftEntity
      // 
      this.pnlLeftEntity.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
      this.pnlLeftEntity.Controls.Add(this.pnlEntityTransformation);
      this.pnlLeftEntity.Controls.Add(this.pnlEntityPacks);
      this.pnlLeftEntity.Dock = System.Windows.Forms.DockStyle.Left;
      this.pnlLeftEntity.Location = new System.Drawing.Point(175, 66);
      this.pnlLeftEntity.Name = "pnlLeftEntity";
      this.pnlLeftEntity.Size = new System.Drawing.Size(175, 650);
      this.pnlLeftEntity.TabIndex = 6;
      this.pnlLeftEntity.Visible = false;
      // 
      // pnlEntityTransformation
      // 
      this.pnlEntityTransformation._Checked = false;
      this.pnlEntityTransformation.BACKCOLOR = System.Drawing.Color.Transparent;
      this.pnlEntityTransformation.BORDERCOLOR = System.Drawing.Color.Black;
      this.pnlEntityTransformation.BORDERRADIUS = 5;
      this.pnlEntityTransformation.BORDERWIDTH = 1;
      this.pnlEntityTransformation.Controls.Add(this.btnEntityStickToTerrain);
      this.pnlEntityTransformation.Controls.Add(this.btnEntityRot);
      this.pnlEntityTransformation.Controls.Add(this.btnEntityScl);
      this.pnlEntityTransformation.Controls.Add(this.btnEntityObject);
      this.pnlEntityTransformation.Controls.Add(this.btnEntityPos);
      this.pnlEntityTransformation.Location = new System.Drawing.Point(3, 2);
      this.pnlEntityTransformation.Margin = new System.Windows.Forms.Padding(3, 2, 3, 0);
      this.pnlEntityTransformation.Name = "pnlEntityTransformation";
      this.pnlEntityTransformation.Size = new System.Drawing.Size(167, 108);
      this.pnlEntityTransformation.TabIndex = 0;
      this.pnlEntityTransformation.Text = "Transformation";
      // 
      // btnEntityStickToTerrain
      // 
      this.btnEntityStickToTerrain.BackColor = System.Drawing.Color.Transparent;
      this.btnEntityStickToTerrain.BACKCOLOR = System.Drawing.Color.Transparent;
      this.btnEntityStickToTerrain.BORDERCOLOR = System.Drawing.Color.Black;
      this.btnEntityStickToTerrain.BORDERRADIUS = 5;
      this.btnEntityStickToTerrain.BORDERWIDTH = 0;
      this.btnEntityStickToTerrain.CHECKABLE = true;
      this.btnEntityStickToTerrain.Image = null;
      this.btnEntityStickToTerrain.Location = new System.Drawing.Point(14, 75);
      this.btnEntityStickToTerrain.Name = "btnEntityStickToTerrain";
      this.btnEntityStickToTerrain.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.btnEntityStickToTerrain.SCALEBORD = true;
      this.btnEntityStickToTerrain.Size = new System.Drawing.Size(141, 20);
      this.btnEntityStickToTerrain.TabIndex = 3;
      this.btnEntityStickToTerrain.Text = "Stick to terrain";
      this.btnEntityStickToTerrain.UseVisualStyleBackColor = false;
      // 
      // btnEntityRot
      // 
      this.btnEntityRot.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnEntityRot.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntityRot.BackgroundImage")));
      this.btnEntityRot.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntityRot.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntityRot.Location = new System.Drawing.Point(123, 31);
      this.btnEntityRot.Name = "btnEntityRot";
      this.btnEntityRot.Size = new System.Drawing.Size(32, 32);
      this.btnEntityRot.TabIndex = 2;
      this.btnEntityRot.Tag = "3";
      this.btnEntityRot.UseVisualStyleBackColor = false;
      this.btnEntityRot.Click += new System.EventHandler(this.btnEntityTransform_Click);
      // 
      // btnEntityScl
      // 
      this.btnEntityScl.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnEntityScl.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntityScl.BackgroundImage")));
      this.btnEntityScl.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntityScl.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntityScl.Location = new System.Drawing.Point(87, 31);
      this.btnEntityScl.Name = "btnEntityScl";
      this.btnEntityScl.Size = new System.Drawing.Size(32, 32);
      this.btnEntityScl.TabIndex = 1;
      this.btnEntityScl.Tag = "2";
      this.btnEntityScl.UseVisualStyleBackColor = false;
      this.btnEntityScl.Click += new System.EventHandler(this.btnEntityTransform_Click);
      // 
      // btnEntityObject
      // 
      this.btnEntityObject.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnEntityObject.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntityObject.BackgroundImage")));
      this.btnEntityObject.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntityObject.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntityObject.Location = new System.Drawing.Point(14, 31);
      this.btnEntityObject.Name = "btnEntityObject";
      this.btnEntityObject.Size = new System.Drawing.Size(32, 32);
      this.btnEntityObject.TabIndex = 0;
      this.btnEntityObject.Tag = "0";
      this.btnEntityObject.UseVisualStyleBackColor = false;
      this.btnEntityObject.Click += new System.EventHandler(this.btnEntityTransform_Click);
      // 
      // btnEntityPos
      // 
      this.btnEntityPos.BackColor = System.Drawing.SystemColors.ControlLightLight;
      this.btnEntityPos.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnEntityPos.BackgroundImage")));
      this.btnEntityPos.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btnEntityPos.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEntityPos.Location = new System.Drawing.Point(51, 31);
      this.btnEntityPos.Name = "btnEntityPos";
      this.btnEntityPos.Size = new System.Drawing.Size(32, 32);
      this.btnEntityPos.TabIndex = 0;
      this.btnEntityPos.Tag = "1";
      this.btnEntityPos.UseVisualStyleBackColor = false;
      this.btnEntityPos.Click += new System.EventHandler(this.btnEntityTransform_Click);
      // 
      // pnlEntityPacks
      // 
      this.pnlEntityPacks._Checked = false;
      this.pnlEntityPacks.BACKCOLOR = System.Drawing.Color.Transparent;
      this.pnlEntityPacks.BORDERCOLOR = System.Drawing.Color.Black;
      this.pnlEntityPacks.BORDERRADIUS = 5;
      this.pnlEntityPacks.BORDERWIDTH = 1;
      this.pnlEntityPacks.Controls.Add(this.awA_Button2);
      this.pnlEntityPacks.Controls.Add(this.textBox1);
      this.pnlEntityPacks.Controls.Add(this.awA_Button1);
      this.pnlEntityPacks.Controls.Add(this.listBox1);
      this.pnlEntityPacks.Location = new System.Drawing.Point(3, 112);
      this.pnlEntityPacks.Margin = new System.Windows.Forms.Padding(3, 2, 3, 0);
      this.pnlEntityPacks.Name = "pnlEntityPacks";
      this.pnlEntityPacks.Size = new System.Drawing.Size(167, 167);
      this.pnlEntityPacks.TabIndex = 1;
      this.pnlEntityPacks.Text = "Packs";
      // 
      // awA_Button2
      // 
      this.awA_Button2.BackColor = System.Drawing.Color.Transparent;
      this.awA_Button2.BACKCOLOR = System.Drawing.Color.Transparent;
      this.awA_Button2.BORDERCOLOR = System.Drawing.Color.Red;
      this.awA_Button2.BORDERRADIUS = 5;
      this.awA_Button2.BORDERWIDTH = 1;
      this.awA_Button2.Font = new System.Drawing.Font("Bauhaus 93", 13F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.awA_Button2.ForeColor = System.Drawing.Color.Red;
      this.awA_Button2.Image = null;
      this.awA_Button2.Location = new System.Drawing.Point(141, 53);
      this.awA_Button2.Name = "awA_Button2";
      this.awA_Button2.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.awA_Button2.SCALEBORD = true;
      this.awA_Button2.Size = new System.Drawing.Size(20, 20);
      this.awA_Button2.TabIndex = 3;
      this.awA_Button2.Text = "-";
      this.awA_Button2.UseVisualStyleBackColor = false;
      // 
      // textBox1
      // 
      this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.textBox1.Location = new System.Drawing.Point(3, 31);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new System.Drawing.Size(135, 20);
      this.textBox1.TabIndex = 1;
      // 
      // awA_Button1
      // 
      this.awA_Button1.BackColor = System.Drawing.Color.Transparent;
      this.awA_Button1.BACKCOLOR = System.Drawing.Color.Transparent;
      this.awA_Button1.BORDERCOLOR = System.Drawing.Color.Green;
      this.awA_Button1.BORDERRADIUS = 5;
      this.awA_Button1.BORDERWIDTH = 1;
      this.awA_Button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.awA_Button1.ForeColor = System.Drawing.Color.Green;
      this.awA_Button1.Image = null;
      this.awA_Button1.Location = new System.Drawing.Point(141, 31);
      this.awA_Button1.Name = "awA_Button1";
      this.awA_Button1.PUSHEDCOLOR = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(215)))), ((int)(((byte)(215)))));
      this.awA_Button1.SCALEBORD = true;
      this.awA_Button1.Size = new System.Drawing.Size(20, 20);
      this.awA_Button1.TabIndex = 2;
      this.awA_Button1.Text = "+";
      this.awA_Button1.UseVisualStyleBackColor = false;
      // 
      // listBox1
      // 
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new System.Drawing.Point(3, 53);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new System.Drawing.Size(135, 108);
      this.listBox1.TabIndex = 0;
      // 
      // pnlLeftWater
      // 
      this.pnlLeftWater.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
      this.pnlLeftWater.Dock = System.Windows.Forms.DockStyle.Left;
      this.pnlLeftWater.Location = new System.Drawing.Point(350, 66);
      this.pnlLeftWater.Name = "pnlLeftWater";
      this.pnlLeftWater.Size = new System.Drawing.Size(175, 650);
      this.pnlLeftWater.TabIndex = 7;
      this.pnlLeftWater.Visible = false;
      // 
      // cmsEntity
      // 
      this.cmsEntity.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.transformationToolStripMenuItem});
      this.cmsEntity.Name = "cmsEntity";
      this.cmsEntity.Size = new System.Drawing.Size(166, 26);
      // 
      // transformationToolStripMenuItem
      // 
      this.transformationToolStripMenuItem.Name = "transformationToolStripMenuItem";
      this.transformationToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
      this.transformationToolStripMenuItem.Text = "Transformation...";
      // 
      // firstPersonFreeToolStripMenuItem
      // 
      this.firstPersonFreeToolStripMenuItem.Name = "firstPersonFreeToolStripMenuItem";
      this.firstPersonFreeToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.G)));
      this.firstPersonFreeToolStripMenuItem.Size = new System.Drawing.Size(200, 22);
      this.firstPersonFreeToolStripMenuItem.Tag = "3";
      this.firstPersonFreeToolStripMenuItem.Text = "First person free";
      this.firstPersonFreeToolStripMenuItem.Click += new System.EventHandler(this.CameraType_Click);
      // 
      // EditorForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1020, 741);
      this.Controls.Add(this.pnlRender);
      this.Controls.Add(this.pnlLeftWater);
      this.Controls.Add(this.pnlLeftEntity);
      this.Controls.Add(this.pnlRight);
      this.Controls.Add(this.pnlLeftTerrain);
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
      this.pnlLeftTerrain.ResumeLayout(false);
      this.pnlTerrainMain.ResumeLayout(false);
      this.pnlTerrainMain.PerformLayout();
      this.pnlTerrainTerraforming.ResumeLayout(false);
      this.pnlTerrainTerraformingDummy.ResumeLayout(false);
      this.panel9.ResumeLayout(false);
      this.panel8.ResumeLayout(false);
      this.panel7.ResumeLayout(false);
      this.panel7.PerformLayout();
      this.panel6.ResumeLayout(false);
      this.panel6.PerformLayout();
      this.panel5.ResumeLayout(false);
      this.panel5.PerformLayout();
      this.panel4.ResumeLayout(false);
      this.panel4.PerformLayout();
      this.panel3.ResumeLayout(false);
      this.panel3.PerformLayout();
      this.panel2.ResumeLayout(false);
      this.panel2.PerformLayout();
      this.pnlTerrainTexturing.ResumeLayout(false);
      this.pnlTerrainTexturingDummy.ResumeLayout(false);
      this.panel15.ResumeLayout(false);
      this.panel15.PerformLayout();
      this.panel17.ResumeLayout(false);
      this.panel17.PerformLayout();
      this.panel12.ResumeLayout(false);
      this.pnlTerrainTexturePacks.ResumeLayout(false);
      this.pnlTerrainTexturePacks.PerformLayout();
      this.pnlTop.ResumeLayout(false);
      this.pnlTopMain.ResumeLayout(false);
      this.pnlLeftEntity.ResumeLayout(false);
      this.pnlEntityTransformation.ResumeLayout(false);
      this.pnlEntityPacks.ResumeLayout(false);
      this.pnlEntityPacks.PerformLayout();
      this.cmsEntity.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuMain;
        private System.Windows.Forms.ToolStripMenuItem menuFile;
        private System.Windows.Forms.ToolStripMenuItem menuFileExit;
        private System.Windows.Forms.Panel pnlDown;
        private System.Windows.Forms.FlowLayoutPanel pnlLeftTerrain;
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
        private System.Windows.Forms.Button btnTopWater;
        private System.Windows.Forms.Button btnTopEntity;
        private System.Windows.Forms.Button btnTopTerrain;
        private GUI_elements.Panel_Ex pnlTerrainMain;
        private GUI_elements.AWA_Button btnTerrainCreate;
        private System.Windows.Forms.Label label1;
        private GUI_elements.AWA_Value_Button vbtnTerrainSizeY;
        private GUI_elements.AWA_Value_Button vbtnTerrainSizeX;
        private System.Windows.Forms.FlowLayoutPanel pnlLeftEntity;
        private GUI_elements.Panel_Ex pnlEntityTransformation;
        private GUI_elements.AWA_Button btnEntityStickToTerrain;
        private System.Windows.Forms.Button btnEntityRot;
        private System.Windows.Forms.Button btnEntityScl;
        private System.Windows.Forms.Button btnEntityObject;
        private System.Windows.Forms.Button btnEntityPos;
        private System.Windows.Forms.FlowLayoutPanel pnlLeftWater;
        private GUI_elements.Panel_Ex pnlTerrainTerraforming;
        private GUI_elements.Panel_Ex pnlEntityPacks;
        private System.Windows.Forms.Panel pnlTerrainTerraformingDummy;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label label4;
        private GUI_elements.AWA_Value_Button vbtnTerraformingHard;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label3;
        private GUI_elements.AWA_Value_Button vbtnTerraformingSizeOut;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label2;
        private GUI_elements.AWA_Value_Button vbtnTerraformingSizeIn;
        private System.Windows.Forms.Panel panel9;
        private GUI_elements.AWA_Button btnTerraformingSmoothOut;
        private System.Windows.Forms.Panel panel8;
        private GUI_elements.AWA_Button btnTerraformingSmoothIn;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Label label7;
        private GUI_elements.AWA_Value_Button vbtnTerraformingSmoothKoeff;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Label label6;
        private GUI_elements.AWA_Value_Button vbtnTerraformingShiftHeight;
        private System.Windows.Forms.Panel panel5;
        private GUI_elements.AWA_Value_Button vbtnTerraformingAltHard;
        private System.Windows.Forms.ContextMenuStrip cmsEntity;
        private System.Windows.Forms.ToolStripMenuItem transformationToolStripMenuItem;
        private GUI_elements.Panel_Ex pnlTerrainTexturing;
        private System.Windows.Forms.Panel pnlTerrainTexturingDummy;
        private System.Windows.Forms.Panel panel15;
        private System.Windows.Forms.Label label11;
        private GUI_elements.AWA_Value_Button vbtnTexturingHard;
        private System.Windows.Forms.Panel panel17;
        private System.Windows.Forms.Label label13;
        private GUI_elements.AWA_Value_Button vbtnTexturingSize;
        private System.Windows.Forms.Panel panel12;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btnTexturingCirc;
        private System.Windows.Forms.Button btnTexturingCustom;
        private System.Windows.Forms.Button btnTexturingQuad;
        private System.Windows.Forms.Button btnTexturingRhomb;
        private GUI_elements.Panel_Ex pnlTerrainTexturePacks;
        private GUI_elements.AWA_Button btnTerrainTexturePacksDel;
        private GUI_elements.AWA_Button btnTerrainTexturePacksAdd;
        private System.Windows.Forms.TextBox tbxTerrainTexturePacks;
        private System.Windows.Forms.ListBox lbxTerrainTexturePacks;
        private GUI_elements.AWA_Button awA_Button2;
        private System.Windows.Forms.TextBox textBox1;
        private GUI_elements.AWA_Button awA_Button1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.ToolStripMenuItem firstPersonFreeToolStripMenuItem;
    }
}