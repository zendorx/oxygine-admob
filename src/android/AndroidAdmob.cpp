#include <jni.h>
#include <android/log.h>
#include <assert.h>
#include "core/oxygine.h"
#include "core/Object.h"
#include "core/ThreadMessages.h"
#include "core/oxygine.h"
#include "core/android/jniHelper.h"
#include "core/android/jniUtils.h"
#include "json/json.h"
#include "src/admob.h"


using namespace oxygine;

jclass _jAdmobClass = 0;
jobject _jAdmobObject = 0;

bool isAdmobEnabled()
{
    return _jAdmobClass && _jAdmobObject;
}


extern "C"
{
    JNIEXPORT void JNICALL Java_org_oxygine_admob_AdmobAdapter_onNativeChanged(JNIEnv* env, jobject obj, int newStatus)
    {
        core::getMainThreadDispatcher().postCallback([ = ]()
        {
            admob::internal::onChange(newStatus);
        });
    }
}


void jniAdmobInit()
{
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        JNI_NOT_NULL(env);

        _jAdmobClass = env->FindClass("org/oxygine/admob/AdmobAdapter");
        JNI_NOT_NULL(_jAdmobClass);

        _jAdmobClass = (jclass) env->NewGlobalRef(_jAdmobClass);
        JNI_NOT_NULL(_jAdmobClass);

        _jAdmobObject = env->NewGlobalRef(jniFindExtension(env, _jAdmobClass));
        JNI_NOT_NULL(_jAdmobObject);
    }
    catch (const notFound&)
    {
        log::error("jniAdmobInit failed, class/member not found");
    }
}

void jniAdmobFree()
{
    if (!isAdmobEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        env->DeleteGlobalRef(_jAdmobClass);
        _jAdmobClass = 0;

        env->DeleteGlobalRef(_jAdmobObject);
        _jAdmobObject = 0;
    }
    catch (const notFound&)
    {

    }
}

void jniAdmobShow()
{
    if (!isAdmobEnabled())
        return;
            
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        
        jmethodID jmethod = env->GetMethodID(_jAdmobClass, "show", "()V");
        JNI_NOT_NULL(jmethod);
        
        env->CallBooleanMethod(_jAdmobObject, jmethod);
    }
    catch (const notFound&)
    {
        log::error("jniAdmobLoad failed, class/member not found");
    }
}


void jniAdmobLoad()
{
    if (!isAdmobEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        
        jmethodID jmethod = env->GetMethodID(_jAdmobClass, "load", "()V");
        JNI_NOT_NULL(jmethod);
        
        env->CallBooleanMethod(_jAdmobObject, jmethod);
    }
    catch (const notFound&)
    {
        log::error("jniAdmobLoad failed, class/member not found");
    }
}


bool jniAdmobIsLoaded()
{
    if (!isAdmobEnabled())
        return false;

    bool result = false;
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        
        jmethodID jisMethod = env->GetMethodID(_jAdmobClass, "isLoaded", "()Z");
        JNI_NOT_NULL(jisMethod);
        
        jboolean jb = env->CallBooleanMethod(_jAdmobObject, jisMethod);
        result = (bool) jb;

    }
    catch (const notFound&)
    {
        log::error("jniAdmobIsLoaded failed, class/member not found");
    }

    return result;
}

/*
bool jniAdmobSomeBoolFunc()
    {
    if (!isAdmobEnabled())
        return false;

    bool result = false;
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        //jstring jappLinkUrl = env->NewStringUTF(appLinkUrl.c_str()); //to jstring example
        jmethodID jisMethod = env->GetMethodID(_jAdmobClass, "FUNC_NAME_JAVA", "()Z");
        JNI_NOT_NULL(jisMethod);
        //string data = jniGetString(env, (jstring) obj); //string example
        jboolean jb = env->CallBooleanMethod(_jAdmobObject, jisMethod);
        result = (bool) jb;

    }
    catch (const notFound&)
    {
        log::error("jniAdmobSomeBoolFunc failed, class/member not found");
    }

    return result;
}
*/
