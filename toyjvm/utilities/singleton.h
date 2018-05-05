//
// Created by cyhone on 18-4-22.
//

#ifndef TOYJVM_SINGLETON_H
#define TOYJVM_SINGLETON_H
namespace jvm {
    template<typename T>
    class Singleton {
    public:
        static T *instance();

        static void destroy();

        Singleton() = delete;

        ~Singleton() = delete;

        Singleton(const Singleton &) = delete;

        Singleton &operator=(Singleton const &) = delete;

    protected:
        static T *instance_;
    };

    template<typename T>
    T *Singleton<T>::instance_ = nullptr;

    template<typename T>
    T *Singleton<T>::instance()
    {
        if (nullptr == instance_) {
            instance_ = new T();
        }
        return instance_;
    }

    template<typename T>
    void Singleton<T>::destroy()
    {
        delete instance_;
        instance_ = nullptr;
    }

}
#endif //TOYJVM_SINGLETON_H
