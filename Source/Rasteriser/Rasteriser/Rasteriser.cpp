#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	//Load the model into memory!
	if (!MD2Loader::LoadModel("teapot.md2", _model, &Model::AddPolygon, &Model::AddVertex))
	{
		return false;
	}
	
	//Calculates the size of the Vertex and Polygon lists
	_model.CalculatePolygonCount();
	_model.CalculateVerticesCount();


	//_pointLighting.push_back(pointLight);

	return true;
}

//The update method
void Rasteriser::Update(Bitmap &bitmap)
{
	_frameCounter = _frameCounter++;
	if (_frameCounter >= 0 && _frameCounter < 100)
	{
		_wireFrameState = true;
		_stateDescription = (L"Model Loading and Wireframe View");

	}
	else if (_frameCounter >= 100 && _frameCounter < 150)
	{
		_backfaceCulling = true;
		_stateDescription = (L"Backface culling");
	}
	else if (_frameCounter >= 150 && _frameCounter < 200)
	{
		_polygonSorting = true;
		_stateDescription = (L"Polygon sorting");
	}
	else if (_frameCounter >= 200 && _frameCounter < 250)
	{
		_xRotationState = true;
		_stateDescription = (L"Rotation on X Axis");
	}
	else if (_frameCounter >= 250 && _frameCounter < 300)
	{
		_xRotationState = false;
		_yRotationState = true;
		_stateDescription = (L"Rotation on Y Axis");
	}
	else if (_frameCounter >= 300 && _frameCounter < 350)
	{
		_yRotationState = false;
		_zRotationState = true;
		_stateDescription = (L"Rotation on Z Axis");
	}
	else if (_frameCounter >= 350 && _frameCounter < 400)
	{
		_zRotationState = false;
		_scaleState = true;
		_stateDescription = (L"Scaling on XYZ Axis");
	}
	else if (_frameCounter >= 400 && _frameCounter < 450)
	{
		_scaleState = false;
		_translateState = true;
		_stateDescription = (L"Translating on XYZ Axis");
	}
	else if (_frameCounter >= 450 && _frameCounter < 500)
	{
		_translateState = false;
		_wireFrameState = false;
		_xyzRotationState = true;
		_gdiFlatShading = true;
		_ambientLighting.clear();
		_ambientLighting.push_back(AmbientLight(255, 255, 255));
		_stateDescription = (L"GDI Flat Shading");
	}
	else if (_frameCounter >= 500 && _frameCounter < 550)
	{
		_ambientLighting.clear();
		_ambientLighting.push_back(amblight);
		_stateDescription = (L"Ambient Lighting");
	}
	else if (_frameCounter >= 550 && _frameCounter < 600)
	{
		_ambientLighting.clear();
		_directionalLighting.clear();
		_directionalLighting.push_back(temp);
		_directionalLighting.push_back(temp2);
		_stateDescription = (L"Directional Lighting");
	}
	else if (_frameCounter >= 600 && _frameCounter < 650)
	{
		_directionalLighting.clear();
		_pointLighting.clear();
		_pointLighting.push_back(pointLight);
		_stateDescription = (L"Point Lighting");
	}
	else if (_frameCounter >= 650 && _frameCounter < 700)
	{
		_gdiFlatShading = false;
		_customFlatShading = true;
		_ambientLighting.clear();
		_directionalLighting.clear();
		_pointLighting.clear();
		_ambientLighting.push_back(amblight);
		_directionalLighting.push_back(temp);
		_directionalLighting.push_back(temp2);
		_pointLighting.push_back(pointLight);
		_stateDescription = (L"Set Pixel GDI");
	}
	else if (_frameCounter >= 700)
	{
		_customFlatShading = false;
		_gouraudShading = true;
		_stateDescription = (L"Gouraud Shading");
	}
	//Generates the aspect ratio of the window
	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();
	float aspectRatio = (float)width / (float)height;

	//Make updates to the model transformation.
	if (_xRotationState)
	{
		_radian = CalculateRadian(_degree++);
		transformMatrix = GenerateXRotationMatrix(_radian);
	}
	else if (_yRotationState)
	{
		_radian = CalculateRadian(_degree++);
		transformMatrix = GenerateYRotationMatrix(_radian);
	}
	else if (_zRotationState)
	{
		_radian = CalculateRadian(_degree++);
		transformMatrix = GenerateZRotationMatrix(_radian);
	}
	else if (_xyzRotationState)
	{
		_radian = CalculateRadian(_degree++);
		transformMatrix = GenerateYRotationMatrix(_radian) * GenerateXRotationMatrix(_radian) * GenerateZRotationMatrix(_radian);
	}
	else if (_scaleState)
	{
		_scale = _scale - 0.01f;
		transformMatrix = GenerateScaleMatrix(_scale, _scale, _scale);
	}
	else if (_translateState)
	{
		_translate = _translate + 1;
		transformMatrix = GenerateTranslateMatrix(_translate, _translate, _translate);
	}
	else
	{
		transformMatrix = GenerateScaleMatrix(1, 1, 1);
	}

	//Call GeneratePerspectiveMatrix to create the perspective matrix
	GeneratePerspectiveMatrix(1, aspectRatio);

	//Call GenerateViewMatrix to create the screen matrix
	GenerateViewMatrix(1, width, height);
}

