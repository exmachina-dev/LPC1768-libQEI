#include "LPC17XX.h"

#include "cmsis.h"
#include "pinmap.h"

#include "QEI_api.h"

#define QEI_PCLK_DIV        (8)

static const PinMap PinMap_QEI[] = {        // Might be no needed
    {P1_20, (int)LPC_QEI_BASE, 1},
    {P1_23, (int)LPC_QEI_BASE, 1},
    {P1_24, (int)LPC_QEI_BASE, 1},
    {NC,    NC,     0}
};

int qei_get_pclk_reg(uint8_t pclk_div) {
    switch (pclk_div) {
        case 1:
            return 0b01;
            break;
        case 2:
            return 0b10;
            break;
        case 4:
            return 0b00;
            break;
        case 8:
            return 0b11;
            break;
        default:
            return 0b00;
    }
}

void qei_init(void) {
    LPC_SC->PCONP |= (1 << 18);             // Enable power for the QEI module

    // set PCLK of QEI to CCLK/1 (1:0)
    LPC_SC->PCLKSEL1 &= ~(0b11);
    LPC_SC->PCLKSEL1 |= (qei_get_pclk_reg(QEI_PCLK_DIV));

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

void qei_set_velocity_frequency(int frequency) {
    uint32_t tick_number;

    tick_number = SystemCoreClock / (frequency * QEI_PCLK_DIV);
    LPC_QEI->QEILOAD = tick_number;
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
void qei_set_filter(int filter_frequency) {
    uint32_t sample_number;

    sample_number = SystemCoreClock / (filter_frequency * QEI_PCLK_DIV);
    LPC_QEI->FILTER = sample_number;        // Set filter value
}

// QEICON control
void qei_reset_position(bool reset) {
    if (reset)
        LPC_QEI->QEICON |= (1 << 0);       // Reset position register
}

void qei_reset_position_on_index(bool reset) {
    if (reset)
        LPC_QEI->QEICON |= (1 << 1);       // Reset position when index pulse occurs
}

void qei_reset_velocity(bool reset) {
    if (reset)
        LPC_QEI->QEICON |= (1 << 2);       // Reset velocity register
}

void qei_reset_index(bool reset) {
    if (reset)
        LPC_QEI->QEICON |= (1 << 3);       // Reset index register
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
