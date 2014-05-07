#include "AutomGraphicsScene.h"
#include <qmimedata.h>
#include <QGraphicsPixmapItem>
#include <qimage.h>


AutomGraphicsScene::AutomGraphicsScene(QList<BOMObject*> bomTypesList, IBOMTypeLoadInterface* iBOMType,IBOMInstanceCreation* iBOMInst )
{
	this->m_BOMTypesList=bomTypesList;
	this->m_BOMTypeLoader=iBOMType;

	this->m_BOMInstanceCreator=iBOMInst;
}


AutomGraphicsScene::~AutomGraphicsScene(void)
{
}

void AutomGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) 
{
    bool acceptDrag = false;
    const QMimeData* mime = event->mimeData();
	bool hastext=mime->hasText();
	QString itemName;
	if (hastext)
	{
		//Obtain the Text set on the dragged item
		itemName=mime->text();
		this->m_currentItemName=itemName;
	}
    // Is an image present?
    if (mime->hasImage()) {
        QImage img = qvariant_cast<QImage>(mime->imageData());
        dragPix = QPixmap::fromImage(img);
        acceptDrag = !dragPix.isNull();
    }
    event->setAccepted(true);
}

void AutomGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
    // Add the relevant QGraphicsTextItem. Here it is just as text
	
	//Snap In Mechanism : If within the event->scenePos().x() + 30  and event->scenePos().y() + 30
	//x-30, Y+30 (top left)
	//------------- x+30, y+30 (top right)
	//x-30, Y-30 (bottom left) and x+30,y-30 (bottom right)
	int xPos=0;
	int yPos=0;
    QGraphicsItem* itemToSnap= this->itemAt(event->scenePos().x()-30,event->scenePos().y()+30,QTransform() );
    if (itemToSnap==NULL) itemToSnap= this->itemAt(event->scenePos().x()+30,event->scenePos().y()+30,QTransform() );
    if (itemToSnap==NULL) itemToSnap= this->itemAt(event->scenePos().x()-30,event->scenePos().y()-30,QTransform() );
    if (itemToSnap==NULL) itemToSnap= this->itemAt(event->scenePos().x()+30,event->scenePos().y()-30,QTransform() );
	if (itemToSnap!=NULL) //nearby item exists
	{
		xPos= itemToSnap->scenePos().x();
		yPos=itemToSnap->scenePos().y();
	}
	//QGraphicsTextItem* selectedBOMId= this->addText(this->m_currentItemName);
	//selectedBOMId->setPos(event->scenePos().x(),event->scenePos().y());
		
		BOMObject* bomType= this->m_BOMTypeLoader->FindBOMType(this->m_currentItemName);
		BOMInstance* instToCreate;
		
	
		BOMInstance* instBOM;
		
	if (xPos==0 && yPos==0)
	{
		instToCreate=this->m_BOMInstanceCreator->createBOMInstance(bomType,event->scenePos().x(),event->scenePos().y(), bomType->GetModelIdentification()->GetName() +   ":1");
		//instBOM= //new BOMInstance(bomTypeSel,event->scenePos().x(),event->scenePos().y(),1);
	}
	 else
	 {
		 instToCreate=this->m_BOMInstanceCreator->createBOMInstance(bomType,xPos,yPos,bomType->GetModelIdentification()->GetName() +   ":1");
		 //instBOM=//new BOMInstance(bomTypeSel,xPos,yPos,1);
	}
	//BOMInstance* instBOM=new BOMInstance(bomTypeSel,event->scenePos().x(),event->scenePos().y(),1);
	this->AssignBomInstanceNumber(this->m_currentItemName, instToCreate);
	this->addItem(instToCreate);
	
	//Important event->scenePos() is important that this translates to
	//the right position on the scene.
	this->m_BOMInstanceList.append(instToCreate);
	
}


BOMObject* AutomGraphicsScene::FindBOMType(QString BOMTypeName)
{
    foreach(BOMObject* bomType,  this->m_BOMTypesList)
    {
        if (bomType->GetModelIdentification()->GetName()==BOMTypeName)
        {
            return bomType;
        }
    }
}

void AutomGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
	event->setAccepted(true);

}
void AutomGraphicsScene::mousePressEvent(QMouseEvent* event)
{
	if (this->selectedItems().count()>0)
	{

		BOMInstance* bomInst =(BOMInstance*)this->selectedItems().at(0);

		Singleton* container= Singleton::instance();
		container->setCurrentBOMInstance(bomInst);
		//container->addBOM(bomInst);

	}
}

void AutomGraphicsScene::clearAllItems()
{
	this->m_BOMInstanceList.clear();
	this->m_Connections.clear();
	this->clear();
}

void AutomGraphicsScene::foundChanges()
{
    QEvent* event1= new QEvent(QEvent::ChildRemoved);
    QApplication::postEvent(this->parent(),event1);
  }
