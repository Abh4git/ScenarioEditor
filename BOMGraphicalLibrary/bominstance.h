#ifndef BOMGRAPHINSTANCE_H
#define BOMGRAPHINSTANCE_H
#include <QGraphicsItemGroup>
#include <../BOMLibrary/bomobject.h>
#include "devicegraphicitem.h"
#include "EquipmentGraphicItem.h"
// #include <QWidget>
 #include <QIcon>
#include <qdir.h>

#include <../BOMGraphicalLibrary/interfgraphicitem.h>
using namespace BOMLIB;
namespace WSIMINST
{
	//! BOMInstance class
	/*!
		Responsibility: Base Class for all the BOM Instances to inherit from
		Base class provides all common member functions
	*/
class BOMInstance:public QGraphicsItemGroup
{
public:
	//! Constructor
	/*!
		\param bomType type of BOMObject to be instantiated
		\param centerX x pos of Graphical instance center
		\param centerY y pos of Graphical instance center
		\param instanceNumber to be instantiated BOM Object
		\param userDefName string for userdefined name
		The constructor has specific approach of Graphical creation. The BOMInstance is created
		from bomfactory.cpp
	*/
    BOMInstance(BOMObject* bomType,int startX, int startY,int instanceNumber, QString userDefinedName="");
	//! GetContainedBOMType
	/*!
		Returns the contained BOM Type of the BOM Instance.
	*/
    BOMObject* GetContainedBOMType()
	{
		return m_BOMType;
	}
	//! GetInstanceNumber
	/*!
		Returns the instance number of the BOM Instance.
	*/
    int GetInstanceNumber()
	{
		return m_instanceNumber;
	}
	//! GetPosition
	/*!
		Returns the position of the BOM Instance as QPointF.
	*/
    QPointF GetPosition()
	{
		
		return m_Point;
	}
	//! setInstanceNumber
	/*!
		\param instNo integer 
		Sets the instance number of the BOM Instance
	*/
	void setInstanceNumber(int instNo)
	{
		m_instanceNumber=instNo;
	}
	//! GetPosition
	/*!
		Returns the center position of the BOM Instance as QPointF.
	*/
	QPointF GetCenterPosition()
	{
		QPointF point=m_Point;
		QPointF centerPos=QPointF(point.x()-10,point.y()+30); 
		return centerPos;
	}
	//! hoverEnterEvent
	/*!
		Override of events for hover
	*/
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //! hoverEnterEvent
	/*!
		Override of events for hover
	*/
	void  hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ) ;
    //! FindSignal
	/*!
		\param signalName as QString
		Returns the interface items based on signal names
	*/
	InterfGraphicItem* FindSignal(QString signalName);
	//if it is non electrical then process model
	

signals:
    void objectSelected(BOMObject* bomType);
protected:
    BOMObject* m_BOMType;
    int m_instanceNumber;
    QPointF m_Point;
    QList<InterfGraphicItem*> m_Signals;
	QString m_userDefName;
	QString m_modelObjectType;
	QString m_modelInstanceName;
	
};
}
#endif // BOMGRAPHINSTANCE_H


