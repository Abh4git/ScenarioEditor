#ifndef IBOMINSTCREATE_H
#define IBOMINSTCREATE_H

#include "../BOMGraphicalLibrary/bominstance.h"
#include "../BOMGraphicalLibrary/connectorgraphicitem.h"
#include "../BOMGraphicalLibrary/msgGraphicsItemWithText.h"
#include "../BOMGraphicalLibrary/MsgGraphicsItem.h"
#include "../BOMGraphicalLibrary/ActionGraphicsItem.h"
#include <qplugin.h>

using namespace BOMLIB;
using namespace WSIMINST;
//! IBOMInstanceCreation Interface class
	/*!
		Responsibility: Act as Base class for BOM Instance creation of varied BOM Types and Connectors, Messages
		and Action Graphics
	*/
class IBOMInstanceCreation
 {
 public:
	 virtual BOMInstance* createBOMInstance(BOMObject* typeofBOM, int centerXPos,int centerYPos,QString userDefName)=0;
	 virtual ConnectorGraphicitem* createConnector(int startX,int startY, int endX,int endY, QString UserDefName="Default")=0;
     virtual msgGraphicsItemWithText* createMessagePacketTxt(QPoint position,QString UserDefname="Packet")=0;
	 virtual MsgGraphicsItem* createMessagePacket(QPoint position)=0;
	 virtual ActionGraphicsItem* createActionSignal(QPoint position)=0;
	 virtual QGraphicsTextItem* createHighLightedText(QPoint position,QString valueText)=0;
 };

Q_DECLARE_INTERFACE(IBOMInstanceCreation,
                     "BOMInstanceCreator/1.0");


#endif