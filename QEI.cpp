#include "LPC17XX.h"

#if MBED_TARGET != "LPC1768"
#error This library is only compatible with the LPC1768
#endif

#include "cmsis.h"
#include "pinmap.h"

QEI::QEI(QEIConfig_t opts) {
    LPC_SC->PCONP |= (1 << 18);     // Enable power for the QEI module
    LPC_SC->PCONP |= (1 << 12);

    // set PCLK of QEI to CCLK/1 (1:0)
    LPC_SC->PCLKSEL1 &= ~(0x3 << 0);
    LPC_SC->PCLKSEL1 |= (0x1 << 0);

    pinmap_pinout(0, PinMap_QEI);
    pinmap_pinout(1, PinMap_QEI);

    pin_function(0, 0x1);
    pin_function(1, 0x1);

    if (opts & QEI_INDEX) {
        pinmap_pinout(2, PinMap_QEI);
        pin_function(2, 0x1);       // Enable index counting
    }

    LPC_QEI->QEIIES
    NVIC_SetVector(QEI_IRQn, (uint32_t) &can_irq_n);
    NVIC_EnableIRQ(QEI_IRQn);

    if (opts & QEI_SIGNAL_MODE)
        qei_set_signal_mode(true);     // Set encoder mode to DIR/STEP mode (default A & B)

    if (opts & QEI_4XCOUNT)
        qei_set_capture_mode(true);    // Count A & B edges (more resolution but less range)
} 

void qei_set_signal_mode(bool signal_mode) {
}

void qei_set_capture_mode(bool capture_mode) {
}
