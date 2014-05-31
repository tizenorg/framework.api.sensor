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

#define API_NAME_SENSOR_PROXIMITY_SET_CB "sensor_proximity_set_cb"
#define API_NAME_SENSOR_MOTION_FACEDOWN_SET_CB "sensor_motion_facedown_set_cb"
#define API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB "sensor_motion_doubletap_set_cb"
#define API_NAME_SENSOR_MOTION_PANNING_SET_CB "sensor_motion_panning_set_cb"
#define API_NAME_SENSOR_MOTION_SHAKE_SET_CB "sensor_motion_shake_set_cb"
#define API_NAME_SENSOR_MOTION_SNAP_SET_CB "sensor_motion_snap_set_cb"

#define TEST_STRING "TEST_TEST_TEST"

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_system_sensor_motion_doubletap_set_cb_p(void);
static void utc_system_sensor_motion_facedown_set_cb_p(void);
static void utc_system_sensor_motion_panning_set_cb_p(void);
static void utc_system_sensor_motion_shake_set_cb_p(void);
static void utc_system_sensor_motion_snap_set_cb_p(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_system_sensor_motion_doubletap_set_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_motion_facedown_set_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_motion_panning_set_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_motion_shake_set_cb_p, POSITIVE_TC_IDX },
	{ utc_system_sensor_motion_snap_set_cb_p, POSITIVE_TC_IDX },
	{ NULL, 0},
};

static bool support_doubletap;
static bool support_facedown;
static bool support_panning;
static bool support_shake;
static bool support_snap;
static bool support_proximity;

static sensor_h handle;
static GMainLoop* mainloop;

static void startup(void)
{
    int error = SENSOR_ERROR_NONE;

    sensor_is_supported(SENSOR_MOTION_DOUBLETAP, &support_doubletap);
    sensor_is_supported(SENSOR_MOTION_FACEDOWN, &support_facedown);
    sensor_is_supported(SENSOR_MOTION_PANNING, &support_panning);
    sensor_is_supported(SENSOR_MOTION_SHAKE, &support_shake);
    sensor_is_supported(SENSOR_MOTION_SNAP, &support_snap);

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

static bool called = false;
static int timeout = 100;

static void test_callback_snap (sensor_motion_snap_e snap, void *user_data)
{
    char* ud = (char*)user_data;

    if(strcmp(ud, TEST_STRING) == 0)
        called = true;
    
    if(mainloop)
        g_main_loop_quit(mainloop);
}
static void test_callback_shake (sensor_motion_shake_e shake, void *user_data)
{
    char* ud = (char*)user_data;

    if(strcmp(ud, TEST_STRING) == 0)
        called = true;
    
    if(mainloop)
        g_main_loop_quit(mainloop);
}
static void test_callback_doubletap (void *user_data)
{
    char* ud = (char*)user_data;

    if(strcmp(ud, TEST_STRING) == 0)
        called = true;
    
    if(mainloop)
        g_main_loop_quit(mainloop);
}
static void test_callback_panning (int x, int y, void *user_data)
{
    char* ud = (char*)user_data;

    if(strcmp(ud, TEST_STRING) == 0)
        called = true;
    
    if(mainloop)
        g_main_loop_quit(mainloop);
}
static void test_callback_facedown (void *user_data)
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

/**
 * @brief Positive test case of sensor_motion_doubletap_set_cb()
 */
static void utc_system_sensor_motion_doubletap_set_cb_p(void)
{
    int i=0;
    int error = SENSOR_ERROR_NONE;

    if(!support_doubletap)
        dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);

    mainloop = g_main_loop_new(NULL, FALSE);

    called = false;
    error = sensor_motion_doubletap_set_cb(handle, test_callback_doubletap, TEST_STRING);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);

    sensor_start(handle, SENSOR_MOTION_DOUBLETAP);

    g_timeout_add(1000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_main_loop_unref(mainloop);

    sensor_motion_doubletap_unset_cb(handle);
    sensor_stop(handle, SENSOR_MOTION_DOUBLETAP);

    if(called){
        dts_pass(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB);
    }

    dts_fail(API_NAME_SENSOR_MOTION_DOUBLETAP_SET_CB, "Time out");
}

/**
 * @brief Positive test case of sensor_motion_facedown_set_cb()
 */
