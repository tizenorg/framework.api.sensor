/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
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
 * @file sensor.h
 * @brief This file contains Sensor API related structures and enumerations.
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MODULE
 * @{
 */

#define MAX_VALUE_SIZE 16
#ifndef TIZEN_ERROR_SENSOR
#define TIZEN_ERROR_SENSOR -0x02440000
#endif
#ifndef TIZEN_ERROR_NOT_SUPPORTED
#define TIZEN_ERROR_NOT_SUPPORTED (TIZEN_ERROR_MIN_PLATFORM_ERROR+2)
#endif

/**
 * @brief The sensor handle.
 * @details This handle indicates a specific sensor itself.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef void* sensor_h;


/**
 * @brief The listener handle.
 * @details This listener is an event listener used to receive sensor data asynchronously.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef struct sensor_listener_s *sensor_listener_h;


/**
 * @brief The structure type containing information of an event.
 * @details It holds information such as timestamp, accuracy, and sensor values.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @remarks If you use proximity sensor, see #sensor_proximity_e
 */
typedef struct
{
	int accuracy;                  /**< Accuracy */
	unsigned long long timestamp;  /**< Timestamp */
	int value_count;               /**< Count of values */
	float values[MAX_VALUE_SIZE];  /**< Sensor values */
} sensor_event_s;

/**
 * @brief Enumeration for sensor data accuracy.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
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
 * @brief Enumeration for sensor error.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum
{
	SENSOR_ERROR_NONE                  = TIZEN_ERROR_NONE,                 /**< Successful */
	SENSOR_ERROR_IO_ERROR              = TIZEN_ERROR_IO_ERROR,             /**< I/O error */
	SENSOR_ERROR_INVALID_PARAMETER     = TIZEN_ERROR_INVALID_PARAMETER,    /**< Invalid parameter */
	SENSOR_ERROR_NOT_SUPPORTED         = TIZEN_ERROR_NOT_SUPPORTED,        /**< Unsupported sensor in the current device */
	SENSOR_ERROR_PERMISSION_DENIED     = TIZEN_ERROR_PERMISSION_DENIED,    /**< Permission denied */
	SENSOR_ERROR_OUT_OF_MEMORY         = TIZEN_ERROR_OUT_OF_MEMORY,        /**< Out of memory */
	SENSOR_ERROR_NOT_NEED_CALIBRATION  = TIZEN_ERROR_SENSOR | 0x03,        /**< Sensor doesn't need calibration */
	SENSOR_ERROR_OPERATION_FAILED      = TIZEN_ERROR_SENSOR | 0x06,        /**< Operation failed */
} sensor_error_e;

/**
 * @brief Enumeration for proximity sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum
{
	SENSOR_PROXIMITY_NEAR = 0,    /**< The object is near */
	SENSOR_PROXIMITY_FAR = 5,     /**< The object is far */
} sensor_proximity_e;


/**
 * @brief Enumeration for sensor types.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum
{
	SENSOR_ALL = -1,                         /**< All sensors */
	SENSOR_ACCELEROMETER,                    /**< Accelerometer */
	SENSOR_GRAVITY,                          /**< Gravity sensor */
	SENSOR_LINEAR_ACCELERATION,              /**< Linear acceleration sensor */
	SENSOR_MAGNETIC,                         /**< Magnetic sensor */
	SENSOR_ROTATION_VECTOR,                  /**< Rotation Vector sensor */
	SENSOR_ORIENTATION,                      /**< Orientation sensor */
	SENSOR_GYROSCOPE,                        /**< Gyroscope sensor */
	SENSOR_LIGHT,                            /**< Light sensor */
	SENSOR_PROXIMITY,                        /**< Proximity sensor */
	SENSOR_PRESSURE,                         /**< Pressure sensor */
	SENSOR_ULTRAVIOLET,                      /**< Ultraviolet sensor */
	SENSOR_TEMPERATURE,                      /**< Temperature sensor */
	SENSOR_HUMIDITY,                         /**< Humidity sensor */
	SENSOR_HRM,                              /**< Heart Rate Monitor sensor @if MOBILE (Since Tizen 2.3.1) @endif */
	SENSOR_HRM_LED_GREEN,                    /**< HRM (LED Green) sensor @if MOBILE (Since Tizen 2.3.1) @endif */
	SENSOR_HRM_LED_IR,                       /**< HRM (LED IR) sensor @if MOBILE (Since Tizen 2.3.1) @endif */
	SENSOR_HRM_LED_RED,                      /**< HRM (LED RED) sensor @if MOBILE (Since Tizen 2.3.1) @endif */
	SENSOR_GYROSCOPE_UNCALIBRATED,           /**< Uncalibrated Gyroscope sensor (Since Tizen 2.4) */
	SENSOR_GEOMAGNETIC_UNCALIBRATED,         /**< Uncalibrated Geomagnetic sensor (Since Tizen 2.4) */
	SENSOR_GYROSCOPE_ROTATION_VECTOR,        /**< Gyroscope-based rotation vector sensor (Since Tizen 2.4) */
	SENSOR_GEOMAGNETIC_ROTATION_VECTOR,      /**< Geomagnetic-based rotation vector sensor (Since Tizen 2.4) */
	SENSOR_LAST,                             /**< End of sensor enum values */
	SENSOR_CUSTOM = 10000                    /**< Custom sensor */
} sensor_type_e;

