/*
 * CLARK_PARK.C
 *
 *  Created on: 2026.3.30
 *      Author: Administrator
 */
#include "clark_park.h"
#define SQRT3               (1.732f)
#define _1_3                (0.3333333f) //  1/3
#define _2_3                (0.6666666f) //  2/3
#define SQRT3_3             (0.57735f)   //  sqrt(3)/3
#define SQRT3_2             (0.866f)   //  sqrt(3)/2

//Based on the follow figure
///**************************************************************************************************
//  Function:       clark_park_clark
//  Description:    ?????
//  Called By:      ?
//  Input:          ?????????
//  Output:         alphaeta
//  Return:         ?
//  Others:         ?
//**************************************************************************************************/
//void clark_park_clark(clark_park_t *pst_clark_park)
//{
//    pst_clark_park->alpha = _2_3*(pst_clark_park->phase_a - 0.5f*pst_clark_park->phase_b - 0.5f*pst_clark_park->phase_c);
//
//    pst_clark_park->beta = SQRT3_3*(pst_clark_park->phase_b - pst_clark_park->phase_c);
//}
//
///**************************************************************************************************
//  Function:       clark_park_park
//  Description:    ?????
//  Called By:      ?
//  Input:          ?????????
//  Output:         d\q
//  Return:         ?
//  Others:         ?
//**************************************************************************************************/
//void clark_park_park(clark_park_t *pst_clark_park)
//{
//    pst_clark_park->d = pst_clark_park->cos_sita*pst_clark_park->alpha + pst_clark_park->sin_sita*pst_clark_park->beta;
//    pst_clark_park->q = -pst_clark_park->sin_sita*pst_clark_park->alpha + pst_clark_park->cos_sita*pst_clark_park->beta;
//}
//
///**************************************************************************************************
//  Function:       clark_park_ipark
//  Description:    ?????
//  Called By:      ?
//  Input:          ?????????
//  Output:         alphaeta
//  Return:         ?
//  Others:         ?
//**************************************************************************************************/
//void clark_park_ipark(clark_park_t *pst_clark_park)
//{
//    pst_clark_park->alpha = pst_clark_park->cos_sita*pst_clark_park->d - pst_clark_park->sin_sita*pst_clark_park->q;
//    pst_clark_park->beta = pst_clark_park->sin_sita*pst_clark_park->d + pst_clark_park->cos_sita*pst_clark_park->q;
//}
//
///**************************************************************************************************
//  Function:       clark_park_iclark
//  Description:    ?????
//  Called By:      ?
//  Input:          ?????????
//  Output:         a\c
//  Return:         ?
//  Others:         ?
//**************************************************************************************************/
//void clark_park_iclark(clark_park_t *pst_clark_park)
//{
//    pst_clark_park->phase_a = pst_clark_park->alpha;
//    pst_clark_park->phase_b = -0.5f*pst_clark_park->phase_a + SQRT3_2*pst_clark_park->beta;
//    pst_clark_park->phase_c = -0.5f*pst_clark_park->phase_a - SQRT3_2*pst_clark_park->beta;
//}



