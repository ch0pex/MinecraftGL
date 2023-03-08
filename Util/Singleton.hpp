#pragma once
#include <cstdlib>
#include <utility>


template<class Derived>
class Singleton
{
public:
	template<typename...Args>
	static inline Derived* getInstance(Args &&...args) {
		static Derived* instance = createInstance(std::forward<Args>(args)...);
		return instance;
	}
private:

	static Derived* instance;

	template<typename...Args>
	static inline Derived* createInstance(Args &&...args)
	{
		if (Singleton::getInstance() == nullptr) {
			void* data = static_cast<void*>(getData());
			new (data) Derived(std::forward<Args>(args)...);
			Singleton::instance = reinterpret_cast<Derived*>(data);
			std::atexit(&Singleton::destroyInstance);
		}
		return Singleton::instance;
	}

	static inline void destroyInstance()
	{
		reinterpret_cast<Derived*>(getData())->~Derived();
	}

	static inline unsigned char* getData()
	{
		static unsigned char data[sizeof(Derived)];
		return data;
	}

protected:
	Singleton() = default;
	Singleton(Singleton const&) = default;
	Singleton(Singleton&&) = default;

	Singleton& operator=(Singleton const&) = default;
	Singleton& operator=(Singleton&&) = default;

	virtual ~Singleton() = default;


};

template <class Derived>
Derived* Singleton<Derived>::instance = nullptr;