/**
 * @brief Enumeration for sensor options.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
#ifndef __SENSOR_COMMON_H__
typedef enum
{
	SENSOR_OPTION_DEFAULT,              /**< Does not receive data when the LCD is off and in the power save mode */
	SENSOR_OPTION_ON_IN_SCREEN_OFF,     /**< Receives data when the LCD is off */
	SENSOR_OPTION_ON_IN_POWERSAVE_MODE, /**< Receives data in the power save mode */
	SENSOR_OPTION_ALWAYS_ON,            /**< Receives data when the LCD is off and in the power save mode */
} sensor_option_e;
#endif

/**
 * @brief Checks whether a given sensor type is available on a device.
 * @details Availability of a sensor should be checked first because this sensor may not be supported on the device.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks For getting a handle of HRM Sensor(including HRM_LED_GREEN, HRM_LED_IR and HRM_LED_RED)
 * the privilege should be set to, %http://tizen.org/privilege/healthinfo.
 *
 * @param[in]   type        The sensor type to check
 * @param[out]  supported   If @c true this sensor type is supported,
 *                          otherwise @c false
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 *
 */
int sensor_is_supported(sensor_type_e type, bool *supported);

/**
 * @brief Gets a specific sensor handle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks For getting a handle of HRM Sensor(including HRM_LED_GREEN, HRM_LED_IR and HRM_LED_RED)
 * the privilege should be set to, %http://tizen.org/privilege/healthinfo.
 *
 * @param[in]  type     The sensor type
 * @param[out] sensor   The sensor handle
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_PERMISSION_DENIED    Permission denied
 */
int sensor_get_default_sensor(sensor_type_e type, sensor_h *sensor);

/**
 * @brief Gets a sensor list.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks If you want to get a handle list of all sensors,
 * use SENSOR_ALL type in sensor_type_e.
 * @remarks The caller should explicitly free this list.
 *
 * @param[in]  type         The sensor type
 * @param[out] list         The sensor list
 * @param[out] sensor_count The count of sensors
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_PERMISSION_DENIED    Permission denied
 */
int sensor_get_sensor_list(sensor_type_e type, sensor_h **list, int *sensor_count);

/**
 * @brief Called when a sensor event occurs.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in] sensor    The sensor handle
 * @param[in] event     The event information
 * @param[in] data      The user data passed from the callback registration function
 *
 * @see sensor_create_listener()
 * @see sensor_listener_set_event_cb()
 * @see sensor_listener_unset_event_cb()
 */
typedef void (*sensor_event_cb)(sensor_h sensor, sensor_event_s *event, void *data);

/**
 * @brief Creates a sensor listener.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @remarks You must release @a listener using sensor_destroy_listener().
 *
 * @param[in]  sensor          The sensor handle
 * @param[out] listener        A new listener handle
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_OUT_OF_MEMORY        Out of memory
 *
 * @see sensor_listener_set_event_cb()
 * @see sensor_listener_set_interval()
 * @see sensor_listener_set_max_batch_latency()
 * @see sensor_listener_set_option()
 * @see sensor_destroy_listener()
 */
