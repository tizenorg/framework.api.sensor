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

struct sensor_listener_s {
	int id;
	int type;
	int option;
	unsigned int magic;
	void *sensor;
	void *callback;
	void *user_data;
	void *accu_callback;
	void *accu_user_data;
};

#ifdef __cplusplus
extern "C"
{
#endif

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
