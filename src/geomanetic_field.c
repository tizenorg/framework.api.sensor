/*
 * This file is part of WMM source code.
 * The original code is the WMM Source from National Oceanic And Atmospheric.
 *
 * See the license below for more details.
 *
 * The WMM source code is in the public domain and not licensed or under
 * copyright. The information and software may be used freely by the public.
 * As required by 17 U.S.C. 403, third parties producing copyrighted works
 * consisting predominantly of the material produced by U.S.
 * government agencies must provide notice with such work  identifying the U.S.
 * Government material incorporated and stating that such material is not
 * subject to copyright protection.
 */

#include <math.h>
#include <stdlib.h>

const float c[13][13] = {
	{0.0, -29496.6, -3594.9, 3350.2, 3992.6, -1818.3, 1051.0, 2158.4, 1226.7, 512.8, -360.9, 1033.3, -1452.4, },
	{4944.4, -1586.3, 5241.4, -7122.5, 4476.4, 3631.5, 1296.8, -2663.8, 543.0, 1197.6, -1532.7, -699.6, -179.4, },
	{-4689.9, -498.9, 1445.0, 2385.6, 652.3, 1539.3, 1135.8, -136.1, -813.2, 369.4, 189.6, -859.0, 238.5, },
	{-490.5, 487.8, -424.2, 501.2, -746.9, -664.0, -1408.7, 927.7, -231.9, -431.5, -181.8, 557.5, 649.2, },
	{1584.9, -826.5, 343.7, -228.6, 66.1, -361.6, -124.4, 171.7, -516.0, 174.8, -23.4, -119.8, -292.1, },
	{453.4, 1451.7, -556.3, 0.0, 70.8, -5.5, 30.7, 64.2, 170.6, -417.8, 184.8, 79.2, 300.6, },
	{-393.2, 659.0, 612.7, -361.8, 7.2, 36.9, -52.3, 4.1, 74.8, -12.2, -12.4, -75.3, -20.8, },
	{-2053.7, -611.1, 133.1, 307.5, 43.2, -67.1, -2.1, 3.2, -35.3, 63.3, 44.1, 19.8, 58.5, },
	{737.3, -1121.6, 492.9, -465.2, 247.7, 48.1, -27.1, 1.1, -2.3, -22.0, 25.4, 41.0, -23.4, },
	{-2611.8, 1249.5, 1062.2, -405.9, -249.3, 139.2, 15.8, -15.8, 4.3, -6.2, -2.7, 0.9, -10.2, },
	{681.2, -21.1, 776.8, 514.2, -532.2, -41.3, -78.2, -16.4, -5.3, -4.9, -1.7, 1.9, 1.9, },
	{93.3, 695.4, -196.8, -431.1, 142.6, -37.6, -124.0, -29.6, -18.5, -5.2, -1.0, 2.2, -2.2, },
	{-807.3, 238.5, 1363.4, -1217.3, 167.0, 125.0, 0.0, 5.9, 7.7, -8.5, -0.6, 0.5, 0.0, }};


const float cd[13][13] = {
	{0.0, 11.6, -18.1, 1.0, -7.9, -7.9, -2.9, 2.7, -5.0, 0.0, 0.0, 0.0, 0.0, },
	{-25.9, 16.5, -7.6, -12.6, 12.7, 6.1, -3.8, -3.5, 6.7, -12.7, 0.0, 0.0, 0.0, },
	{-39.0, -10.2, 1.6, -5.6, -34.0, -13.8, -1.5, -17.4, -33.6, 0.0, -21.1, 0.0, 79.5, },
	{22.4, -7.6, -2.1, -6.1, 9.6, -4.7, 19.9, 26.6, 8.3, 24.9, 33.1, 32.8, 64.9, },
	{6.1, 10.6, 8.2, -0.6, -1.6, 2.0, -9.3, 4.9, -5.3, -22.6, 0.0, 0.0, -48.7, },
	{4.1, 13.8, 5.6, 8.9, -0.4, 0.7, -0.7, 1.9, 4.4, -10.1, -7.4, 0.0, 0.0, },
	{-3.8, -31.4, -4.0, -3.3, 1.2, 0.6, 1.1, -1.7, 2.1, 1.7, -8.3, 0.0, 0.0, },
	{24.8, 8.7, -2.0, -1.2, -4.9, -0.7, 0.2, 0.4, -1.5, -0.8, 0.0, 0.0, 0.0, },
	{-6.7, 11.2, 16.6, 10.7, 1.5, -0.7, 1.0, 0.2, 0.1, -1.0, -0.8, 0.0, 0.0, },
	{0.0, -21.7, 0.0, -5.6, 3.4, 0.0, -1.5, 0.8, 0.1, -0.1, -0.5, 0.0, 0.0, },
	{24.3, -21.1, 0.0, -11.7, -7.4, 0.0, -2.0, -1.6, 0.0, -0.1, -0.1, -0.3, 0.0, },
	{0.0, 40.9, 0.0, 24.0, 0.0, 9.4, 0.0, -2.3, -0.9, 0.0, -0.1, 0.0, -0.3, },
	{0.0, 0.0, 0.0, 0.0, 0.0, 20.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, }};

