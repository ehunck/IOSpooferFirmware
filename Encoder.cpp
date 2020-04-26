#include "Encoder.h"

Encoder::Encoder(PinName phaseA, PinName phaseB, PinName button) :
    _phaseA(phaseA),
    _phaseB(phaseB),
    _button(button),
    _state(false),
    _count(0),
    _current_phase(Phase_0)
{

}

Encoder::~Encoder()
{

}

void Encoder::Init()
{
    _current_phase = GetPhase(_phaseA.read(), _phaseB.read());

    _phaseA.rise(callback(this, &Encoder::HandleEncoderChange));
    _phaseA.fall(callback(this, &Encoder::HandleEncoderChange));
    _phaseB.rise(callback(this, &Encoder::HandleEncoderChange));
    _phaseB.fall(callback(this, &Encoder::HandleEncoderChange));


}

bool Encoder::GetButtonState()
{
    return (_button.read() == 1);
}

int32_t Encoder::GetEncoderChange()
{
    const int32_t diff_count = _count;
    _count = 0;
    return diff_count;
}

void Encoder::HandleEncoderChange()
{
    Phase new_phase = GetPhase( _phaseA, _phaseB);

    switch(_current_phase)
    {
        case Phase_0:
        {
            if(new_phase == Phase_1)
            {
                _count ++;
            }
            else if(new_phase == Phase_3)
            {
                _count --;
            }
            break;
        }
        case Phase_1:
        {
            if(new_phase == Phase_2)
            {
                _count ++;
            }
            else if(new_phase == Phase_0)
            {
                _count --;
            }
            break;
        }
        case Phase_2:
        {
            if(new_phase == Phase_3)
            {
                _count ++;
            }
            else if(new_phase == Phase_1)
            {
                _count --;
            }
            break;
        }
        case Phase_3:
        {
            if(new_phase == Phase_0)
            {
                _count ++;
            }
            else if(new_phase == Phase_2)
            {
                _count --;
            }
            break;
        }
    }

    new_phase = _current_phase;
}

Encoder::Phase Encoder::GetPhase(int A, int B)
{
    if( A == 0 && B == 0 )
    {
        return Phase_0;
    }
    else if( A == 1 && B == 0 )
    {
        return Phase_1;
    }
    else if( A == 1 && B == 1 ) 
    {
        return Phase_2;
    }
    else if( A == 0 && B == 1 )
    {
        return Phase_3;
    }
    else
    {
        return Phase_0;
    }
}
