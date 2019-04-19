#pragma once

struct Frame
{
	int cur, end, start;
	float delay, frameSkip;

	bool operator()(float dt)
	{
		// Frame Update
		frameSkip += dt;

		if (frameSkip >= delay)
		{
			if (++cur > end)
				cur = start;
			
			frameSkip = 0;

			return true;
		}
		return false;
	}

	void operator()(int start, int end, float delay)
	{
		cur = Frame::start = start;
		Frame::end = end;
		Frame::delay = delay;
		frameSkip = 0;
	}
};