float g_declination = 0;
float g_inclination = 0;

static void E0000(int IENTRY, int maxdeg, float alt,float glat,float glon, float time, float *dec, float *dip, float *ti, float *gv);

int getDeclination(float *decl)
{
	if(decl == NULL)
		return -1;

	*decl = g_declination;

	return 0;
}

int getInclination(float *incl)
{
        if(incl == NULL)
                return -1;

        *incl = g_inclination;

        return 0;
}

int setCoordinate(float latitude, float longitude, float altitude, float *declination, float *inclination, int option)
{
	float dec, dip, ti, gv;
	float h;
	float rTd=0.017453292;

	E0000(0,12,0.0,0.0,0.0,0.0,NULL,NULL,NULL,NULL);
	E0000(1,0,altitude,latitude,longitude,2,&dec,&dip,&ti,&gv);

	h=ti*(cos((dip*rTd)));

	/* deal with geographic and magnetic poles */

	if (h < 100.0) /* at magnetic poles */
	{
		dec = 0;
	}

	if(option == 1)
	{
		if(declination != NULL)
			*declination = dec;
		if(inclination != NULL)
			*inclination = dip;
	}
	else if( option == 0)
	{
		g_declination = dec;
		g_inclination = dip;
	}

	return 0;
}
/*************************************************************************/

