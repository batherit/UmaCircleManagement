#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment	(lib, "ws2_32.lib")

#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<string>
#include<Windows.h>
#include<io.h>
#include<conio.h>
#include<oleauto.h>
#include<iomanip>
#include<regex>
#include<memory>
using namespace std;

#define CONSOL_VERSION
#define OUT
#define PURE = 0

using FileDate = int;

#define GENERATED_ONLY_STATIC(ClassType)\
private:\
	ClassType() {}\

#define GENERATED_SINGLETON(ClassType)\
private:\
	ClassType() {}\
public:\
static ClassType& Get()\
{\
	static ClassType instance; \
	return instance;\
}\
