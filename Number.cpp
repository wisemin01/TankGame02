#include "DXUT.h"
#include "Number.h"


Number::Number()
	: pPngFont(nullptr)
{
	pPngFont = ADDTEXTURE("NUMBER", "./RS/UI/NUMBER/(%d).png", 10);

	w = pPngFont->GetTexture(0)->tInfo.Width;
	h = pPngFont->GetTexture(0)->tInfo.Height;
}


Number::~Number()
{
}

void Number::Draw(int number, Vector3 pos, float fontScale, float widthDepth)
{
	string numStr = to_string(number);

	for (int i = 0; i < numStr.size(); i++)
	{
		int numCnt = (int)numStr[i] - (int)'0';

		RESOURCE.ApplyWorldTransform(pos
			+ Vector3(i * (w + widthDepth) * fontScale, 0, 0),
			Vector3(fontScale, fontScale, 0), 0);

		RESOURCE.Draw(pPngFont->GetTexture(numCnt), Vector3(w / 2.f, h / 2.f, 0.f), 0xffffffff);
	}
}
