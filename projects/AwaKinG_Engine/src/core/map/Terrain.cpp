#include "Terrain.h"
#include "../../render/Render.h"

Terrain::Terrain() {
  errorMessage = ED_UNDEFINED;
  _numTileVerts = NUM_VERTS * NUM_VERTS;
  _numQuads = NUM_VERTS - 1;
  _numTileQuads = _numQuads * _numQuads;
  _numIndexs = _numTileQuads * 6;
  _indexBuffer = 0;
  _vertexBuffers = 0;
  _numTiles = 0;
  _initialized = false;
#ifdef _DLL_EXPORT
  _2048dds = "../../../../media/_2048.dds";
#endif
#ifdef _LIB_EXPORT
  _2048dds = "../../media/_2048.dds";
#endif
}
void Terrain::shutdown() {
  SAFE_RELEASE(_indexBuffer);
  for(int i = 0; i < _numTiles; i++) 
    SAFE_RELEASE(_vertexBuffers[i]);
  for(int i = 0; i < _numTiles; i++)
    SAFE_RELEASE(_textures[i]);
  delete[] _vertexBuffers;
  delete[] _textures;
  delete[] _normalMap;
  delete[] _heightMap;
  delete[] _indexes;
  for(int i = 0; i < _maxId; i++)
    delete[] _heightMapToTerrain[i];
  delete[] _heightMapToTerrain;
  for(int i = 0; i < _numTiles; i++)
    delete[] _pickToHeightMap[i];
  delete[] _pickToHeightMap;
  
  _numTiles = 0;
  _initialized = false;
}
Terrain& Terrain::getInstance() {
  static Terrain terrain_;
  return terrain_;
}
bool Terrain::create(int sizeX, int sizeY) {
  shutdown();
  _sizeX = sizeX;
  _sizeY = sizeY;
  _generateHeightMap();

  XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());
  return _generateGeometry();
}
void Terrain::_generateHeightMap() {
  _numTiles = _sizeX * _sizeY;
  _numVertsInRaw = _sizeX * _numQuads + 1;
  _numVertsInCol = _sizeY * _numQuads + 1;
  _maxId = _numVertsInRaw * _numVertsInCol;
  _heightMapToTerrain = new int*[_maxId];
  _pickToHeightMap = new int*[_numTiles];

  for(int i = 0; i < _maxId; i++) {
    _heightMapToTerrain[i] = new int[1];
    _heightMapToTerrain[i][0] = 0;
  }
  for(int i = 0; i < _numTiles; i++)
    _pickToHeightMap[i] = new int[_numTileVerts];
  
  int k = 0; int k_raw = 0;
  for(int i = 0; i < _numTiles; i++) {
    k_raw = 0;
    int qwer = i % _sizeX;
    if(qwer == 0 && i != 0) k += _numVertsInRaw * _numQuads;
    else qwer *= _numQuads;

    int savedI_ = 0; int savedJ_ = 0; int savedK_ = 0; int savedL_ = 0; int savedM_ = 0; int savedN_ = 0;
    for(int j = 0; j < _numTileVerts; j++) {
      if(j % NUM_VERTS == 0 && j != 0) k_raw += _numVertsInRaw - NUM_VERTS;

      _pickToHeightMap[i][j] = k + qwer + j + k_raw;

      switch(_heightMapToTerrain[k + qwer + j + k_raw][0]) {
      case 0:
        _heightMapToTerrain[k + qwer + j + k_raw] = new int[3];
        _heightMapToTerrain[k + qwer + j + k_raw][0] = 1;
        _heightMapToTerrain[k + qwer + j + k_raw][1] = i;
        _heightMapToTerrain[k + qwer + j + k_raw][2] = j;
        break;
      case 1:
        savedI_ = _heightMapToTerrain[k + qwer + j + k_raw][1];
        savedJ_ = _heightMapToTerrain[k + qwer + j + k_raw][2];

        _heightMapToTerrain[k + qwer + j + k_raw] = new int[5];
        _heightMapToTerrain[k + qwer + j + k_raw][0] = 2;
        _heightMapToTerrain[k + qwer + j + k_raw][1] = savedI_;
        _heightMapToTerrain[k + qwer + j + k_raw][2] = savedJ_;
        _heightMapToTerrain[k + qwer + j + k_raw][3] = i;
        _heightMapToTerrain[k + qwer + j + k_raw][4] = j;
        break;
      case 2:
        savedI_ = _heightMapToTerrain[k + qwer + j + k_raw][1];
        savedJ_ = _heightMapToTerrain[k + qwer + j + k_raw][2];
        savedK_ = _heightMapToTerrain[k + qwer + j + k_raw][3];
        savedL_ = _heightMapToTerrain[k + qwer + j + k_raw][4];

        _heightMapToTerrain[k + qwer + j + k_raw] = new int[7];
        _heightMapToTerrain[k + qwer + j + k_raw][0] = 3;
        _heightMapToTerrain[k + qwer + j + k_raw][1] = savedI_;
        _heightMapToTerrain[k + qwer + j + k_raw][2] = savedJ_;
        _heightMapToTerrain[k + qwer + j + k_raw][3] = savedK_;
        _heightMapToTerrain[k + qwer + j + k_raw][4] = savedL_;
        _heightMapToTerrain[k + qwer + j + k_raw][5] = i;
        _heightMapToTerrain[k + qwer + j + k_raw][6] = j;
        break;
      case 3:
        savedI_ = _heightMapToTerrain[k + qwer + j + k_raw][1];
        savedJ_ = _heightMapToTerrain[k + qwer + j + k_raw][2];
        savedK_ = _heightMapToTerrain[k + qwer + j + k_raw][3];
        savedL_ = _heightMapToTerrain[k + qwer + j + k_raw][4];
        savedM_ = _heightMapToTerrain[k + qwer + j + k_raw][5];
        savedN_ = _heightMapToTerrain[k + qwer + j + k_raw][6];

        _heightMapToTerrain[k + qwer + j + k_raw] = new int[9];
        _heightMapToTerrain[k + qwer + j + k_raw][0] = 4;
        _heightMapToTerrain[k + qwer + j + k_raw][1] = savedI_;
        _heightMapToTerrain[k + qwer + j + k_raw][2] = savedJ_;
        _heightMapToTerrain[k + qwer + j + k_raw][3] = savedK_;
        _heightMapToTerrain[k + qwer + j + k_raw][4] = savedL_;
        _heightMapToTerrain[k + qwer + j + k_raw][5] = savedM_;
        _heightMapToTerrain[k + qwer + j + k_raw][6] = savedN_;
        _heightMapToTerrain[k + qwer + j + k_raw][7] = i;
        _heightMapToTerrain[k + qwer + j + k_raw][8] = j;
        break;
      }
    }
  }

  float oneWidth_ = ((float)_numQuads) * CELL_SPACE;
  float halfWidth_ = _sizeX * oneWidth_ / 2.0f;
  float halfHeight_ = _sizeY * oneWidth_ / 2.0f;
  _heightMap = new XMFLOAT3[_maxId];
  _normalMap = new XMFLOAT3[_maxId];
  for(int i = 0; i < _numVertsInCol; i++) {
    for(int j = 0; j < _numVertsInRaw; j++) {
      _heightMap[i*_numVertsInCol + j] = XMFLOAT3(CELL_SPACE * i - halfHeight_, 0.0f, CELL_SPACE * j - halfWidth_);
      _normalMap[i*_numVertsInCol + j] = XMFLOAT3(0.0f, 1.0f, 0.0f);
    }
  }
}
bool Terrain::_generateGeometry() {
  D3D11_BUFFER_DESC bd_;
  ZeroMemory(&bd_, sizeof(bd_));
  bd_.Usage = D3D11_USAGE_DYNAMIC;
  bd_.ByteWidth = sizeof(Vertex::Default) * _numTileVerts;
  bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  D3D11_SUBRESOURCE_DATA initData_;

  _vertexBuffers = new ID3D11Buffer*[_numTiles];
  float texs_ = (float)1.0f / (float)_numQuads;
  int ter_ind = 0;
  Vertex::Default* verts_ = new Vertex::Default[_numTileVerts];
  for(int ter_ind_x = 0; ter_ind_x < _sizeX; ter_ind_x++) {
    for(int ter_ind_y = 0; ter_ind_y < _sizeY; ter_ind_y++) {
      int number = 0;
      for(int i = 0; i < NUM_VERTS; i++) {
        for(int j = 0; j < NUM_VERTS; j++) {
          verts_[number] = Vertex::Default(_heightMap[_pickToHeightMap[ter_ind][number]],
            XMFLOAT2(texs_ * (float)j, texs_ * (float)i), _normalMap[_pickToHeightMap[ter_ind][number]]);
          number++;
        }
      }
      ZeroMemory(&initData_, sizeof(initData_));
      initData_.pSysMem = verts_;
      if(!Render::getInstance().createBuffer(&bd_, &initData_, &_vertexBuffers[ter_ind])) { 
        errorMessage = "Create vertex buffer error!";
        return false;
      }
      ter_ind++;
    }
  }
  if(!_createIndexBuffer()) return false;

  D3DX11_IMAGE_LOAD_INFO ili_;
  //ili_.MipLevels = 0;
  ili_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  ili_.Width = 512; ili_.Height = 512;
  ili_.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  ili_.CpuAccessFlags = 0;
  ili_.MipFilter = D3D11_FILTER_TYPE_LINEAR;
  ili_.FirstMipLevel = 1;
  ili_.MiscFlags = 0;
  ili_.Usage = D3D11_USAGE_DEFAULT;

  _textures = new ID3D11ShaderResourceView*[_numTiles];
  for(int i = 0; i < _numTiles; i++)
  if(!Render::getInstance().createTexture(_2048dds, &ili_, &_textures[i])) {
    errorMessage = "Create Texture error with path!";
    return false;
  }

  _initialized = true;
  return true;
}
bool Terrain::_createIndexBuffer() {
  _indexes = new unsigned int[_numIndexs];
  unsigned int index = 0;
  for(int i = 0; i < _numQuads; i++) {
    for(int j = 0; j < _numQuads; j++) {
      _indexes[index] = (unsigned int)(i * NUM_VERTS + j);
      _indexes[index + 1] = (unsigned int)(i *  NUM_VERTS + j + 1);
      _indexes[index + 2] = (unsigned int)((i + 1) *  NUM_VERTS + j);

      _indexes[index + 3] = (unsigned int)(i *  NUM_VERTS + j + 1);
      _indexes[index + 4] = (unsigned int)((i + 1) *  NUM_VERTS + j + 1);
      _indexes[index + 5] = (unsigned int)((i + 1) *  NUM_VERTS + j);

      index += 6;
    }
  }
  D3D11_BUFFER_DESC bd_;
  D3D11_SUBRESOURCE_DATA initData_;
  ZeroMemory(&bd_, sizeof(bd_));
  bd_.Usage = D3D11_USAGE_DEFAULT;
  bd_.ByteWidth = sizeof(UINT)* _numIndexs;
  bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd_.CPUAccessFlags = 0;
  bd_.MiscFlags = 0;
  ZeroMemory(&initData_, sizeof(initData_));
  initData_.pSysMem = _indexes;
  if(!Render::getInstance().createBuffer(&bd_, &initData_, &_indexBuffer)) {
    errorMessage = "Create index buffer error!";
    return false;
  }
  return true;
}
int Terrain::getNumTiles() {
  return _numTiles;
}
ID3D11ShaderResourceView** Terrain::getTexture(int index) {
  return &_textures[index];
}
ID3D11Buffer** Terrain::getVertexBuffer(int index) {
  return &_vertexBuffers[index];
}
ID3D11Buffer* Terrain::getIndexBuffer() {
  return _indexBuffer;
}
XMFLOAT4X4* Terrain::getWorldMatrix() {
  return &_worldMatrix;
}
int Terrain::getIndexCount() {
  return _numIndexs;
}
bool Terrain::getInitialized() {
  return _initialized;
}
