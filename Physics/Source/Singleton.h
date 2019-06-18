#pragma once
template<class T>

class Singleton
{
	static T* m_Instance;
public:
	Singleton() {};
	~Singleton() {};

	static T* GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new T;
		return m_Instance;
	};

	static void DeleteInstance()
	{
		if (m_Instance)
			delete m_Instance;
	}
};
template <class T>
T * Singleton<T>::m_Instance = nullptr;