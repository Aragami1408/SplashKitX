#include <core/skx_logger.h>
#include <core/skx_asserts.h>

int main(void) {
    SKX_FATAL("A test message: %f\n", 3.14f);
    SKX_ERROR("A test message: %f\n", 3.14f);
    SKX_WARN("A test message: %f\n", 3.14f);
    SKX_INFO("A test message: %f\n", 3.14f);
    SKX_DEBUG("A test message: %f\n", 3.14f);
    SKX_TRACE("A test message: %f\n", 3.14f);

    return 0;
}
