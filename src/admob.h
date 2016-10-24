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

    /*class YourEventExample : public Event
    {
    public:
        enum { EVENT = sysEventID('f', 'b', 't')};
        YourEventExample() : Event(EVENT) {};
    };*/

    spEventDispatcher dispatcher();

    //void doSomething();

    namespace internal
    {
            //void callItFromNativeCallback();
    }
};