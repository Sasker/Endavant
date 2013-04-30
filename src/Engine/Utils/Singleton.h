#ifndef SINGLETON_H_
#define SINGLETON_H_

template <typename Type>
class CSingleton
{
public:
	static Type& get_instance()
	{
	    static Type m_instance;
	    return m_instance;
	}

protected:
	CSingleton() { }
	~CSingleton() { }

private:
	CSingleton(CSingleton const&) { }
	void operator=(CSingleton const&) { }
};

#endif
