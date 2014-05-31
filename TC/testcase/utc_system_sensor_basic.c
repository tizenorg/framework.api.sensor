/*
 * 
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 * PROPRIETARY/CONFIDENTIAL
 * 
 * This software is the confidential and proprietary information of SAMSUNG 
 * ELECTRONICS ("Confidential Information"). You agree and acknowledge that 
 * this software is owned by Samsung and you shall not disclose such 
 * Confidential Information and shall use it only in accordance with the terms 
 * of the license agreement you entered into with SAMSUNG ELECTRONICS. SAMSUNG 
 * make no representations or warranties about the suitability of the software, 
 * either express or implied, including but not limited to the implied 
 * warranties of merchantability, fitness for a particular purpose, or 
 * non-infringement. SAMSUNG shall not be liable for any damages suffered by 
 * licensee arising out of or related to this software.
 * 
 */
#include <tet_api.h>
#include <sensors.h>
#include <dlog.h>

#undef LOG_TAG
#define LOG_TAG "SENSOR_TC"

#define API_NAME_SENSOR_CREATE "sensor_create"
#define API_NAME_SENSOR_DESTROY "sensor_destroy"
#define API_NAME_SENSOR_START "sensor_start"
#define API_NAME_SENSOR_STOP "sensor_stop"
#define API_NAME_SENSOR_GET_SPEC "sensor_get_spec"

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_system_sensor_create_p(void);
static void utc_system_sensor_create_n(void);
static void utc_system_sensor_destroy_p(void);
static void utc_system_sensor_destroy_n(void);
static void utc_system_sensor_start_p(void);
static void utc_system_sensor_start_n_1(void);
static void utc_system_sensor_start_n_2(void);
static void utc_system_sensor_stop_p(void);
static void utc_system_sensor_stop_n_1(void);
static void utc_system_sensor_stop_n_2(void);
static void utc_system_sensor_stop_n_3(void);
static void utc_system_sensor_get_spec_p(void);
static void utc_system_sensor_get_spec_n(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_system_sensor_create_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_create_n, NEGATIVE_TC_IDX },
	{ utc_system_sensor_destroy_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_destroy_n, NEGATIVE_TC_IDX },
	{ utc_system_sensor_start_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_start_n_1, NEGATIVE_TC_IDX },
	{ utc_system_sensor_start_n_2, NEGATIVE_TC_IDX },
	{ utc_system_sensor_stop_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_stop_n_1, NEGATIVE_TC_IDX },
	{ utc_system_sensor_stop_n_2, NEGATIVE_TC_IDX },
	{ utc_system_sensor_stop_n_3, NEGATIVE_TC_IDX },
	{ utc_system_sensor_get_spec_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_get_spec_n, NEGATIVE_TC_IDX },
	{ NULL, 0},
};

static void startup(void)
{
	
}

static void cleanup(void)
{
	/* end of TC */
}

/**
 * @brief Positive test case of sensor_create()
 */
static void utc_system_sensor_create_p(void)
{
    sensor_h handle;
    int error = SENSOR_ERROR_NONE;

    error = sensor_create(&handle);
    if (error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_CREATE);
    sensor_destroy(handle);

    dts_pass(API_NAME_SENSOR_CREATE);
}

/**
 * @brief Negative test case of sensor_create()
 */
static void utc_system_sensor_create_n(void)
{
    int error = SENSOR_ERROR_NONE;

    error = sensor_create(NULL);
    if (error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_CREATE);

    dts_pass(API_NAME_SENSOR_CREATE);
}

/**
 * @brief Positive test case of sensor_destroy()
 */
