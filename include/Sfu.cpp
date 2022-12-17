#include <stdio.h>
#include "Sfu.h"

uint32_t fp2fx2dot26(float input)
{
	uint32_t value = *(uint32_t *)&input;
	uint32_t output = 0;
	
	output = value & ((1 << 23) - 1);
	output |= (1 << 23);

	uint32_t sign = value & (1 << 31);

	output = output << 3; //expend frac to 26bit

	int32_t exp = ((value >> 23) & 0xFF) - 127;

	if (exp < 0)
	{
		output = output >> -exp;
	}
	else
	{
		output = output << exp;
	}

	if (sign)
	{
		output = ~output + 1;
	}

	output = output & 0xFFFFFFF;

	output |= sign;

	return output;
}

float Sfu::rcp(float f)
{
	return 0;
}

float Sfu::rsq(float f)
{
	return 0;
}

float Sfu::sqrt(float f)
{
	return 0;
}

float Sfu::log(float f)
{
	return 0;
}

float Sfu::exp(float a, float b)
{
	return 0;
}

float Sfu::sin(float input)
{
    if (m_useSystemMath)
    {
        printf("sin(%20.14f)   actual:%20.14f   expected:%20.14f   diff:%20.14f\n", input, ::sin(input), ::sin(input), 0.0f);
        return (float)::sin(input);
    }

	float MaxFix = 1.999999999f;
	float MinFix = -2.0000000f;
	float PI = 3.141592654f;
	float PI2 = 6.283185307f;
	float Zero = 0.0f;
	float A = 0.636619772f; // 2/pi

    float rawInput = input;

	bool needAbs = (input < -2) ? true : false; // x < Minfix,  sin(-x) = -sin(x)
	float absInput = needAbs ? (float)fabs(input) : input;

	bool absGreateThan2PI = (absInput > PI2) ? true : false;

	float tmpInput = 0.0;
	if (absGreateThan2PI)
	{
		tmpInput = absInput - (int(absInput / PI2)) * PI2;
	}
	else
	{
		tmpInput = absInput;
	}

	bool tmpGreateThanPI = tmpInput > PI ? true : false;

	tmpInput = tmpGreateThanPI ? (tmpInput - PI) : tmpInput;

	bool TmpGreateThanMaxFix = tmpInput > MaxFix ? true : false;

	input = TmpGreateThanMaxFix ? (PI - tmpInput) : tmpInput;
	input = input * A;

	uint32_t fxValue = fp2fx2dot26(input);

	uint32_t output = 0;
	do_sfu_function(SFU_SIN, fxValue, output);

	/*
	v1 = fp2fxcc(input);
	v2 = sin(v1);
	if(tmpGreateThanPI) v2 = -v2;
	if(needAbs) v2 = -v2
	return v2;*/

	float fValue = *(float*)&output;

	if (tmpGreateThanPI)
	{
		fValue = -fValue;
	}

	if (needAbs)
	{
		fValue = -fValue;
	}

    float diff = (float)fabs(fValue - ::sin(rawInput));
	printf("sin(%20.14f)   actual:%20.14f   expected:%20.14f   diff:%20.14f %s\n", rawInput, fValue, ::sin(rawInput), diff, diff > 0.0008 ? "precision error" : "");

	return fValue;
}

float Sfu::cos(float input)
{
    if (m_useSystemMath)
    {
        printf("cos(%20.14f)   actual:%20.14f   expected:%20.14f   diff:%20.14f\n", input, ::cos(input), ::cos(input), 0.0f);
        return (float)::cos(input);
    }

	float MaxFix = 1.999999f;
	float PI = 3.1415926f;
	float PI2 = 6.283185f;
	float A = 0.636619772f; // 2/pi
    
    float rawInput = input;

	// x <0,  cos(-x) = cos(x)
	bool needAbs = (input < 0) ? true : false; // x < Minfix,  cos(-x) = cos(x)
	float absInput = needAbs ? (float)fabs(input) : input;

	bool absGreateThan2PI = (absInput > PI2) ? true : false;

	float tmpInput = 0.0;
	if (absGreateThan2PI)
	{
		tmpInput = absInput - (int(absInput / PI2)) * PI2;
	}
	else
	{
		tmpInput = absInput;
	}

	bool tmpGreateThanPI = tmpInput > PI ? true : false;

	tmpInput = tmpGreateThanPI ? (tmpInput - PI) : tmpInput;

	bool TmpGreateThanMaxFix = tmpInput > MaxFix ? true : false;

	input = TmpGreateThanMaxFix ? (PI - tmpInput) : tmpInput;
	input = input * A;

	uint32_t fxValue = fp2fx2dot26(input);

	uint32_t output = 0;
	do_sfu_function(SFU_COS, fxValue, output);

	float fValue = *(float*)&output;

	if (tmpGreateThanPI)
	{
		fValue = -fValue;
	}
	if (TmpGreateThanMaxFix)
	{
		fValue = -fValue;
	}

    float diff = (float)fabs(fValue - ::cos(rawInput));
	printf("cos(%20.14f)   actual:%20.14f   expected:%20.14f   diff:%20.14f %s\n", rawInput, fValue, ::cos(rawInput), diff, diff > 0.0008 ? "precision error":"");

	return fValue;
}