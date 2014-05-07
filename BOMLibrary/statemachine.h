#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <QStringList>
#include "state.h"
namespace BOMLIB
{
	//! stateMachine
	/*! Responsibility: Holds the states and the transitions list and
	based on exit conditions transitions the object to the next state.
	*/
class stateMachine
{
public:
	//! Constructor
    stateMachine(QString name);
	//! GetStatesList
	/*! Returns the list of states associated in the state machine
	*/
    QList<state*> GetStatesList();
    //! AddState
	/*! 
		\param state* stateName
		State to be associated to the machine.
	*/
	void AddState(state* stateName);
	//! AddEntity
	/*! 
		\param QString entity 
		Add the domain objects associated to the object and states.
	*/
    void AddEntity(QString entity);
	//! GetName
	/*! Returns the name of the state machine.
	*/
    QString GetName();
private:
    QList<state*> m_StatesList;
    QStringList m_Entities;
    QString m_Name;
};
}

#endif // STATEMACHINE_H
