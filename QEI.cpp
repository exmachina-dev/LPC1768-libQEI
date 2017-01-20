#include "QEI.h"
#include "LPC17XX.h"

#include "cmsis.h"
#include "pinmap.h"

static const PinMap PinMap_QEI[] = {    // Might be no needed
    {P1_20, (int)LPC_QEI_BASE, 1},
    {P1_23, (int)LPC_QEI_BASE, 1},
    {P1_24, (int)LPC_QEI_BASE, 1},
    {NC,    NC,     0}
};

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


    if (opts & QEI_INDEX) {
        pinmap_pinout(P1_24, PinMap_QEI);
        pin_function(P1_24, 1);         // Enable index counting
        pin_mode(P1_24, PullDown);
    }

    NVIC_EnableIRQ(QEI_IRQn);

    if (opts & QEI_SIGNAL_MODE)
        qei_set_signal_mode(true);      // Set encoder mode to DIR/STEP mode (default A & B)

    if (opts & QEI_4XCOUNT)
        qei_set_capture_mode(true);     // Count A & B edges (more resolution but less range)

    LPC_QEI->QEIMAXPOS = 0xFFFFFFFF;    // Allow QEI to count up to maximum range
    LPC_QEI->FILTER = 3;                // Digital filter (debounce). In order
                                        // to get counted, the new state must be
                                        // maintain n clock ticks. (0 to bypass)

    pulses_per_rev = (float)ppr;
} 

int QEI::getPulses(void) {
    qei_get_pulses();
    return pulses;
}

float QEI::getRevolutions(void) {
    qei_get_revolutions();
    return revolutions;
}

void QEI::qei_get_pulses(void) {
    pulses = LPC_QEI->QEIPOS;           // Read position register
}

void QEI::qei_get_revolutions(void) {
    qei_get_pulses();
    revolutions = (float)(pulses / pulses_per_rev);
}

void QEI::qei_set_direction(bool invert) {
    if (invert) {
        LPC_QEI->QEICONF |= (1 << 0);   // Invert encoder direction
    } else {
        LPC_QEI->QEICONF &= ~(1 << 0);
    }
}

void QEI::qei_set_invert_index(bool invert) {
    if (invert) {
        LPC_QEI->QEICONF |= (1 << 3);   // Invert revolution counter
    } else {
        LPC_QEI->QEICONF &= ~(1 << 3);
    }
}

void QEI::qei_set_signal_mode(bool signal_mode) {
    if (signal_mode) {
        LPC_QEI->QEICONF |= (1 << 1);   // Set signal mode to DIR/STEP
    } else {
        LPC_QEI->QEICONF &= ~(1 << 1);  // Set signal mode to quadrature encoder
    }
}

void QEI::qei_set_capture_mode(bool capture_mode) {
    if (capture_mode) {
        LPC_QEI->QEICONF |= (1 << 2);   // Count 4 edges (PhA + PhB)
    } else {
        LPC_QEI->QEICONF &= ~(1 << 2);  // Only count PhA edges
    }
}