static void utc_system_sensor_motion_facedown_set_cb_p(void)
{
    int i=0;
    int error = SENSOR_ERROR_NONE;

    if(!support_facedown)
        dts_pass(API_NAME_SENSOR_MOTION_FACEDOWN_SET_CB);

    mainloop = g_main_loop_new(NULL, FALSE);

    called = false;
    error = sensor_motion_facedown_set_cb(handle, test_callback_facedown, TEST_STRING);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_FACEDOWN_SET_CB);

    sensor_start(handle, SENSOR_MOTION_FACEDOWN);

    g_timeout_add(1000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_main_loop_unref(mainloop);

    sensor_motion_facedown_unset_cb(handle);
    sensor_stop(handle, SENSOR_MOTION_FACEDOWN);

    if(called){
        dts_pass(API_NAME_SENSOR_MOTION_FACEDOWN_SET_CB);
    }

    dts_fail(API_NAME_SENSOR_MOTION_FACEDOWN_SET_CB, "Time out");
}

/**
 * @brief Positive test case of sensor_motion_panning_set_cb()
 */
static void utc_system_sensor_motion_panning_set_cb_p(void)
{
    int i=0;
    int error = SENSOR_ERROR_NONE;

    if(!support_panning)
        dts_pass(API_NAME_SENSOR_MOTION_PANNING_SET_CB);

    mainloop = g_main_loop_new(NULL, FALSE);

    called = false;
    error = sensor_motion_panning_set_cb(handle, test_callback_panning, TEST_STRING);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_PANNING_SET_CB);

    sensor_start(handle, SENSOR_MOTION_PANNING);

    g_timeout_add(1000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_main_loop_unref(mainloop);

    sensor_motion_panning_unset_cb(handle);
    sensor_stop(handle, SENSOR_MOTION_PANNING);

    if(called){
        dts_pass(API_NAME_SENSOR_MOTION_PANNING_SET_CB);
    }

    dts_fail(API_NAME_SENSOR_MOTION_PANNING_SET_CB, "Time out");
}

/**
 * @brief Positive test case of sensor_motion_shake_set_cb()
 */
static void utc_system_sensor_motion_shake_set_cb_p(void)
{
    int i=0;
    int error = SENSOR_ERROR_NONE;

    if(!support_shake)
        dts_pass(API_NAME_SENSOR_MOTION_SHAKE_SET_CB);

    mainloop = g_main_loop_new(NULL, FALSE);

    called = false;
    error = sensor_motion_shake_set_cb(handle, test_callback_shake, TEST_STRING);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_SHAKE_SET_CB);

    sensor_start(handle, SENSOR_MOTION_SHAKE);

    g_timeout_add(1000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_main_loop_unref(mainloop);

    sensor_motion_shake_unset_cb(handle);
    sensor_stop(handle, SENSOR_MOTION_SHAKE);

    if(called){
        dts_pass(API_NAME_SENSOR_MOTION_SHAKE_SET_CB);
    }

    dts_fail(API_NAME_SENSOR_MOTION_SHAKE_SET_CB, "Time out");
}

/**
 * @brief Positive test case of sensor_motion_snap_set_cb()
 */
static void utc_system_sensor_motion_snap_set_cb_p(void)
{
    int i=0;
    int error = SENSOR_ERROR_NONE;

    if(!support_snap)
        dts_pass(API_NAME_SENSOR_MOTION_SNAP_SET_CB);

    mainloop = g_main_loop_new(NULL, FALSE);

    called = false;
    error = sensor_motion_snap_set_cb(handle, test_callback_snap, TEST_STRING);
    if(error != SENSOR_ERROR_NONE)
        dts_fail(API_NAME_SENSOR_MOTION_SNAP_SET_CB);

    sensor_start(handle, SENSOR_MOTION_SNAP);

    g_timeout_add(1000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_main_loop_unref(mainloop);

    sensor_motion_snap_unset_cb(handle);
    sensor_stop(handle, SENSOR_MOTION_SNAP);

    if(called){
        dts_pass(API_NAME_SENSOR_MOTION_SNAP_SET_CB);
    }

    dts_fail(API_NAME_SENSOR_MOTION_SNAP_SET_CB, "Time out");
}
