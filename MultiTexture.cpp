#include "DXUT.h"
#include "MultiTexture.h"

#include "SingleTexture.h"

MultiTexture::MultiTexture()
{
}


MultiTexture::~MultiTexture()
{
	for (auto iter : vecTexture)
		SAFE_DELETE(iter);
}

void MultiTexture::AddTexture(RsKey path, int count)
{
	char sz[256] = "";

	vecTexture.reserve(sizeof(SingleTexture) * count);

	for (int i = 1; i <= count; i++)
	{
		sprintf(sz, path.c_str(), i);

		SingleTexture* tex = new SingleTexture;

		tex->AddTexture(sz);

		vecTexture.push_back(tex);
	}
}

Texture * MultiTexture::GetTexture(int count)
{
	if (count == -1)
		return this;
	else {
		assert(count < Size(), "TEXTURE GET FAILED - OUT OF RANGE");
		return vecTexture[count];
	}
}
