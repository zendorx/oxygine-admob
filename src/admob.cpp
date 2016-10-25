#include "admob.h"

#ifdef __ANDROID__
    #include "android/AndroidAdmob.h"
#elif __APPLE__
    #include <TargetConditionals.h>
    #include "ios/iosAdmob.h"
#else
    #include "sim/AdmobSimulator.h"
#endif



#define ADMOB_EXT_ENABLED 1

namespace admob
{

    spEventDispatcher _dispatcher;

    spEventDispatcher dispatcher()
    {
        return _dispatcher;
    }

    void init()
    {
#if !ADMOB_EXT_ENABLED
        return;
#endif

        log::messageln("admob::init");

        OX_ASSERT(_dispatcher == 0);
        _dispatcher = new EventDispatcher;

#ifdef __ANDROID__
        jniAdmobInit();
#elif TARGET_OS_IPHONE

#else
        admobSimulatorInit();
#endif
        log::messageln("admob::init done");
    }

    void free()
    {
#if !ADMOB_EXT_ENABLED
        return;
#endif

        log::messageln("admob::free");

        OX_ASSERT(_dispatcher);

#ifdef __ANDROID__
        jniAdmobFree();
#endif
        _dispatcher->removeAllEventListeners();
        _dispatcher = 0;
        log::messageln("admob::free done");
    }

    void load()
    {
#if !ADMOB_EXT_ENABLED
        return;
#endif


#ifdef __ANDROID__
        jniAdmobLoad();
#endif
    }

    void show()
    {
#if !ADMOB_EXT_ENABLED
        return;
#endif

        
#ifdef __ANDROID__
        jniAdmobShow();
#endif
    }

    bool isLoaded()
    {
#if !ADMOB_EXT_ENABLED
        return false;
#endif
        

#ifdef __ANDROID__
        return  jniAdmobIsLoaded();
#endif
        return false;
    }

    
    namespace internal
    {

        void onChange(int newStatus)
        {
            OnChangeEvent ev(newStatus);
            _dispatcher->dispatchEvent(&ev);
        }
    }
}

