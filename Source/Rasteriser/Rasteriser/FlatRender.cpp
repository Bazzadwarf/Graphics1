#include "FlatRender.h"

void FlatRender::MyDrawSolidFlat(Model & model, HDC hDc)
{
	std::vector<Polygon3D> polygons = model.GetPolygons();
	std::vector<Vertex> vertices = model.GetTransformedVertices();
	std::vector<FPoint> polygonVertices;

	int count = model.GetPolygonCount();
	COLORREF polyColor;

	for (size_t i = 0; i < count; i++)
	{
		if (polygons[i].GetCulling() == false)
		{
			polyColor = polygons[i].GetColor();
			for (size_t j = 0; j < 3; j++)
			{
				polygonVertices.push_back(FPoint{ vertices[polygons[i].GetIndex(j)].GetX(), vertices[polygons[i].GetIndex(j)].GetY() });
			}
			std::sort(polygonVertices.begin(), polygonVertices.end(), [](FPoint & lhs, FPoint & rhs) { return lhs.GetY() < rhs.GetY(); });

			if (polygonVertices[1]._y == polygonVertices[2].GetY())
			{
				FillPolygonFlatBottom(polygonVertices[0], polygonVertices[1], polygonVertices[2], polyColor, hDc);
			}
			else if (polygonVertices[0].GetY() == polygonVertices[1].GetY())
			{
				FIllPolygonFlatTop(polygonVertices[0], polygonVertices[1], polygonVertices[2], polyColor, hDc);
			}
			else
			{
				FPoint tempVert = FPoint{ (polygonVertices[0].GetX() + ((polygonVertices[1].GetY() - polygonVertices[0].GetY()) / (polygonVertices[2].GetY() - polygonVertices[0].GetY())) * (polygonVertices[2].GetX() - polygonVertices[0].GetX())), polygonVertices[1].GetY() };
				FillPolygonFlatBottom(polygonVertices[0], polygonVertices[1], tempVert, polyColor, hDc);
				FIllPolygonFlatTop(polygonVertices[1], tempVert, polygonVertices[2], polyColor, hDc);
			}
			polygonVertices.clear();
		}
	}
}

void FlatRender::FillPolygonFlatBottom(FPoint & v1, FPoint & v2, FPoint & v3, COLORREF & color, HDC & hDc)
{

}
