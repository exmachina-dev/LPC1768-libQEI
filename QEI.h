#ifndef QEI_H_
#define QEI_H_

#include "mbed.h"

typedef enum {
    QEI_INDEX       = 0x01;
    QEI_VELOCITY    = 0x02;
    QEI_POSITION    = 0x04;
    QEI_2XCOUNT     = 0x08;
    QEI_SIGNAL_MODE = 0x0F;
    // QEI_SIGNAL_MODE = 0x0F;
} QEIConfig_t;

class QEI {
    public:
        QEI(QEIConfig_t opts);

        int getPulses(void);

        void setFilterDelay(uint16_t delay);

        static const PinMap PinMap_QEI[] = {
            {P1_20, QEI0_A, 1},
            {P1_23, QEI0_B, 1},
            {P1_24, QEI0_I, 1},
            {NC,    NC,     0}
        }

    private:
        void qei_set_signal_mode(bool signal_mode);
        void qei_set_capture_mode(bool capture_mode);

        int32_t pulses;
        int32_t revolutions;
}
#endif