int sensor_create_listener(sensor_h sensor, sensor_listener_h *listener);

/**
 * @brief Destroys the sensor handle and releases all its resources.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @remarks After this function is called, the attached sensor is detached and
 *          the corresponding sensor connection is released.
 *
 * @param[in] listener  The listener handle
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 *
 * @see sensor_create_listener()
 */
int sensor_destroy_listener(sensor_listener_h listener);

/**
 * @brief Starts the sensor server for the given listener.
 *
 * @details After this function is called, sensor events will occur and
 *          the specific sensor type related callback function will be called. An application can read sensor data.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in] listener  The listener handle
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 *
 * @pre Call sensor_create_listener() before using this function.
 *
 * @see sensor_listener_stop()
 */
int sensor_listener_start(sensor_listener_h listener);

/**
 * @brief     Stops the sensor server for the given listener.
 *
 * @details   The given @a type event will not occur any more and the callback functions also won't be called.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener  The listener handle
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 *
 * @see sensor_listener_start()
 */
int sensor_listener_stop(sensor_listener_h listener);

/**
 * @brief  Registers a callback function to be invoked when a sensor event occurs.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener    The listener handle
 * @param[in]   interval_ms The interval at which sensor events are delivered (in milliseconds) \n
 *                          If @a rate is zero, it uses the default value(100ms) \n
 *                          Min value is 10ms, Max value is 1000ms(10ms ~ 1000ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   data        The user data to be passed to the callback function
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 *
 * @see sensor_event_cb()
 * @see sensor_listener_unset_event_cb()
 */
int sensor_listener_set_event_cb(sensor_listener_h listener, unsigned int interval_ms, sensor_event_cb callback, void *data);

/**
 * @brief  Unregisters the sensor callback function.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener    The listener handle
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 *
 * @see sensor_listener_set_event_cb()
 */
int sensor_listener_unset_event_cb(sensor_listener_h listener);

/**
 * @brief Called when the accuracy of a sensor has changed.
 *
 * @details When something is artificially influencing, such as ferrous metal objects or
 *          electromagnetic fields (car electrical systems, automobile engines, steel pitons, and so on.), this callback is called.
 *          One way of implementing this callback is to instruct a user to make big 8-like gestures with the device.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   timestamp   The time in milliseconds at which the event happened
 * @param[in]   accuracy    The accuracy of this data
 * @param[in]   user_data   The user data passed from the callback registration function
 */
typedef void (*sensor_accuracy_changed_cb)(sensor_h sensor, unsigned long long timestamp, sensor_data_accuracy_e accuracy, void *data);

/**
 * @brief Registers an accuracy callback function to be invoked when the accuracy of a sensor has changed.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener    The listener handle
 * @param[in]   callback    The callback function to register
 * @param[in]   data        The user data to be passed to the callback function
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 *
 * @see sensor_accuracy_changed_cb()
 * @see sensor_listener_unset_accuracy_cb()
 */
int sensor_listener_set_accuracy_cb(sensor_listener_h listener, sensor_accuracy_changed_cb callback, void *data);

/**
 * @brief Unregisters the sensor accuracy changed callback function.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener    The listener handle
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 *
 * @see sensor_listener_set_accuracy_cb()
 */
int sensor_listener_unset_accuracy_cb(sensor_listener_h listener);

/**
 * @brief Gets sensor data.
 * @details	This function may fail (return #SENSOR_ERROR_OPERATION_FAILED) if it is called before the sensor is ready.
 *			In case of interval-driven sensors,
 *			it is recommended to call the function after at least one sensor event is delivered.
 *			Otherwise, applications can retry to call this function to be sure that the sensor is ready.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener    The listener handle
 * @param[out]  event       The event information
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 *
 * @pre In order to read sensor data, an application should call sensor_listener_start().
 */
int sensor_listener_read_data(sensor_listener_h listener, sensor_event_s *event);

