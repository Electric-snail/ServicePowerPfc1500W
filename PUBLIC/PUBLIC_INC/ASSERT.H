/*
 * assert.h
 *
 *  Created on: 2022-07-21
 *      Author: Hongbo.jiang
 */

#ifndef BSW_PUBLIC_PUBLIC_INC_ASSERT_H_
#define BSW_PUBLIC_PUBLIC_INC_ASSERT_H_


#define ASSERT_RETURN(CON)     				if(CON) return
#define ASSERT_BREAK(CON)      					if(CON) break

#define TIME_OVER_U32(Target,Current)    ((((unsigned long)Current) - ((unsigned long)Target)) < 0x80000000UL)
#define TIME_OVER_U16(Target,Current)    ((((unsigned int)Current) - ((unsigned int)Target)) < 0x8000U)

#endif /* BSW_PUBLIC_PUBLIC_INC_ASSERT_H_ */
