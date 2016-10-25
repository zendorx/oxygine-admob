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

    class OnChangeEvent : public Event
    {
    public:
        enum { EVENT = sysEventID('f', 'b', 't')};
        OnChangeEvent(int newStatus) : Event(EVENT),newStatus(newStatus) {};
        int newStatus = 0;
    };

    spEventDispatcher dispatcher();

    void load();
    void show();
    bool isLoaded();

    namespace internal
    {
            void onChange(int newStatus);
    }
};