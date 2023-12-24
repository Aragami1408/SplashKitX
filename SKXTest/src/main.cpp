#include <core/skx_logger.h>
#include <core/skx_asserts.h>

#include <platform/skx_platform.h>

int main(void) {
    SKX_FATAL("A test message: %f\n", 3.14f);
    SKX_ERROR("A test message: %f\n", 3.14f);
    SKX_WARN("A test message: %f\n", 3.14f);
    SKX_INFO("A test message: %f\n", 3.14f);
    SKX_DEBUG("A test message: %f\n", 3.14f);
    SKX_TRACE("A test message: %f\n", 3.14f);

    SKXPlatformState state;
    if (state.startup("SplashKitX Test", 100, 100, 1280, 720)) {
        while (TRUE) {
            state.pump_messages();
        }
    }
    state.shutdown();

    return 0;
}
