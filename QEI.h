#ifndef QEI_H_
#define QEI_H_

#ifndef TARGET_LPC176X
#error This library is only compatible with the LPC1768
#endif

#include "QEI_config.h"

class QEI {
    public:
        QEI(QEIConfig_t opts);

        void setTimeInterval(int time);

        int getPulses(void);

        int getRevolutions(void);

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
