#include <jni.h>
#include <string>
#include <unistd.h>
#include <android/log.h>

#include<stdio.h>//头文件
#include <arpa/inet.h>
#include <codecvt>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <locale>
#include <malloc.h>
#include <math.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#define LOG_TAG "GetPIDJNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)




extern "C" JNIEXPORT jstring JNICALL
Java_com_example_lesson3_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_lesson3_AIDLService_nativeGetUid(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeGetUid()
    LOGI("登录成功");

    return getuid();
}


//获取进程pid函数
int get_pid_by_package_name(const char *packageName) {

    int id = -1;
    DIR *dir;
    FILE *fp;
    char filename[64];
    char cmdline[64];
    struct dirent *entry;
    dir = opendir("/proc");
    while ((entry = readdir(dir)) != NULL)
    {
        id = atoi(entry->d_name);
        if (id != 0)
        {
            sprintf(filename, "/proc/%d/cmdline", id);
            LOGI("目录名: %s", filename);

            fp = fopen(filename, "r");
            if (fp)
            {
                fgets(cmdline, sizeof(cmdline), fp);
                fclose(fp);
                if (strcmp(packageName, cmdline) == 0)
                {
                    return id;
                }
            }
        }
    }
    closedir(dir);
    return -1;
}

//将java字符串转为c字符串
//char *Jstring2string(JNIEnv *env, jstring jstr) {
//    char *rtn = NULL;
//    jclass clsstring = env->FindClass("java/lang/String");
//    jstring strencode = env->NewStringUTF("GB2312");
//    jmethodID mid = env->GetMethodID(clsstring, "getBytes",
//                                     "(Ljava/lang/String;)[B");
//    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
//    jsize alen = env->GetArrayLength(barr);
//    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
//    if (alen > 0) {
//        rtn = (char *) malloc(alen + 1);
//        memcpy(rtn, ba, alen);
//        rtn[alen] = 0;
//    }
//    env->ReleaseByteArrayElements(barr, ba, 0);
//    return rtn;
//}
//将java字符串转为c字符串
char *Jstring2string(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    // 查找 java.lang.String 类
    jclass clsstring = env->FindClass("java/lang/String");

    // 获取字符串的编码格式
    jstring charsetName = env->NewStringUTF("UTF-8"); // 默认使用 UTF-8 编码格式
    // 获取 getBytes 方法的 ID
    jmethodID getBytesMethodID = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    // 调用 getBytes 方法获取字节数组
    jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, getBytesMethodID, charsetName);
                                      //这个函数的第一个参数是需要调用方法的 Java 对象，
                                      // 第二个参数是需要调用的方法的 ID，
                                      // 后面的参数是要传递给方法的参数。


    // 获取字节数组的长度
    jsize alen = env->GetArrayLength(barr);
    // 获取字节数组的指针                            JNI_FALSE表示不复制字节数组的数据，而是直接返回指向数组数据的指针。
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = '\0'; // 添加字符串终止符
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}



//对应java中的getpid方法
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_lesson3_AIDLService_nataveHHH(JNIEnv *env, jobject clazz, jstring PackageName){
    LOGI("原始包名: %s", PackageName);

    const char *target_package_name = Jstring2string(env,PackageName);  // 字符串转换
    LOGI("应用包名: %s", target_package_name);

    int pid = get_pid_by_package_name(target_package_name);
    LOGI("查找的pid为:: %d", pid);


    //下面是使用syscall进行写入内存
//        struct iovec local2,remote2;
//        int writedata=999999;//修改为999999
//        local2.iov_base=&writedata;
//        local2.iov_len=8;
//        remote2.iov_base=(void *)0xAFCDEE10;//要修改的数值所在的地址
//        remote2.iov_len=8;
//
//        long int res_write = syscall(__NR_process_vm_writev,pid,&local2,1,&remote2,1,0);


//修改后的

    return pid;
}