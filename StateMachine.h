#ifndef CCU_ST_MCH
#define CCU_ST_MCH

#include<stdint.h>

typedef struct _state_machine_const_struct_     SM_StateMachineConst;
typedef struct _state_transition_               SM_StateTransition;

typedef int (*SM_StateFunctions)(uint32_t *pEventData);

struct _state_machine_const_struct_ {
    const char* name;
    const SM_StateFunctions* stateMap;
    const uint16_t maxStates;
    const SM_StateTransition *stateTransition;
    const uint16_t maxTransitions;
};

struct _state_transition_{
    uint8_t current_state;
    uint8_t current_state_res;
    uint8_t next_state;
};

#define SM_NAME NAME(_smName_) _smName_ 
#define BEGIN_TRANSITION_MAP(_smName_) static const SM_StateTransition _smName_##_StateTransition[] = {

#define TRANSITION_MAP_ENTRY(_current_,_res_,_next_) {_current_,_res_,_next_},

#define END_TRANSITION_MAP };

#define BEGIN_STATE_MAP(_smName_) static const SM_StateFunctions _smName_##StateMap[] = { 

#define STATE_MAP_ENTRY(_stateFunc_)_stateFunc_,

#define END_STATE_MAP(_smName_) };

#define SM_DECLARE(_smName_) extern SM_StateMachine _smName_##Obj; 

#define StateMachine_DEFINE(_smName_) \
 SM_StateMachineConst _smName_##Obj = { #_smName_, \
_smName_##StateMap, \
sizeof(_smName_##StateMap)/sizeof(_smName_##StateMap[0]), \
_smName_##_StateTransition, \
sizeof(_smName_##_StateTransition)/sizeof(_smName_##_StateTransition[0])}; 

#define BEGIN_STATE_DECLARE(_smName_) \
 typedef enum _##_smName_##_{


#define END_STATE_DECLARE(_smName_) \
 }_smName_##_States;

#define STATE_DECLARE(_stateFunc_) \
 static int _stateFunc_(uint32_t *pEventData);

#define STATE_DEFINE(_stateFunc_) \
 static int _stateFunc_(uint32_t *pEventData)

#define SM_TRANSITION_HANDLER_DEFINE(_smName_) \
    int _smName_##_StateTransitionHandler_(int p_current, int p_ret){ \
    int l_temp_state = 0; \
    for (int index = 0; index < _smName_##Obj.maxTransitions; ++index) {    \
        if (_smName_##Obj.stateTransition[index].current_state == p_current && _smName_##Obj.stateTransition[index].current_state_res == p_ret) {   \
            l_temp_state = _smName_##Obj.stateTransition[index].next_state; \
            break;  \
        }   \
    }   \
    return l_temp_state;    \
}
#define SM_TRANSITION_HANDLER_DECLARE(_smName_) \
int _smName_##_StateTransitionHandler_(int p_current, int p_ret);

#define SM_TRANSITION_HANDLER(_smName_,p_current,p_ret)\
    _smName_##_StateTransitionHandler_(p_current,p_ret)

#define SM_GET_CURRENT_STATE_DEFINE(_smName_)\
    SM_StateFunctions _smName_##_GetCurrentState (int p_current_state){\
        return _smName_##Obj.stateMap[p_current_state];\
    }

#define SM_GET_CURRENT_STATE_DECLARE(_smName_)\
    SM_StateFunctions _smName_##_GetCurrentState (int p_current_state);

#define SM_GET_CURRENT_STATE(_smName_,p_current)\
    _smName_##_GetCurrentState(p_current)

#endif /*CCU_ST_MCH*/
