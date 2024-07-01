#define LOG_TAG "HELLO_TAG"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Hello.h"

using aidl::android::hardware::hello::Hello;
using std::string_literals::operator""s;

void logd(std::string msg) {
    std::cout << msg << std::endl;
    ALOGD("%s", msg.c_str());
}

void loge(std::string msg) {
    std::cout << msg << std::endl;
    ALOGE("%s", msg.c_str());
}

int main() {
    // Enable vndbinder to allow vendor-to-venfor binder call
    android::ProcessState::initWithDriver("/dev/vndbinder");

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();

    std::shared_ptr<Hello> hello = ndk::SharedRefBase::make<Hello>();
    const std::string name = Hello::descriptor + "/default"s;

    if (hello != nullptr) {
        if(AServiceManager_addService(hello->asBinder().get(), name.c_str()) != STATUS_OK) {
            loge("Failed to register IHello service");
            return -1;
        }
    } else {
        loge("Failed to get IHello instance");
        return -1;
    }

    logd("IHello service starts to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}
