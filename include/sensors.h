/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 */




#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MODULE
 * @{
 */

/**
 * @brief The sensor handle.
 */
typedef struct sensor_handle_s* sensor_h;

/**
* @brief	Enumerations of sensor data accuracy.
*/
typedef enum
{
	SENSOR_DATA_ACCURACY_UNDEFINED   = -1,  /**< Undefined accuracy */
	SENSOR_DATA_ACCURACY_BAD         = 0,   /**< Bad accuracy */
	SENSOR_DATA_ACCURACY_NORMAL      = 1,   /**< Normal accuracy */
	SENSOR_DATA_ACCURACY_GOOD        = 2,   /**< Good accuracy */
	SENSOR_DATA_ACCURACY_VERYGOOD    = 3    /**< Very good accuracy */
} sensor_data_accuracy_e;


/**
* @brief	Enumerations of error code for sensor.
 */
typedef enum
{
	SENSOR_ERROR_NONE                  = TIZEN_ERROR_NONE,                   /**< Successful */
	SENSOR_ERROR_IO_ERROR              = TIZEN_ERROR_IO_ERROR,             /**< I/O error */
	SENSOR_ERROR_INVALID_PARAMETER     = TIZEN_ERROR_INVALID_PARAMETER,    /**< Invalid parameter */
	SENSOR_ERROR_OUT_OF_MEMORY         = TIZEN_ERROR_SYSTEM_CLASS | 0x02,  /**< Out of memory */
	SENSOR_ERROR_NOT_NEED_CALIBRATION  = TIZEN_ERROR_SYSTEM_CLASS | 0x03,  /**< Sensor doesn't need calibration */
	SENSOR_ERROR_NOT_SUPPORTED         = TIZEN_ERROR_SYSTEM_CLASS | 0x04,  /**< Unsupported sensor in current device */
	SENSOR_ERROR_OPERATION_FAILED      = TIZEN_ERROR_SYSTEM_CLASS | 0x06,  /**< Operation failed */

} sensor_error_e;


/**
* @brief	Enumerations of sensor type.
*/
typedef enum
{
	SENSOR_ACCELEROMETER,                    /**< Accelerometer */
	SENSOR_GRAVITY,				 /**< Gravity sensor */
	SENSOR_LINEAR_ACCELERATION,              /**< Linear acceleration sensor */
	SENSOR_DEVICE_ORIENTATION,               /**< Device orientation sensor */
	SENSOR_MAGNETIC,                         /**< Magnetic sensor */
	SENSOR_ORIENTATION,                      /**< Orientation sensor */
	SENSOR_GYROSCOPE,                        /**< Gyroscope sensor */
	SENSOR_LIGHT,                            /**< Light sensor */
	SENSOR_PROXIMITY,                        /**< Proximity sensor */
	SENSOR_MOTION_SNAP,                      /**< Snap motion sensor */
	SENSOR_MOTION_SHAKE,                     /**< Shake motion sensor */
	SENSOR_MOTION_DOUBLETAP,                 /**< Double tap motion sensor */
	SENSOR_MOTION_PANNING,                   /**< Panning motion sensor */
	SENSOR_MOTION_PANNING_BROWSE,            /**< Panning browse motion sensor */
	SENSOR_MOTION_TILT,                      /**< Tilt motion sensor */
	SENSOR_MOTION_FACEDOWN,                  /**< Face to down motion sensor */
	SENSOR_MOTION_DIRECTCALL,                /**< Direct call motion sensor */
	SENSOR_MOTION_SMART_ALERT,               /**< Smart alert motion sensor */
	SENSOR_MOTION_NO_MOVE,                   /**< No move motion sensor */
	SENSOR_LAST                              /**< End of sensor enum values */
} sensor_type_e;
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SNAP_MODULE
 * @{
 */

/**
 * @brief	Enumerations of snap motion event.
 */
typedef enum
{
	SENSOR_MOTION_SNAP_NONE,            /**< No Snap */
	SENSOR_MOTION_SNAP_RIGHT,           /**< Snap right to left */
	SENSOR_MOTION_SNAP_LEFT,            /**< Snap left to right */
	SENSOR_MOTION_SNAP_X_POSITIVE = SENSOR_MOTION_SNAP_RIGHT, /**< Snap to positive direction in X-axis, it is the same as @SENSOR_MOTION_SNAP_RIGHT */
	SENSOR_MOTION_SNAP_X_NEGATIVE = SENSOR_MOTION_SNAP_LEFT, /**< Snap to negative direction in X-axis, it is the same as @SENSOR_MOTION_SNAP_LEFT */
	SENSOR_MOTION_SNAP_Y_POSITIVE, /**< Snap to positive direction in Y-axis */
	SENSOR_MOTION_SNAP_Y_NEGATIVE, /**< Snap to Negative direction in Y-axis */
	SENSOR_MOTION_SNAP_Z_POSITIVE, /**< Snap to positive direction in Z-axis */
	SENSOR_MOTION_SNAP_Z_NEGATIVE, /**< Snap to Negative direction in Z-axis */
} sensor_motion_snap_e;
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SHAKE_MODULE
 * @{
 */

/**
 * @brief	Enumerations of shake motion event.
 */
typedef enum
{
	SENSOR_MOTION_SHAKE_NONE,                /**< No Shake */
	SENSOR_MOTION_SHAKE_DETECTED,            /**< Shake motion detected */
	SENSOR_MOTION_SHAKE_CONTINUING,          /**< Shake motion continuing */
	SENSOR_MOTION_SHAKE_FINISHED,            /**< Shake motion finished */
	SENSOR_MOTION_SHAKE_BROKEN,              /**< Shake motion broken */
} sensor_motion_shake_e;
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MODULE
 * @{
 */

/**
 * @brief Called when the current sensor reading falls outside of a defined normal range.
 *
 * @details When something is artificially influencing, such as ferrous metal objects or 
 * electromagnetic fields (car electrical systems, automobile engines, steel pitons, etc.), this callback is called.
 * One way of implementing this callback is to notice a user to make big 8-like gesture with device.
 *
 * @param[in] user_data	The user data passed from the callback registration function
 *
 * @see sensor_magnetic_set_calibration_cb()
 * @see sensor_magnetic_unset_calibration_cb()
 * @see sensor_orientation_set_calibration_cb()
 * @see sensor_orientation_unset_calibration_cb()
 */
typedef void (*sensor_calibration_cb)(void *user_data);


/**
 * @brief Checks whether the given sensor type is available on a device.
 * @details
 * You need to check availability of a sensor first because this sensor may not be supported on the device.
 *
 * @param[in]   type        The sensor type to check
 * @param[out]  supported   @c true if this sensor type is supported, otherwise @c false
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 *
 */
int sensor_is_supported(sensor_type_e type, bool *supported);


/**
 * @brief Gets data specification for a sensor type, except motion sensors.
 *
 * @remark When the given @a type is one of the motion sensors, this function returns #SENSOR_ERROR_INVALID_PARAMETER.
 *
 * @param[in]   type         The sensor type to check
 * @param[out]  vendor       The vendor name of the sensor
 * @param[out]  model        The model name of the sensor
 * @param[out]  max          The maximum range of the sensor in the sensor's unit 
 * @param[out]  min          The minimum range of the sensor in the sensor's unit
 * @param[out]  resolution   The resolution of the sensor
 *
 * @return      0 on success, otherwise a negative error value.
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED         The sensor type is not supported in current device
 *
 * @pre #sensor_is_supported()
 */
int sensor_get_spec(sensor_type_e type, char** vendor, char** model, float *max, float *min, float *resolution);


/**
 * @brief Creates a sensor handle.
 *
 * @remarks @a sensor must be released sensor_destroy() by you.
 *
 * @param[out] sensor	A new sensor handle to the sensors
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE               Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval      #SENSOR_ERROR_OUT_OF_MEMORY      Out of memory
 *
 * @see sensor_destroy()
 */
int sensor_create(sensor_h *sensor);


/**
 * @brief Destroys the sensor handle and releases all its resources.
 *
 * @remark After this function is called, the attached sensor will be detached and 
 *		the corresponding sensor connection will be released.
 *
 * @param[in] sensor	The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 *
 * @see sensor_create()
 */
int sensor_destroy(sensor_h sensor);


/**
 * @brief Starts sensor server for the given sensor handle and sensor type.
 * @details
 * After this function is called, sensor events will occur and 
 * the specific sensor type related callback function will be called. An application can read sensor data.
 *
 * @param[in] sensor  The sensor handle
 * @param[in] type    The sensor type
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED         The sensor type is not supported in current device
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @pre call sensor_create() before using this function.
 * @post This function invokes sensor_calibration_cb(), sensor_accelerometer_event_cb(), sensor_magnetic_event_cb(),
 * sensor_orientation_event_cb(), sensor_gyroscope_event_cb(), sensor_light_event_cb(),
 * sensor_proximity_event_cb(), sensor_motion_snap_event_cb(), sensor_motion_shake_event_cb(),
 * sensor_motion_doubletap_event_cb(), sensor_motion_panning_event_cb(), or sensor_motion_facedown_event_cb().
 *
 * @see sensor_stop()
 */
int sensor_start(sensor_h sensor, sensor_type_e type);


/**
 * @brief Stops sensor server for the given sensor handle and type.
 * @details The given @a type event will not occur any more and the callback functions also won't be called.
 *
 * @param[in]   sensor  The sensor handle
 * @param[in]   type    The sensor type
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 *
 * @see sensor_start()
 */
int sensor_stop(sensor_h sensor, sensor_type_e type);

/**
 * @brief Retrieve minimum and maximum interval time that can use to measuring specific sensor.
 *
 * @param[in]  type    The sensor type
 * @param[out] min     The minimum interval time
 * @param[out] max     The maximum interval time
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 */
int sensor_get_delay_boundary(sensor_type_e type, int *min, int *max);

/**
 * @brief Retrieve whether supported or not supported the awaken from specific sensor.
 *
 * @param[in]   type         The sensor type
 * @param[out]  supported    @c true if this sensor type is supported, otherwise @c false
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 */
int sensor_awake_is_supported(sensor_type_e type, bool *supported);

/**
 * @brief Set the awaken behavior from specific sensor.
 *
 * @param[in]   sensor       The sensor handle
 * @param[in]   type         The sensor type
 * @param[out]  enable       @c true if set enable the awaken behavior from the sensor, or @c false
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 */
int sensor_awake_is_enabled(sensor_h sensor, sensor_type_e type, bool *enable);

/**
 * @brief Called when a device awaken.
 *
 * @param[in] user_data     The user data passed from the callback registration function
 *
 * @see sensor_awake_is_supported()
 * @see sensor_awake_set()
 * @see sensor_awake_set_cb()
 * @see sensor_awake_unset_cb()
 */
typedef void (*sensor_awake_cb) (void *user_data);

/**
 * @brief Set the callback that called when device awaken.
 * 
 * @param[in]   sensor  The sensor handle
 * @param[in]   type         The sensor type
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 */
int sensor_awake_set_cb(sensor_h sensor, sensor_type_e type, sensor_awake_cb callback, void* user_data);

/**
 * @brief Unset the callback that called when device awaken.
 * 
 * @param[in]   sensor	  The sensor handle
 * @param[in]   type         The sensor type
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 */
int sensor_awake_unset_cb(sensor_h sensor, sensor_type_e type);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_ACCELEROMETER_MODULE
 * @{
 */

/**
 * @brief Called when an accelerometer event occurs.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             The acceleration Gx on the x-axis in [m/s^2]
 * @param[in] y             The acceleration Gy on the y-axis in [m/s^2]
 * @param[in] z             The acceleration Gz on the z-axis in [m/s^2]
 * @param[in] user_data     The user data passed from the callback registration function
 *
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_accelerometer_set_cb().
 *
 * @see sensor_accelerometer_set_cb()
 * @see sensor_accelerometer_unset_cb()
 */
typedef void (*sensor_accelerometer_event_cb)( unsigned long long timestamp,
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);


/**
 * @brief	Registers a callback function to be invoked when an accelerometer event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered at (in milliseconds) \n
 *							If @a rate is zero, it uses default value(100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_accelerometer_event_cb() will be invoked.
 *
 * @see sensor_accelerometer_event_cb()
 * @see sensor_accelerometer_unset_cb()
 */
int sensor_accelerometer_set_cb(sensor_h sensor, int interval_ms, sensor_accelerometer_event_cb callback, void *user_data);


/**
 * @brief	Unregister the accelerometer callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_accelerometer_set_cb()
 */
int sensor_accelerometer_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at accelerometer measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED        Operation failed
 *
 * @see sensor_accelerometer_set_cb()
 */
int sensor_accelerometer_set_interval(sensor_h sensor, int interval_ms);


/**
 * @brief	Gets sensor data from the accelerometer sensor.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  x           The acceleration minus Gx on the x-axis in meters per second squared (m/s^2)
 * @param[out]  y           The acceleration minus Gy on the y-axis in meters per second squared (m/s^2)
 * @param[out]  z           The acceleration minus Gz on the z-axis in meters per second squared (m/s^2)
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 */
int sensor_accelerometer_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *x, float *y, float *z);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_GRAVITY_MODULE
 * @{
 */

/**
 * @brief Called when an gravity event occurs.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             g (9.8 m/s^2 = 1g)
 * @param[in] y             g (9.8 m/s^2 = 1g)
 * @param[in] z             g (9.8 m/s^2 = 1g)
 * @param[in] user_data     The user data passed from the callback registration function
 *
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_rotation_vector_set_cb().
 *
 * @see sensor_gravity_set_cb()
 * @see sensor_gravity_unset_cb()
 */
typedef void (*sensor_gravity_event_cb)(unsigned long long timestamp,
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when an gravity event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms The interval sensor events are delivered at (in milliseconds) \n
 *							If @a rate is zero, it uses default value(100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_gravity_event_cb() will be invoked.
 *
 * @see sensor_gravity_event_cb()
 * @see sensor_gravity_unset_cb()
 */
int sensor_gravity_set_cb(sensor_h sensor, int interval_ms, sensor_gravity_event_cb callback, void* user_data);

/**
 * @brief	Unregister the gravity callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_gravity_set_cb()
 */
int sensor_gravity_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at gravity measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_gravity_set_cb()
 */
int sensor_gravity_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief	Gets sensor data from the gravity sensor.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[in] x             g (9.8 m/s^2 = 1g)
 * @param[in] y             g (9.8 m/s^2 = 1g)
 * @param[in] z             g (9.8 m/s^2 = 1g)
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 */
int sensor_gravity_read_data(sensor_h sensor, sensor_data_accuracy_e* accuracy, float* x, float* y, float* z);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_LINEAR_ACCELERATION_MODULE
 * @{
 */

/**
 * @brief Called when an linear accleration event occurs.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             The acceleration Gx on the x-axis in [m/s^2] not including gravity
 * @param[in] y             The acceleration Gy on the y-axis in [m/s^2] not including gravity
 * @param[in] z             The acceleration Gz on the z-axis in [m/s^2] not including gravity
 * @param[in] user_data     The user data passed from the callback registration function
 *
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_linear_acceleration_set_cb().
 *
 * @see sensor_linear_acceleration_set_cb()
 * @see sensor_linear_acceleration_unset_cb()
 */
typedef void (*sensor_linear_acceleration_event_cb)( unsigned long long timestamp,
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when an linear acceleration event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered at (in milliseconds) \n
 *							If @a rate is zero, it uses default value(100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_linear_acceleration_event_cb() will be invoked.
 *
 * @see sensor_linear_acceleration_event_cb()
 * @see sensor_linear_acceleration_unset_cb()
 */
int sensor_linear_acceleration_set_cb(sensor_h sensor, int interval_ms, sensor_linear_acceleration_event_cb callback, void *user_data);

/**
 * @brief	Unregister the linear acceleration callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_linear_acceleration_set_cb()
 */
int sensor_linear_acceleration_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at linear acceleration measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_linear_acceleration_set_cb()
 */
int sensor_linear_acceleration_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief	Gets sensor data from the linear acceleration sensor.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  x           The acceleration Gx on the x-axis in meters per second squared (m/s^2) not including gravity
 * @param[out]  y           The acceleration Gy on the y-axis in meters per second squared (m/s^2) not including gravity
 * @param[out]  z           The acceleration Gz on the z-axis in meters per second squared (m/s^2) not including gravity
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 */
int sensor_linear_acceleration_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *x, float *y, float *z);


/**
 * @}
 * 
 * @addtogroup CAPI_SYSTEM_SENSOR_DEVICE_ORIENTATION_MODULE
 * @{
 */

/**
 * @brief Called when an device orientation event occurs.
 *
 * @remark  All values are angles in degrees.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] accuracy      The accuracy of @a yaw, @a pitch, and @a roll values
 * @param[in] yaw           The rotation around z-axis [0 ~ 360], with positive values when the y-axis moves \n
 *                          toward the x-axis
 * @param[in] pitch         The rotation around x-axis [-180 ~ 180], with positive values when the z-axis moves \n
 *                          toward the y-axis
 * @param[in] roll          The rotation around y-axis [-90 ~ 90], with positive values when the x-axis moves \n
 *                          toward the z-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_device_orientation_set_cb().
 * @see sensor_device_orientation_set_cb()
 * @see sensor_device_orientation_unset_cb()
 */
typedef void (*sensor_device_orientation_event_cb)( unsigned long long timestamp,
		sensor_data_accuracy_e accuracy, float yaw, float pitch, float roll, void *user_data);
		
/**
 * @brief	Registers a callback function to be invoked when an device orientation event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function 
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_device_orientation_event_cb() will be invoked.
 *
 * @see sensor_device_orientation_event_cb()
 * @see sensor_device_orientation_unset_cb()
*/
int sensor_device_orientation_set_cb(sensor_h sensor, int interval_ms, sensor_device_orientation_event_cb callback, void *user_data);

/**
 * @brief	Unregister the device orientation callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR		    I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_device_orientation_set_cb()
 */
int sensor_device_orientation_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at device orientation measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED        Operation failed
 *
 * @see sensor_device_orientation_set_cb()
 */
int sensor_device_orientation_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief Gets sensor data from the device orientation sensor.
 *
 * @remark
 * All values are angles in degrees.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[in]   yaw         The rotation around z-axis [0 ~ 360], with positive values when the y-axis moves \n
 *                          toward the x-axis
 * @param[out]  pitch       The rotation in degrees around x-axis [-180 ~ 180], with positive values when the \n
 *                          z-axis moves toward the y-axis
 * @param[out]  roll        The rotation in degrees around y-axis [-90 ~ 90], with positive values when the \n
 *                          x-axis moves toward the z-axis
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see sensor_start()
 */
int sensor_device_orientation_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *yaw, float *pitch, float *roll);


/**
 * @}
 * 
 * @addtogroup CAPI_SYSTEM_SENSOR_MAGNETIC_MODULE
 * @{
 */

/**
 * @brief Called when a magnetic event occurs.
 *
 * @remark @a x, @a y, and @a z values are in micro-Teslas(uT) and measure the ambient magnetic field in the X, Y and Z axis.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             Micro-Tesla value from ambient magnetic field on the x-axis
 * @param[in] y             Micro-Tesla value from ambient magnetic field on the y-axis
 * @param[in] z             Micro-Tesla value from ambient magnetic field on the z-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_magnetic_set_cb().
 * @see sensor_magnetic_set_cb()
 * @see sensor_magnetic_unset_cb()
 */
typedef void (*sensor_magnetic_event_cb)( unsigned long long timestamp,
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);
				
/**
 * @brief	Registers a callback function to be invoked when a magnetic event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_magnetic_event_cb() will be invoked.
 *
 * @see sensor_magnetic_event_cb()
 * @see	sensor_magnetic_unset_cb()
 */
int sensor_magnetic_set_cb(sensor_h sensor, int interval_ms, sensor_magnetic_event_cb callback, void *user_data);

/**
 * @brief	Unregister the magnetic callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_magnetic_set_cb()
 */
int sensor_magnetic_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at magnetic sensor measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_magnetic_set_cb()
 */
int sensor_magnetic_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief Gets sensor data from the magnetic sensor.
 *
 * @remark All values are in micro-Teslas (uT) and measure the ambient magnetic field in the X, Y and Z axis.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  x           Micro-Tesla value on the x-axis
 * @param[out]  y           Micro-Tesla value on the y-axis
 * @param[out]  z           Micro-Tesla value on the z-axis
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 *
 * @see sensor_start()
 */
int sensor_magnetic_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *x, float *y, float *z);

/**
 * @brief	Registers a callback function to be invoked when the current sensor reading falls outside of a defined normal range.
 *
 * @param[in]   sensor     The sensor handle
 * @param[in]   callback   The callback function to register
 * @param[in]   user_data  The user data to be passed to the callback function
 *
 * @return		0 on success, otherwise a negative error value
 * @retval		#SENSOR_ERROR_NONE                  Successful
 * @retval		#SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval		#SENSOR_ERROR_IO_ERROR              I/O error
 * @retval		#SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval		#SENSOR_ERROR_NOT_NEED_CALIBRATION	Sensor doesn't need calibration
 *
 * @post sensor_calibration_cb() will be invoked.
 *
 * @see sensor_calibration_cb()
 * @see	sensor_magnetic_unset_calibration_cb()
 */
int sensor_magnetic_set_calibration_cb(sensor_h sensor, sensor_calibration_cb callback, void *user_data);

/**
 * @brief	Unregisters the magnetic calibration callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval		#SENSOR_ERROR_NOT_NEED_CALIBRATION	Sensor doesn't need calibration
 * @see sensor_magnetic_set_calibration_cb()
 */
int sensor_magnetic_unset_calibration_cb(sensor_h sensor);


/**
 * @}
 * 
 * @addtogroup CAPI_SYSTEM_SENSOR_ORIENTATION_MODULE
 * @{
 */

/**
 * @brief Called when an orientation event occurs.
 *
 * @remark  All values are angles in degrees.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] accuracy      The accuracy of @a azimuth, @a pitch, and @a roll values
 * @param[in] azimuth       The angle between the magnetic north direction and the y-axis, around the z-axis [0 ~ 359]. \n
 *                          0 = North, 90 = East, 180 = South, 270 = West
 * @param[in] pitch         The rotation around x-axis [-180 ~ 180], with positive values when the z-axis moves \n
 *                          toward the y-axis
 * @param[in] roll          The rotation around y-axis [-90 ~ 90], with positive values when the x-axis moves \n
 *                          toward the z-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_orientation_set_cb().
 * @see sensor_orientation_set_cb()
 * @see sensor_orientation_unset_cb()
 */
typedef void (*sensor_orientation_event_cb)( unsigned long long timestamp,
		sensor_data_accuracy_e accuracy, float azimuth, float pitch, float roll, void *user_data);
		
/**
 * @brief	Registers a callback function to be invoked when an orientation event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function 
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_orientation_event_cb() will be invoked.
 *
 * @see sensor_orientation_event_cb()
 * @see sensor_orientation_unset_cb()
*/
int sensor_orientation_set_cb(sensor_h sensor, int interval_ms, sensor_orientation_event_cb callback, void *user_data);

/**
 * @brief	Unregister the orientation callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_orientation_set_cb()
 */
int sensor_orientation_unset_cb(sensor_h sensor);

/**
 * @brief	Registers a callback function to be invoked when the current sensor reading falls outside of a defined normal range.
 *
 * @param[in]   sensor     The sensor handle
 * @param[in]   callback   The callback function to register
 * @param[in]   user_data  The user data to be passed to the callback function 
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval      #SENSOR_ERROR_NOT_NEED_CALIBRATION  Sensor doesn't need calibration
 *
 * @post sensor_calibration_cb() will be invoked.
 *
 * @see sensor_orientation_set_calibration_cb()
 * @see sensor_orientation_unset_calibration_cb()
 */
int sensor_orientation_set_calibration_cb(sensor_h sensor, sensor_calibration_cb callback, void *user_data);

/**
 * @brief	Unregister the orientation calibration callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR		    I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval	#SENSOR_ERROR_NOT_NEED_CALIBRATION  Sensor doesn't need calibration
 *
 * @see sensor_orientation_set_calibration_cb()
 */
int sensor_orientation_unset_calibration_cb(sensor_h sensor);

/**
 * @brief change the interval at orientation measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED        Operation failed
 *
 * @see sensor_orientation_set_cb()
 */
int sensor_orientation_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief Gets sensor data from the orientation sensor.
 *
 * @remark
 * All values are angles in degrees.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  azimuth     The angle in degrees between the magnetic north direction and the y-axis, \n
 *                          around the z-axis [0 ~ 359]. 0=North, 90=East, 180=South, 270=West
 * @param[out]  pitch       The rotation in degrees around x-axis [-180 ~ 180], with positive values when the \n
 *                          z-axis moves toward the y-axis
 * @param[out]  roll        The rotation in degrees around y-axis [-90 ~ 90], with positive values when the \n
 *                          x-axis moves toward the z-axis
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see sensor_start()
 */
int sensor_orientation_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *azimuth, float *pitch, float *roll);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_GYROSCOPE_MODULE
 * @{
 */

/**
 * @brief Called when a gyroscope event occurs.
 *
 * @remark
 * Measure the rate of rotation around X, Y and Z axis in radians/second values.
 * All values is observed by positive value in the counter-clockwise direction.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             Angular speed around the x-axis in degree per second
 * @param[in] y             Angular speed around the y-axis in degree per second
 * @param[in] z             Angular speed around the z-axis in degree per second
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_gyroscope_set_cb().
 * @see sensor_gyroscope_set_cb()
 * @see sensor_gyroscope_unset_cb()
 */
typedef void (*sensor_gyroscope_event_cb)( unsigned long long timestamp,
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);
		
/**
 * @brief	Registers a callback function to be invoked when a gyroscope event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post	sensor_gyroscope_event_cb() will be invoked
 *
 * @see sensor_gyroscope_event_cb()
 * @see sensor_gyroscope_unset_cb()
 */
int sensor_gyroscope_set_cb(sensor_h sensor, int interval_ms, sensor_gyroscope_event_cb callback, void *user_data);

/**
 * @brief	Unregister the gyroscope callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_gyroscope_set_cb()
 */
int sensor_gyroscope_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at gyroscope measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED        Operation failed
 *
 * @see sensor_gyroscope_set_cb()
 */
int sensor_gyroscope_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief
 * Gets sensor data from the gyroscope sensor.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  x           The angular speed around the x-axis in degree per second
 * @param[out]  y           The angular speed around the y-axis in degree per second
 * @param[out]  z           The angular speed around the z-axis in degree per second
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see	sensor_start()
 */
int sensor_gyroscope_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *x, float *y, float *z);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_LIGHT_MODULE
 * @{
 */

/**
 * @brief Called when a light event occurs.
 *
 * @remark
 * You should use lux between min and max values obtained \n
 * with #sensor_get_spec().
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] lux           The ambient light level in SI lux units \n
 *			@a lux is between min and max values obtained with #sensor_get_spec().\n
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_light_set_cb().
 * @see sensor_light_set_cb()
 * @see sensor_light_unset_cb()
 */
typedef void (*sensor_light_event_cb)( unsigned long long timestamp, float lux, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a light event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_light_event_cb() will be invoked.
 *
 * @see sensor_light_event_cb()
 * @see	sensor_light_unset_cb()
 */
int sensor_light_set_cb(sensor_h sensor, int interval_ms, sensor_light_event_cb callback, void *user_data);

/**
 * @brief	Unregister the light callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_light_set_cb()
 */
int sensor_light_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at light sensor measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED        Operation failed
 *
 * @see sensor_light_set_cb()
 */
int sensor_light_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief	Gets sensor data from the light sensor.
 *
 * @remark
 * You should use lux between min and max values obtained \n
 * with #sensor_get_spec().
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  lux       The ambient light level in SI lux units \n
 *			@a lux is between min and max values obtained with #sensor_get_spec().\n
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see #sensor_data_accuracy_e
 * @see sensor_start()
 */
int sensor_light_read_data(sensor_h sensor, float *lux);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_PROXIMITY_MODULE
 * @{
 */

/**
 * @brief Called when a proximity event occurs.
 *
 * @param[in]  timestamp     The time in nanosecond at which the event ahppened
 * @param[in]  distance       The distance measured in centemeters
 * @param[in]  user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_proximity_set_cb().
 * @see sensor_proximity_set_cb()
 * @see sensor_proximity_unset_cb()
 */
typedef void (*sensor_proximity_event_cb)( unsigned long long timestamp, float distance, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a proximity event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_proximity_event_cb() will be invoked.
 *
 * @see sensor_proximity_event_cb()
 * @see sensor_proximity_unset_cb()
 */
int sensor_proximity_set_cb(sensor_h sensor, int interval_ms, sensor_proximity_event_cb callback, void *user_data);

/**
 * @brief	Unregister the proximity callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_proximity_set_cb()
 */
int sensor_proximity_unset_cb(sensor_h sensor);

/**
 * @brief change the interval at proximity measurements.
 * 
 * @param[in]   sensor          The sensor handle
 * @param[in]   interval_ms     in milliseconds.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_proximity_set_cb()
 */
int sensor_proximity_set_interval(sensor_h sensor, int interval_ms);

/**
 * @brief Gets sensor data from the Proximity sensor.
 *
 * @remark
 * All values are angles in degrees.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  distance    The distance measured in centemeters
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see sensor_start()
 */
int sensor_proximity_read_data(sensor_h sensor, float *distance);


/**
 * @}
 *
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_MODULE
 * @{
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SNAP_MODULE
 * @{
 */

/**
 * @brief Called when a snap motion event occurs.
 * @image html phone_snap.png
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] snap          The type of motion snap
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_snap_set_cb().
 * @see sensor_motion_snap_set_cb()
 * @see sensor_motion_snap_unset_cb()
 */
typedef void (*sensor_motion_snap_event_cb) ( unsigned long long timestamp, sensor_motion_snap_e snap, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion snap event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_snap_event_cb() will be invoked.
 *
 * @see sensor_motion_snap_event_cb()
 * @see sensor_motion_snap_unset_cb() 
 */
int sensor_motion_snap_set_cb(sensor_h sensor, sensor_motion_snap_event_cb callback, void *user_data);

/**
 * @brief	Unregister the snap callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR		    I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_snap_set_cb() 
 */
int sensor_motion_snap_unset_cb(sensor_h sensor);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SHAKE_MODULE
 * @{
 */

/**
 * @brief Called when a shake motion event occurs.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] shake         The type of motion shake
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_shake_set_cb().
 * @see sensor_motion_shake_set_cb()
 * @see sensor_motion_shake_unset_cb()
 */
typedef void (*sensor_motion_shake_event_cb) ( unsigned long long timestamp, sensor_motion_shake_e shake, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion shake event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback	The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_shake_event_cb() will be invoked.
 *
 * @see sensor_motion_shake_event_cb()
 * @see sensor_motion_shake_unset_cb()
 */
int sensor_motion_shake_set_cb(sensor_h sensor, sensor_motion_shake_event_cb callback, void *user_data);

/**
 * @brief	Unregister the callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR		    I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_shake_set_cb()
 */
int sensor_motion_shake_unset_cb(sensor_h sensor);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_DOUBLETAP_MODULE
 * @{
 */

/**
 * @brief Called when a double tap motion event occurs.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_doubletap_set_cb().
 * @see sensor_motion_doubletap_set_cb()
 * @see sensor_motion_doubletap_unset_cb()
 */
typedef void (*sensor_motion_doubletap_event_cb) ( unsigned long long timestamp, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion doubletap event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_doubletap_event_cb() will be invoked.
 *
 * @see sensor_motion_doubletap_event_cb()
 * @see	sensor_motion_doubletap_unset_cb()
 */
int sensor_motion_doubletap_set_cb(sensor_h sensor, sensor_motion_doubletap_event_cb callback, void *user_data);

/**
 * @brief	Unregister the doubletap callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_motion_doubletap_set_cb()
 */
int sensor_motion_doubletap_unset_cb(sensor_h sensor);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_PANNING_MODULE
 * @{
 */

/**
 * @brief Called when a panning motion event occurs.
 * @image html phone_panning.png
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] x             1/10 angle on x-axis
 * @param[in] y             1/10 angle on y-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_panning_set_cb().
 * @see sensor_motion_panning_set_cb()
 * @see sensor_motion_panning_unset_cb()
 */
typedef void (*sensor_motion_panning_event_cb) ( unsigned long long timestamp, int x, int y, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion panning event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_panning_event_cb() will be invoked.
 *
 * @see sensor_motion_panning_event_cb()
 * @see	sensor_motion_panning_unset_cb()
 */
int sensor_motion_panning_set_cb(sensor_h sensor, sensor_motion_panning_event_cb callback, void *user_data);

/**
 * @brief	Unregister the callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_motion_panning_set_cb()
 */
int sensor_motion_panning_unset_cb(sensor_h sensor);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_PANNING_BROWSE_MODULE
 * @{
 */

/**
 * @brief Called when a panning browse motion event occurs.
 * @image html phone_panning.png
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] x             1/10 angle on x-axis
 * @param[in] y             1/10 angle on y-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_panning_browse_set_cb().
 * @see sensor_motion_panning_browse_set_cb()
 * @see sensor_motion_panning_browse_unset_cb()
 */
typedef void (*sensor_motion_panning_browse_event_cb) ( unsigned long long timestamp, int x, int y, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion panning browse event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_panning_browse_event_cb() will be invoked.
 *
 * @see sensor_motion_panning_browse_event_cb()
 * @see	sensor_motion_panning_browse_unset_cb()
 */
int sensor_motion_panning_browse_set_cb(sensor_h sensor, sensor_motion_panning_browse_event_cb callback, void *user_data);

/**
 * @brief	Unregister the callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_motion_panning_browse_set_cb()
 */
int sensor_motion_panning_browse_unset_cb(sensor_h sensor);



/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_TILT_MODULE
 * @{
 */

/**
 * @brief Called when a tilt motion event occurs.
 * @image html phone_panning.png
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] x             1/10 angle on x-axis
 * @param[in] y             1/10 angle on y-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_tilt_set_cb().
 * @see sensor_motion_tilt_set_cb()
 * @see sensor_motion_tilt_unset_cb()
 */
typedef void (*sensor_motion_tilt_event_cb) ( unsigned long long timestamp, int x, int y, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion tilt event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_tilt_event_cb() will be invoked.
 *
 * @see sensor_motion_tilt_event_cb()
 * @see	sensor_motion_tilt_unset_cb()
 */
int sensor_motion_tilt_set_cb(sensor_h sensor, sensor_motion_tilt_event_cb callback, void *user_data);

/**
 * @brief	Unregister the callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_motion_tilt_set_cb()
 */
int sensor_motion_tilt_unset_cb(sensor_h sensor);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_FACEDOWN_MODULE
 * @{
 */

/**
 * @brief Called when a facedown motion event occurs.
 * @details
 * This event occurs when device is flipped as follows:
 * @image html phone_facedown.png
 * This motion event will fire only when the device is flipped from face to back.
 * It will not occur when the device is flipped from back to face.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_facedown_set_cb().
 * @see sensor_motion_facedown_set_cb()
 * @see sensor_motion_facedown_unset_cb()
 */
typedef void (*sensor_motion_facedown_event_cb) ( unsigned long long timestamp, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion facedown event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_facedown_event_cb() will be invoked.
 *
 * @see sensor_motion_facedown_event_cb()
 * @see sensor_motion_facedown_unset_cb()
 */
int sensor_motion_facedown_set_cb(sensor_h sensor, sensor_motion_facedown_event_cb callback, void *user_data);

/**
 * @brief	Unregister the facedown callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_facedown_set_cb()
 */

int sensor_motion_facedown_unset_cb(sensor_h sensor);

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_DIRECTCALL_MODULE
 * @{
 */

/**
 * @brief Called when a directcall motion event occurs.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_directcall_set_cb().
 * @see sensor_motion_directcall_set_cb()
 * @see sensor_motion_directcall_unset_cb()
 */
typedef void (*sensor_motion_directcall_event_cb) ( unsigned long long timestamp, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion directcall event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_directcall_event_cb() will be invoked.
 *
 * @see sensor_motion_directcall_event_cb()
 * @see sensor_motion_directcall_unset_cb()
 */
int sensor_motion_directcall_set_cb(sensor_h sensor, sensor_motion_directcall_event_cb callback, void *user_data);

/**
 * @brief	Unregister the directcall callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_directcall_set_cb()
 */
int sensor_motion_directcall_unset_cb(sensor_h sensor);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SMART_ALERT_MODULE
 * @{
 */

/**
 * @brief Called when a smart alert motion event occurs.
 * @details
 * This event occurs when device is picked up as follows:
 * @image html phone_smart_alert.png
 * This motion event will fire only when the device is picked up on desk or etc.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_smart_alert_set_cb().
 * @see sensor_motion_smart_alert_set_cb()
 * @see sensor_motion_smart_alert_unset_cb()
 */
typedef void (*sensor_motion_smart_alert_event_cb) ( unsigned long long timestamp, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when a motion smart alert event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_smart_alert_event_cb() will be invoked.
 *
 * @see sensor_motion_smart_alert_event_cb()
 * @see sensor_motion_smart_alert_unset_cb()
 */
int sensor_motion_smart_alert_set_cb(sensor_h sensor, sensor_motion_smart_alert_event_cb callback, void *user_data);

/**
 * @brief	Unregister the smart alert callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_smart_alert_set_cb()
 */
int sensor_motion_smart_alert_unset_cb(sensor_h sensor);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_NO_MOVE_MODULE
 * @{
 */

/**
 * @brief Called when a no move motion event occurs.
 * @details
 * This event occurs when device doesn't move
 * @image html phone_no_move.png
 * This motion event will fire only when the device doesn't move at any position during 1 or 2 seconds.
 *
 * @param[in] timestamp     The time in nanosecond at which the event ahppened
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_no_move_set_cb().
 * @see sensor_motion_no_move_set_cb()
 * @see sensor_motion_no_move_unset_cb()
 */
typedef void (*sensor_motion_no_move_event_cb) ( unsigned long long timestamp, void *user_data);


/**
 * @brief       Registers a callback function to be invoked when a motion no move event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_no_move_event_cb() will be invoked.
 *
 * @see sensor_motion_no_move_event_cb()
 * @see sensor_motion_no_move_unset_cb()
 */
int sensor_motion_no_move_set_cb(sensor_h sensor, sensor_motion_no_move_event_cb callback, void *user_data);


/**
 * @brief       Unregister the no move callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                          I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_no_move_set_cb()
 */
int sensor_motion_no_move_unset_cb(sensor_h sensor);


/**
 * @}
 *
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_ROTATION_VECTOR_MODULE
 * @{
 */

/**
 * @brief Called when an rotation vector event occurs.
 * @details
 * The values of rotation vector represents orientation of the device as a combination of an angle and an axis.
 * Each value of the rotation vector is not have unit. the x,y,z axis is same unit as accelerometer.
 *
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             x*sin(θ/2)
 * @param[in] y             y*sin(θ/2)
 * @param[in] z             z*sin(θ/2)
 * @param[in] w             cos(θ/2)
 * @param[in] user_data     The user data passed from the callback registration function
 *
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_rotation_vector_set_cb().
 *
 * @see sensor_rotation_vector_set_cb()
 * @see sensor_rotation_vector_unset_cb()
 */
typedef void (*sensor_rotation_vector_event_cb)(
		sensor_data_accuracy_e accuracy, float x, float y, float z, float w, void *user_data);

/**
 * @brief	Registers a callback function to be invoked when an rotation vector event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered at (in milliseconds) \n
 *							If @a rate is zero, it uses default value(100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_accelerometer_event_cb() will be invoked.
 *
 * @see sensor_accelerometer_event_cb()
 * @see sensor_accelerometer_unset_cb()
 */
int sensor_rotation_vector_set_cb(sensor_h sensor, int interval_ms, sensor_rotation_vector_event_cb callback, void* user_data);

/**
 * @brief	Unregister the rotation vector callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_rotation_vector_set_cb()
 */
int sensor_rotation_vector_unset_cb(sensor_h sensor);

/**
 * @brief	Gets sensor data from the rotation vector sensor.
 * 
 * @details
 * The rotation vector sensor retrieves quaternion elements <cos(θ/2), x*sin(θ/2), y*sin(θ/2), z*sin(θ/2)>. \n
 * Last three elements of the quaternion represents rotation vector. \n
 * Each axis value of rotation vector is composed of the angle from magnitude equal to sin(θ/2) and the axis. \n
 * The value of rotation vector in each axis don't have unit. the axis x,y and z have same unit as the acceleration sensor.
 * 
 * 
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[in] x             x*sin(θ/2)
 * @param[in] y             y*sin(θ/2)
 * @param[in] z             z*sin(θ/2)
 * @param[in] w             cos(θ/2)
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 */
int sensor_rotation_vector_read_data(sensor_h sensor, sensor_data_accuracy_e* accuracy, float* x, float* y, float* z, float* w);
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_UTILITY_MODULE
 * @{
 */

/**
 * @brief	Enumerations of Axis used in #sensor_util_remap_coordinate_system 
 *
 * @see #sensor_util_remap_coordinate_system
 */
typedef enum
{
    sensor_util_axis_minus_x,
    sensor_util_axis_minus_y,
    sensor_util_axis_minus_z,
    sensor_util_axis_x,
    sensor_util_axis_y,
    sensor_util_axis_z,
} sensor_util_axis_e;
/**
 * @}
 */

/**
 * @brief
 * Getting Inclination matrix "I" and Rotation matrix "R" transforming a vector from the device coordinate to the world's coordinate.
 * 
 * @details
 * [0 0 g] = R * gravity (g = magnitude of gravity) \n
 * [0 m 0] = I * R * geomagnetic (m = magnitude of geomagnetic field) \n
 * R is the identity matrix when the device is aligned with the world's coordinate system, that is, when the device's X axis points toward East, the Y axis points to the North Pole and the device is facing the sky. \n
 * I is a rotation matrix transforming the geomagnetic vector into the same coordinate space as gravity (the world's coordinate space). I is a simple rotation around the X axis. \n
 *
 * @remark
 * Parameter Gx, Gy, Gz can be got from the values returned by a #sensor_gravity_event_cb or #sensor_gravity_read_data. \n
 * Parameter Mx, My, Mz can be got from the values returned by a #sensor_magnetic_event_cb or #sensor_magnetic_read_data.
 * Output parameter R and I is always returned 3x3 matrix array of 9 floats like this form:
 * <pre>
 * { R[0], R[1], R[2],
 *   R[3], R[4], R[5],
 *   R[6], R[7], R[6] }
 * </pre>
 * 
 * 
 * @param[in]  Gx   X-axis gravity vector in the device's coordinate. 
 * @param[in]  Gy   Y-axis gravity vector in the device's coordinate. 
 * @param[in]  Gz   Z-axis gravity vector in the device's coordinate. 
 * @param[in]  Mx   X-axis geomagnetic vector in the device's coordinate. 
 * @param[in]  My   Y-axis geomagnetic vector in the device's coordinate. 
 * @param[in]  Mz   Z-axis geomagnetic vector in the device's coordinate. 
 * @param[out] R    Array of 9 floats that represents the rotation matrix "R". It can be null.
 * @param[out] I    Array of 9 floats that represents the inclination matrix "I". It can be null.
 * 
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 */
int sensor_util_get_rotation_matrix(float Gx, float Gy, float Gz, 
        float Mx, float My, float Mz,
        float R[], float I[]);

/**
 * @brief
 * Convert a rotation vector to a rotation matrix. 
 *
 * @details
 * rotation vectors (Vx, Vy, Vz) can be got from #sensor_rotation_vector_event_cb or #sensor_rotation_vector_read_data.
 * It returns a 9 elements rotation matrix in the array R. R must have langth 9.
 *
 * @param[in]  Vx   X-axis rotation vector.
 * @param[in]  Vy   Y-axis rotation vector.
 * @param[in]  Vz   Z-axis rotation vector.
 * @param[out] R    A 9 elements ration matrix in the array R that must have length 9.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * 
 * @see sensor_util_rotation_matrix3
 * @see sensor_util_rotation_matrix4
 */
int sensor_util_get_rotation_matrix_from_vector(float Vx, float Vy, float Vz, float R[]);

/**
 * @brief
 * Rotates the supplied rotation matrix so it is expressed in a different coordinate system.
 *
 * @details
 * This is typically used when an application needs to compute the three orientation angles of the device in a different coordinate system.
 * 
 * @remark
 * inR and outR can be the same array, but it is not recommended for performance reason.
 * Return error when X and Y defines the same axis.
 *
 * @param[in]  inR  the rotation matrix (3x3) to be transformed. Usually it is the matrix returned by get #sensor_util_rotation_matrix3 or #sensor_util_rotation_matrix4.
 * @param[in]  x    defines on which world axis and direction the X axis of the device is mapped.
 * @param[in]  y    defines on which world axis and direction the Y axis of the device is mapped.
 * @param[out] outR the transformed rotation matrix (3x3).
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * 
 * @see sensor_util_rotation_matrix3
 * @see sensor_util_rotation_matrix4
 * @see sensor_util_rotation_matrix_from_vector
 * @see sensor_util_rotation_matrix_from_quaternion
 */
int sensor_util_remap_coordinate_system(float inR[], sensor_util_axis_e x, sensor_util_axis_e y, float outR[]);

/**
 * @brief
 * Computes the geomagnetic inclination angle in radians from the inclination matrix I returned by #sensor_util_get_rotation_matrix()
 *
 * @param[in]  I            inclination matrix from #sensor_util_get_rotation_matrix()
 * @param[out] inclination  The geomagnetic inclination angle in radians.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 *
 * @see sensor_util_get_rotation_matrix()
 */
int sensor_util_get_inclination(float I[], float* inclination); 

/**
 * @brief
 * Compute the device's orientation based on the rotation matrix
 *
 * @details
 * When it returns, they array values is filled with the result:
 *  - values[0]: azimuth, rotation around the Z axis.
 *  - values[1]: pitch, rotation around the X axis.
 *  - values[2]: roll, rotation around the Y axis.
 *
 * @remark
 * Parameter R must be array of 9 floats from #sensor_util_get_rotation_matrix() \n
 * Returned values are always array of 3 floats.
 * 
 *
 * @param[in]     R         A 9 elements ration matrix in the array.
 * @param[values] values    An array of 3 floats to hold the result.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 *
 * @see sensor_util_get_rotation_matrix()
 *
 */
int sensor_util_get_orientation(float R[], float values[]);

/**
 * @brief
 * Helper function to compute the angle change between two rotation matrices. 
 *
 * @details
 * Given a current rotation matrix (R) and a previous rotation matrix (prevR) computes 
 * the rotation around the x,y, and z axes which transforms prevR to R. 
 * outputs a 3 element vector containing the x,y, and z angle change at indexes 0, 1, and 2 respectively. \n
 *
 * @remark
 * Each input matrix is 3x3 matrix like this form:
 * <pre>
 * { R[0], R[1], R[2],
 *   R[3], R[4], R[5],
 *   R[6], R[7], R[6] }
 * </pre>
 * 
 * @param[in] R             current rotation matrix
 * @param[in] prevR         previous rotation matrix
 * @param[out] angleChange  an array of floats in which the angle change is stored
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 */
int sensor_util_get_angle_change(float R[], float prevR[], float angleChange[]);

/**
 * @brief
 * Getting the declination of the horizontal component of the magnetic field from true north, in degrees
 *
 * @param[in]  latitude     Latitude in geodetic coordinates 
 * @param[in]  longitude    Longitude in geodetic coordinates
 * @param[in]  altitude     Altitude in geodetic coordinates
 * @param[out] declination  The declination of the horizontal component of the magnetic field in degrees.
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 */
int sensor_util_get_declination(float latitude, float longitude, float altitude, float* declination);

/**
 * @brief Determines whether or not to be near from proximity sensor's distance value.
 * 
 * @remark
 * This function can be used to determine the proximity to device from other object like human face.
 *
 * @param[in] distance      Distance in centimeter from proximity sensor.
 * @param[out] is_near      proximity to device from other object.
 */
int sensor_util_is_near(float distance, bool *is_near);

/**
 * @brief Continues to sense even when LCD is off
 * 
 * @param[in]  sensor    The sensor handle 
 * @param[out] type      The sensor type 
 */
int sensor_set_always_on(sensor_h sensor, sensor_type_e type);
/**
 * @}
 */


/**
 *
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

