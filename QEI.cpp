#include "QEI.h"
#include "LPC17XX.h"

#include "QEI_api.h"

QEI::QEI(int opts) {
    qei_init();

    linear_factor = 1.0;
    position_offset = 0.0;

    if (opts & QEI_INDEX) {
        qei_init_index();
    }

    if (opts & QEI_SIGNAL_MODE)
        qei_set_signal_mode(true);      // Set encoder mode to DIR/STEP mode (default A & B)
    else
        qei_set_signal_mode(false);      // Set encoder mode to DIR/STEP mode (default A & B)

    qei_set_direction(opts & QEI_INVERT);

    if (opts & QEI_4XCOUNT)
        qei_set_capture_mode(true);     // Count A & B edges (more resolution but less range)
    else
        qei_set_capture_mode(false);     // Count A & B edges (less resolution but more range)

    qei_set_max_pulses(0xFFFFFFFF);     // Allow QEI to count up to maximum range
    qei_set_filter(1000000);                  // Digital filter (debounce). In order
                                        // to get counted, the new state must be
                                        // maintain n clock ticks. (0 to bypass)
} 

void QEI::setVelocityFrequency(int time) {
    velocity_frequency = time;
    qei_set_velocity_frequency(time);
}

void QEI::setPPR(int ppr) {
    pulses_per_rev = (float)ppr;
}

void QEI::setMaxPosition(int pulses) {
    qei_set_max_pulses(pulses);
}

void QEI::setFilterFrequency(int filter_freq) {
    qei_set_filter(filter_freq);
}

void QEI::setLinearFactor(float lfactor) {
    linear_factor = lfactor;
}

void QEI::setHome(float offset) {
    qei_reset_position(true);
    qei_reset_index(true);

    position_offset = offset;
}

int QEI::getPulses(void) {
    qei_get_pulses(&pulses);
    if (pulses_per_rev > 0) {
        qei_get_index_count(&revolutions);
        return pulses + (pulses_per_rev * revolutions);
    } else {
        return pulses;
    }
}

int QEI::getRevolutions(void) {
    qei_get_index_count(&revolutions);
    return revolutions;
}

int QEI::getInstantVelocity(void) {
    qei_get_velocity(&ivelocity);
    return ivelocity;
}


float QEI::getVelocity(void) {
    qei_get_velocity_capture(&velocity);
    if (pulses_per_rev > 0) {
        return (float)((velocity * velocity_frequency) / pulses_per_rev);
    } else {
        return (float)(velocity * velocity_frequency);
    }
}

float QEI::getSpeed(void) {
    return getVelocity() * linear_factor;
}

float QEI::getPosition(void) {
    return position_offset + (float)(getPulses() / pulses_per_rev) * linear_factor;
}

