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
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sensors.h>
#include <dlog.h>
#include <stdbool.h>

#undef LOG_TAG
#define LOG_TAG "SENSOR_TC"

#define API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB "sensor_motion_doubletap_set_cb"
#define API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB "sensor_motion_doubletap_unset_cb"

#define TEST_STRING "TEST_TEST_TEST"

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_system_sensor_motion_doubletap_set_cb_p(void);
static void utc_system_sensor_motion_doubletap_set_cb_n(void);
static void utc_system_sensor_motion_doubletap_unset_cb_p(void);
static void utc_system_sensor_motion_doubletap_unset_cb_n(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_system_sensor_motion_doubletap_set_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_motion_doubletap_set_cb_n, NEGATIVE_TC_IDX },
	{ utc_system_sensor_motion_doubletap_unset_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_motion_doubletap_unset_cb_n, NEGATIVE_TC_IDX },
	{ NULL, 0},
};

static bool support;
static sensor_h handle;

static void startup(void)
{
    int error = SENSOR_ERROR_NONE;

    sensor_is_supported(SENSOR_MOTION_DOUBLETAP, &support);

    error = sensor_create(&handle);
    if (error != SENSOR_ERROR_NONE)
        dts_fail("on start up");
}

static void cleanup(void)
{
    int error = SENSOR_ERROR_NONE;

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE)
        dts_fail("on clean up");
}

static void test_callback(void* user_data)
{
}

static void utc_system_sensor_motion_doubletap_set_cb_p(void)
{
    int i=0;
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);

    error = sensor_motion_doubletap_set_cb(handle, test_callback, TEST_STRING);
    sensor_motion_doubletap_unset_cb(handle);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);

    dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);
}


static void utc_system_sensor_motion_doubletap_set_cb_n(void)
{
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);

    error = sensor_motion_doubletap_set_cb(NULL, test_callback, TEST_STRING);

    if(error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);

    dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);
}

static void utc_system_sensor_motion_doubletap_unset_cb_p(void)
{
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB);

    error = sensor_motion_doubletap_set_cb(handle, test_callback, TEST_STRING);

    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB);

    error = sensor_motion_doubletap_unset_cb(handle);

    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB);

    dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB);
}

static void utc_system_sensor_motion_doubletap_unset_cb_n(void)
{
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB);

    error = sensor_motion_doubletap_unset_cb(NULL);

    if(error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB);

    dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_UNSET_CB);
}

