///////////////////////////////////////////////////////////
//  Model Identification.h
//  Implementation of the Class Model Identification
//  Created on:      23-Aug-2012 5:58:52 PM
//  Original author: INABG
///////////////////////////////////////////////////////////

#ifndef MODELIDENTIFY_H
#define MODELIDENTIFY_H
#include <qstring.h>
#include "POC.h"
#include "Keyword.h"
#include "Glymph.h"
#include "Reference.h"
#include "UseHistory.h"
#include <QList>
#include "interface.h"
#include <qimage.h>
#include "bomlibrary_global.h"
#include <qplugin.h>
#include <qsize.h>
namespace BOMLIB
{
//! ModelIdentification	
	/*!	Responsibility: Responsible as Identifier for the Model Object to be uniquely
		identified from a list of Model objects.
	*/
class BOMLIBRARY_EXPORT ModelIdentification
{

public:
	//! Constructor
	ModelIdentification();
	//! Destructor
	virtual ~ModelIdentification();
	//! All attributes or Properties associated with the Model 
    QString GetApplicationDomain();
	QString GetDescription();
    QString GetModificationDate();
	//! Name of the Model Identification 
	QString GetName();
	int GetOther();
	QString GetPurpose();
    QString GetReleaseRestriction();
    QString GetSecurityClassification();
    int GetBOMType();
    int GetUseLimitation();
	double GetVersion();
	//! Get Toolbox Image, Sizes and FileName
    QImage GetToolboxImage();
	QString GetToolBoxImageFileName();	
	QSize GetToolBoxImageSize();
	QString GetToolBoxImageFileNameWithExtension();
	//! Get Scene Image, Sizes and FileName
	QImage GetSceneImage();
    QString GetSceneImageFileName();
	QString GetSceneImageFileNameWithExtension();
	QSize GetSceneImageSize();
	QString GetSceneImageStateChangedFileNameWithExtension();
	//! Set the attributes or properties on Model
	void SetApplicationDomain(QString newVal);
	void SetDescription(QString newVal);
    void SetModificationDate(QString newVal);
	void SetName(QString newVal);
	void SetOther(int newVal);
	void SetPurpose(QString newVal);
    void SetReleaseRestriction(QString newVal);
    void SetSecurityClassification(QString newVal);
    void SetBOMType(int newVal);
    void SetUseLimitation(int newVal);
	void SetVersion(double newVal);
	//! Add the Objects associated with the BOM Object
        //contained objects
        void AddPOC(POC* poc);
        void AddGlymph(Glymph* picture);
        void AddReference(Reference* ref);
        void AddUseHistory(UseHistory* useHist);
        void AddKeyword(Keyword* keyword);
        void AddInterface(Interface* inf);
	//! getGlymphList
	/*!
		Returns the list of Glymph items.
	*/
		QList<Glymph*> getGlymphList();
private:
    QString ApplicationDomain;
	QString Description;
    QString ModificationDate;
	QString Name;
	int Other;
	QString Purpose;
    QString ReleaseRestriction;
    QString SecurityClassification;
    int m_Type;
    int UseLimitation;
	double Version;
    //contained objects
    QList<POC*> m_POCList;
    QList<Keyword*> m_KeywordList;
    QList<Glymph*> m_GlymphList;
    QList<Reference*> m_ReferenceList;
    QList<UseHistory*> m_UseHistoryList;
    //added by us
    QList<Interface*> m_Interfaces;

};
}
#endif // !defined(EA_36E4F885_D731_4d1f_9983_0C20B40AE542__INCLUDED_)
