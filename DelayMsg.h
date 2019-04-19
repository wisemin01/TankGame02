#pragma once

#include <set>

class DelayMsg
{
public:
	float fFrameSkip;
	float fDelay;

	function<void()> pFunc;
public:
	DelayMsg();
	virtual ~DelayMsg();

	inline void PlusDt(float dt) { fFrameSkip += dt; }
public:
	static std::set<DelayMsg*> msgContainer;
	static void MessageLoop(float dt);
	static void ReleaseMeseages();
	static void Send(float delay, function<void()> func);

	inline bool operator <(const DelayMsg* other)
		const {
		return (fDelay - fFrameSkip) < (other->fDelay - other->fFrameSkip);
	}
};

