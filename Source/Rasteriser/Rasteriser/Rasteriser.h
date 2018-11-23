#pragma once
#include "Framework.h"
#include "MD2Loader.h"
#include "FPoint.h"
#define _USE_MATH_DEFINES

class Rasteriser : public Framework
{
public:
	//Initaliser
	bool Initialise();
	
	//Main methods
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);

	//Matrix methods
	Matrix Rasteriser::GenerateScaleMatrix(float x, float y, float z);
	Matrix Rasteriser::GenerateTranslateMatrix(float x, float y, float z);
	Matrix Rasteriser::GenerateXRotationMatrix(float angle);
	Matrix Rasteriser::GenerateYRotationMatrix(float angle);
	Matrix Rasteriser::GenerateZRotationMatrix(float angle);
	float Rasteriser::CalculateRadian(float degrees);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);

	//Basic Render Methods
	void DrawWireFrame(Bitmap &bitmap);
	void DrawSolidFlat(Bitmap &bitmap);

	//My Flat Render Methods
	void MyDrawSolidFlat(HDC hDc);
	void FillPolygonFlatBottom(FPoint &v1, FPoint &v2, FPoint &v3, COLORREF &color, HDC &hDc);
	void FIllPolygonFlatTop(FPoint &v1, FPoint &v2, FPoint &v3, COLORREF &color, HDC &hDc);

	//Gouraud Render Methods
	void DrawGouraud(HDC hDc);
	void GouraudFillPolygonFlatBottom(Vertex &v1, Vertex &v2, Vertex &v3, HDC &hDc);
	void GouraudFillPolygonFlatTop(Vertex &v1, Vertex &v2, Vertex &v3, HDC &hDc);

	//Text Renderer
	void DrawString(HDC hDc, LPCTSTR text);

protected:
	float _degree = 0.0f;
	float _radian = 0.0f;
	float _scale = 1.0f;
	float _translate = 1.0f;
	
	int _frameCounter = 0;
	wstring  _stateDescription = (L"no state");
	bool _wireFrameState = false;
	bool _xRotationState = false;
	bool _yRotationState = false;
	bool _zRotationState = false;
	bool _xyzRotationState = false;
	bool _scaleState = false;
	bool _translateState = false;
	bool _backfaceCulling = false;
	bool _polygonSorting = false;
	bool _gdiFlatShading = false;
	bool _ambientLights = false;
	bool _directionalLights = false;
	bool _pointLights = false;
	bool _customFlatShading = false;
	bool _gouraudShading = false;

	//Creates a directional Light
	Vector3D temp3d = { 0, 1, 0 };
	DirectionalLight temp = { 255, 0, 0, temp3d };
	//_directionalLighting.push_back(temp);

	//Creates a directional Light 
	Vector3D temp3d2 = { 0, -50, 0 };
	DirectionalLight temp2 = { 0, 255, 0, temp3d2 };
	

	//Creates a ambient light
	AmbientLight amblight = { 0, 0, 255 };

	//Creates a point light
	Vertex pointLightPos = { 0, 0, -10 };
	PointLight pointLight = { 255, 255, 255, 0, 1, 0, pointLightPos };

private:
	//The Model
	Model _model;

	//The Camera
	Camera _camera = { 0, 0, 0, Vertex(0, 0, -10) };
	
	//Render pipeline matrices
	Matrix perspectiveMatrix{};
	Matrix viewMatrix{};
	Matrix transformMatrix{};
	Matrix cameraTransformMatrix;

	//List of lights
	std::vector<DirectionalLight> _directionalLighting;
	std::vector<AmbientLight> _ambientLighting;
	std::vector<PointLight> _pointLighting;
};

