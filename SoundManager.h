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

	// 음악 객체 생성
	void Create(RsKey key, const wstring& path);

	// 재생
	void Play(RsKey key, BOOL loop);
	// 메모리 공유 버퍼 재생 (효과음 재생에 사용, 끊기지 않음)
	void DuplicatePlay(RsKey key, BOOL loop);
	// 멈춤
	void Stop(RsKey key);

	// 맵 클리어
	void Clear();
};

#define SOUND SoundManager::GetInstance()