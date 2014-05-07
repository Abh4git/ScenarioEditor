///////////////////////////////////////////////////////////
//  Use History.h
//  Implementation of the Class Use History
//  Created on:      23-Aug-2012 5:58:56 PM
//  Original author: INABG
///////////////////////////////////////////////////////////

#if !defined(EA_0E0391D9_5CD5_486a_84BF_15851DC4B1D6__INCLUDED_)
#define EA_0E0391D9_5CD5_486a_84BF_15851DC4B1D6__INCLUDED_
#include <QString>
namespace BOMLIB
{
	//! UseHistory
	/*! Responsibility: Holds the Historical information related to the usage of the BOM ObjectType.
	*/
class UseHistory
{

public:
		//! Constructor
        UseHistory();
		//! Destructor
        virtual ~UseHistory();
		//! GetUseHistoryVal
		/*! Returns the usage history as string.
		*/
        QString GetUseHistoryVal();
		//! SetUseHistoryVal
		/*! Sets the usage history as string.
		*/
        void SetUseHistoryVal(QString newVal);

private:
        QString UseHistoryval;

};
}

#endif // !defined(EA_0E0391D9_5CD5_486a_84BF_15851DC4B1D6__INCLUDED_)
