#include "DXUT.h"
#include "DelayMsg.h"

std::set<DelayMsg*> DelayMsg::msgContainer;

DelayMsg::DelayMsg()
{
	float fFrameSkip = 0;
	float fDelay = 0;
}


DelayMsg::~DelayMsg()
{
}

void DelayMsg::MessageLoop(float dt)
{
	for (auto iter = msgContainer.begin(); iter != msgContainer.end(); iter++)
	{
		DelayMsg* msg = *iter;

		msg->PlusDt(dt);

		if (msg->fFrameSkip >= msg->fDelay) {

			msg->pFunc();

			SAFE_DELETE(msg);
			msgContainer.erase(iter);
			return;
		}
	}
}

void DelayMsg::ReleaseMeseages()
{
	for (auto iter : msgContainer)
	{
		SAFE_DELETE(iter);
	}
	msgContainer.clear();
}

void DelayMsg::Send(float delay, function<void()> func)
{
	DelayMsg* msg = new DelayMsg;

	msg->fDelay = delay;
	msg->fFrameSkip = 0;
	msg->pFunc = func;

	msgContainer.insert(msg);
}
