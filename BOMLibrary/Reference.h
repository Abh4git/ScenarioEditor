///////////////////////////////////////////////////////////
//  Reference.h
//  Implementation of the Class Reference
//  Created on:      23-Aug-2012 5:58:55 PM
//  Original author: INABG
///////////////////////////////////////////////////////////

#if !defined(EA_6014AAEA_6494_4ee6_BCAF_5FE9EB990636__INCLUDED_)
#define EA_6014AAEA_6494_4ee6_BCAF_5FE9EB990636__INCLUDED_
#include <QString>
namespace BOMLIB
{
	//! Reference
	/*! Responsibility : Hold References to the BOM Objects */
class Reference
{

public:
	//! Constructor
	Reference();
	//! Destructor
	virtual ~Reference();
	//! GetIdentification
	/*! Returns the Identifier as string. */
    QString GetIdentification();
	//! GetType
	/*! Returns the Type as string. */
    QString GetType();
	//! SetIdentification
	/*! \param QString newVal 
		Set the Identifier. */
    void SetIdentification(QString newVal);
	//! SetType
	/*! \param QString newVal 
		Set the Type. */
    void SetType(QString newVal);

private:
        QString Identification;
	QString Type;

};
}
#endif // !defined(EA_6014AAEA_6494_4ee6_BCAF_5FE9EB990636__INCLUDED_)
