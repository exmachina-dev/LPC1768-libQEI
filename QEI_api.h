#ifndef QEI_H_
#define QEI_H_

#ifndef TARGET_LPC176X
#error This library is only compatible with the LPC1768
#endif

#include "pinmap.h"

typedef enum {
    QEI_NONE        = 0x00,
    QEI_INDEX       = 0x01,
    QEI_VELOCITY    = 0x02,
    QEI_POSITION    = 0x04,
    QEI_4XCOUNT     = 0x08,
    QEI_SIGNAL_MODE = 0x0F,
} QEIConfig_t;

void qei_init(QEIConfig_t opts);

void qei_get_pulses(int *pulses);
void qei_set_max_pulses(int max_pos);
void qei_get_index_count(int *count);
void qei_get_velocity(int *velocity);
void qei_get_velocity_capture(int *velocity_capture);
void qei_set_filter(int filter);
void qei_set_direction(bool invert);
void qei_set_invert_index(bool invert);
void qei_set_signal_mode(bool signal_mode);
void qei_set_capture_mode(bool capture_mode);
uint8_t qei_get_direction(void);
