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




#ifndef __SENSOR_PRIVATE_H__
#define __SENSOR_PRIVATE_H__

#ifdef __cplusplus
extern "C"
{
#endif

enum _sensor_ids_index{
	ID_ACCELEOMETER,
	ID_GEOMAGNETIC,
	ID_GYROSCOPE,
	ID_LIGHT,
	ID_PROXIMITY,
	ID_MOTION,
	ID_PEDO,
	ID_BIO,
	ID_BIO_HRM,
	ID_NUMBERS
};

#define CB_NUMBERS (SENSOR_LAST)
#define CALIB_CB_NUMBERS (SENSOR_ORIENTATION+1)
#define WAKEUP_CB_NUMBERS (SENSOR_DEVICE_ORIENTATION+1)
#define EMPTY_EVENT 0

struct sensor_handle_s {
	int ids[ID_NUMBERS];
	int started[CB_NUMBERS];
	int sensor_option[CB_NUMBERS];

	void* cb_func[CB_NUMBERS];
	void* cb_user_data[CB_NUMBERS];

	void* calib_func[CALIB_CB_NUMBERS];
	void* calib_user_data[CALIB_CB_NUMBERS];

	void* wakeup_func[WAKEUP_CB_NUMBERS];
	void* wakeup_user_data[WAKEUP_CB_NUMBERS];
};

#define SENSOR_INIT(handle) \
do { \
	handle->ids[ID_ACCELEOMETER] = -1; \
	handle->ids[ID_GEOMAGNETIC] = -1; \
	handle->ids[ID_GYROSCOPE] = -1; \
	handle->ids[ID_LIGHT] = -1; \
	handle->ids[ID_PROXIMITY] = -1; \
	handle->ids[ID_MOTION] = -1; \
	handle->ids[ID_PEDO] = -1; \
	handle->ids[ID_BIO] = -1; \
	handle->ids[ID_BIO_HRM] = -1; \
	handle->started[SENSOR_ACCELEROMETER] = 0; \
	handle->started[SENSOR_GRAVITY] = 0; \
	handle->started[SENSOR_LINEAR_ACCELERATION] = 0; \
	handle->started[SENSOR_DEVICE_ORIENTATION] = 0; \
	handle->started[SENSOR_MAGNETIC] = 0; \
	handle->started[SENSOR_ORIENTATION] = 0; \
	handle->started[SENSOR_GYROSCOPE] = 0; \
	handle->started[SENSOR_LIGHT] = 0; \
	handle->started[SENSOR_PROXIMITY] = 0; \
	handle->started[SENSOR_MOTION_SNAP] = 0; \
	handle->started[SENSOR_MOTION_SHAKE] = 0; \
	handle->started[SENSOR_MOTION_DOUBLETAP] = 0; \
	handle->started[SENSOR_MOTION_PANNING] = 0; \
	handle->started[SENSOR_MOTION_PANNING_BROWSE] = 0; \
	handle->started[SENSOR_MOTION_TILT] = 0; \
	handle->started[SENSOR_MOTION_FACEDOWN] = 0; \
	handle->started[SENSOR_MOTION_DIRECTCALL] = 0; \
	handle->started[SENSOR_MOTION_SMART_ALERT] = 0; \
	handle->started[SENSOR_MOTION_NO_MOVE] = 0; \
	handle->started[SENSOR_PEDOMETER_STEP] = 0; \
	handle->started[SENSOR_BIO] = 0; \
	handle->started[SENSOR_BIO_HRM] = 0; \
	handle->sensor_option[SENSOR_ACCELEROMETER] = 0; \
	handle->sensor_option[SENSOR_GRAVITY] = 0; \
	handle->sensor_option[SENSOR_LINEAR_ACCELERATION] = 0; \
	handle->sensor_option[SENSOR_DEVICE_ORIENTATION] = 0; \
	handle->sensor_option[SENSOR_MAGNETIC] = 0; \
	handle->sensor_option[SENSOR_ORIENTATION] = 0; \
	handle->sensor_option[SENSOR_GYROSCOPE] = 0; \
	handle->sensor_option[SENSOR_LIGHT] = 0; \
	handle->sensor_option[SENSOR_PROXIMITY] = 0; \
	handle->sensor_option[SENSOR_MOTION_SNAP] = 0; \
	handle->sensor_option[SENSOR_MOTION_SHAKE] = 0; \
	handle->sensor_option[SENSOR_MOTION_DOUBLETAP] = 0; \
	handle->sensor_option[SENSOR_MOTION_PANNING] = 0; \
	handle->sensor_option[SENSOR_MOTION_PANNING_BROWSE] = 0; \
	handle->sensor_option[SENSOR_MOTION_TILT] = 0; \
	handle->sensor_option[SENSOR_MOTION_FACEDOWN] = 0; \
	handle->sensor_option[SENSOR_MOTION_DIRECTCALL] = 0; \
	handle->sensor_option[SENSOR_MOTION_SMART_ALERT] = 1; \
	handle->sensor_option[SENSOR_MOTION_NO_MOVE] = 0; \
	handle->sensor_option[SENSOR_PEDOMETER_STEP] = 0; \
	handle->sensor_option[SENSOR_BIO] = 0; \
	handle->sensor_option[SENSOR_BIO_HRM] = 0; \
	handle->cb_func[SENSOR_ACCELEROMETER] = NULL; \
	handle->cb_func[SENSOR_GRAVITY] = NULL; \
	handle->cb_func[SENSOR_LINEAR_ACCELERATION] = NULL; \
	handle->cb_func[SENSOR_DEVICE_ORIENTATION] = NULL; \
	handle->cb_func[SENSOR_MAGNETIC] = NULL; \
	handle->cb_func[SENSOR_ORIENTATION] = NULL; \
	handle->cb_func[SENSOR_GYROSCOPE] = NULL; \
	handle->cb_func[SENSOR_LIGHT] = NULL; \
	handle->cb_func[SENSOR_PROXIMITY] = NULL; \
	handle->cb_func[SENSOR_MOTION_SNAP] = NULL; \
	handle->cb_func[SENSOR_MOTION_SHAKE] = NULL; \
	handle->cb_func[SENSOR_MOTION_DOUBLETAP] = NULL; \
	handle->cb_func[SENSOR_MOTION_PANNING] = NULL; \
	handle->cb_func[SENSOR_MOTION_PANNING_BROWSE] = NULL; \
	handle->cb_func[SENSOR_MOTION_TILT] = NULL; \
	handle->cb_func[SENSOR_MOTION_FACEDOWN] = NULL; \
	handle->cb_func[SENSOR_MOTION_DIRECTCALL] = NULL; \
	handle->cb_func[SENSOR_MOTION_SMART_ALERT] = NULL; \
	handle->cb_func[SENSOR_MOTION_NO_MOVE] = NULL; \
	handle->cb_func[SENSOR_PEDOMETER_STEP] = NULL; \
	handle->cb_func[SENSOR_BIO] = NULL; \
	handle->cb_func[SENSOR_BIO_HRM] = NULL; \
	handle->cb_user_data[SENSOR_ACCELEROMETER] = NULL; \
	handle->cb_user_data[SENSOR_GRAVITY] = NULL; \
	handle->cb_user_data[SENSOR_LINEAR_ACCELERATION] = NULL; \
	handle->cb_user_data[SENSOR_DEVICE_ORIENTATION] = NULL; \
	handle->cb_user_data[SENSOR_MAGNETIC] = NULL; \
	handle->cb_user_data[SENSOR_ORIENTATION] = NULL; \
	handle->cb_user_data[SENSOR_GYROSCOPE] = NULL; \
	handle->cb_user_data[SENSOR_LIGHT] = NULL; \
	handle->cb_user_data[SENSOR_PROXIMITY] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_SNAP] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_SHAKE] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_DOUBLETAP] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_PANNING] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_PANNING_BROWSE] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_TILT] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_FACEDOWN] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_DIRECTCALL] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_SMART_ALERT] = NULL; \
	handle->cb_user_data[SENSOR_MOTION_NO_MOVE] = NULL; \
	handle->cb_user_data[SENSOR_PEDOMETER_STEP] = NULL; \
	handle->cb_user_data[SENSOR_BIO] = NULL; \
	handle->cb_user_data[SENSOR_BIO_HRM] = NULL; \
	handle->calib_func[SENSOR_ACCELEROMETER] = NULL; \
	handle->calib_func[SENSOR_GRAVITY] = NULL; \
	handle->calib_func[SENSOR_LINEAR_ACCELERATION] = NULL; \
	handle->calib_func[SENSOR_DEVICE_ORIENTATION] = NULL; \
	handle->calib_func[SENSOR_MAGNETIC] = NULL; \
	handle->calib_func[SENSOR_ORIENTATION] = NULL; \
	handle->calib_user_data[SENSOR_ACCELEROMETER] = NULL; \
	handle->calib_user_data[SENSOR_GRAVITY] = NULL; \
	handle->calib_user_data[SENSOR_LINEAR_ACCELERATION] = NULL; \
	handle->calib_user_data[SENSOR_DEVICE_ORIENTATION] = NULL; \
	handle->calib_user_data[SENSOR_MAGNETIC] = NULL; \
	handle->calib_user_data[SENSOR_ORIENTATION] = NULL; \
	handle->wakeup_func[SENSOR_ACCELEROMETER] = NULL; \
	handle->wakeup_user_data[SENSOR_ACCELEROMETER] = NULL;\
}while(0) \

float clamp(float v);
int getAngleChange(float *R, float *prevR, float *angleChange);
int quatToMatrix(float *quat, float *R);
int matrixToQuat(float *mat, float *q);
int getRotationMatrix(float *accel, float *geo, float *R, float *I);
int remapCoordinateSystem(float *inR, int X, int Y, float *outR);
int getDeclination(float *decl);
int getInclination(float *incl);
int setCoordinate(float latitude, float longitude, float altitude, float *declination, float *inclination, int option);

#ifdef __cplusplus
}
#endif

#endif // __SENSOR_PRIVATE_H__ 
