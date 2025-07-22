#include "main.h"

#define FLOAT_EPSILON 0.0001f

void BIG_NUM_MUL(unsigned long in[5], unsigned long out[6], unsigned long factor)
{
	/*
		Based on TTMath library by Tomasz Sowa.
	*/

	unsigned long src[5] = { 0 };
	for (int i = 0; i < 5; i++)
		src[i] = ((in[4 - i] >> 24) | ((in[4 - i] << 8) & 0x00FF0000) | ((in[4 - i] >> 8) & 0x0000FF00) | (in[4 - i] << 24));

	unsigned long long tmp = 0;

	tmp = unsigned long long(src[0]) * unsigned long long(factor);
	out[0] = tmp & 0xFFFFFFFF;
	out[1] = tmp >> 32;
	tmp = unsigned long long(src[1]) * unsigned long long(factor) + unsigned long long(out[1]);
	out[1] = tmp & 0xFFFFFFFF;
	out[2] = tmp >> 32;
	tmp = unsigned long long(src[2]) * unsigned long long(factor) + unsigned long long(out[2]);
	out[2] = tmp & 0xFFFFFFFF;
	out[3] = tmp >> 32;
	tmp = unsigned long long(src[3]) * unsigned long long(factor) + unsigned long long(out[3]);
	out[3] = tmp & 0xFFFFFFFF;
	out[4] = tmp >> 32;
	tmp = unsigned long long(src[4]) * unsigned long long(factor) + unsigned long long(out[4]);
	out[4] = tmp & 0xFFFFFFFF;
	out[5] = tmp >> 32;

	for (int i = 0; i < 12; i++)
	{
		unsigned char temp = ((unsigned char*)out)[i];
		((unsigned char*)out)[i] = ((unsigned char*)out)[23 - i];
		((unsigned char*)out)[23 - i] = temp;
	}
}


int random(int min, int max)
{
	return min + (rand() % (max - min));
}

void gen_random(char* s, const int len)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}

int near_zero ( float v )
{
	if ( !isfinite(v) )
		return 1;
	return fabs( v ) < FLOAT_EPSILON;
}

void vect2_normalize ( const float in[2], float out[2] )
{
	float	m;
	int		i;

	m = sqrtf( in[0] * in[0] + in[1] * in[1] );

	for ( i = 0; i < 2; i++ )
		out[i] = in[i] / m;
}

float vect2_length ( const float in[2] )
{
	return sqrtf( in[0] * in[0] + in[1] * in[1] );
}

int vect2_near_zero ( const float in[2] )
{
	//if ( !isfinite(in[0]) || !isfinite(in[1]) )
	//	return 1;
	return near_zero( in[0] ) && near_zero( in[1] );
}

void vect3_zero ( float out[3] )
{
	int i;

	for ( i = 0; i < 3; i++ )
		out[i] = 0.0f;
}

void vect2_copy ( const uint8_t in[2], uint8_t out[2] )
{
	memcpy( out, in, sizeof(uint8_t) * 2 );
}

void vect3_normalize ( const float in[3], float out[3] )
{
	float	m;
	int		i;

	m = sqrtf( in[0] * in[0] + in[1] * in[1] + in[2] * in[2] );

	for ( i = 0; i < 3; i++ )
		out[i] = in[i] / m;
}

float vect3_length ( const float in[3] )
{
	return sqrtf( in[0] * in[0] + in[1] * in[1] + in[2] * in[2] );
}

void vect3_div ( const float in[3], float m, float out[3] )
{
	int i;

	for ( i = 0; i < 3; i++ )
		out[i] = in[i] / m;
}

void vect3_mult ( const float in[3], float m, float out[3] )
{
	int i;

	for ( i = 0; i < 3; i++ )
		out[i] = in[i] * m;
}

void vect3_vect3_mult ( const float in1[3], const float in2[3], float out[3] )
{
	int i;

	for ( i = 0; i < 3; i++ )
		out[i] = in1[i] * in2[i];
}

