#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "mbed.h"

class Encoder{
public:
    Encoder(PinName phaseA, PinName phaseB, PinName button);
    virtual ~Encoder();

    void Init();

    bool GetButtonState();
    int32_t GetEncoderChange();

private:
    typedef enum{
        Phase_0,
        Phase_1,
        Phase_2,
        Phase_3
    } Phase;

    Phase _current_phase;

    Phase GetPhase(int A, int B);
    void HandleEncoderChange();

    bool _state;
    int32_t _count;

    InterruptIn _phaseA;
    InterruptIn _phaseB;

    InterruptIn _button;

};



#endif // _ENCODER_H_