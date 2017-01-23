#ifndef QEI_API_H_
#define QEI_API_H_

#ifndef TARGET_LPC176X
#error This library is only compatible with the LPC1768
#endif

#include "pinmap.h"
#include "QEI_config.h"

void qei_init(QEIConfig_t opts);
void qei_init_index(void);

void qei_set_velocity_frequency(int frequency);

void qei_get_pulses(int *pulses);
void qei_set_max_pulses(int max_pos);
void qei_get_index_count(int *count);
void qei_get_velocity(int *velocity);
void qei_get_velocity_capture(int *velocity_capture);
void qei_set_filter(int filter_frequency);
void qei_set_direction(bool invert);
void qei_set_invert_index(bool invert);
void qei_set_signal_mode(bool signal_mode);
void qei_set_capture_mode(bool capture_mode);
uint8_t qei_get_direction(void);

#endif