static void utc_system_sensor_destroy_p(void)
{
    sensor_h handle;
    int error = SENSOR_ERROR_NONE;

    error = sensor_create(&handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    dts_pass(API_NAME_SENSOR_DESTROY);
}

/**
 * @brief Negative test case of sensor_destroy()
 */
static void utc_system_sensor_destroy_n(void)
{
    int error = SENSOR_ERROR_NONE;

    error = sensor_destroy(NULL);
    if(error == SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    dts_pass(API_NAME_SENSOR_DESTROY);
}

/**
 * @brief Positive test case of sensor_start()
 */
static void utc_system_sensor_start_p(void)
{
    int error = SENSOR_ERROR_NONE;

    int i=0;

    sensor_h handle;
    error = sensor_create(&handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_START);
    }

    sensor_type_e types[] = {
        SENSOR_ACCELEROMETER,
        SENSOR_MAGNETIC,
        SENSOR_ORIENTATION,
        SENSOR_GYROSCOPE,
        SENSOR_LIGHT,
        SENSOR_PROXIMITY,
        SENSOR_MOTION_SNAP,
        SENSOR_MOTION_SHAKE,
        SENSOR_MOTION_DOUBLETAP,
        SENSOR_MOTION_PANNING,
        SENSOR_MOTION_FACEDOWN
    };

    for(i=0; i<9; i++){
        error = sensor_start(handle, types[i]);
        if(error == SENSOR_ERROR_NOT_SUPPORTED){
            dts_message(API_NAME_SENSOR_START, "%d is passed", i);
            continue;
        }
        if(error != SENSOR_ERROR_NONE){
            dts_message(API_NAME_SENSOR_START, "%d, %x", i, error);
            dts_fail(API_NAME_SENSOR_START);
        }
        sensor_stop(handle, types[i]);
    }

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_START);
    }

    dts_pass(API_NAME_SENSOR_START);
}

/**
 * @brief Negative test case of sensor_start()
 */
static void utc_system_sensor_start_n_1(void)
{
    int error = SENSOR_ERROR_NONE;

    int i=0;

    sensor_type_e types[] = {
        SENSOR_ACCELEROMETER,
        SENSOR_MAGNETIC,
        SENSOR_ORIENTATION,
        SENSOR_GYROSCOPE,
        SENSOR_LIGHT,
        SENSOR_PROXIMITY,
        SENSOR_MOTION_SNAP,
        SENSOR_MOTION_SHAKE,
        SENSOR_MOTION_DOUBLETAP,
        SENSOR_MOTION_PANNING,
        SENSOR_MOTION_FACEDOWN
    };

    for(i=0; i<9; i++){
        error = sensor_start(NULL, types[i]);
        if(error == SENSOR_ERROR_NONE)
            dts_fail(API_NAME_SENSOR_START);
    }

    dts_pass(API_NAME_SENSOR_START);
}

/**
 * @brief Negative test case of sensor_start()
 */
static void utc_system_sensor_start_n_2(void)
{
    int error = SENSOR_ERROR_NONE;

    int i=0;

    sensor_h handle;
    error = sensor_create(&handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    error = sensor_start(handle, -1);
    if(error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_START);

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    dts_pass(API_NAME_SENSOR_START);
}

/**
 * @brief Positive test case of sensor_stop()
 */
static void utc_system_sensor_stop_p(void)
{
    int error = SENSOR_ERROR_NONE;

    int i=0;

    sensor_h handle;
    error = sensor_create(&handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    sensor_type_e types[] = {
        SENSOR_ACCELEROMETER,
        SENSOR_MAGNETIC,
        SENSOR_ORIENTATION,
        SENSOR_GYROSCOPE,
        SENSOR_LIGHT,
        SENSOR_PROXIMITY,
        SENSOR_MOTION_SNAP,
        SENSOR_MOTION_SHAKE,
        SENSOR_MOTION_DOUBLETAP,
        SENSOR_MOTION_PANNING,
        SENSOR_MOTION_FACEDOWN
    };

    for(i=0; i<9; i++){
        error = sensor_start(handle, types[i]);
        if(error == SENSOR_ERROR_NOT_SUPPORTED)
            continue;
        if(error != SENSOR_ERROR_NONE){
            dts_message(API_NAME_SENSOR_STOP, "%d", i);
            dts_fail(API_NAME_SENSOR_STOP);
        }
        
        error = sensor_stop(handle, types[i]);
        if(error != SENSOR_ERROR_NONE)
            dts_fail(API_NAME_SENSOR_STOP);
    }

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_STOP);
    }

    dts_pass(API_NAME_SENSOR_STOP);
}

/**
 * @brief Negative test case of sensor_stop()
 */
