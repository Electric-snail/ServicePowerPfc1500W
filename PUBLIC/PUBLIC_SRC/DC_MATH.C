/*
 * DC_MATH.C
 *
 *  Created on: 	2024.8.28
 *      	Author:  	Hongbo.Jiang
 */
#include "PUBLIC_INC/DC_MATH.H"

#ifndef  DLLX64
#pragma  CODE_SECTION(ctrl_pi_gain_position, 		".TI.ramfunc");
#pragma  CODE_SECTION(ctrl_pi_position, 				".TI.ramfunc");
#endif
/*
*Function name:    Ctrl2z3p **************************
 * Input variable:    CTRL_2z3_VARS_T *: 2z2p控制器的变量数据结构体指针;
 *                          CTRL_2z3p_COEFFS_T * 2z2p控制器的参数数据结构体指针
 *Describle:            实现2z2p控制器软件算法;
 *                          差分方程如下:
 *                          Y(n)            b2*Z^-2 + b1*Z^-1 + b0
 *                          ----- = k* ---------------------------------------------
 *                          X(n)          a3*Z^-3 + a2*Z^-2 + a1*Z^-1 + 1
 *                          对应的S 域的传递函数有两种形式:
 *                          (1)
 *                                              (s/Wz1 + 1)(s/Wz2 +1)
 *                          G(s) =  k *  -------------------------------       一般极点都是实数极点，一个极点位于远端, 一个是原始极点，一个临着在两个零点的后面
 *                                              s(s/Wp1 + 1)(s/Wp2 + 1)
 *
 *                         (2)
 *                                               (s^2/Wn^2 + 2*r*s/Wn + 1)
 *                         G(s) =   k *  -----------------------------------    其中 r < 1;  即零点为共轭的复数跟
 *                                                s(s/Wp1 + 1)(s/Wp2 + 1)
 *                         根据需要，选择不同的表达类型，再通过 matlab 的c2d 函数，得到 b2, b1, b0, a3 a2, a1 系数
 *                         但是本控制器原型为一个三零3极，但是在电源中很少见
 */
void Ctrl2z3p(CTRL_2Z3P_VARS_T *loop2z3p_obj, FLOAT32 errVal)
{
    loop2z3p_obj->x[0] = errVal * loop2z3p_obj->loop2z3p_coeff.k;

    loop2z3p_obj->y[0] = loop2z3p_obj->loop2z3p_coeff.b0 * loop2z3p_obj->x[0] +
                         loop2z3p_obj->loop2z3p_coeff.b1 * loop2z3p_obj->x[1] +
                         loop2z3p_obj->loop2z3p_coeff.b2 * loop2z3p_obj->x[2] +
                         loop2z3p_obj->loop2z3p_coeff.a1 * loop2z3p_obj->y[1] -
                         loop2z3p_obj->loop2z3p_coeff.a2 * loop2z3p_obj->y[2] -
                         loop2z3p_obj->loop2z3p_coeff.a3 * loop2z3p_obj->y[3] ;

    loop2z3p_obj->x[2] = loop2z3p_obj->x[1];
    loop2z3p_obj->x[1] = loop2z3p_obj->x[0];

    loop2z3p_obj->y[3] = loop2z3p_obj->y[2];
    loop2z3p_obj->y[2] = loop2z3p_obj->y[1];
    loop2z3p_obj->y[1] = loop2z3p_obj->y[0];

    loop2z3p_obj->Out = loop2z3p_obj->y[0];
}

/*Function name:    Ctrl2z2p **************************
 * Input variable:    CTRL_2z2p_VARS_T *: 2z2p控制器的变量数据结构体指针;
 *                          CTRL_2z2p_COEFFS_T * 2z2p控制器的参数数据结构体指针
 *Describle:            实现2z2p控制器软件算法;
 *                          差分方程如下:
 *                          Y(n)     B2*Z^-2 + B1*Z^-1 + B0
 *                          ----- =----------------------------------
 *                          X(n)     -A2*Z^-2 - A1*Z^-1 + 1
 *                          对应的S 域的传递函数有两种形式:
 *                          (1)
 *                                       k*(s/Wz1 + 1)(s/Wz2 +1)
 *                          G(s) =  --------------------------------
 *                                               s(s/Wp1 + 1)
 *
 *                          (2)
 *                                      k(s^2/Wn^2 + 2*r*s/Wn + 1)
 *                         G(s) =  -----------------------------------    其中 r < 1;  即零点为共轭的复数跟
 *                                                s(s/Wp1 + 1)
 *                         根据需要，选择不同的表达类型，再通过 matlab 的c2d 函数，得到 B2, B1, B0, A2, A1 系数
 */
