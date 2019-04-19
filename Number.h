#pragma once
class Number
{
public:
	Texture* pPngFont = nullptr;

	float w;
	float h;
public:
	Number();
	virtual ~Number();

	void Draw(int number, Vector3 pos, float fontScale, float widthDepth);
};