/**
 * @brief Changes the interval at sensor measurements.
 * @details	The specified interval is only a suggested interval between sensor measurements.
 *			You will get at least one sensor measurement within the interval you specify,
 *			but the actual interval between sensor measurements can be affected by other applications and the system.
 *			To reduce the system overhead, it is recommended to set the longest interval that you can,
 *			because the system usually chooses the shortest interval among all intervals specified.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener       The listener handle
 * @param[in]   interval_ms    The interval at which sensor events are delivered (in milliseconds) \n
 *                             If @a rate is zero, it uses the default value(100ms) \n
 *                             Min value is 10ms, Max value is 1000ms(10ms ~ 1000ms)
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_listener_set_interval(sensor_listener_h listener, unsigned int interval_ms);

/**
 * @brief Changes the max batch latency at sensor measurements.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener           The listener handle
 * @param[in]   max_batch_latency  The latency at which sensor events are delivered (in milliseconds)
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_listener_set_max_batch_latency(sensor_listener_h listener, unsigned int max_batch_latency);

/**
 * @brief Changes the option of the sensor.
 * @details If it is default, sensor data cannot be received when the LCD is off and in the power save mode.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   listener        The listener handle
 * @param[in]   option          The sensor option
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_listener_set_option(sensor_listener_h listener, sensor_option_e option);

/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_INFORMATION_MODULE
 * @{
 */

/**
 * @brief Gets the name of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  name            The name of the sensor
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_name(sensor_h sensor, char** name);

/**
 * @brief Gets the vendor of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  vendor          The vendor of the sensor
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_vendor(sensor_h sensor, char** vendor);

/**
 * @brief Gets the type of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  type            The type of the sensor
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_type(sensor_h sensor, sensor_type_e *type);

/**
 * @brief Gets the minimum range of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  min_range       The minimum range
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_min_range(sensor_h sensor, float *min_range);

/**
 * @brief Gets the maximum range of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  max_range       The maximum range
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_max_range(sensor_h sensor, float *max_range);

/**
 * @brief Gets the resolution of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  resolution      The resolution
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_resolution(sensor_h sensor, float *resolution);

/**
 * @brief Gets the minimun interval of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  min_interval    The minimum interval (in milliseconds)
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_min_interval(sensor_h sensor, int *min_interval);

/**
 * @brief Gets the fifo count of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  fifo_count      The fifo count
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_fifo_count(sensor_h sensor, int *fifo_count);

/**
 * @brief Gets the maximum batch count of the sensor.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]   sensor          The sensor handle
 * @param[out]  max_batch_count The maximum batch count
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 * @retval      #SENSOR_ERROR_IO_ERROR             I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_get_max_batch_count(sensor_h sensor, int *max_batch_count);
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_UTILITY_MODULE
 * @{
 */

/**
 * @brief  Enumeration of the axis used in #sensor_util_remap_coordinate_system.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
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
 * @brief Gets the Inclination matrix "I" and Rotation matrix "R" transforming a vector from the device coordinate to the world's coordinate.
 *
 * @details [0 0 g] = R * gravity (g = magnitude of gravity) \n
 *          [0 m 0] = I * R * geomagnetic (m = magnitude of the geomagnetic field) \n
 *          R is the identity matrix when the device is aligned with the world's coordinate system, that is, when the device's X axis points towards the East, the Y axis points to the North Pole and the device is facing the sky. \n
 *          I is a rotation matrix transforming the geomagnetic vector into the same coordinate space as gravity (the world's coordinate space). I is a simple rotation around the X axis. \n
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @remarks Parameters Gx, Gy, and Gz can be obtained from the values returned by #SENSOR_GRAVITY. \n
 *          Parameters Mx, My, and Mz can be obtained from the values returned by #SENSOR_MAGNETIC.
 *          Output parameter R and I are always returned as a 3x3 matrix array of 9 floats like this form:
 *          <pre>
 *          { R[0], R[1], R[2],
 *            R[3], R[4], R[5],
 *            R[6], R[7], R[6] }
 *          </pre>
 *
 *
 * @param[in]  Gx   The X-axis gravity vector in the device's coordinate
 * @param[in]  Gy   The Y-axis gravity vector in the device's coordinate
 * @param[in]  Gz   The Z-axis gravity vector in the device's coordinate
 * @param[in]  Mx   The X-axis geomagnetic vector in the device's coordinate
 * @param[in]  My   The Y-axis geomagnetic vector in the device's coordinate
 * @param[in]  Mz   The Z-axis geomagnetic vector in the device's coordinate
 * @param[out] R    The array of 9 floats that represent the rotation matrix "R" \n
 *                  It can be null.
 * @param[out] I    The array of 9 floats that represent the inclination matrix "I" \n
 *                  It can be null.
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 */
int sensor_util_get_rotation_matrix(float Gx, float Gy, float Gz,
        float Mx, float My, float Mz,
        float R[], float I[]);

