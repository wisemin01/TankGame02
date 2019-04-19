#pragma once


class Maingame
{
public:
	Maingame();
	virtual ~Maingame();

	void Init();
	void Update(float dt);
	void Render();
	void Destroy();

	void OnLost();
	void OnReset();

	void Cheet();
};

