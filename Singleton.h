#pragma once

template <class T>
class Singleton
{
private:
	static T* instance;
public:
	Singleton() {}
	virtual ~Singleton() {}

	static T& GetInstance()
	{
		if (!instance)
			instance = new T;

		return *instance;
	}

	static void ReleaseInstance()
	{
		if (instance) {
			delete instance;
			instance = nullptr;
		}
	}
};

template <typename T>
T* Singleton<T>::instance = nullptr;