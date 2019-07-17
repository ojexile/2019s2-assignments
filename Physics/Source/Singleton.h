#pragma once
template<class T>

class Singleton
{
protected:
	static T* m_Instance;
	Singleton() {};
	virtual ~Singleton() {};
public:

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
		m_Instance = nullptr;
	}
};
template <class T>
T * Singleton<T>::m_Instance = nullptr;