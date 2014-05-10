#pragma once
#include "qgraphicsscene.h"
#include <QGraphicsSceneDragDropEvent>
#include <qpixmap.h>
#include <qgraphicssceneevent.h>
#include <QGraphicsView>
#include "../BOMLibrary/IBOMTypeLoadInterface.h"
#include "../BOMGraphicalLibrary/IBOMInstanceCreation.h"
#include "../BOMGraphicalLibrary/bominstance.h"
#include <Singleton.h>
#include <QApplication>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;
class QMouseEvent;
QT_END_NAMESPACE

	using namespace BOMLIB;
	using namespace WSIMINST;
//! AutomGraphicsScene Class
/*!
	Responsibility: Inheriting from QGraphicsScene this is responsible for
	Supporting drag and drop of BOM Object types. Holds BOM Instances and
	Graphics items and provides helper functions for finding the BOMType based
	on name.
*/
class AutomGraphicsScene :
	public QGraphicsScene
{
public:
	//AutomGraphicsScene(QList<BOMObject*> bomTypesList, IBOMTypeLoadInterface* iBOMTypeLoad );
	//! Constructor
	/*!
		\param bomTypesList list of BOMObject
		\param iBOMType IBOMTypeLoadInterface
		\param iBOMInst IBOMInstanceCreation
	*/
	AutomGraphicsScene(QList<BOMObject*> bomTypesList, IBOMTypeLoadInterface* iBOMType,IBOMInstanceCreation* iBOMInst );
	//! getBOMInstanceList
	/*!
		Return the current List of BOM Instances as a list
	*/
	QList<BOMInstance*> getBOMInstanceList()
	{
		return m_BOMInstanceList;
	}
	//! getBOMInstanceCreator
	/*!
		Return the IBOMInstance creation object
	*/
	IBOMInstanceCreation* getBOMInstanceCreator()
	{
		return m_BOMInstanceCreator;
	}
	/*void addItem(QGraphicsItem *item)
	{
		this->addItem(item);
		this->m_BOMInstanceList.append(item);
	}*/
	//! AddBOMInstance
	/*!
		Return the IBOMInstance creation object
        \param instance BOMInstance*
	*/
	void AddBOMInstance(BOMInstance* instance)
	{
		this->m_BOMInstanceList.append(instance);
	}
	//! AssignBomInstanceNumber
	/*!
		Return the IBOMInstance creation object
        \param bomTypeName string
        \param bomInst BOMInstance*
	*/
	void AssignBomInstanceNumber(QString bomTypeName,BOMInstance* bomInst)
	{
		int highestInstNumber=0;
		int currentInstNumber=0;
		foreach(BOMInstance* inst, m_BOMInstanceList)
		{
			if (inst->GetContainedBOMType()->GetModelIdentification()->GetName()==bomTypeName)
			{
				currentInstNumber=inst->GetInstanceNumber();
				if (currentInstNumber>highestInstNumber)
				{
					highestInstNumber=currentInstNumber;
				}
			}
		}
		
		bomInst->setInstanceNumber(highestInstNumber+1);
	}
    //! getConnections
    /*!
        Return the QList of ConnectorGraphicitem* s
    */
	QList<ConnectorGraphicitem*> getConnections()
	{
		return m_Connections;
	}
    //! FindBOMType
    /*!
        Return the BOMObject based on BOMTypeName
        \param BOMTypeName string
    */
	BOMObject* FindBOMType(QString BOMTypeName);
    //! clearAllItems
    /*!
        Clear all the graphical items in scene as well as scene actions in
        right pane.
    */
    void clearAllItems();
    //! foundChanges
    /*!
        Found Changes based on detection logic.
    */
    void foundChanges();
protected:
	void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
	void mousePressEvent(QMouseEvent *event);
	
    ~AutomGraphicsScene(void);
private:
	QPixmap dragPix;
	QString m_currentItemName;
	QList<BOMObject*> m_BOMTypesList;
	QList<BOMInstance*> m_BOMInstanceList;
	
	IBOMTypeLoadInterface* m_BOMTypeLoader;
	IBOMInstanceCreation* m_BOMInstanceCreator;
	QList<ConnectorGraphicitem*> m_Connections;
};

