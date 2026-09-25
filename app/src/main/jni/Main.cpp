#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/MonoString.h"
#include "Menu/Register.h"
#include "AutoHook/AutoHook.h"
#include "Includes/Strings.h"
//@liyaharuno
//@CheatCodeRevo
//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

#include "Includes/Macros.h"

//---👇🏻PUT YOUR BOOL&FLOAT HERE👇🏻---

bool mod1 = false;










//---👇🏻PUT YOUR HOOKS HERE 👇🏻---


bool (*old_mod1)(void *instance);
bool new_mod1(void *instance) {
    if (instance != NULL && mod1) {
        return 99;
    }
    return old_mod1(instance);
}






ProcMap il2cppMap;
void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));
    
    do {
        il2cppMap = KittyMemory::getLibraryMap("libil2cpp.so");
         sleep(5); // Don't Increase
    } while (!il2cppMap.isValid());


/*void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    do {
        sleep(25);
    } while (!isLibraryLoaded("libil2cpp.so"));

    do {
        sleep(5);
    } while (!isLibraryLoaded("MyLibName.so"));
	
	*/
    
    
    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);


//👇🏻---IF YOUR HOOK 64BIT THEN PUT HERE👇🏻---
#if defined(__aarch64__)



//👇🏻---IF YOUR HOOK 32BIT THEN PUT HERE👇🏻---
#else

    auto Playerclassname = new LoadClass("namespace", OBFUSCATE("classname"));
    DWORD mod1 = Playerclassname->GetMethodOffsetByName(OBFUSCATE("offsetname"), 0);
    MSHookFunction((void *)("libil2cpp.so", mod1), (void *) new_mod1, (void **) &old_mod1);

    
    LOGI(OBFUSCATE("Done"));
#endif


    

    return NULL;
}



jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
    //👇🏻---YOUR MENU---👇🏻
            OBFUSCATE("Category_Liya Hack_cpp"),
            OBFUSCATE("1_Toggle_Hack 1_cpp"),
            
    };

    //MODDED BY LIYA HACK
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");



    switch (featNum) {
case 1: mod1 = boolean; break;

        
        

    }
}


__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;

    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    static const JNINativeMethod menuMethods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };

    if (Register(env, "com/android/support/Menu", menuMethods, sizeof(menuMethods) / sizeof(JNINativeMethod)) != 0)
        return JNI_ERR;

    static const JNINativeMethod prefMethods[] = {
            { OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };

    if (Register(env, "com/android/support/Preferences",
                 prefMethods, sizeof(prefMethods) / sizeof(JNINativeMethod)) != 0)
        return JNI_ERR;

    static const JNINativeMethod mainMethods[] = {
            { OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };

    if (Register(env, "com/android/support/Main", mainMethods, sizeof(mainMethods) / sizeof(JNINativeMethod)) != 0)
        return JNI_ERR;

    return JNI_VERSION_1_6;
}
