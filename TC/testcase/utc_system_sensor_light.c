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

#include <glib.h>

#undef LOG_TAG
#define LOG_TAG "SENSOR_TC"

#define API_NAME "sensor_light"
#define API_NAME_SENSOR_LIGHT_SET_CB "sensor_light_set_cb"
#define API_NAME_SENSOR_LIGHT_UNSET_CB "sensor_light_unset_cb"
#define API_NAME_SENSOR_LIGHT_READ_DATA "sensor_light_read_data"

#define TEST_STRING "TEST_TEST_TEST"

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_system_sensor_light_set_cb_p(void);
static void utc_system_sensor_light_set_cb_n(void);
static void utc_system_sensor_light_read_data_p(void);
static void utc_system_sensor_light_read_data_n(void);
static void utc_system_sensor_light_unset_cb_p(void);
static void utc_system_sensor_light_unset_cb_n(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_system_sensor_light_set_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_light_set_cb_n, NEGATIVE_TC_IDX },
	{ utc_system_sensor_light_read_data_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_light_read_data_n, NEGATIVE_TC_IDX },
	{ utc_system_sensor_light_unset_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_light_unset_cb_n, NEGATIVE_TC_IDX },
	{ NULL, 0},
};

static bool support;
static sensor_h handle;
static GMainLoop* mainloop;

static void startup(void)
{
    int error = SENSOR_ERROR_NONE;

    sensor_is_supported(SENSOR_LIGHT, &support);

    error = sensor_create( &handle);
    if (error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME);

    mainloop = g_main_loop_new(NULL, FALSE);
}

static void cleanup(void)
{
    int error = SENSOR_ERROR_NONE;

    error = sensor_destroy(handle);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME);
}

static bool called = false;
static int timeout = 100;

static void test_callback(sensor_data_accuracy_e accuracy, float lux, void* user_data)
{
    char* ud = (char*)user_data;

    if(strcmp(ud, TEST_STRING) == 0)
        called = true;

    if(mainloop)
        g_main_loop_quit(mainloop);
}

gboolean timeout_func(gpointer data)
{
    static int i=0;

    i++;
    if(timeout == i){
        g_main_loop_quit((GMainLoop*)data);
        return FALSE;
    }

    return TRUE;
}


static void utc_system_sensor_light_set_cb_p(void)
{
    int i=0; 
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_LIGHT_SET_CB);

    called = false;
    error = sensor_light_set_cb(handle, 0, test_callback, TEST_STRING);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_SET_CB);

    sensor_start(handle, SENSOR_LIGHT);

    g_timeout_add(1000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_main_loop_unref(mainloop);

    sensor_light_unset_cb(handle);
    sensor_stop(handle, SENSOR_LIGHT);
    if(called){
        dts_pass(API_NAME_SENSOR_LIGHT_SET_CB);
    }

    dts_fail(API_NAME_SENSOR_LIGHT_SET_CB, "Time out");
}

/**
 * @brief Negative test case of sensor_light_set_cb()
 */
static void utc_system_sensor_light_set_cb_n(void)
{
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_LIGHT_SET_CB);

    called = false;
    error = sensor_light_set_cb(NULL, 0, test_callback, TEST_STRING);

    if(error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_SET_CB);

    dts_pass(API_NAME_SENSOR_LIGHT_SET_CB);
}

/**
 * @brief Positive test case of sensor_light_read_data()
 */
static void utc_system_sensor_light_read_data_p(void)
{
    int error = SENSOR_ERROR_NONE;
    sensor_data_accuracy_e accuracy = SENSOR_DATA_ACCURACY_UNDEFINED;
    float lux = 0;

    if(!support)
        dts_pass(API_NAME_SENSOR_LIGHT_READ_DATA);

    error = sensor_start(handle, SENSOR_LIGHT);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_READ_DATA);

    error = sensor_light_read_data(handle, &lux);

    error = sensor_stop(handle, SENSOR_LIGHT);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_READ_DATA);

    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_READ_DATA);

    dts_pass(API_NAME_SENSOR_LIGHT_READ_DATA);
}

/**
 * @brief Negative test case of sensor_light_read_data()
 */
static void utc_system_sensor_light_read_data_n(void)
{
    int error = SENSOR_ERROR_NONE;
    sensor_data_accuracy_e accuracy = SENSOR_DATA_ACCURACY_UNDEFINED;
    float lux = 0;

    if(!support)
        dts_pass(API_NAME_SENSOR_LIGHT_READ_DATA);

    error = sensor_light_read_data(NULL, &lux);

    if(error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_READ_DATA);

    dts_pass(API_NAME_SENSOR_LIGHT_READ_DATA);
}

/**
 * @brief Positive test case of sensor_light_unset_cb()
 */
static void utc_system_sensor_light_unset_cb_p(void)
{
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_LIGHT_UNSET_CB);

    called = false;
    error = sensor_light_set_cb(handle, 0, test_callback, TEST_STRING);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_UNSET_CB);

    error = sensor_light_unset_cb(handle);

    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_UNSET_CB);

    dts_pass(API_NAME_SENSOR_LIGHT_UNSET_CB);
}

/**
 * @brief Negative test case of sensor_light_unset_cb()
 */
static void utc_system_sensor_light_unset_cb_n(void)
{
    int error = SENSOR_ERROR_NONE;

    if(!support)
        dts_pass(API_NAME_SENSOR_LIGHT_UNSET_CB);

    error = sensor_light_unset_cb(NULL);

    if(error == SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_LIGHT_UNSET_CB);

    dts_pass(API_NAME_SENSOR_LIGHT_UNSET_CB);
}