void Rasteriser::Render(Bitmap &bitmap)
{		
	//INSERT CODE HERE FOR WHEN RENDERING

	//Apply the model (world) transform to the local vertices in the model.
	//To do this, call the ApplyTransformToLocalVertices method in the Model class 
	//passing it the model transform that you updated in the Update method.
	_model.ApplyTransformToLocalVertiecs(transformMatrix);
	
	//Sort all the polygons in the model so that those furthest away are rendered first.
	if (_polygonSorting)
	{
		_model.Sort();
	}

	//Calculate each polygon to check to see if it should be culled so that it is not rendered.
	if (_backfaceCulling)
	{
		_model.CalculateBackfaces(_camera.GetPosition());
	}
	
	if (_gdiFlatShading || _customFlatShading)
	{
		//Calculate the Ambient Lighting
		_model.CalculateAmbientLighting(_ambientLighting);
		
		//Calculate the directional Lighting
		_model.CalculatePointLighting(_pointLighting);

		//Calculate the point lighting
		_model.CalculateLightingDirectional(_directionalLighting);
	} else if (_gouraudShading)
	{
		//Calculate the normal vector of the list of vertices
		_model.CalculateVertexNormals();

		//Calculate the Ambient Lighting
		_model.CalculateVertexAmbientLighting(_ambientLighting);

		//Calculate the directional Lighting
		_model.CalculateVertexLightingDirectional(_directionalLighting);

		//Calculate the point lighting
		_model.CalculateVertexPointLighting(_pointLighting);
	}
	
	//Apply the viewing (camera) transform to the transformed vertices in the model.
	//To do this, call the ApplyTransformToTransformedVertices method in the Model class
	//passing it the Camera transform retrieved from the Camera object created in step 2 above).
	_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());

	//Apply the perspective transform to the transformed vertices in the model 
	//(using ApplyTransformToTransformedVertices).
	_model.ApplyTransformToTransformedVertices(perspectiveMatrix);

	//Dehomogenize the transformed vertices
	_model.dehemoginiseVerticies();

	//Apply the view (screen) transform to the transformed vertices in the model
	_model.ApplyTransformToTransformedVertices(viewMatrix);

	//Clear the bitmap for rendering!
	bitmap.Clear(RGB(0, 0, 0));

	//Draw the model
	if (_wireFrameState)
	{
		DrawWireFrame(bitmap);
	}
	else if (_gdiFlatShading)
	{
		DrawSolidFlat(bitmap);
	}
	else if (_customFlatShading)
	{
		MyDrawSolidFlat((bitmap.GetDC()));
	}
	else if (_gouraudShading)
	{
		DrawGouraud(bitmap.GetDC());
	}
	DrawString(bitmap.GetDC(), (wchar_t*)_stateDescription.c_str());
}

//A method for scaling a vertex
Matrix Rasteriser::GenerateScaleMatrix(float x, float y, float z)
{
	//Create a matrix for scaling
	Matrix scaleMatrix = { x, 0.0f, 0.0f, 0.0f,
						   0.0f, y, 0.0f, 0.0f,
						   0.0f, 0.0f, z, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f };

	return scaleMatrix;
}

