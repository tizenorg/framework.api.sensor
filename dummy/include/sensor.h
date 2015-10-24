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

#pragma GCC diagnostic warning "-Wunused-value"
#pragma GCC diagnostic warning "-Wunused-variable"
#pragma GCC diagnostic warning "-Wunused-but-set-variable"
#pragma GCC diagnostic warning "-Wmaybe-uninitialized"

#include <tizen.h>

#define MAX_VALUE_SIZE 16

#ifdef __cplusplus
extern "C"
{
#endif

typedef void* sensor_h;

typedef struct sensor_listener_s *sensor_listener_h;

typedef struct
{
	int accuracy;                  /**< Accuracy */
	unsigned long long timestamp;  /**< Timestamp */
	int value_count;               /**< Count of values */
	float values[MAX_VALUE_SIZE];  /**< Sensor values */
} sensor_event_s;

typedef enum
{
	SENSOR_DATA_ACCURACY_UNDEFINED   = -1,  /**< Undefined accuracy */
	SENSOR_DATA_ACCURACY_BAD         = 0,   /**< Bad accuracy */
	SENSOR_DATA_ACCURACY_NORMAL      = 1,   /**< Normal accuracy */
	SENSOR_DATA_ACCURACY_GOOD        = 2,   /**< Good accuracy */
	SENSOR_DATA_ACCURACY_VERYGOOD    = 3    /**< Very good accuracy */
} sensor_data_accuracy_e;

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

typedef enum
{
	SENSOR_PROXIMITY_NEAR = 0,    /**< The object is near */
	SENSOR_PROXIMITY_FAR = 5,     /**< The object is far */
} sensor_proximity_e;

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

#ifndef __SENSOR_COMMON_H__
typedef enum
{
	SENSOR_OPTION_DEFAULT,              /**< Does not receive data when the LCD is off and in the power save mode */
	SENSOR_OPTION_ON_IN_SCREEN_OFF,     /**< Receives data when the LCD is off */
	SENSOR_OPTION_ON_IN_POWERSAVE_MODE, /**< Receives data in the power save mode */
	SENSOR_OPTION_ALWAYS_ON,            /**< Receives data when the LCD is off and in the power save mode */
} sensor_option_e;
#endif

#define sensor_is_supported(type, supported) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_default_sensor(type, sensor) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_sensor_list(type, list, sensor_count) SENSOR_ERROR_NOT_SUPPORTED

typedef void (*sensor_event_cb)(sensor_h sensor, sensor_event_s *event, void *data);

#define sensor_create_listener(sensor, listener) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_destroy_listener(listener) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_start(listener) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_stop(listener) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_set_event_cb(listener, interval_ms, callback, data) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_unset_event_cb(listener) SENSOR_ERROR_NOT_SUPPORTED

typedef void (*sensor_accuracy_changed_cb)(sensor_h sensor, unsigned long long timestamp, sensor_data_accuracy_e accuracy, void *data);

#define sensor_listener_set_accuracy_cb(listener, callback, data) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_unset_accuracy_cb(listener) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_read_data(listener, event) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_set_interval(listener, interval_ms) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_set_max_batch_latency(listener, max_batch_latency) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_listener_set_option(listener, option) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_name(sensor, name) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_vendor(sensor, vendor) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_type(sensor, type) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_min_range(sensor, min_range) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_max_range(sensor, max_range) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_resolution(sensor, resolution) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_min_interval(sensor, min_interval) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_fifo_count(sensor, fifo_count) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_get_max_batch_count(sensor, max_batch_count) SENSOR_ERROR_NOT_SUPPORTED

typedef enum
{
    sensor_util_axis_minus_x,
    sensor_util_axis_minus_y,
    sensor_util_axis_minus_z,
    sensor_util_axis_x,
    sensor_util_axis_y,
    sensor_util_axis_z,
} sensor_util_axis_e;

#define sensor_util_get_rotation_matrix(Gx, Gy, Gz, Mx, My, Mz, R, I) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_util_get_rotation_matrix_from_vector(Vx, Vy, Vz, R) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_util_remap_coordinate_system(inR, x, y, outR) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_util_get_inclination(I, inclination) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_util_get_orientation(R, values) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_util_get_angle_change(R, prevR, angleChange) SENSOR_ERROR_NOT_SUPPORTED
#define sensor_util_get_declination(latitude, longitude, altitude, declination) SENSOR_ERROR_NOT_SUPPORTED

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H__ */
