#include "LPC17XX.h"

#include "cmsis.h"
#include "pinmap.h"

#include "QEI_api.h"


static const PinMap PinMap_QEI[] = {        // Might be no needed
    {P1_20, (int)LPC_QEI_BASE, 1},
    {P1_23, (int)LPC_QEI_BASE, 1},
    {P1_24, (int)LPC_QEI_BASE, 1},
    {NC,    NC,     0}
};

void qei_init(QEIConfig_t opts) {
    LPC_SC->PCONP |= (1 << 18);             // Enable power for the QEI module

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

    NVIC_EnableIRQ(QEI_IRQn);               //Enable QEI IRQ
}

void qei_init_index(void) {
    pinmap_pinout(P1_24, PinMap_QEI);
    pin_function(P1_24, 1);                 // Enable index counting
    pin_mode(P1_24, PullDown);
}

// QEIPOS
void qei_get_pulses(int *pulses) {
    *pulses = LPC_QEI->QEIPOS;              // Read position register
}

// QEIMAXPOS
void qei_set_max_pulses(int max_pos) {
    LPC_QEI->QEIMAXPOS = max_pos;           // Set maximum position range
}

// INXCNT
void qei_get_index_count(int *count) {
    *count = LPC_QEI->INXCNT;               // Get index counts
}

// QEIVEL
void qei_get_velocity(int *velocity) {
    *velocity = LPC_QEI->QEIVEL;            // Read velocity register
}

// QEICAP
void qei_get_velocity_capture(int *velocity_capture) {
    *velocity_capture = LPC_QEI->QEICAP;    // Read velocity capture register
}

// FILTER
void qei_set_filter(int filter) {
    LPC_QEI->FILTER = filter;               // Set filter value
}

// QEICONF options
void qei_set_direction(bool invert) {
    if (invert) {
        LPC_QEI->QEICONF |= (1 << 0);       // Invert encoder direction
    } else {
        LPC_QEI->QEICONF &= ~(1 << 0);
    }
}

void qei_set_invert_index(bool invert) {
    if (invert) {
        LPC_QEI->QEICONF |= (1 << 3);       // Invert index counter
    } else {
        LPC_QEI->QEICONF &= ~(1 << 3);
    }
}

void qei_set_signal_mode(bool signal_mode) {
    if (signal_mode) {
        LPC_QEI->QEICONF |= (1 << 1);   // Set signal mode to DIR/STEP
    } else {
        LPC_QEI->QEICONF &= ~(1 << 1);  // Set signal mode to quadrature encoder (PhA/PhB)
    }
}

void qei_set_capture_mode(bool capture_mode) {
    if (capture_mode) {
        LPC_QEI->QEICONF |= (1 << 2);   // Count 4 edges (PhA + PhB)
    } else {
        LPC_QEI->QEICONF &= ~(1 << 2);  // Only count PhA edges
    }
}

// QEISTAT
uint8_t qei_get_direction(void) {
    return (uint8_t)(LPC_QEI->QEISTAT & 0x01);
}