static void E0000(int IENTRY, int maxdeg, float alt, float glat, float glon, float time, float *dec, float *dip, float *ti, float *gv)
{
	static int maxord,n,m,j,D1,D2,D3,D4;
	static float tc[13][13],dp[13][13],snorm[169],
		      sp[13],cp[13],fn[13],fm[13],pp[13],k[13][13],pi,dtr,a,b,re,
		      a2,b2,c2,a4,b4,c4,flnmj,otime,oalt,
		      olat,olon,dt,rlon,rlat,srlon,srlat,crlon,crlat,srlat2,
		      crlat2,q,q1,q2,ct,st,r2,r,d,ca,sa,aor,ar,br,bt,bp,bpp,
		      par,temp1,temp2,parp,bx,by,bz,bh;
	static float *p = snorm;

	switch(IENTRY){case 0: goto GEOMAG; case 1: goto GEOMG1;}

GEOMAG:
	maxord = 12;
	sp[0] = 0.0;
	cp[0] = *p = pp[0] = 1.0;
	dp[0][0] = 0.0;
	a = 6378.137;
	b = 6356.7523142;
	re = 6371.2;
	a2 = a*a;
	b2 = b*b;
	c2 = a2-b2;
	a4 = a2*a2;
	b4 = b2*b2;
	c4 = a4 - b4;

	*snorm = 1.0;
	fm[0] = 0.0;
	for (n=1; n<=maxord; n++)
	{
		*(snorm+n) = *(snorm+n-1)*(float)(2*n-1)/(float)n;
		j = 2;
		for (m=0,D1=1,D2=(n-m+D1)/D1; D2>0; D2--,m+=D1)
		{
			k[m][n] = (float)(((n-1)*(n-1))-(m*m))/(float)((2*n-1)*(2*n-3));
			if (m > 0)
			{
				flnmj = (float)((n-m+1)*j)/(float)(n+m);
				*(snorm+n+m*13) = *(snorm+n+(m-1)*13)*sqrt(flnmj);
				j = 1;
			}
		}
		fn[n] = (float)(n+1);
		fm[n] = (float)n;
	}
	k[1][1] = 0.0;

	otime = oalt = olat = olon = -1000.0;

	return;

	/*************************************************************************/

GEOMG1:

	dt = time;
	pi = 3.14159265359;
	dtr = pi/180.0;
	rlon = glon*dtr;
	rlat = glat*dtr;
	srlon = sin(rlon);
	srlat = sin(rlat);
	crlon = cos(rlon);
	crlat = cos(rlat);
	srlat2 = srlat*srlat;
	crlat2 = crlat*crlat;
	sp[1] = srlon;
	cp[1] = crlon;

	if (alt != oalt || glat != olat)
	{
		q = sqrt(a2-c2*srlat2);
		q1 = alt*q;
		q2 = ((q1+a2)/(q1+b2))*((q1+a2)/(q1+b2));
		ct = srlat/sqrt(q2*crlat2+srlat2);
		st = sqrt(1.0-(ct*ct));
		r2 = (alt*alt)+2.0*q1+(a4-c4*srlat2)/(q*q);
		r = sqrt(r2);
		d = sqrt(a2*crlat2+b2*srlat2);
		ca = (alt+d)/r;
		sa = c2*crlat*srlat/(r*d);
	}
	if (glon != olon)
	{
		for (m=2; m<=maxord; m++)
		{
			sp[m] = sp[1]*cp[m-1]+cp[1]*sp[m-1];
			cp[m] = cp[1]*cp[m-1]-sp[1]*sp[m-1];
		}
	}
	aor = re/r;
	ar = aor*aor;
	br = bt = bp = bpp = 0.0;
	for (n=1; n<=maxord; n++)
	{
		ar = ar*aor;
		for (m=0,D3=1,D4=(n+m+D3)/D3; D4>0; D4--,m+=D3)
		{
			if (alt != oalt || glat != olat)
			{
				if (n == m)
				{
					*(p+n+m*13) = st**(p+n-1+(m-1)*13);
					dp[m][n] = st*dp[m-1][n-1]+ct**(p+n-1+(m-1)*13);
					goto S50;
				}
				if (n == 1 && m == 0)
				{
					*(p+n+m*13) = ct**(p+n-1+m*13);
					dp[m][n] = ct*dp[m][n-1]-st**(p+n-1+m*13);
					goto S50;
				}
				if (n > 1 && n != m)
				{
					if (m > n-2) *(p+n-2+m*13) = 0.0;
					if (m > n-2) dp[m][n-2] = 0.0;
					*(p+n+m*13) = ct**(p+n-1+m*13)-k[m][n]**(p+n-2+m*13);
					dp[m][n] = ct*dp[m][n-1] - st**(p+n-1+m*13)-k[m][n]*dp[m][n-2];
				}
			}
S50:
			if (time != otime)
			{
				tc[m][n] = c[m][n]+dt*cd[m][n];
				if (m != 0) tc[n][m-1] = c[n][m-1]+dt*cd[n][m-1];
			}

			par = ar**(p+n+m*13);
			if (m == 0)
			{
				temp1 = tc[m][n]*cp[m];
				temp2 = tc[m][n]*sp[m];
			}
			else
			{
				temp1 = tc[m][n]*cp[m]+tc[n][m-1]*sp[m];
				temp2 = tc[m][n]*sp[m]-tc[n][m-1]*cp[m];
			}
			bt = bt-ar*temp1*dp[m][n];
			bp += (fm[m]*temp2*par);
			br += (fn[n]*temp1*par);

			if (st == 0.0 && m == 1)
			{
				if (n == 1) pp[n] = pp[n-1];
				else pp[n] = ct*pp[n-1]-k[m][n]*pp[n-2];
				parp = ar*pp[n];
				bpp += (fm[m]*temp2*parp);
			}
		}
	}
	if (st == 0.0) bp = bpp;
	else bp /= st;

	bx = -bt*ca-br*sa;
	by = bp;
	bz = bt*sa-br*ca;
	bh = sqrt((bx*bx)+(by*by));
	*ti = sqrt((bh*bh)+(bz*bz));
	*dec = atan2(by,bx)/dtr;
	*dip = atan2(bz,bh)/dtr;
	*gv = -999.0;
	if (fabs(glat) >= 55.)
	{
		if (glat > 0.0 && glon >= 0.0) *gv = *dec-glon;
		if (glat > 0.0 && glon < 0.0) *gv = *dec+fabs(glon);
		if (glat < 0.0 && glon >= 0.0) *gv = *dec+glon;
		if (glat < 0.0 && glon < 0.0) *gv = *dec-fabs(glon);
		if (*gv > +180.0) *gv -= 360.0;
		if (*gv < -180.0) *gv += 360.0;
	}
	otime = time;
	oalt = alt;
	olat = glat;
	olon = glon;
	return;
}

