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
    /*JNIEXPORT void JNICALL Java_org_oxygine_admob_AdmobAdapter_YOUR_FUNC_NAME(JNIEnv* env, jobject obj, jstring json_data, jboolean error)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadDispatcher().postCallback([ = ]()
        {
            //call internal function there from src/admob/admob.h
            admob::internal::callItFromNativeCallback();
        });
    }*/


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
