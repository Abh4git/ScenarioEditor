#ifndef BOMINTERFGRAPHICITEM_H
#define BOMINTERFGRAPHICITEM_H
#include <QGraphicsEllipseItem>
#include <../BOMLibrary/interface.h>
#include <QPainter>
using namespace BOMLIB;
namespace WSIMINST
{
	//! InterfGraphicItem class
	/*!
		Responsibility: Create a small elliptic Item to represent interfaces in graphics scene
	*/
class InterfGraphicItem:public QGraphicsEllipseItem
{
public:
    //InterfGraphicItem();
	//! Constructor
	/*!
		\param parent
	*/
    explicit InterfGraphicItem(QGraphicsItem *parent = 0);
    //! Constructor
	/*!
		\param typeOfInterface as Interface pointer
		\param parent
		\param startX int
		\param startY int
	*/
	explicit InterfGraphicItem(Interface* typeOfInterface,QGraphicsItem *parent = 0,int startX=0, int startY=0);
    //! GetPosition
	/*!
		Return the position as QPOintF
	*/
	QPointF GetPosition()
    {
        return QPointF(_startX,_startY);
    }


private:
    int _startX, _startY;
    Interface* _typeOfInterface;
};
}
#endif // BOMINTERFGRAPHICITEM_H
