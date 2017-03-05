#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace ATL {

template<typename T>
class Singleton
{
public:
    inline static T* getCurrent()
    {
        return _instance;
    }
    
protected:
    Singleton()
    {
        _instance = (T*)this;
    }
    
    static T* _instance;
};

template<typename T>
T* Singleton<T>::_instance;

} // ATL

#endif /* SINGLETON_H_ */