/**
 * @brief Converts a rotation vector to a rotation matrix.
 *
 * @details Rotation vectors (Vx, Vy, Vz) can be obtained from #SENSOR_ROTATION_VECTOR.
 *          It returns a 9 element rotation matrix in the array R. R must have length as 9.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]  Vx   The X-axis rotation vector
 * @param[in]  Vy   The Y-axis rotation vector
 * @param[in]  Vz   The Z-axis rotation vector
 * @param[out] R    A 9 element rotation matrix in the array R that must have length as 9
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 */
int sensor_util_get_rotation_matrix_from_vector(float Vx, float Vy, float Vz, float R[]);

/**
 * @brief Rotates the supplied rotation matrix so that it is expressed in a different coordinate system.
 *
 * @details This is typically used when an application needs to compute the three orientation angles of the device in a different coordinate system.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @remarks inR and outR can be the same array, but this is not recommended for performance reasons.
 *          This returns an error when X and Y define the same axis.
 *
 * @param[in]  inR  The rotation matrix (3x3) to be transformed
 * @param[in]  x    The world axis and direction on which the X axis of the device is mapped
 * @param[in]  y    The world axis and direction on which the Y axis of the device is mapped
 * @param[out] outR The transformed rotation matrix (3x3)
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 *
 */
int sensor_util_remap_coordinate_system(float inR[], sensor_util_axis_e x, sensor_util_axis_e y, float outR[]);

/**
 * @brief Computes the geomagnetic inclination angle in radians from the inclination matrix I returned by sensor_util_get_rotation_matrix().
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]  I            The inclination matrix from sensor_util_get_rotation_matrix()
 * @param[out] inclination  The geomagnetic inclination angle in radians
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 *
 * @see sensor_util_get_rotation_matrix()
 */
int sensor_util_get_inclination(float I[], float* inclination);

/**
 * @brief Computes the device's orientation based on the rotation matrix.
 *
 * @details When it returns, the array values are filled with the result:
 *          - values[0]: azimuth, rotation around the Z axis.
 *          - values[1]: pitch, rotation around the X axis.
 *          - values[2]: roll, rotation around the Y axis.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @remarks Parameter R must be an array of 9 floats from sensor_util_get_rotation_matrix() \n
 *          Returned values are always arrays of 3 floats.
 *
 * @param[in]  R         A 9 element rotation matrix in the array
 * @param[out] values    An array of 3 floats to hold the result
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 *
 * @see sensor_util_get_rotation_matrix()
 *
 */
int sensor_util_get_orientation(float R[], float values[]);

/**
 * @brief Computes the angle change between two rotation matrices.
 *
 * @details Given a current rotation matrix (R) and a previous rotation matrix (prevR), it computes
 *          the rotation around the x,y, and z axes which transforms prevR to R.
 *          It outputs a 3 element vector containing the x,y, and z angle change at indexes 0, 1, and 2 respectively. \n
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @remarks Each input matrix is a 3x3 matrix like this form:
 *          <pre>
 *          { R[0], R[1], R[2],
 *            R[3], R[4], R[5],
 *            R[6], R[7], R[6] }
 *          </pre>
 *
 * @param[in] R             The current rotation matrix
 * @param[in] prevR         The previous rotation matrix
 * @param[out] angleChange  An array of floats in which the angle change is stored
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 */
int sensor_util_get_angle_change(float R[], float prevR[], float angleChange[]);

/**
 * @brief Gets the declination of the horizontal component of the magnetic field from true north, in degrees.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]  latitude     The latitude in geodetic coordinates
 * @param[in]  longitude    The longitude in geodetic coordinates
 * @param[in]  altitude     The altitude in geodetic coordinates
 * @param[out] declination  The declination of the horizontal component of the magnetic field in degrees
 *
 * @return      @c 0 on success,
 *              otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                 Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED        The sensor type is not supported in the current device
 */
int sensor_util_get_declination(float latitude, float longitude, float altitude, float* declination);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H__ */
