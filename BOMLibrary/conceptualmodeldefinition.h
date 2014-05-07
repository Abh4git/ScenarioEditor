#ifndef CONCEPTUALMODELDEFINITION_H
#define CONCEPTUALMODELDEFINITION_H
#include "statemachine.h"
namespace BOMLIB
{
class ConceptualModelDefinition
{
public:
	//! Constructor
    ConceptualModelDefinition();
	//! GetStateMachine
	/*!
		Returns the stateMachine* associated to the behavioral or conceptual model.
	*/
    stateMachine* GetStateMachine();
	//! SetStateMachine
	/*!
		\param stateMachine* associate the statemachine to the model.
	*/
    void SetStateMachine(stateMachine* stateMachineofModel);
private:
    stateMachine* m_stateMachine;
};
}
#endif // CONCEPTUALMODELDEFINITION_H