void vect3_vect3_add ( const float in1[3], const float in2[3], float out[3] )
{
	int i;

	for ( i = 0; i < 3; i++ )
		out[i] = in1[i] + in2[i];
}

void vect3_vect3_sub ( const float in1[3], const float in2[3], float out[3] )
{
	int i;

	for ( i = 0; i < 3; i++ )
		out[i] = in1[i] - in2[i];
}

void vect3_invert ( const float in[3], float out[3] )
{
	int i;

	for ( i = 0; i < 3; i++ )
		out[i] = -in[i];
}

int vect3_near_zero ( const float in[3] )
{
	//if ( !isfinite(in[0]) || !isfinite(in[1]) || !isfinite(in[2]) )
	//	return 1;
	return near_zero( in[0] ) && near_zero( in[1] ) && near_zero( in[2] );
}

void vect3_copy ( const float in[3], float out[3] )
{
	memcpy( out, in, sizeof(float) * 3 );
}

float vect3_dist ( const float in1[3], const float in2[3] )
{
	float	dist[3];

	vect3_vect3_sub( in1, in2, dist );
	return vect3_length( dist );
}

int vect4_near_zero ( const float in[4] )
{
	//if ( !isfinite(in[0]) || !isfinite(in[1]) || !isfinite(in[2]) || !isfinite(in[3]) )
	//	return 1;
	return near_zero( in[0] ) && near_zero( in[1] ) && near_zero( in[2] ) && near_zero( in[3] );
}

void vect4_copy ( const uint8_t in[4], uint8_t out[4] )
{
	memcpy( out, in, sizeof(uint8_t) * 4 );
}

void vect4_copy ( const float in[4], float out[4] )
{
	memcpy( out, in, sizeof(float) * 4 );
}

void matrix_copy ( const float in[16], float out[16] )
{
	memcpy( out, in, sizeof(float) * 16 );
}

float vect3_dot_product ( const float in1[3], const float in2[3] )
{
	return in1[0] * in2[0] + in1[1] * in2[1] + in1[2] * in2[2];
}

void vect3_cross_product ( const float in1[3], const float in2[3], float out[3] )
{
	out[0] = ( in1[1] * in2[2] ) - ( in2[1] * in1[2] );
	out[1] = ( in1[2] * in2[0] ) - ( in2[2] * in1[0] );
	out[2] = ( in1[0] * in2[1] ) - ( in2[0] * in1[1] );
}

void matrix_vect3_mult ( const float matrix[16], const float in[3], float out[3] )
{
	const float in4[4] = { in[0], in[1], in[2], 1.0f };
	float		out4[4];

	matrix_vect4_mult( matrix, in4, out4 );
	vect3_copy( out4, out );
}

void matrix_vect4_mult ( const float matrix[16], const float in[4], float out[4] )
{
	float	res[4];
	int		i;

	for ( i = 0; i < 4; i++ )
	{
		res[i] = in[0] * matrix[0 + i] + in[1] * matrix[4 + i] + in[2] * matrix[8 + i] + in[3] * matrix[12 + i];
	}

	vect4_copy( res, out );
}

void matrix_matrix_mult ( const float in1[16], const float in2[16], float out[16] )
{
	float	res[16];
	int		i, j;

	for ( i = 0; i < 4; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			res[i * 4 + j] = in1[i * 4 + 0] *
				in2[0 + j] +
				in1[i * 4 + 1] *
				in2[4 + j] +
				in1[i * 4 + 2] *
				in2[8 + j] +
				in1[i * 4 + 3] *
				in2[12 + j];
		}
	}

	matrix_copy( res, out );
}