void Ctrl2z2p(CTRL_2Z2P_VARS_T *v, Ctrl2Z2PCoeffs *k)
{
    v->err = v->ref - v->fdbk;
    v->deltaOut = (k->coeffB2 * v->err2) + (k->coeffB1 * v->err1) + (k->coeffB0 * v->err);
    if (((v->out >= k->coeffOutMax) && (v->err > 0.0f)) || ((v->out <= k->coeffOutMin) && (v->err < 0.0f)))
    {
        v->deltaOut = 0;
    }
    v->out = (k->coeffA2 * v->out2) + (k->coeffA1 * v->out1) + v->deltaOut;
    // 输出限幅
    v->out = (v->out < k->coeffOutMax) ? v->out : k->coeffOutMax;
    v->out = (v->out > k->coeffOutMin) ? v->out : k->coeffOutMin;
    v->err2 = v->err1;
    v->err1 = v->err;
    /* Store outputs */
    v->out2 = v->out1;
    v->out1 = v->out;
}

/*Function name:    ctrl_pi_inc **************************
 * Input variable:    PI_POS_CTRL_PARAM_T *p_stPI: 位置式控制器的变量数据结构体指针;
 *Describle:            实现位置式控制器软件算法;
 *                          差分方程如下:
 *                          Y(n)     (Kp + Ki*Ts) - Kp*Z^-1
 *                          ----- =----------------------------------
 *                          X(n)                 1-Z^-1
 *
 *                         直接可以比较 S域的传递函数 PI(s) = kp + ki/s 进行分析
 */

void ctrl_pi_inc(PI_INC_CTRL_PARAM_T * p_stPI)
{
    float f32Temp = 0;

    p_stPI->f32ErrN = p_stPI->f32Ref - p_stPI->f32Fb;

    if (p_stPI->f32ErrN > p_stPI->f32ErrMax)  p_stPI->f32ErrN = p_stPI->f32ErrMax;

    if (p_stPI->f32ErrN < p_stPI->f32ErrMin)  p_stPI->f32ErrN = p_stPI->f32ErrMin;

    f32Temp = p_stPI->f32Kp *(p_stPI->f32ErrN - p_stPI->f32ErrN_1);

    f32Temp += (p_stPI->f32Ki* p_stPI->f32Ts) * p_stPI->f32ErrN;

    p_stPI->f32YN += f32Temp;
    if (p_stPI->f32YN > p_stPI->f32OutMax)   p_stPI->f32YN = p_stPI->f32OutMax;
    if (p_stPI->f32YN < p_stPI->f32OutMin)   p_stPI->f32YN = p_stPI->f32OutMin;
    p_stPI->f32ErrN_1 = p_stPI->f32ErrN;
}

/*Function name:    ctrl_pi_position **************************
 * Input variable:    PI_INC_CTRL_PARAM_T *: 增量式控制器的变量数据结构体指针;
 *Describle:            实现增量式控制器软件算法;
 *                          差分方程如下:
 *                          Y(n)     (Kp + Ki*Ts) - Kp*Z^-1
 *                          ----- =----------------------------------
 *                          X(n)                 1-Z^-1
 *
 *                         直接可以比较 S域的传递函数 PI(s) = kp + ki/s 进行分析
 *                         其中p_stPI->f32Kp 对应kp,
 *                               p_stPI->f32Ki 对应ki
 *                               p_stPI->f32Ts 对应控制算法周期. 为常数.
 */

