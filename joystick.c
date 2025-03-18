#include "stdio.h"
#include "stdlib.h"
#include "joystick.h"

typedef struct joystick {
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
} joystick_t;

static int16_t joystick_constrain(int16_t value, int16_t max, int16_t min)
{
	int16_t temp_data;
	if (value > max)
	{
		temp_data = max;
	}
	else if (value < min)
	{
		temp_data = min;
	}
	else
	{
		temp_data = value;
	}

	return temp_data;
}

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

	handle->min_acceptable_raw_x 	= config.min_acceptable_raw_x;
	handle->max_acceptable_raw_x 	= config.max_acceptable_raw_x;
	handle->min_scale_x 			= config.min_scale_x;
	handle->max_scale_x 			= config.max_scale_x;
	handle->inverse_x  				= config.inverse_x;
	handle->min_acceptable_raw_y 	= config.min_acceptable_raw_y;
	handle->max_acceptable_raw_y 	= config.max_acceptable_raw_y;
	handle->min_scale_y 			= config.min_scale_y;
	handle->max_scale_y 			= config.max_scale_y;
	handle->inverse_y  				= config.inverse_y;
	handle->get_pos_x 				= config.get_pos_x;
	handle->get_pos_y 				= config.get_pos_y;
	handle->get_button 				= config.get_button;

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

err_code_t joystick_get_pos_x_scale(joystick_handle_t handle, int16_t *pos_x)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	uint16_t raw_pos_x;
	int16_t old_value, old_min, old_max, new_value, new_min, new_max;

	if (handle->get_pos_x != NULL)
	{
		handle->get_pos_x(&raw_pos_x);
	}

	old_value = (int16_t)joystick_constrain(raw_pos_x, handle->max_acceptable_raw_x, handle->min_acceptable_raw_x);
	old_min = handle->min_acceptable_raw_x;
	old_max = handle->max_acceptable_raw_x;
	new_min = handle->min_scale_x;
	new_max = handle->max_scale_x;

	if ((old_max - old_min) > 0)
	{
		new_value = ((float)(old_value - old_min) / (float)(old_max - old_min) ) * (new_max - new_min) + new_min;
	}
	else
	{
		new_value = old_value;
	}

	if (handle->inverse_x == 1)
	{
		*pos_x = new_max + new_min - new_value;
	}
	else
	{
		*pos_x = new_value;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_get_pos_y_scale(joystick_handle_t handle, int16_t *pos_y)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	uint16_t raw_pos_y;
	int16_t old_value, old_min, old_max, new_value, new_min, new_max;

	if (handle->get_pos_y != NULL)
	{
		handle->get_pos_y(&raw_pos_y);
	}

	old_value = (int16_t)joystick_constrain(raw_pos_y, handle->max_acceptable_raw_y, handle->min_acceptable_raw_y);
	old_min = handle->min_acceptable_raw_y;
	old_max = handle->max_acceptable_raw_y;
	new_min = handle->min_scale_y;
	new_max = handle->max_scale_y;

	if ((old_max - old_min) > 0)
	{
		new_value = ((float)(old_value - old_min) / (float)(old_max - old_min) ) * (new_max - new_min) + new_min;
	}
	else
	{
		new_value = old_value;
	}

	if (handle->inverse_y == 1)
	{
		*pos_y = new_max + new_min - new_value;
	}
	else
	{
		*pos_y = new_value;
	}

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