void matrix_vect3_rotate ( const float in[16], const float vect[3], float t, float out[16] )
{
	const float x = vect[0], y = vect[1], z = vect[2];
	const float sin_t = sinf( t ), cos_t = cosf( t );
	float		res[16];
	const float matrix[16] =
	{
		cos_t + ( 1.0f - cos_t ) * x * x,
		( 1.0f - cos_t ) * x * y - sin_t * z,
		( 1.0f - cos_t ) * x * z + sin_t * y,
		0.0f,
		( 1.0f - cos_t ) * y * x + sin_t * z,
		cos_t + ( 1.0f - cos_t ) * y * y,
		( 1.0f - cos_t ) * y * z - sin_t * x,
		0.0f,
		( 1.0f - cos_t ) * z * x - sin_t * y,
		( 1.0f - cos_t ) * z * y + sin_t * x,
		cos_t + ( 1.0f - cos_t ) * z * z,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f
	};

	matrix_matrix_mult( in, matrix, res );
	vect4_copy( &in[4 * 3], &res[4 * 3] );
	matrix_copy( res, out );
}

void matrix_vect3_switchXY ( const float in[16], float out[16] )
{
	float	res[16];
	vect4_copy( &in[4 * 0], &res[4 * 0] );
	vect4_copy( &in[4 * 1], &res[4 * 1] );
	vect4_copy( &in[4 * 2], &res[4 * 2] );

	vect4_copy( &in[4 * 3], &res[4 * 3] );
	matrix_copy( res, out );
}

void matrix_identity ( float out[16] )
{
	static const float	id[16] =
	{
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f
	};

	matrix_copy( id, out );
}

float random_float(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float roundf(float v)
{
	return floorf(v + 0.5f);
}

// BitStream::WriteOrthMatrix
void GetOrthMatrix(float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22,
	float* fOutW, float* fOutX, float* fOutY, float* fOutZ)
{
	double qw;
	double qx;
	double qy;
	double qz;

#ifdef _MSC_VER
#pragma warning(disable:4100)   // m10, m01 : unreferenced formal parameter
#endif

	// Convert matrix to quat
	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
	float sum;
	sum = 1 + m00 + m11 + m22;
	if (sum < 0.0f) sum = 0.0f;
	qw = sqrt(sum) / 2;
	sum = 1 + m00 - m11 - m22;
	if (sum < 0.0f) sum = 0.0f;
	qx = sqrt(sum) / 2;
	sum = 1 - m00 + m11 - m22;
	if (sum < 0.0f) sum = 0.0f;
	qy = sqrt(sum) / 2;
	sum = 1 - m00 - m11 + m22;
	if (sum < 0.0f) sum = 0.0f;
	qz = sqrt(sum) / 2;
	if (qw < 0.0) qw = 0.0;
	if (qx < 0.0) qx = 0.0;
	if (qy < 0.0) qy = 0.0;
	if (qz < 0.0) qz = 0.0;
	qx = _copysign(qx, m21 - m12);
	qy = _copysign(qy, m02 - m20);
	qz = _copysign(qz, m10 - m01);
	*fOutW = (float)qw;
	*fOutX = (float)qx;
	*fOutY = (float)qy;
	*fOutZ = (float)qz;
}

// BitStream::ReadOrthMatrix
void MakeOrthMatrix(float fInW, float fInX, float fInY, float fInZ,
	float* m00, float* m01, float* m02,
	float* m10, float* m11, float* m12,
	float* m20, float* m21, float* m22)
{
	// Quat to orthogonal rotation matrix
	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	float sqw = fInW * fInW;
	float sqx = fInX * fInX;
	float sqy = fInY * fInY;
	float sqz = fInZ * fInZ;
	*m00 = (sqx - sqy - sqz + sqw); // since sqw + sqx + sqy + sqz =1
	*m11 = (-sqx + sqy - sqz + sqw);
	*m22 = (-sqx - sqy + sqz + sqw);

	float tmp1 = fInX * fInY;
	float tmp2 = fInZ * fInW;
	*m10 = (2.0f * (tmp1 + tmp2));
	*m01 = (2.0f * (tmp1 - tmp2));

	tmp1 = fInX * fInZ;
	tmp2 = fInY * fInW;
	*m20 = (2.0f * (tmp1 - tmp2));
	*m02 = (2.0f * (tmp1 + tmp2));
	tmp1 = fInY * fInZ;
	tmp2 = fInX * fInW;
	*m21 = (2.0f * (tmp1 + tmp2));
	*m12 = (2.0f * (tmp1 - tmp2));
}


std::string cp1251_to_utf8(const std::string str)
{
	int len_u = MultiByteToWideChar(1251, 0, str.data(), -1, 0, 0);
	if (len_u == NULL) return NULL;

	wchar_t* ures = new wchar_t[len_u];
	if (!MultiByteToWideChar(1251, 0, str.data(), -1, ures, len_u)) {
		delete[] ures; return NULL;
	}
	int len_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
	if (len_c == NULL) {
		delete[] ures;
		return NULL;
	}
	char* cres = new char[len_c];
	if (!WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, len_c, 0, 0)) {
		delete[] cres;
		return NULL;
	}
	std::string result = cres;

	delete[] ures; delete[] cres;
	return result;
}

