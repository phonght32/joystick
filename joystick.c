#include "stdio.h"
#include "stdlib.h"
#include "joystick.h"

typedef struct joystick {
	joystick_func_get_pos_x 		get_pos_x;		/*!< Function get x analog value */
	joystick_func_get_pos_y 		get_pos_y;		/*!< Function get y analog value */
	joystick_func_get_bt_status 	get_bt_status;	/*!< Function get button status */
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
	handle->get_bt_status = config.get_bt_status;

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

err_code_t joystick_get_pos_x(joystick_handle_t handle, uint16_t *pos_x)
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

err_code_t joystick_get_pos_y(joystick_handle_t handle, uint16_t *pos_y)
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

err_code_t joystick_get_bt_status(joystick_handle_t handle, uint8_t *bt_status)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	if (handle->get_bt_status != NULL)
	{
		handle->get_bt_status(bt_status);
	}

	return ERR_CODE_SUCCESS;
}

err_code_t joystick_get_all(joystick_handle_t handle, uint16_t *pos_x, uint16_t *pos_y, uint8_t *bt_status)
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

	if (handle->get_pos_y != NULL)
	{
		handle->get_pos_y(pos_y);
	}

	if (handle->get_bt_status != NULL)
	{
		handle->get_bt_status(bt_status);
	}

	return ERR_CODE_SUCCESS;
}
