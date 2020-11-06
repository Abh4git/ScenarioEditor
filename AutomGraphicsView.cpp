#include "AutomGraphicsView.h"
#include <QPointF>
#include <qmessagebox.h>
#include <qfiledialog.h>
AutomGraphicsView::AutomGraphicsView(QList<BOMObject*> bomTypesList,  IBOMTypeLoadInterface* iBOMTypeLoad, IBOMInstanceCreation* iBOMInstCreat, QWidget *parent) :
        QGraphicsView(parent)
    {
        scene = new AutomGraphicsScene(bomTypesList,iBOMTypeLoad,iBOMInstCreat);
		this->setAcceptDrops(true);
		this->setMouseTracking(true);
        this->setSceneRect(50, 50, 350, 350);
        this->setScene(scene);

		m_actConnectItems = new QAction(tr("&Connect with COM_BUS"), this);
        m_actConnectItems->setStatusTip(tr("Connect with another Item"));
		connect(m_actConnectItems, SIGNAL(triggered()), this, SLOT(doConnectItems()));
	 //menu for animation - action
	 m_actClearAll = new QAction(tr("&Clear All"), this);
     m_actClearAll->setStatusTip(tr("Clear All Items"));
     connect(m_actClearAll, SIGNAL(triggered()), this, SLOT(clearAllItems()));
	 //menu for save - action
	 m_actSaveScene = new QAction(tr("&Save Scenario"), this);
     m_actSaveScene->setStatusTip(tr("Save Scenario"));
     connect(m_actSaveScene, SIGNAL(triggered()), this, SLOT(doSaveScene()));

	 m_actOpenScenarioFromFile = new QAction(tr("&Open Scenario"), this);
     m_actOpenScenarioFromFile->setStatusTip(tr("Open Scenario"));
     connect(m_actOpenScenarioFromFile, SIGNAL(triggered()), this, SLOT(openScenarioFromFile()));

	 /*m_actActions = new QAction(tr("&Open Scenario"), this);
     m_actOpenScenarioFromFile->setStatusTip(tr("Open Scenario"));
     connect(m_actOpenScenarioFromFile, SIGNAL(triggered()), this, SLOT(openScenarioFromFile()));*/


		
    }