std::string utf8_to_cp1251(const std::string str)
{
	int len_u = MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, 0, 0);
	if (len_u == NULL) return NULL;

	wchar_t* ures = new wchar_t[len_u];
	if (!MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, ures, len_u)) {
		delete[] ures;
		return 0;
	}
	int len_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);
	if (len_c == NULL) {
		delete[] ures;
		return NULL;
	}
	char* cres = new char[len_c];
	if (!WideCharToMultiByte(1251, 0, ures, -1, cres, len_c, 0, 0)) {
		delete[] cres; delete[] ures; return NULL;
	}
	std::string result = cres;

	delete[] ures; delete[] cres;
	return result;
}



std::string GetExePath()
{
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	/*
	strrchr: function function: find the position of the last occurrence of a character c in another string str (that is, find the position of the first occurrence of the character c from the right side of str),
	 And return the address of this location. If the specified character cannot be found, the function returns NULL.
	 Use this address to return the string from the last character c to the end of str.
	*/
	(strrchr(szFilePath, '\\'))[0] = 0; // Delete the file name, only get the path string //
	std::string path = szFilePath;
	return path;
}

std::string GetExeName()
{
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	/*
	strrchr: function function: find the position of the last occurrence of a character c in another string str (that is, find the position of the first occurrence of the character c from the right side of str),
	 And return the address of this location. If the specified character cannot be found, the function returns NULL.
	 Use this address to return the string from the last character c to the end of str.
	*/
//	(strrchr(szFilePath, '\\'))[0] = 0; // Delete the file name, only get the path string //
	std::string path = szFilePath;
	return path;
}

/// s - from, c - what
char* del_char(char* from, char what) 
{
	char* buf = strchr(from, what);
	while (buf)
	{
		if (buf + 1)
			strcpy(buf, buf + 1);
		else
			buf[0] = '\0';
		buf = strchr(buf, what);
	}
	return from;
}

DEVMODE mode;

void GetDisplayVidModes()
{
	static int num = 0;
	DEVMODEA dm = { 0 };
	dm.dmSize = sizeof(dm);	
	for (int iModeNum = 0; EnumDisplaySettingsA(NULL, iModeNum, &dm) != 0; iModeNum++) 
	{
		sn->con.AddLog("Найдено разрешение экрана: w: %d | h: %d > номер режима %i,",
			dm.dmPelsWidth,dm.dmPelsHeight, num++); ///cdd - current device display
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		//num++;
	}			
};

int SupportCPU_AVX_check() 
{
	int can_use_avx;
	// Verify CPU capabilities: 
	bool bAVXok = false; 
	int cpuInfo[4] = { 0,0,0,0 };
	__cpuid(cpuInfo, 0); 
	if (cpuInfo[0] != 0) 
	{ 
		__cpuid(cpuInfo, 1);
		if (cpuInfo[2] & (1 << 28)) 
		{ 
			bAVXok = true;
		// Note: this test only confirms CPU AVX capability, and does not check OS capability. // to-do: check for AVX2 ... 
		} 
	}			

	if (bAVXok)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
 