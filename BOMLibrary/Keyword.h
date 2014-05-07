///////////////////////////////////////////////////////////
//  Keyword.h
//  Implementation of the Class Keyword
//  Created on:      23-Aug-2012 5:58:50 PM
//  Original author: INABG
///////////////////////////////////////////////////////////

#if !defined(EA_33E1BA0C_10B3_42d9_8A56_49AF9AC5D471__INCLUDED_)
#define EA_33E1BA0C_10B3_42d9_8A56_49AF9AC5D471__INCLUDED_
#include <QString>
namespace BOMLIB
{
	//! Keyword
	/*!
		Holds Keyword as per BOM Model SISO - STD 008
	*/
class Keyword
{

public:
	//! Constructor
	Keyword();
	virtual ~Keyword();
	//! GetKeywordValue
	/*!
		Returns the value of Keyword
	*/
    QString GetKeywordValue();
	//! GetTaxonomy
	/*!
		Returns the taxonomy used
	*/
	QString GetTaxonomy();
	//! SetKeywordValue
	/*!
		\param QString newVal
		Sets the Keyword Value
	*/
    void SetKeywordValue(QString newVal);
	//! SetTaxonomy	
	/*!	\param QString newVal
		Sets the Taxonomy
	*/
	void SetTaxonomy(QString newVal);

private:
    QString KeywordValue;
	QString Taxonomy;

};
}
#endif // !defined(EA_33E1BA0C_10B3_42d9_8A56_49AF9AC5D471__INCLUDED_)
