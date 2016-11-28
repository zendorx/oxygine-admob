#pragma once

#include "EventDispatcher.h"
#include "Event.h"
#include "json/json.h"
#include <string>
#include <list>

using namespace std;
using namespace oxygine;

namespace admob
{

    void init();
    void free();

	const static int ON_LOADED = 1;
	const static int ON_FAILED = 2;
	const static int ON_OPENED = 3;
	const static int ON_CLOSED = 4;

    const static int RW_ON_LOADED = 101;
    const static int RW_ON_OPENED = 102;
    const static int RW_ON_STARTED = 103;
    const static int RW_ON_CLOSED = 104;
    const static int RW_ON_REWARD = 105;
    const static int RW_ON_LEFT_APP = 106;
    const static int RW_ON_FAILED = 107;

    class OnChangeEvent : public Event
    {
    public:
        enum { EVENT = eventID('A', 'M', 'C', 'E')};
        OnChangeEvent(int newStatus) : Event(EVENT),newStatus(newStatus) {};
        int newStatus = 0;
    };

    class OnRewardChangeEvent : public Event
    {
        enum { EVENT = eventID('A', 'M', 'R', 'E')};
        OnRewardChangeEvent() : Event(EVENT),newStatus(newStatus) {};
        int newStatus = 0;

        //on reward
        int amount = 0;
        string type;

        int errorCode = 0;

    };

    spEventDispatcher dispatcher();

    void load();
    void show();
    bool isLoaded();

    void loadRewarded(const string& unit_id);
    void showRewarded();
    bool isRewardedLoaded();



    namespace internal
    {
            void onChange(int newStatus);
            void onRewardChange(int newStatus);
            void onReward(const string& type, int amount);
            void onRewardFailed(int errorCode);
    }

};