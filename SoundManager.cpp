#include "DXUT.h"
#include "SoundManager.h"

#pragma comment(lib, "dsound.lib")

SoundManager::SoundManager()
	: pSoundManager(nullptr)
{
	pSoundManager = new CSoundManager;

	pSoundManager->Initialize(DXUTGetHWND(), 2);
	pSoundManager->SetPrimaryBufferFormat(2, 22050, 16);
}


SoundManager::~SoundManager()
{
	Clear();
	SAFE_DELETE(pSoundManager);
}

void SoundManager::Create(RsKey key, const wstring & path)
{
	auto find = mapSound.find(key);

	if (find == mapSound.end()) {
		CSound* pSound;
		pSoundManager->Create(&pSound, (LPWSTR)path.c_str(), 0, GUID_NULL);

		mapSound.insert(make_pair(key, pSound));
	}
}

void SoundManager::Play(RsKey key, BOOL loop)
{
	mapSound[key]->Play(0, loop);
}

void SoundManager::DuplicatePlay(RsKey key, BOOL loop)
{
	LPDIRECTSOUNDBUFFER lpDS;

	pSoundManager->GetDirectSound()->DuplicateSoundBuffer(mapSound[key]->GetBuffer(0), &lpDS);

	lpDS->SetCurrentPosition(0);
	lpDS->Play(0, 0, loop);
}

void SoundManager::Stop(RsKey key)
{
	mapSound[key]->Stop();
}

void SoundManager::Clear()
{
	for (auto iter : mapSound)
	{
		SAFE_DELETE(iter.second);
	}
	mapSound.clear();
}