//A method for translating a vertex
Matrix Rasteriser::GenerateTranslateMatrix(float x, float y, float z)
{
	//Create a matrix for translating
	Matrix translateMatrix = { 1.0f, 0.0f, 0.0f, x,
							   0.0f, 1.0f, 0.0f, y,
							   0.0f, 0.0f, 1.0f, z,
							   0.0f, 0.0f, 0.0f, 1.0f };

	return translateMatrix;
}

//A method for rotating a vertex around the x axis
Matrix Rasteriser::GenerateXRotationMatrix(float angle)
{
	//Create a matrix for rotating around the x axis
	Matrix xrotateMatrix = { 1.0f,       0.0f,        0.0f, 0.0f,
							0.0f, cos(angle), -sin(angle), 0.0f,
							0.0f, sin(angle),  cos(angle), 0.0f,
							0.0f,       0.0f,        0.0f, 1.0f };

	return xrotateMatrix;
}

//A method for rotating a vertex around the y axis
Matrix Rasteriser::GenerateYRotationMatrix(float angle)
{
	//Create a matrix for rotating around the y axis
	Matrix yrotateMatrix = { cos(angle), 0.0f, sin(angle), 0.0f,
								   0.0f, 1.0f,		 0.0f, 0.0f,
							-sin(angle), 0.0f, cos(angle), 0.0f,
								   0.0f, 0.0f,		 0.0f, 1.0f };

	return yrotateMatrix;
}

//A method for rotating a vertex around the z axis
Matrix Rasteriser::GenerateZRotationMatrix(float angle)
{
	//Create a matrix for rotating around the z axis
	Matrix zrotateMatrix = { cos(angle), -sin(angle), 0.0f, 0.0f,
							 sin(angle),  cos(angle), 0.0f, 0.0f,
								   0.0f,		0.0f, 1.0f, 0.0f,
								   0.0f,		0.0f, 0.0f, 1.0f };
	return  zrotateMatrix;
}

//A method for converting from degrees to radians
float Rasteriser::CalculateRadian(float degrees)
{
	if (degrees >= 180)
	{
		_degree = -180;
		degrees = _degree;
	}
	degrees = degrees * (4 * atanf(1)) / 180;
	return degrees;
}

//A method for creating the perspective matrix
void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	perspectiveMatrix = { (d / aspectRatio), 0.0f, 0.0f, 0.0f,
									   0.0f,    d, 0.0f, 0.0f,
									   0.0f, 0.0f,    d, 0.0f,
									   0.0f, 0.0f, 1.0f, 0.0f };
}

//A method for creating the view matrix
void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	viewMatrix = { (width / 2.0f),			   0.0f,	   0.0f,  (width / 2.0f),
							 0.0f, -(height / 2.0f),	   0.0f, (height / 2.0f),
							 0.0f,			   0.0f, (d / 2.0f),	  (d / 2.0f),
							 0.0f,			   0.0f,	   0.0f,		   1.0f };
}

//A method for drawing a wireframe model
void Rasteriser::DrawWireFrame(Bitmap & bitmap)
{
	//Get the list of polygons and vertices
	std::vector<Polygon3D> polygons = _model.GetPolygons();
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	
	//Get the size of the list of polygons 
	int count = _model.GetPolygonCount();
	
	//Create a pen
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);
	
	//For each polygon in the list of polygons
	for (int i = 0; i < count; i++)
	{
		//If the polygon hasn't been set to be culled
		if (polygons[i].GetCulling() != true)
		{
			//Draw the polygon to the screen
			MoveToEx(bitmap.GetDC(), (int)vertices[polygons[i].GetIndex(0)].GetX(), (int)vertices[polygons[i].GetIndex(0)].GetY(), NULL);
			LineTo(bitmap.GetDC(), (int)vertices[polygons[i].GetIndex(1)].GetX(), (int)vertices[polygons[i].GetIndex(1)].GetY());
			LineTo(bitmap.GetDC(), (int)vertices[polygons[i].GetIndex(2)].GetX(), (int)vertices[polygons[i].GetIndex(2)].GetY());
			LineTo(bitmap.GetDC(), (int)vertices[polygons[i].GetIndex(0)].GetX(), (int)vertices[polygons[i].GetIndex(0)].GetY());
		}
	}
	//Delete the pen
	DeleteObject(hPen);
}

