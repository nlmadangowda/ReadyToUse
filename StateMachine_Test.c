/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include "StateMachine.h"

typedef enum {
    EntryState = 0,
    SMState1,
    SMState2,
    SMState3,
    SMState4,
    ExitState
}SMStates;

STATE_DECLARE(Entry)
STATE_DECLARE(State1)
STATE_DECLARE(State2)
STATE_DECLARE(State3)
STATE_DECLARE(State4)
STATE_DECLARE(Exit)

BEGIN_STATE_MAP(TEST)
    STATE_MAP_ENTRY(Entry)
    STATE_MAP_ENTRY(State1)
    STATE_MAP_ENTRY(State2)
    STATE_MAP_ENTRY(State3)
    STATE_MAP_ENTRY(State4)
    STATE_MAP_ENTRY(Exit)
END_STATE_MAP(TEST)

BEGIN_TRANSITION_MAP(TEST)
    TRANSITION_MAP_ENTRY(EntryState,            SMState1,       SMState1)
    TRANSITION_MAP_ENTRY(SMState1,              SMState2,       SMState2)
    TRANSITION_MAP_ENTRY(SMState2,              SMState3,       SMState3)
    TRANSITION_MAP_ENTRY(SMState3,              SMState4,       SMState4)
    TRANSITION_MAP_ENTRY(SMState4,              ExitState,      ExitState)
END_TRANSITION_MAP

StateMachine_DEFINE (TEST)
SM_TRANSITION_HANDLER_DEFINE(TEST)
SM_GET_CURRENT_STATE_DEFINE(TEST)

STATE_DEFINE(Entry){
    *pEventData+=1;
    printf("\r\nEntryState");
    return SMState1;
}

STATE_DEFINE(State1){
    *pEventData+=1;
    printf("\r\nState1");
    return SMState2;
}

STATE_DEFINE(State2){
    *pEventData+=1;
    printf("\r\nState2");
    return SMState3;
}

STATE_DEFINE(State3){
    *pEventData+=1;
    printf("\r\nState3");
    return SMState4;
}

STATE_DEFINE(State4){
    *pEventData+=1;
    printf("\r\nState4");   
    return ExitState;
}

STATE_DEFINE(Exit){
    *pEventData+=1;
    printf("\r\nExitState");
    return ExitState;
}

void SMTest(){
    int l_cur_state = 0;
    int l_nxt_state = 0;
    uint32_t l_event_data=0;
    SM_StateFunctions state_fun;
    while(1){
        state_fun = SM_GET_CURRENT_STATE(TEST,l_cur_state);
        l_nxt_state = state_fun(&l_event_data);
        if(l_nxt_state == ExitState && l_cur_state == ExitState){
            printf("\r\nl_event_data: %d",l_event_data);
            break;
        }
        l_cur_state = SM_TRANSITION_HANDLER(TEST,l_cur_state, l_nxt_state);
    }
}
int main()
{
    SMTest();
    return 0;
}
