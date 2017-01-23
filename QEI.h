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

class QEI {
    public:
        QEI(QEIConfig_t opts, int ppr);

        int getPulses(void);

        float getRevolutions(void);

        int getInstantVelocity(void);

        int getVelocity(void);

        void setFilterDelay(int delay);

    private:
        int pulses;
        int revolutions;
        int velocity;
        int ivelocity;
};
#endif