void AutomGraphicsView::openScenarioFromFile()
{
	QString selfilter = tr("XML (*.xml)");
	QString defaultScenePath= QDir::currentPath() + "\\Scenarios";
	QString fileName = QFileDialog::getOpenFileName(this,"Open Scene File",defaultScenePath,  tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" ), &selfilter );
	ReadScenario(fileName);
	 doConnectItems();
}
void AutomGraphicsView::ReadScenario(QString fileName)
{
	ScenarioReader* reader1=new ScenarioReader(fileName);
		reader1->SetDirectory("C:/");
        reader1->ReadDefintions();
        QList<SceneItem*> topology;
		topology= reader1->GetSceneTopology();
		this->m_currentSceneItems=topology;
		//QList<SceneAction*> actions=reader1->GetActionSequence();
		this->m_currentSceneActions=reader1->GetActionSequence();
		QList<ComAction*> comactions=reader1->GetComActions();
		BOMInstance* combusInst;
	//this->getCurrentScene()->m_BOMInstancesList=  QList<BOMInstance*>();
	foreach(SceneItem* item,topology)
	{
		QString identifier=item->getIdentifier();
		QStringList idParts=identifier.split(".");
		QString bomTypeName;
		bomTypeName= idParts.at(0);
		int instNo=idParts.at(1).toInt();
		BOMObject* bomType= this->getCurrentScene()->FindBOMType( bomTypeName);
		BOMInstance* instToCreate;
		instToCreate=this->getCurrentScene()->getBOMInstanceCreator() ->createBOMInstance(bomType,item->getPosition().x(),item->getPosition().y(),"");
		instToCreate->setInstanceNumber(instNo);
		scene->addItem(instToCreate);
		scene->AddBOMInstance(instToCreate);
		if (bomTypeName=="COM_BUS") combusInst=instToCreate;
	}

	foreach(BOMInstance* inst,this->scene->getBOMInstanceList())
	{ 
		if (inst!=combusInst)
		{
		ConnectorGraphicitem* itemConEng=this->getCurrentScene()->getBOMInstanceCreator()->createConnector(inst->boundingRect().center().x()-40,combusInst->boundingRect().center().y()+10,inst->boundingRect().center().x()-40,inst->boundingRect().bottomRight().y(),"EL-CTRLHARM");
		this->getCurrentScene()->addItem(itemConEng);
		this->getCurrentScene()->getConnections().append(itemConEng);
		}
	}
	

}

void AutomGraphicsView::doSaveScene()
{
	QString currentDir = QDir::currentPath();
	
	QString selfilter = tr("XML (*.xml)");
	QString fileName = QFileDialog::getSaveFileName(this,"Save Scene File",currentDir + "\\Scenarios",  tr("All Scenario files (*.*);" ), &selfilter );
	//ScenarioWriter* writer= new ScenarioWriter( currentDir + "\\Scenarios" + "TestScene.xml");
	ScenarioWriter* writer= new ScenarioWriter( fileName);
	int iCount=1;
	foreach(BOMInstance* bomInst, this->getCurrentScene()->getBOMInstanceList())
	{
		SceneItem* item=new SceneItem(bomInst->GetContainedBOMType()->GetModelIdentification()->GetName()+ "." + QString::number(bomInst->GetInstanceNumber()), 1,"Testme",bomInst->GetPosition().toPoint());
		writer->AddTopologyItem(item);
		iCount++;
	}
	//SceneAction* action= new SceneAction("1",1, 1,"ENGG-SPLUS.1","ENGG-SPLUS.2",3,1000);
	foreach(SceneAction* act, this->m_currentSceneActions)
	{
	writer->AddActions(act);
	}
	writer->WriteAndClose();
	QMessageBox box;
	box.setText("File Saved as" + fileName);
	box.exec();
}
//Create connect items
void AutomGraphicsView::doConnectItems()
{
	BOMInstance* boiler;
	BOMInstance* turbine;
	BOMInstance* generator;
	BOMInstance* controldev;
	foreach(BOMInstance* inst,this->getCurrentScene()->getBOMInstanceList())
	{
		if (inst->GetContainedBOMType()->GetModelIdentification()->GetName()=="BOILER")
		{
			boiler= inst;
			
		}
		else if  (inst->GetContainedBOMType()->GetModelIdentification()->GetName()=="GENERATOR")
		{
			generator=inst;
		}
		else if  (inst->GetContainedBOMType()->GetModelIdentification()->GetName()=="TURBINE")
		{
			turbine=inst;
		}
		else if  (inst->GetContainedBOMType()->GetModelIdentification()->GetName()=="CONTROL_DEVICE")
		{
			controldev=inst;
		}

	}

	//from boiler to turbine 
	if (boiler!=NULL && turbine!=NULL)
	{
	ConnectorGraphicitem* itemConToTurbine;
	itemConToTurbine=this->getCurrentScene()->getBOMInstanceCreator()->createConnector(boiler->boundingRect().center().x()-40,boiler->boundingRect().center().y()+10,turbine->boundingRect().center().x()-40,turbine->boundingRect().bottomRight().y(),"Steam flow");
	this->scene->addItem(itemConToTurbine);
	}
	//from turbine to generator
	if (generator!=NULL && turbine!=NULL)
	{
	
	ConnectorGraphicitem* itemConFromTurbine;
	itemConFromTurbine=this->getCurrentScene()->getBOMInstanceCreator()->createConnector(turbine->boundingRect().center().x()-40,turbine->boundingRect().center().y()+10,generator->boundingRect().center().x()-40,generator->boundingRect().bottomRight().y(),"Power");
	this->scene->addItem(itemConFromTurbine);
	}

	//from turbine to generator
	if (boiler!=NULL && controldev!=NULL)
	{
	
	ConnectorGraphicitem* itemConBoilerToDev;
	itemConBoilerToDev=this->getCurrentScene()->getBOMInstanceCreator()->createConnector(boiler->boundingRect().center().x()-40,boiler->boundingRect().center().y()+10,controldev->boundingRect().center().x()-40,controldev->boundingRect().bottomRight().y(),"Signal flow");
	this->scene->addItem(itemConBoilerToDev);
	}
	
	/*
	BOMInstance* one=this->getCurrentScene()->getBOMInstaceList().at(0);
	BOMInstance* two=this->getCurrentScene()->getBOMInstaceList().at(1);
	
	ConnectorGraphicitem* itemConEng=this->getCurrentScene()->getBOMInstanceCreator()->createConnector(one->boundingRect().center().x()-40,two->boundingRect().center().y()+10,one->boundingRect().center().x()-40,one->boundingRect().bottomRight().y(),"EL-CTRLHARM");
	this->getCurrentScene()->addItem(itemConEng);
	*/
	//this->m_Connections.append(itemConEng);
		


	//QAction *actToConnect= this->m_MainContextMenu->actions().at(0);
	//actToConnect->addm
	/*QAction* actNew= new QAction("Testme",this);
	QMenu* subMenu=this->m_MainContextMenu->addMenu("Items");
	subMenu->addAction(actNew);*/
}

void AutomGraphicsView::clearAllItems()
{
	
	
	this->getCurrentScene()->clearAllItems();
}



AutomGraphicsView::~AutomGraphicsView(void)
{
}

void AutomGraphicsView::contextMenuEvent(QContextMenuEvent *event)
 {
     //QMenu menu(this);
	 QMenu menu(this);
	 m_MainContextMenu=&menu;
	 
	 QMenu subMenu(&menu);
	 m_connectSubMenu= &subMenu;
	 subMenu.setTitle("Connect Items");
	 menu.addMenu(&subMenu);
     subMenu.addAction(m_actConnectItems);
	 /*
	 QMenu actionsubMenu(&menu);
	 m_addActionSubMenu=&actionsubMenu;
	 actionsubMenu.setTitle("Define Action");
	 menu.addMenu(&actionsubMenu);

	 QString actionsList;
	 int iCount=1;
	 actionsList.append("Action Between");

	 foreach(BOMInstance* inst, m_BOMInstanceList)
	 {
		if (inst->GetContainedBOMType()->GetModelIdentification()->GetName()!="COM_BUS")
		{
			if (iCount>2) break;
			actionsList.append(inst->GetContainedBOMType()->GetModelIdentification()->GetName() + "." + QString::number(inst->GetInstanceNumber()));
			iCount++;
		}
		 
	 }
	 actionsubMenu.addAction(actionsList);
	 */
	 menu.addAction(m_actClearAll);
	 menu.addAction(m_actSaveScene);
	 menu.addAction(m_actOpenScenarioFromFile);
	 //removed now -menu.addAction(m_actAllocation);
     menu.exec(event->globalPos());
 }

void AutomGraphicsView::mousePressEvent(QMouseEvent* e)
{
	//QPointF pt = mapToScene(e->pos());

	//scene->addText("MY Test1");
	if (this->getCurrentScene()->selectedItems().count()>0)
	{

		BOMInstance* bomInst =(BOMInstance*)this->getCurrentScene()->selectedItems().at(0);

		Singleton* container= Singleton::instance();
		container->setCurrentBOMInstance(bomInst);
		//container->addBOM(bomInst);

	}

}

void AutomGraphicsView::mouseReleaseEvent(QMouseEvent* e)
{
	//QPointF pt = mapToScene(e->pos());
	//scene->addText("MY Test2");
}
