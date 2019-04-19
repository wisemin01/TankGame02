#pragma once
#include "Singleton.h"
#include "SDKsound.h"

class SoundManager :
	public Singleton<SoundManager>
{
public:
	CSoundManager * pSoundManager;

	map<string, CSound*> mapSound;
public:
	SoundManager();
	virtual ~SoundManager();

	// ���� ��ü ����
	void Create(RsKey key, const wstring& path);

	// ���
	void Play(RsKey key, BOOL loop);
	// �޸� ���� ���� ��� (ȿ���� ����� ���, ������ ����)
	void DuplicatePlay(RsKey key, BOOL loop);
	// ����
	void Stop(RsKey key);

	// �� Ŭ����
	void Clear();
};

#define SOUND SoundManager::GetInstance()