//A method for drawing a solid model
void Rasteriser::DrawSolidFlat(Bitmap & bitmap)
{
	//Get the list of polygons and vertices
	std::vector<Polygon3D> polygons = _model.GetPolygons();
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	
	//Get the bitmap
	HDC hdc = bitmap.GetDC();
	
	//Create an array of points
	POINT pointList[3];
	const POINT * points = pointList;

	//Declare a pen and brush
	HBRUSH hBrush;
	HPEN hPen;

	//Get the size of the list of polygons
	int count = _model.GetPolygonCount();

	//For each polygon in the list of polygons
	for (int i = 0; i < count; i++)
	{
		//If the polygon hasn't been set to be culled
		if (polygons[i].GetCulling() == false)
		{
			//Create a brush and pen that has the color stored in the polygon
			hBrush = CreateSolidBrush(polygons[i].GetColor());
			hPen = CreatePen(PS_SOLID, 1, polygons[i].GetColor());
			
			//Select the brush and pen
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			
			//Set the list of points to the vertices used to make up the polygon
			for (int j = 0; j < 3; j++)
			{	
				pointList[j] = { POINT{ (long)vertices[polygons[i].GetIndex(j)].GetX(), (long)vertices[polygons[i].GetIndex(j)].GetY() } };
			}
			
			//Draw the polygon to the screen
			Polygon(hdc, pointList, 3);

			//Delete the pen and brush
			DeleteObject(hBrush);
			DeleteObject(hPen);
		}
	}
}

//A method for drawing a flat model using set pixel
void Rasteriser::MyDrawSolidFlat(HDC hDc)
{
	//Get the list of polygons and vertices
	std::vector<Polygon3D> polygons = _model.GetPolygons();
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	std::vector<FPoint> polygonVertices;

	//Get the size of the list of polygons
	int count = _model.GetPolygonCount();
	
	//Declare a color reference
	COLORREF polyColor;

	//For each polygon in the list of polygons
	for (int i = 0; i < count; i++)
	{
		//If the polygon hasn't been set to be culled
		if (polygons[i].GetCulling() == false)
		{
			//Set the polyColor to the colour stored in the polygon
			polyColor = polygons[i].GetColor();

			//Set the list of points to the vertices used to make up the polygon
			for (int j = 0; j < 3; j++)
			{
				polygonVertices.push_back(FPoint{ vertices[polygons[i].GetIndex(j)].GetX(), vertices[polygons[i].GetIndex(j)].GetY() });
			}

			//Sort the array of vertices in ascending order
			std::sort(polygonVertices.begin(), polygonVertices.end(), [](FPoint & lhs, FPoint & rhs) { return lhs.GetY() < rhs.GetY(); });
			
			//Check to see if the polygon is flat bottomed, flat topped or neither
			if (polygonVertices[1].GetY() == polygonVertices[2].GetY())
			{
				//Fill in the polygon
				FillPolygonFlatBottom(polygonVertices[0], polygonVertices[1], polygonVertices[2], polyColor, hDc);
			}
			else if (polygonVertices[0].GetY() == polygonVertices[1].GetY())
			{
				//Fill in the polygon
				FIllPolygonFlatTop(polygonVertices[0], polygonVertices[1], polygonVertices[2], polyColor, hDc);
			}
			else
			{
				//Create a temporary vertex for splitting the polygon
				FPoint tempVert = FPoint{ (polygonVertices[0].GetX() + ((polygonVertices[1].GetY() - polygonVertices[0].GetY()) /(polygonVertices[2].GetY() - polygonVertices[0].GetY())) * (polygonVertices[2].GetX() - polygonVertices[0].GetX())), polygonVertices[1].GetY() };
				
				//Fill in the polygons
				FillPolygonFlatBottom(polygonVertices[0], polygonVertices[1], tempVert, polyColor, hDc);
				FIllPolygonFlatTop(polygonVertices[1], tempVert, polygonVertices[2], polyColor, hDc);
			}
			//Clear the polygonVertices list
			polygonVertices.clear();
		}
	}
}

