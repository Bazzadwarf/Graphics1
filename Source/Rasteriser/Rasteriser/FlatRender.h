#pragma once
#include "Bitmap.h"
#include "FPoint.h"
#include "POLYCOLOR.h"
#include "Model.h"

class FlatRender : public FPoint
{
	void MyDrawSolidFlat(Model &model, HDC hDc);
	void FillPolygonFlatBottom(FPoint &v1, FPoint &v2, FPoint &v3, COLORREF &color, HDC &hDc);
	void FIllPolygonFlatTop(FPoint &v1, FPoint &v2, FPoint &v3, COLORREF &color, HDC &hDc);
};