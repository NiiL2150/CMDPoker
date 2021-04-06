#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <vector>
#include <tchar.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BLACKB  "\033[40m"
#define REDB    "\033[41m"
#define GREENB  "\033[42m"
#define YELLOWB "\033[43m"
#define BLUEB   "\033[44m"
#define MAGENTAB "\033[45m"
#define CYANB   "\033[46m"
#define WHITEB  "\033[47m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BOLDBLACKB  "\033[1m\033[40m"
#define BOLDREDB    "\033[1m\033[41m"
#define BOLDGREENB  "\033[1m\033[42m"
#define BOLDYELLOWB "\033[1m\033[43m"
#define BOLDBLUEB   "\033[1m\033[44m"
#define BOLDMAGENTAB "\033[1m\033[45m"
#define BOLDCYANB   "\033[1m\033[46m"
#define BOLDWHITEB  "\033[1m\033[47m"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77