//A method for filling in flat bottomed polygons
void Rasteriser::FillPolygonFlatBottom(FPoint &v1, FPoint &v2, FPoint &v3, COLORREF &color, HDC &hDc)
{
	// Check to see if vertcies is the wrong way around
	if (v2.GetX() > v3.GetX())
	{
		FPoint temp = v2;
		v2 = v3;
		v3 = temp;
	}

	//Get the x and y values of the vertices
	float v1x = v1.GetX();
	float v1y = v1.GetY();
	float v2x = v2.GetX();
	float v2y = v2.GetY();
	float v3x = v3.GetX();
	float v3y = v3.GetY();

	//Calculate gradient for sides of triangle
	float lhg = (v2x - v1x) / (v2y - v1y);
	float rhg = (v3x - v1x) / (v3y - v1y);

	//Set start and end positions of the triangle
	float startXPos = v1x;
	float endXPos = v1x + 0.5f;
	int startYPos = (int)v1y;
	int endYPos = (int)v3y;

	//For each row in the triangle
	for (int currentYPos = (int)startYPos; currentYPos < (int)endYPos; currentYPos++)
	{
		//For each pixel in the row
		for (int currentXPos = (int)startXPos; currentXPos <= ceil(endXPos); currentXPos++)
		{
			//Set pixel to selected color
			SetPixel(hDc, currentXPos, currentYPos, color);
		}

		//increment down the line
		startXPos = startXPos + lhg;
		endXPos = endXPos + rhg;
	}
}

//A method for filling in flat topped polygons
void Rasteriser::FIllPolygonFlatTop(FPoint &v1, FPoint &v2, FPoint &v3, COLORREF &color, HDC &hDc)
{
	// Check to see if vertcies is the wrong way around
	if (v1.GetX() > v2.GetX())
	{
		FPoint temp = v1;
		v1 = v2;
		v2 = temp;
	}
	
	//Get the x and y values of the vertices
	float v1x = v1.GetX();
	float v1y = v1.GetY();
	float v2x = v2.GetX();
	float v2y = v2.GetY();
	float v3x = v3.GetX();
	float v3y = v3.GetY();

	//Calculate gradient for sides of triangle
	float lhg = (v3x - v1x) / (v3y - v1y);
	float rhg = (v3x - v2x) / (v3y - v2y);

	//Set start and end positions of the triangle
	float startXPos = v1x;
	float endXPos = v2x;
	int startYPos = (int)v1y;
	int endYPos = (int)v3y;
	
	//For each row in the triangle
	for (int currentYPos = startYPos; currentYPos < endYPos; currentYPos++)
	{
		//For each pixel in the row
		for (int currentXPos = (int)startXPos; currentXPos <= (int)endXPos; currentXPos++)
		{
			//Set pixel to selected color
			SetPixel(hDc, currentXPos, currentYPos, color);
		}

		//increment down the line
		startXPos = startXPos + lhg;
		endXPos = endXPos + rhg;
	}
}

//A method for drawing a gouraud shaded model using set pixel
void Rasteriser::DrawGouraud(HDC hDc)
{
	//Get the list of polygons and vertices
	std::vector<Polygon3D> polygons = _model.GetPolygons();
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	std::vector<Vertex> polyVerts;

	//Get the size of the list of polygons
	int count = _model.GetPolygonCount();

	//For each polygon in the list of polygons
	for (int i = 0; i < count; i++)
	{
		//If the polygon hasn't been set to be culled
		if (polygons[i].GetCulling() == false)
		{
			//Set the list of points to the vertices used to make up the polygon
			for (int j = 0; j < 3; j++)
			{
				polyVerts.push_back(vertices[polygons[i].GetIndex(j)]);
			}

			//Sort the array of vertices in ascending order
			std::sort(polyVerts.begin(), polyVerts.end(), [](Vertex & lhs, Vertex & rhs) { return lhs.GetY() < rhs.GetY(); });

			//Check to see if the polygon is flat bottomed, flat topped or neither
			if (polyVerts[1].GetY() == polyVerts[2].GetY())
			{
				//Fill in the polygon
				GouraudFillPolygonFlatBottom(polyVerts[0], polyVerts[1], polyVerts[2], hDc);
			}
			else if (polyVerts[0].GetY() == polyVerts[1].GetY())
			{
				//Fill in the polygon
				GouraudFillPolygonFlatTop(polyVerts[0], polyVerts[1], polyVerts[2], hDc);
			}
			else
			{
				//Create a temporary vertex for splitting the polygon
				Vertex tempVert = { (polyVerts[0].GetX() + ((polyVerts[1].GetY() - polyVerts[0].GetY()) / (polyVerts[2].GetY() - polyVerts[0].GetY())) * (polyVerts[2].GetX() - polyVerts[0].GetX())), polyVerts[1].GetY() };
				
				//Calculate an interpolated color value for the temporary vertex
				float tempR = (polyVerts[0].GetColor().GetR() + ((polyVerts[1].GetY() - polyVerts[0].GetY()) / (polyVerts[2].GetY() - polyVerts[0].GetY())) * (polyVerts[2].GetColor().GetR() - polyVerts[0].GetColor().GetR()));
				float tempG = (polyVerts[0].GetColor().GetG() + ((polyVerts[1].GetY() - polyVerts[0].GetY()) / (polyVerts[2].GetY() - polyVerts[0].GetY())) * (polyVerts[2].GetColor().GetG() - polyVerts[0].GetColor().GetG()));
				float tempB = (polyVerts[0].GetColor().GetB() + ((polyVerts[1].GetY() - polyVerts[0].GetY()) / (polyVerts[2].GetY() - polyVerts[0].GetY())) * (polyVerts[2].GetColor().GetB() - polyVerts[0].GetColor().GetB()));
				tempVert.SetColor(POLYCOLOR((int)tempR, (int)tempG, (int)tempB));
				
				//Fill in the polygons
				GouraudFillPolygonFlatBottom(polyVerts[0], polyVerts[1], tempVert, hDc);
				GouraudFillPolygonFlatTop(polyVerts[1], tempVert, polyVerts[2], hDc);
			}
			//Clear the polygonVertices list
			polyVerts.clear();
		}
	}
}

