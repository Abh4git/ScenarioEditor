#ifndef STATE_H
#define STATE_H
#include <QString>
#include "exitcondition.h"
namespace BOMLIB
{
	//! state
	/*! Responsibility: Definition of a state in stateMachine is defined and stored here. */
class state
{
public:
	//! Constructor
    state(QString name);
	//! GetName
	/*! Returns the Name as string. */
    QString GetName();
    //! GetExitCondition
	/*! Returns the exitCondition upon which state changes to next. */
	exitCondition* GetExitCondition();
	//! GetNextState
	/*! Returns the next state once which the object transitions into. */
	state* GetNextState();
    //! SetExitCondition
	/*! \param exitCondition
	Exit Condition on which this state gets over. */
	void SetExitCondition(exitCondition* condition);
    //! SetNextState
	/*! \param state nextState
	The next state the object transitions to. */
	void SetNextState(state* nextState);
private:
    QString m_name;
    exitCondition* m_exitCondition;
    state* m_nextState;
};


}

#endif // STATE_H
