/*
 * BSW_MCAL_SDL_CORE.h
 *
 *  Created on: 2024Äê12ÔÂ31ÈÕ
 *      Author: xj8r1j
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_SDL_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_SDL_H_


extern void bsw_mcal_sdl_cpu_reg_diag(void);
extern void bsw_mcal_sdl_flash_diag(void);
extern void bsw_mcal_sdl_pie_ram_diag(void);
extern void bsw_mcal_sdl_lcm_diag(void);
extern void bsw_mcal_sdl_march_diag(void);
extern void bsw_mcal_mcd_diag(void);
extern void bsw_mcal_sdl_dcc_diag(void);
extern void bsw_mcal_flash_ecc_test(void);
extern unsigned long u32_get_seed0_inject_err_counter(void);
extern void write_m0_correct_ecc_test(void);
extern void write_m0_uncorrect_ecc_test(void);
extern void write_m1_correct_ecc_test(void);
extern void write_m1_uncorrect_ecc_test(void);

extern void write_ls0_uncorrect_parity_test(void);

extern void write_ls1_uncorrect_parity_test(void);
#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_SDL_H_ */
