#define LOG_TAG "HELLO_TAG"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "Hello.h"

namespace aidl {
namespace android {
namespace hardware {
namespace hello {

#define FILE_PATH "/data/vendor/chibihate/hello.txt"

//String getChars();
ndk::ScopedAStatus Hello::getChars(std::string* _aidl_return) {
    std::ifstream hello_file;
    hello_file.open(FILE_PATH);
    if(hello_file.good()) {
        std::string line;
        hello_file >> line;
        std::string reverse_line(line.rbegin(),line.rend());
        ALOGD("Hello service: getChars: %s", reverse_line.c_str());
        *_aidl_return =  reverse_line;
    } else {
        ALOGE("getChars: can not open /data/vendor/chibihate/hello.txt");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}

//void putChars(in String msg);
ndk::ScopedAStatus Hello::putChars(const std::string& in_msg) {
    std::ofstream hello_file;
    hello_file.open (FILE_PATH);
    if(hello_file.good()) {
        hello_file << in_msg;
        ALOGD("Hello service: putChars: %s", in_msg.c_str());
    } else {
        ALOGE("putChars: can not open /data/vendor/chibihate/hello.txt");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}
}  // namespace hello
}  // namespace hardware
}  // namespace android
}  // namespace aidl