void Rasteriser::GouraudFillPolygonFlatBottom(Vertex & v1, Vertex & v2, Vertex & v3, HDC & hDc)
{
	// Check to see if vertcies is the wrong way around
	if (v2.GetX() > v3.GetX())
	{
		Vertex temp = v2;
		v2 = v3;
		v3 = temp;
	}

	//Get the x and y values of the vertices
	float v1x = v1.GetX();
	float v1y = v1.GetY();
	float v2x = v2.GetX();
	float v2y = v2.GetY();
	float v3x = v3.GetX();
	float v3y = v3.GetY();

	//Get the color stored in the vertices
	POLYCOLOR c1 = v1.GetColor();
	POLYCOLOR c2 = v2.GetColor();
	POLYCOLOR c3 = v3.GetColor();

	//Calculate the colour gradient for sides of the triangles
	float v2v1Diff = v2y - v1y;
	float colorSlopeRed1 = (c2.GetR() - c1.GetR()) / v2v1Diff;
	float colorSlopeGreen1 = (c2.GetG() - c1.GetG()) / v2v1Diff;
	float colorSlopeBlue1 = (c2.GetB() - c1.GetB()) / v2v1Diff;

	float v3v1Diff = v3y - v1y;
	float colorSlopeRed2 = (c3.GetR() - c1.GetR()) / v3v1Diff;
	float colorSlopeGreen2 = (c3.GetG() - c1.GetG()) / v3v1Diff;
	float colorSlopeBlue2 = (c3.GetB() - c1.GetB()) / v3v1Diff;

	//Get the RGB values stored in the vertices
	float startRed = (float)c1.GetR();
	float startGreen = (float)c1.GetG();
	float startBlue = (float)c1.GetB();
	float endRed = (float)c1.GetR();
	float endGreen = (float)c1.GetG();
	float endBlue = (float)c1.GetB();
	
	//Calculate gradient for sides of triangle
	float lhg = (v2x - v1x) / (v2y - v1y);
	float rhg = (v3x - v1x) / (v3y - v1y);

	//Set start and end positions of the triangle
	float startXPos = v1x;
	float endXPos = v1x + 0.5f;
	int startYPos = (int)v1y;
	int endYPos = (int)v3y;

	//For each row in the triangle
	for (int currentYPos = (int)startYPos; currentYPos < (int)endYPos; currentYPos++)
	{
		//For each pixel in the row
		for (int currentXPos = (int)startXPos; currentXPos <= ceil(endXPos); currentXPos++)
		{
			//Calculate the colour of the pixel
			float i = (currentXPos - startXPos) / (endXPos - startXPos);
			float r = ((1 - i) * startRed + i * endRed);
			float g = ((1 - i) * startGreen + i * endGreen);
			float b = ((1 - i) * startBlue + i * endBlue);

			//Set pixel to selected color
			SetPixel(hDc, currentXPos, currentYPos, RGB(r, g, b));
		}

		//increment down the line
		startXPos = startXPos + lhg;
		endXPos = endXPos + rhg;

		startRed = startRed + colorSlopeRed1;
		startGreen = startGreen + colorSlopeGreen1;
		startBlue = startBlue + colorSlopeBlue1;

		endRed = endRed + colorSlopeRed2;
		endGreen = endGreen + colorSlopeGreen2;
		endBlue = endBlue + colorSlopeBlue2;
	}
}

