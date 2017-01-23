#include "QEI.h"
#include "LPC17XX.h"

#include "QEI_api.h"

QEI::QEI(QEIConfig_t opts) {
    qei_init(opts);

    if (opts & QEI_INDEX) {
        qei_init_index();
    }

    if (opts & QEI_SIGNAL_MODE)
        qei_set_signal_mode(true);      // Set encoder mode to DIR/STEP mode (default A & B)
    else
        qei_set_signal_mode(false);      // Set encoder mode to DIR/STEP mode (default A & B)

    if (opts & QEI_4XCOUNT)
        qei_set_capture_mode(true);     // Count A & B edges (more resolution but less range)
    else
        qei_set_capture_mode(false);     // Count A & B edges (more resolution but less range)

    qei_set_max_pulses(0xFFFFFFFF);     // Allow QEI to count up to maximum range
    qei_set_filter(3);                  // Digital filter (debounce). In order
                                        // to get counted, the new state must be
                                        // maintain n clock ticks. (0 to bypass)
} 

int QEI::getPulses(void) {
    qei_get_pulses(&pulses);
    return pulses;
}

int QEI::getVelocity(void) {
    qei_get_velocity_capture(&velocity);
    return velocity;
}

int QEI::getInstantVelocity(void) {
    qei_get_velocity(&ivelocity);
    return ivelocity;
}

