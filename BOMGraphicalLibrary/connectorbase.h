#ifndef CONNECTORBASE_H
#define CONNECTORBASE_H
#include <QPoint>
namespace WSIMINST
{
enum Orientation
{
    Vertical=1,
    Horizontal=2
};
//! ConnectorBase class
	/*!
		Responsibility: Base Class for all the Connectors to inherit from
		Base class provides all common member functions
	*/
class ConnectorBase
{
public:
	//! Constructor
	/*!
		\param sourcePoint QPOint
		\param destPoint QPoint
		\param orient Orientation
		The source from and dest to it needs to be connected. Orientation is Horizontal or
		Vertical.
	*/
    ConnectorBase(QPoint sourcePoint,QPoint destPoint,Orientation orient=Horizontal)
    {
        _sourcePoint=sourcePoint;
        _destPoint=destPoint;
        _connectorOrient=orient;
    }
	//! SetOrientation
	/*!
		\param newvlaue Orientation
		Set the Orientation to Horizontal or Vertical.
	*/
    void SetOrientation(Orientation newValue)
    {
        _connectorOrient=newValue;
    }
    Orientation _connectorOrient;
    QPoint _sourcePoint;
    QPoint _destPoint;
};
}
#endif // CONNECTORBASE_H
