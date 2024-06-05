#pragma once

namespace Fluffy
{
	template <typename T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}

		virtual ~Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

	protected:
		Singleton() = default;
	};

	template <typename T>
	class ComponentSingleton
	{
	public:
		inline static T* GetInstance() { return m_pInstance; }

		virtual ~ComponentSingleton()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		ComponentSingleton(const ComponentSingleton& other) = delete;
		ComponentSingleton(ComponentSingleton&& other) = delete;
		ComponentSingleton& operator=(const ComponentSingleton& other) = delete;
		ComponentSingleton& operator=(ComponentSingleton&& other) = delete;

	protected:
		inline static T* m_pInstance{ nullptr };

		ComponentSingleton() = default;
		virtual void RegisterInstance() = 0;
	};
}