void ctrl_pi_position(PI_POS_T *p_stPI)
{
    p_stPI->stInner.f32Err = p_stPI->stIn.f32Ref - p_stPI->stIn.f32Fb;

    p_stPI->stInner.f32Integrate += p_stPI->stCoff.f32KiTs * p_stPI->stInner.f32Err;

    if (p_stPI->stInner.f32Integrate > p_stPI->stCoff.f32IntegrateMax)
    	p_stPI->stInner.f32Integrate = p_stPI->stCoff.f32IntegrateMax;
    if (p_stPI->stInner.f32Integrate < p_stPI->stCoff.f32IntegrateMin)
    	p_stPI->stInner.f32Integrate = p_stPI->stCoff.f32IntegrateMin;

    p_stPI->stOut.f32Out = p_stPI->stInner.f32Integrate +  p_stPI->stCoff.f32Kp * p_stPI->stInner.f32Err;

    if (p_stPI->stOut.f32Out > p_stPI->stCoff.f32OutMax)
    	p_stPI->stOut.f32Out = p_stPI->stCoff.f32OutMax;
    if (p_stPI->stOut.f32Out < p_stPI->stCoff.f32OutMin)
    	p_stPI->stOut.f32Out = p_stPI->stCoff.f32OutMin;
}

/*Function name:    ctrl_pi_gian_position **************************
 * Input variable:    PI_INC_CTRL_PARAM_T *: 增量式控制器的变量数据结构体指针;
 *Describle:            实现增量式控制器软件算法;
 *                          差分方程如下:
 *                          Y(n)     (Kp + Ki*Ts) - Kp*Z^-1
 *                          ----- =----------------------------------
 *                          X(n)                 1-Z^-1
 *
 *                         直接可以比较 S域的传递函数 PI(s) = kp + ki/s 进行分析
 *                         其中p_stPI->f32Kp 对应kp,
 *                               p_stPI->f32Ki 对应ki
 *                               p_stPI->f32Ts 对应控制算法周期. 为常数.
 */

void ctrl_pi_gain_position(PI_GAIN_POS_T* p_stPI)
{
    p_stPI->stInner.f32Err = (p_stPI->stIn.f32Ref - p_stPI->stIn.f32Fb) * p_stPI->stIn.f32Gain;

    p_stPI->stInner.f32Integrate += p_stPI->stCoff.f32KiTs * p_stPI->stInner.f32Err;

    if (p_stPI->stInner.f32Integrate > p_stPI->stCoff.f32IntegrateMax)
        p_stPI->stInner.f32Integrate = p_stPI->stCoff.f32IntegrateMax;
    if (p_stPI->stInner.f32Integrate < p_stPI->stCoff.f32IntegrateMin)
        p_stPI->stInner.f32Integrate = p_stPI->stCoff.f32IntegrateMin;

    p_stPI->stOut.f32Out = p_stPI->stInner.f32Integrate + p_stPI->stCoff.f32Kp * p_stPI->stInner.f32Err;

    if (p_stPI->stOut.f32Out > p_stPI->stCoff.f32OutMax)
        p_stPI->stOut.f32Out = p_stPI->stCoff.f32OutMax;
    if (p_stPI->stOut.f32Out < p_stPI->stCoff.f32OutMin)
        p_stPI->stOut.f32Out = p_stPI->stCoff.f32OutMin;
}

void set_pi_position_integrate(PI_POS_T* p_stPI, float f32Value) {
    float f32Temp;
    f32Temp = f32Value > p_stPI->stCoff.f32IntegrateMax ? p_stPI->stCoff.f32IntegrateMax : f32Value;
    p_stPI->stInner.f32Integrate = f32Temp < p_stPI->stCoff.f32IntegrateMin ? p_stPI->stCoff.f32IntegrateMin : f32Temp;
}

void set_pi_integrate(PI_INC_CTRL_PARAM_T *p_stPI, float f32Value) {
    float f32Temp;
    f32Temp              = f32Value > p_stPI->f32OutMax ? p_stPI->f32OutMax:f32Value;
    p_stPI->f32YN_1 = f32Temp < p_stPI->f32OutMin ? p_stPI->f32OutMin: f32Temp;
}