static void utc_system_sensor_stop_n_1(void)
{
    int error = SENSOR_ERROR_NONE;

    int i=0;

    sensor_type_e types[] = {
        SENSOR_ACCELEROMETER,
        SENSOR_MAGNETIC,
        SENSOR_ORIENTATION,
        SENSOR_GYROSCOPE,
        SENSOR_LIGHT,
        SENSOR_PROXIMITY,
        SENSOR_MOTION_SNAP,
        SENSOR_MOTION_SHAKE,
        SENSOR_MOTION_DOUBLETAP,
        SENSOR_MOTION_PANNING,
        SENSOR_MOTION_FACEDOWN
    };

    for(i=0; i<9; i++){
        error = sensor_stop(NULL, types[i]);
        if(error == SENSOR_ERROR_NONE)
            dts_fail(API_NAME_SENSOR_START);
    }

    dts_pass(API_NAME_SENSOR_STOP);
}

/**
 * @brief Negative test case of sensor_stop()
 */
static void utc_system_sensor_stop_n_2(void)
{
    int error = SENSOR_ERROR_NONE;

    int i=0;

    sensor_h handle;
    error = sensor_create(&handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    sensor_type_e types[] = {
        SENSOR_ACCELEROMETER,
        SENSOR_MAGNETIC,
        SENSOR_ORIENTATION,
        SENSOR_GYROSCOPE,
        SENSOR_LIGHT,
        SENSOR_PROXIMITY,
        SENSOR_MOTION_SNAP,
        SENSOR_MOTION_SHAKE,
        SENSOR_MOTION_DOUBLETAP,
        SENSOR_MOTION_PANNING,
        SENSOR_MOTION_FACEDOWN
    };

    for(i=0; i<9; i++){
        error = sensor_stop(handle, types[i]);
        if(error == SENSOR_ERROR_NONE)
            dts_fail(API_NAME_SENSOR_START);
    }

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    dts_pass(API_NAME_SENSOR_STOP);
}

/**
 * @brief Negative test case of sensor_stop()
 */
static void utc_system_sensor_stop_n_3(void)
{
    int error = SENSOR_ERROR_NONE;

    sensor_h handle;
    error = sensor_create(&handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    error = sensor_stop(handle, -1);
    if(error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_START);

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE){
        dts_fail(API_NAME_SENSOR_DESTROY);
    }

    dts_pass(API_NAME_SENSOR_STOP);
}

/**
 * @brief Positive test case of sensor_get_spec()
 */
static void utc_system_sensor_get_spec_p(void)
{
	int error = SENSOR_ERROR_NONE;

	int i = 0;
	float max, min, resolution;
	char *model, *vendor;

	sensor_type_e types[] = {
		SENSOR_ACCELEROMETER,
        SENSOR_MAGNETIC,
        SENSOR_ORIENTATION,
        SENSOR_GYROSCOPE,
        SENSOR_LIGHT,
        SENSOR_PROXIMITY,
    };

	for( i = 0 ; i < 6 ; i++)
	{
		error = sensor_get_spec(types[i], &vendor, &model, &max, &min, &resolution);
		if (error != SENSOR_ERROR_NONE)
			dts_fail(API_NAME_SENSOR_GET_SPEC);
	}

	dts_pass(API_NAME_SENSOR_GET_SPEC);
}

/**
 * @brief Negative test case of sensor_get_spec()
 */
static void utc_system_sensor_get_spec_n(void)
{
	int error = SENSOR_ERROR_NONE;

	int i = 0;
	float max, min, resolution;
	char *model, *vendor;

	sensor_type_e types[] = {
		SENSOR_MOTION_SNAP,
		SENSOR_MOTION_SHAKE,
		SENSOR_MOTION_DOUBLETAP,
		SENSOR_MOTION_PANNING,
		SENSOR_MOTION_FACEDOWN
	};

	for( i = 0 ; i < 5 ; i++)
	{
		error = sensor_get_spec(types[i], &vendor, &model, &max, &min, &resolution);
		if (error == SENSOR_ERROR_NONE)
			dts_fail(API_NAME_SENSOR_GET_SPEC);
	}

	dts_pass(API_NAME_SENSOR_GET_SPEC);
}
