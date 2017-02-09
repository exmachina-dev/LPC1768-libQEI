#ifndef QEI_H_
#define QEI_H_

#ifndef TARGET_LPC176X
#error This library is only compatible with the LPC1768
#endif

#include "QEI_config.h"

class QEI {
    public:
        QEI(int opts);

        void setVelocityFrequency(int frequency);

        void setPPR(int ppr);
        void setMaxPosition(int pulses);
        void setFilterFrequency(int filter_freq);
        void setLinearFactor(float linear_factor);

        int getPulses(void);

        int getRevolutions(void);

        int getInstantVelocity(void);

        float getVelocity(void);
        float getSpeed(void);

        void setFilterDelay(int delay);

    private:
        int velocity_frequency;
        float pulses_per_rev;
        float linear_factor;
        int pulses;
        int revolutions;
        int velocity;
        int ivelocity;
};
#endif
