#include "QEI.h"
#include "LPC17XX.h"

#include "QEI_api.h"

<<<<<<< HEAD
QEI::QEI(QEIConfig_t opts, int ppr) {
    LPC_SC->PCONP |= (1 << 18);         // Enable power for the QEI module

    // set PCLK of QEI to CCLK/1 (1:0)
    LPC_SC->PCLKSEL1 &= ~(0b11);
    LPC_SC->PCLKSEL1 |= (0b10);

    pinmap_pinout(P1_20, PinMap_QEI);
    pinmap_pinout(P1_23, PinMap_QEI);

    // set PhA and PhB pins to QEI mode
    pin_function(P1_20, 1);
    pin_function(P1_23, 1);
    pin_mode(P1_20, PullDown);
    pin_mode(P1_23, PullDown);

=======
QEI::QEI(QEIConfig_t opts) {
    qei_init(opts);
>>>>>>> 2f1147ca5a6cf27097a7fde6955619ee52ba6b2c

    if (opts & QEI_INDEX) {
        qei_init_index();
    }

    if (opts & QEI_SIGNAL_MODE)
        qei_set_signal_mode(true);      // Set encoder mode to DIR/STEP mode (default A & B)

    if (opts & QEI_4XCOUNT)
        qei_set_capture_mode(true);     // Count A & B edges (more resolution but less range)

    qei_set_max_pulses(0xFFFFFFFF);     // Allow QEI to count up to maximum range
    qei_set_filter(3);                  // Digital filter (debounce). In order
                                        // to get counted, the new state must be
                                        // maintain n clock ticks. (0 to bypass)

    pulses_per_rev = (float)ppr;
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

