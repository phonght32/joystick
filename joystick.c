#include "stdio.h"
#include "stdlib.h"
#include "joystick.h"

typedef struct joystick {
	int16_t  						bias_x;			/*!< Bias value for x position */
	int16_t  						bias_y;			/*!< Bias value for y position */
	joystick_func_get_pos_x 		get_pos_x;		/*!< Function get x analog value */
	joystick_func_get_pos_y 		get_pos_y;		/*!< Function get y analog value */
	joystick_func_get_button 		get_button;		/*!< Function get button status */
} joystick_t;

joystick_handle_t joystick_init(void)
{
	joystick_handle_t handle = calloc(1, sizeof(joystick_t));

	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return NULL;
	}

	return handle;
}

err_code_t joystick_set_config(joystick_handle_t handle, joystick_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->get_pos_x = config.get_pos_x;
	handle->get_pos_y = config.get_pos_y;
	handle->get_button = config.get_button;

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_config(joystick_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	/* Nothing to do */

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_get_pos_x_raw(joystick_handle_t handle, uint16_t *pos_x)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	if (handle->get_pos_x != NULL)
	{
		handle->get_pos_x(pos_x);
	}

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_get_pos_y_raw(joystick_handle_t handle, uint16_t *pos_y)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	if (handle->get_pos_y != NULL)
	{
		handle->get_pos_y(pos_y);
	}

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_get_pos_x_calib(joystick_handle_t handle, int16_t *pos_x)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	uint16_t raw_pos_x;

	if (handle->get_pos_x != NULL)
	{
		handle->get_pos_x(&raw_pos_x);
	}

	*pos_x = raw_pos_x - handle->bias_x;

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_get_pos_y_calib(joystick_handle_t handle, int16_t *pos_y)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	uint16_t raw_pos_y;

	if (handle->get_pos_y != NULL)
	{
		handle->get_pos_y(&raw_pos_y);
	}

	*pos_y = raw_pos_y - handle->bias_y;

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_get_button(joystick_handle_t handle, uint8_t *button_status)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	if (handle->get_button != NULL)
	{
		handle->get_button(button_status);
	}

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_set_bias(joystick_handle_t handle, int16_t bias_x, int16_t bias_y)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->bias_x = bias_x;
	handle->bias_y = bias_y;

	return ERR_CODE_SUCCESS;
}
