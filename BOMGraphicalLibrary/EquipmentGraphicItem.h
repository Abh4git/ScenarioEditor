#ifndef BOMEQPMTGRAPHICITEM_H
#define BOMEQPMTGRAPHICITEM_H
#include <QGraphicsPolygonItem>
#include <QPainter>
//#include<../BOMLibrary/ModelIdentification.h>
#include <../BOMLibrary/bomobject.h>
using namespace BOMLIB;
namespace WSIMINST
{
	//! DeviceGraphicItem class
	/*!
		Responsibility: Graphics Item for Devices like Controllers, IEDs etc. This is composed as
		a QGraphicsItemGroup in BOMInstance inherited classes like BOMIEquipment 
		Specifically used for objects of size 128*128 
	*/
class EquipmentGraphicItem : public QGraphicsPolygonItem
        //public QGraphicsItemGroup
        //
{
public:
    //DeviceGraphicItem();

    //
	//
	//! Constructor
	/*!
		\param parent
		
	*/
    explicit EquipmentGraphicItem(QGraphicsItem *parent = 0);
	 //! Constructor
	/*!
		\param typeOfBOM type of BOM
		\param parent
		\param startX as int
		\param startY as int
		\param endX as int
	*/
    explicit EquipmentGraphicItem(BOMObject* typeOfBOM,QGraphicsItem *parent = 0,int startX=0, int startY=0,int endX=0);
	//explicit DeviceGraphicItem(BOMObject* typeOfBOM,QGraphicsItem *parent = 0,int startX=0, int startY=0,int endX=0,int endY=0);
	//! Constructor
	/*!
		\param typeOfBOM type of BOM
		\param parent
		\param startX as int
		\param startY as int
	*/
	explicit EquipmentGraphicItem(QGraphicsItem *parent = 0,int startX=0, int startY=0);
    //! polygon
	/*!
		Return the graphic - Derived from QGraphicsItem
	*/
	QPolygonF polygon() const
        { return deviceGraphic; }
    
	//! setPosition
	/*!
		\param startX int
		\param startY int
		Sets the position of the GraphicsItem
	*/
	void setPosition(int startX, int startY)
    {
        _startX=startX;
        _startY=startY;
       //_leftEnd=QPointF(_startX-40,_startY +40);
        //_rightEnd=QPointF(_startX+40,_startY +40);
		//changes for equipment bigger like 128
		_leftEnd=QPointF(_startX-140,_startY +140);
        _rightEnd=QPointF(_startX+140,_startY +140);
    }
	//! GetRightEnd
	/*!
		Return the right end from QGraphicsItem
	*/
    QPointF GetRightEnd()
    {
        return _rightEnd;
    }
	//! GetLeftEnd
	/*!
		Return the left end of QGraphicsItem
	*/
    QPointF GetLeftEnd()
    {
        return _leftEnd;
    }

   // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void QGraphicsPolygonItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 )
    //{

      //  parentItem()->paint(painter,option,widget);
       // painter
    //}


signals:

public slots:

private:
    QPolygonF deviceGraphic;
    int _startX, _startY;
    QPolygonF polygonF;
     BOMObject* m_BOMType;
    QPointF _rightEnd;
    QPointF _leftEnd;


    //

};
}

#endif // BOMEQPMTGRAPHICITEM_H