void Rasteriser::GouraudFillPolygonFlatTop(Vertex & v1, Vertex & v2, Vertex & v3, HDC & hDc)
{
	// Check to see if vertcies is the wrong way around
	if (v1.GetX() > v2.GetX())
	{
		Vertex temp = v1;
		v1 = v2;
		v2 = temp;
	}

	//Get the x and y values of the vertices
	float v1x = v1.GetX();
	float v1y = v1.GetY();
	float v2x = v2.GetX();
	float v2y = v2.GetY();
	float v3x = v3.GetX();
	float v3y = v3.GetY();

	//Get the color stored in the vertices
	POLYCOLOR c1 = v1.GetColor();
	POLYCOLOR c2 = v2.GetColor();
	POLYCOLOR c3 = v3.GetColor();

	//Calculate the colour gradient for sides of the triangles
	float v3v1Diff = v3y - v1y;
	float colorSlopeRed1 = (c3.GetR() - c1.GetR()) / v3v1Diff;
	float colorSlopeGreen1 = (c3.GetG() - c1.GetG()) / v3v1Diff;
	float colorSlopeBlue1 = (c3.GetB() - c1.GetB()) / v3v1Diff;

	float v3v2Diff = v3y - v2y;
	float colorSlopeRed2 = (c3.GetR() - c2.GetR()) / v3v2Diff;
	float colorSlopeGreen2 = (c3.GetG() - c2.GetG()) / v3v2Diff;
	float colorSlopeBlue2 = (c3.GetB() - c2.GetB()) / v3v2Diff;

	//Get the RGB values stored in the vertices
	float startRed = (float)c1.GetR();
	float startGreen = (float)c1.GetG();
	float startBlue = (float)c1.GetB();
	float endRed = (float)c1.GetR();
	float endGreen = (float)c1.GetG();
	float endBlue = (float)c1.GetB();

	//Calculate gradient for sides of triangle
	float lhg = (v3x - v1x) / (v3y - v1y);
	float rhg = (v3x - v2x) / (v3y - v2y);

	//Set start and end positions of the triangle
	float startXPos = v1x;
	float endXPos = v2x;
	int startYPos = (int)v1y;
	int endYPos = (int)v3y;

	//For each row in the triangle
	for (int currentYPos = (int)startYPos; currentYPos < (int)endYPos; currentYPos++)
	{
		//For each pixel in the row
		for (int currentXPos = (int)startXPos; currentXPos <= ceil(endXPos); currentXPos++)
		{
			//Calculate the colour of the pixel
			float i = (currentXPos - startXPos) / (endXPos - startXPos);
			float r = (int)((1 - i) * startRed + i * endRed);
			float g = (int)((1 - i) * startGreen + i * endGreen);
			float b = (int)((1 - i) * startBlue + i * endBlue);

			//Set pixel to selected color
			SetPixel(hDc, currentXPos, currentYPos, RGB(ceil(r), ceil(g), ceil(b)));
		}

		//Increment down the line
		startXPos = startXPos + lhg;
		endXPos = endXPos + rhg;

		startRed = startRed + colorSlopeRed1;
		startGreen = startGreen + colorSlopeGreen1;
		startBlue = startBlue + colorSlopeBlue1;

		endRed = endRed + colorSlopeRed2;
		endGreen = endGreen + colorSlopeGreen2;
		endBlue = endBlue + colorSlopeBlue2;
	}
}

void Rasteriser::DrawString(HDC hDc, LPCTSTR text)
{
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hDc, hFont))
	{
		SetTextColor(hDc, RGB(255, 255, 255));
		SetBkColor(hDc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hDc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hDc, hOldFont);
	}
	DeleteObject(hFont);
}
