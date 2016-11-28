#pragma once

#include <string>

using namespace std;

void jniAdmobInit();
void jniAdmobFree();

void jniAdmobShow();
void jniAdmobLoad();
bool jniAdmobIsLoaded();

void jniAdmobLoadRewarded(const string& unit_id);
void jniAdmobShowRewarded();
bool jniAdmobIsRewardedLoaded();
