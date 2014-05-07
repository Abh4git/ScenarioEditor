#ifndef EXITCONDITION_H
#define EXITCONDITION_H

#include <QString>
namespace BOMLIB
{
class exitCondition
{
public:
	//! Constructor
	exitCondition();
	//! SetExitAction
	/*!
		\param QString exitAction 
		Associate the exitAction to the exitcondition.
	*/
    void SetExitAction(QString exitAction);
	//! SetNextState
	/*!
		\param QString nextState 
		Next state the BOM Object has to be placed on.
	*/
    void SetNextState(QString nextState);
	//! GetExitAction
	/*!
		Return the action associated to the exitCondition
	*/
    QString GetExitAction();
	//! GetNextState
	/*!
		\param stateMachine* associate the statemachine to the model.
	*/
    QString GetNextState();
private:
    QString m_NextState;
    QString m_exitAction;
};
}

#endif // EXITCONDITION_H
