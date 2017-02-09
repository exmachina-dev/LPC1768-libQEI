#ifndef QEI_CONFIG_H_
#define QEI_CONFIG_H_

enum QEIConfig_e {
    QEI_NONE        = 0x00,
    QEI_INDEX       = 0x01,
    QEI_VELOCITY    = 0x02,
    QEI_INVERT      = 0x04,
    QEI_POSITION    = 0x08,
    QEI_4XCOUNT     = 0x10,
    QEI_SIGNAL_MODE = 0x20,
};

typedef QEIConfig_e QEIConfig_t;

#endif
