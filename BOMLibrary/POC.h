///////////////////////////////////////////////////////////
//  POC.h
//  Implementation of the Class POC
//  Created on:      23-Aug-2012 5:58:54 PM
//  Original author: INABG
///////////////////////////////////////////////////////////

#if !defined(EA_882AA6A8_3915_4230_B3A1_ED65FE65CFB1__INCLUDED_)
#define EA_882AA6A8_3915_4230_B3A1_ED65FE65CFB1__INCLUDED_
#include <QString>
namespace BOMLIB
{
//! POC
	/*!
		Responsibility : Holds the details of the Point Of Contact
		The person responsible for the model object and who can clarify
		the details.
	*/
class POC
{

public:
	//! Constructor
	POC();
	//! Destructor
	virtual ~POC();
	/*! Get the attributes including the name, email, organization and
	telephone details */
	QString GetEmail();
	QString GetName();
	QString GetOrg();
	QString GetTelephone();
	QString GetType();
	/*! Set the attributes including the name, email, organization and
	telephone details */
	void SetEmail(QString newVal);
	void SetName(QString newVal);
	void SetOrg(QString newVal);
	void SetTelephone(QString newVal);
	void SetType(QString newVal);

private:
	QString Email;
	QString Name;
	QString Org;
	QString Telephone;
	QString Type;

};
}
#endif // !defined(EA_882AA6A8_3915_4230_B3A1_ED65FE65CFB1__INCLUDED_)
