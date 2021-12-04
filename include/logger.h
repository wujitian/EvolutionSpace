#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

#define I_OUT printf("[I] Fn:%s(), Line= %d | ", __FUNCTION__, __LINE__); fflush(stdout);
#define D_OUT printf("[D] Fn:%s(), Line= %d | ", __FUNCTION__, __LINE__); fflush(stdout);
#define W_OUT printf("[W] Fn:%s(), Line= %d | ", __FUNCTION__, __LINE__); fflush(stdout);
#define E_OUT printf("[E] Fn:%s(), Line= %d | ", __FUNCTION__, __LINE__); fflush(stdout);

//#if (WIN32) || (_WIN64)
#ifdef WIN32
#define dprintf_i(fmt, ...) I_OUT printf(fmt"\n", __VA_ARGS__)
#define dprintf_d(fmt, ...) D_OUT printf(fmt"\n", __VA_ARGS__)
#define dprintf_w(fmt, ...) W_OUT printf(fmt"\n", __VA_ARGS__)
#define dprintf_e(fmt, ...) E_OUT printf(fmt"\n", __VA_ARGS__)
#else
#define dprintf_i(fmt, arg...) I_OUT printf(fmt"\n", ##arg)
#define dprintf_d(fmt, arg...) D_OUT printf(fmt"\n", ##arg)
#define dprintf_w(fmt, arg...) W_OUT printf(fmt"\n", ##arg)
#define dprintf_e(fmt, arg...) E_OUT printf(fmt"\n", ##arg)
#endif

class Logger
{
public:
    Logger() {};
    ~Logger() {};

    void init(void)
    {
        AllocConsole();
        freopen_s(&pLoggerOut, "conin$", "w", stdin);
        freopen_s(&pLoggerOut, "conout$", "w", stdout);
        freopen_s(&pLoggerOut, "conout$", "w", stderr);

        dprintf_d("[Logger] Logger init finish");
    }

    void deinit(void)
    {
        dprintf_d("Logger deinit");

        fclose(pLoggerOut);
        FreeConsole();
    }

    FILE* pLoggerOut = NULL;
};