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

#include <math.h>
#include <stdlib.h>

float clamp(float v)
{
	return (v < 0) ? 0.0 : v;
}

int getAngleChange(float *R, float *prevR, float *angleChange)
{
	if (R == NULL || prevR == NULL || angleChange == NULL)
		return -1;

	float rd1, rd4, rd6, rd7, rd8;
	float ri0, ri1, ri2, ri3, ri4, ri5, ri6, ri7, ri8;
	float pri0, pri1, pri2, pri3, pri4, pri5, pri6, pri7, pri8;

	ri0 = R[0];
	ri1 = R[1];
	ri2 = R[2];
	ri3 = R[3];
	ri4 = R[4];
	ri5 = R[5];
	ri6 = R[6];
	ri7 = R[7];
	ri8 = R[8];

	pri0 = prevR[0];
	pri1 = prevR[1];
	pri2 = prevR[2];
	pri3 = prevR[3];
	pri4 = prevR[4];
	pri5 = prevR[5];
	pri6 = prevR[6];
	pri7 = prevR[7];
	pri8 = prevR[8];

	rd1 = pri0 * ri1 + pri3 * ri4 + pri6 * ri7;
	rd4 = pri1 * ri1 + pri4 * ri4 + pri7 * ri7;
	rd6 = pri2 * ri0 + pri5 * ri3 + pri8 * ri6;
	rd7 = pri2 * ri1 + pri5 * ri4 + pri8 * ri7;
	rd8 = pri2 * ri2 + pri5 * ri5 + pri8 * ri8;

	angleChange[0] = atan2(rd1, rd4);
	angleChange[1] = asin(-rd7);
	angleChange[2] = atan2(-rd6, rd8);

	return 0;
}
int quatToMatrix(float *quat, float *R)
{
	if (quat == NULL || R == NULL)
		return -1;

	float q0 = quat[0];
	float q1 = quat[1];
	float q2 = quat[2];
	float q3 = quat[3];

	float sq_q1 = 2 * q1 * q1;
	float sq_q2 = 2 * q2 * q2;
	float sq_q3 = 2 * q3 * q3;
	float q1_q2 = 2 * q1 * q2;
	float q3_q0 = 2 * q3 * q0;
	float q1_q3 = 2 * q1 * q3;
	float q2_q0 = 2 * q2 * q0;
	float q2_q3 = 2 * q2 * q3;
	float q1_q0 = 2 * q1 * q0;

	R[0] = 1 - sq_q2 - sq_q3;
	R[1] = q1_q2 - q3_q0;
	R[2] = q1_q3 + q2_q0;
	R[3] = q1_q2 + q3_q0;
	R[4] = 1 - sq_q1 - sq_q3;
	R[5] = q2_q3 - q1_q0;
	R[6] = q1_q3 - q2_q0;
	R[7] = q2_q3 + q1_q0;
	R[8] = 1 - sq_q1 - sq_q2;

	return 0;
}

int matrixToQuat(float *mat, float *q)
{
	if (q == NULL || mat == NULL)
		return -1;

	const float Hx = mat[0];
	const float My = mat[4];
	const float Az = mat[8];
	q[0] = sqrtf(clamp(Hx - My - Az + 1) * 0.25f);
	q[1] = sqrtf(clamp(-Hx + My - Az + 1) * 0.25f);
	q[2] = sqrtf(clamp(-Hx - My + Az + 1) * 0.25f);
	q[3] = sqrtf(clamp(Hx + My + Az + 1) * 0.25f);
	q[0] = copysignf(q[0], mat[7] - mat[5]);
	q[1] = copysignf(q[1], mat[2] - mat[6]);
	q[2] = copysignf(q[2], mat[3] - mat[1]);

	return 0;
}

int getRotationMatrix(float *accel, float *geo, float *R, float *I)
{
	if (accel == NULL || geo == NULL || R == NULL || I == NULL)
		return -1;

	float Ax = accel[0];
	float Ay = accel[1];
	float Az = accel[2];
	float Ex = geo[0];
	float Ey = geo[1];
	float Ez = geo[2];
	float Hx = Ey*Az - Ez*Ay;
	float Hy = Ez*Ax - Ex*Az;
	float Hz = Ex*Ay - Ey*Ax;
	float normH =  (float)sqrt(Hx*Hx + Hy*Hy + Hz*Hz);
	if (normH < 0.1f) {
		return -1;
	}
	float invH = 1.0f / normH;
	Hx *= invH;
	Hy *= invH;
	Hz *= invH;
	float invA = 1.0f / (float)sqrt(Ax*Ax + Ay*Ay + Az*Az);
	Ax *= invA;
	Ay *= invA;
	Az *= invA;
	float Mx = Ay*Hz - Az*Hy;
	float My = Az*Hx - Ax*Hz;
	float Mz = Ax*Hy - Ay*Hx;

	R[0] = Hx;  R[1] = Hy;  R[2] = Hz;
	R[3] = Mx;  R[4] = My;  R[5] = Mz;
	R[6] = Ax;  R[7] = Ay;	R[8] = Az;

	float invE = 1.0 / (float)sqrt(Ex*Ex + Ey*Ey + Ez*Ez);
	float c = (Ex*Mx + Ey*My + Ez*Mz) * invE;
	float s = (Ex*Ax + Ey*Ay + Ez*Az) * invE;

	I[0] = 1;     I[1] = 0;     I[2] = 0;
	I[3] = 0;     I[4] = c;     I[5] = s;
	I[6] = 0;     I[7] = -s;    I[8] = c;

	return 0;
}


int remapCoordinateSystem(float *inR, int X, int Y, float *outR)
{
	if (inR == NULL || outR == NULL)
		return -1;

	if ((X & 0x7C) != 0 || (Y & 0x7C) != 0)
		return -1;   /* invalid parameter */
	if (((X & 0x3) == 0) || ((Y & 0x3) == 0))
		return -1;   /* no axis specified */
	if ((X & 0x3) == (Y & 0x3))
		return -1;   /* same axis specified */

	int Z = X ^ Y;
	int x = (X & 0x3)-1;
	int y = (Y & 0x3)-1;
	int z = (Z & 0x3)-1;

	int axis_y = (z+1)%3;
	int axis_z = (z+2)%3;
	if (((x^axis_y)|(y^axis_z)) != 0)
		Z ^= 0x80;

	char sx = (X >= 0x80) ? 1 : 0;
	char sy = (Y >= 0x80) ? 1 : 0;
	char sz = (Z >= 0x80) ? 1 : 0;

	int i = 0 , j = 0;
	for (j = 0 ; j < 3 ; j++) {
		int offset = j * 3;
		for (i = 0 ; i < 3 ; i++) {
			if (x == i)   outR[offset+i] = sx ? -inR[offset+0] : inR[offset+0];
			if (y == i)   outR[offset+i] = sy ? -inR[offset+1] : inR[offset+1];
			if (z == i)   outR[offset+i] = sz ? -inR[offset+2] : inR[offset+2];
		}
	}
	return 0;
}

