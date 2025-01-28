// MIT License

// Copyright (c) 2024 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

typedef err_code_t (*joystick_func_get_pos_x)(uint16_t *pos_x);
typedef err_code_t (*joystick_func_get_pos_y)(uint16_t *pos_y);
typedef err_code_t (*joystick_func_get_button)(uint8_t *button_status);

/**
 * @brief   Handle structure.
 */
typedef struct joystick *joystick_handle_t;

typedef struct {
	int16_t 					min_acceptable_raw_x; 	/*!< Min acceptable raw value */
	int16_t 					max_acceptable_raw_x; 	/*!< Max acceptable raw value */
	int16_t 					min_scale_x;  			/*!< Min value after converting */
	int16_t 					max_scale_x;  			/*!< Max value after converting */
	uint8_t 					inverse_x;  			/*!< Inverse x axis*/
	int16_t 					min_acceptable_raw_y; 	/*!< Min acceptable raw value */
	int16_t 					max_acceptable_raw_y; 	/*!< Max acceptable raw value */
	int16_t 					min_scale_y;  			/*!< Min value after converting */
	int16_t 					max_scale_y;  			/*!< Max value after converting */
	uint8_t 					inverse_y;  			/*!< Inverse y axis*/
	joystick_func_get_pos_x 	get_pos_x;				/*!< Function get x analog value */
	joystick_func_get_pos_y 	get_pos_y;				/*!< Function get y analog value */
	joystick_func_get_button 	get_button;				/*!< Function get button status */
} joystick_cfg_t;

/*
 * @brief   Initialize joystick with default parameters.
 *
 * @note    This function must be called first.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
joystick_handle_t joystick_init(void);

/*
 * @brief   Set configuration parameters.
 *
 * @param 	handle Handle structure.
 * @param   config Configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t joystick_set_config(joystick_handle_t handle, joystick_cfg_t config);

/*
 * @brief   Configure joystick to run.
 *
 * @param 	handle Handle structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t joystick_config(joystick_handle_t handle);

/**
 * @brief   Get raw current x position.
 *
 * @param   handle Handle structure.
 * @param   x Position x.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t joystick_get_pos_x_raw(joystick_handle_t handle, uint16_t *pos_x);

/**
 * @brief   Get raw current y position.
 *
 * @param   handle Handle structure.
 * @param   y Position y.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t joystick_get_pos_y_raw(joystick_handle_t handle, uint16_t *pos_y);

/**
 * @brief   Get scaled current x position.
 *
 * @param   handle Handle structure.
 * @param   x Position x.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t joystick_get_pos_x_scale(joystick_handle_t handle, int16_t *pos_x);

/**
 * @brief   Get scaled current y position.
 *
 * @param   handle Handle structure.
 * @param   y Position y.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t joystick_get_pos_y_scale(joystick_handle_t handle, int16_t *pos_y);

/**
 * @brief   Get current button status.
 *
 * @param   handle Handle structure.
 * @param   button_status Button status.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t joystick_get_button(joystick_handle_t handle, uint8_t *button_status);

#ifdef __cplusplus
}
#endif

#endif /* __JOYSTICK_H__ */