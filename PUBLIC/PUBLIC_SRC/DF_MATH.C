#include "PUBLIC_INC/DF_MATH.H"

#define PI2    6.283185307179586
//filter  y(n)=a*x+(1-a)*y(n-1)  a=Fc*2*pi*TS/(Fc*2*pi*TS+1)
#define LPF_COEFF(Fc, Ts)  ((PI2*(Fc)*(Ts))/(PI2*(Fc)*(Ts) + 1))


/*void Notch_Init(void){
    stNotchCoff.f32Sin1OmegT = 0.06975647;  //Sin(2*pi*f/fs)
    stNotchCoff.f32Cos1OmegT = 0.997564050;  //Cos(2*pi*f/fs); 500Hz-> 0.997564050
    stNotchCoff.f32Deep      = 0.06975647;
    stNotchCoff.f32Width     = 0.025;
}*/
