#include "automationelementswidget.h"


#include <qmessagebox.h>
#include <qstringlist.h>
#include <../BOMLibrary/Glymph.h>
#include <qpushbutton.h>

AutomationElementsWidget::AutomationElementsWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	LoadPlugins();
	
	loadTypeDefinitions();
	
	setupWidgets();
    m_Order=0;

}

AutomationElementsWidget::~AutomationElementsWidget()
{

}

void AutomationElementsWidget::LoadPlugins()
{
	QString currentPath=QDir::currentPath();
	m_applicationPath=currentPath;
	QMessageBox msgbox;
    //msgbox.setText(m_applicationPath);
    //msgbox.exec();
	//QMessageBox box;
	//box.setText(currentPath);
	//box.exec();
	//loading BOMLibrary
    //QPluginLoader loaderType(currentPath +  "\\Output\\BOMLibrary.dll");
    QPluginLoader loaderType(currentPath +  "\\BOMLibrary.dll");
    QObject *pluginType = loaderType.instance();
	QString error=loaderType.errorString();
	if (pluginType) this->m_BOMTypeLoader=qobject_cast<IBOMTypeLoadInterface*> (pluginType);
    if (!loaderType.isLoaded())
    {
        msgbox.setText(error);
        msgbox.exec();
    }
	//loading BOmGraphicalLibrary
    //QPluginLoader loaderInst(currentPath +  "\\Output\\BOMGraphicalLibrary.dll");
    QPluginLoader loaderInst(currentPath +  "\\BOMGraphicalLibrary.dll");
		//"C:\\Abhilash\\MyToolBox\\SystemsExplorer\\Win32\\Debug\\BOMGraphicalLibrary.dll");
	QObject *pluginInst = loaderInst.instance();
	QString insterror=loaderInst.errorString();
	if (pluginInst) this->m_BOMInstanceCreator=qobject_cast<IBOMInstanceCreation*> (pluginInst);
    if (!loaderInst.isLoaded())
    {
	msgbox.setText(insterror);
	msgbox.exec();
    }
}
void AutomationElementsWidget::loadTypeDefinitions()
{
	
	
	this->m_BOMTypeLoader->LoadDefinitions(m_applicationPath+ "\\ModelElements");
		//"C:\\Abhilash\\MyToolBox\\SystemsExplorer\\ScenarioEditor\\ModelElements");
	m_BOMTypesList= this->m_BOMTypeLoader->getCurrentDefintions();

}

BOMInstance* AutomationElementsWidget::findInstance(QString name,int instNo)
{
	foreach(BOMInstance* inst, this->m_BOMInstancesList)
	{
		if (inst->GetContainedBOMType()->GetModelIdentification()->GetName()==name && inst->GetInstanceNumber()==instNo)
		{
			return inst;
		}
	}
}

void AutomationElementsWidget::setupWidgets()
{

	
	QFrame *frame = new QFrame;
	QHBoxLayout *frameLayout = new QHBoxLayout(frame);
	objectsList = new ObjectsList(100,this);
	
	foreach (BOMObject* obj,m_BOMTypesList)
	{
		objectsList->addObject(obj,QPoint(10,10));
	}
	QVBoxLayout* verticalBottomLayout=new QVBoxLayout();
	//objectsList->setViewMode(QListView::ViewMode::ListMode);
	//this->m_currentView = new QGraphicsView( this); 
		this->m_currentView = new AutomGraphicsView(this->m_BOMTypesList,this->m_BOMTypeLoader, this->m_BOMInstanceCreator, this);
	//this->m_currentView->setAcceptDrops(true);
	verticalBottomLayout->addWidget(this->m_currentView,10);

	//listen to events from graphicsview
	this->m_currentView->getCurrentScene()->installEventFilter(this);
	this->m_currentView->installEventFilter(this);
	//First splitter between toolbox and view and message
	QSplitter* splitBetwnTooBoxAndView= new QSplitter(Qt::Horizontal);

	splitBetwnTooBoxAndView->addWidget(objectsList);

	QSplitter* splitVertBetwnViewAndMsgBox= new QSplitter(Qt::Vertical);

	splitVertBetwnViewAndMsgBox->addWidget(this->m_currentView);

	
	//this->m_tblMessages= new QTableWidget;
	//this->m_tblMessages->setColumnCount(4);
	//this->m_tblMessages->setRowCount(5);
	//QStringList msgHeaders;
	//msgHeaders.append("Category");
	//msgHeaders.append("Title");
	//msgHeaders.append("Description");
	//msgHeaders.append("Recommendation");
	//this->m_tblMessages->setHorizontalHeaderLabels(msgHeaders);
	verticalBottomLayout->setSizeConstraint(QLayout::SetMaximumSize);
	verticalBottomLayout->setStretch(0,60);
	//verticalBottomLayout->addWidget(this->m_tblMessages,10);

	createMessageTableView();

	splitVertBetwnViewAndMsgBox->addWidget(this->m_tblMessages);
	splitBetwnTooBoxAndView->addWidget(splitVertBetwnViewAndMsgBox);
	


	splitBetwnTooBoxAndView->show();

	frameLayout->addWidget(splitBetwnTooBoxAndView);

	
	
	
	QVBoxLayout* verticalRightLayout=new QVBoxLayout;
	verticalRightLayout->setStretchFactor(this,4);
	
	
	createAllocationTableView();

	QSplitter* splitVertBetwnAllocAndPropBox= new QSplitter(Qt::Vertical);

	splitVertBetwnAllocAndPropBox->addWidget(this->m_tblAllocation);

	//createPropertyTableView();
	//splitVertBetwnAllocAndPropBox->addWidget(this->m_objectProperties);

	splitBetwnTooBoxAndView->addWidget(splitVertBetwnAllocAndPropBox);

	this->setLayout(frameLayout);
    //Menu and actions

	 m_actrefreshActionList = new QAction(tr("&Refresh Action List"), this);
     m_actrefreshActionList->setStatusTip(tr("Refresh Action List"));
     connect(m_actrefreshActionList, SIGNAL(triggered()), this, SLOT(refreshActionList()));
	
	 m_actsetActionList = new QAction(tr("&Set Action List"), this);
     m_actsetActionList->setStatusTip(tr("Set Action List"));
     connect(m_actsetActionList, SIGNAL(triggered()), this, SLOT(setActionList()));
	

	 /* not used...
	 m_actDrillDown = new QAction(tr("&Open Scanned Diagram (.png)"), this);
     m_actDrillDown->setShortcuts(QKeySequence::Open);
     m_actDrillDown->setStatusTip(tr("Open and detect from Diagram"));
     connect(m_actDrillDown, SIGNAL(triggered()), this, SLOT(openScannedDiagram()));
	
	 m_actCompare = new QAction(tr("&Perform Symbol Detection"), this);
     m_actCompare->setShortcuts(QKeySequence::Open);
     m_actCompare->setStatusTip(tr("Open and detect from Diagram"));
     connect(m_actCompare, SIGNAL(triggered()), this, SLOT(doDetection()));
	
	
	  m_actsymbolDetectStageA = new QAction(tr("&Perform Symbol Detection  Stage-Segmn"), this);
     m_actsymbolDetectStageA->setShortcuts(QKeySequence::Copy);
     m_actsymbolDetectStageA->setStatusTip(tr("Open and detect from Diagram Stg1"));
     connect(m_actsymbolDetectStageA, SIGNAL(triggered()), this, SLOT(performDetectionStage(void)));

	 m_actsymbolDetectStageB = new QAction(tr("&Perform Symbol Detection  Stage2-OCR"), this);
     m_actsymbolDetectStageB->setShortcuts(QKeySequence::AddTab);
     m_actsymbolDetectStageB->setStatusTip(tr("Open and detect from Diagram Stg2"));
     connect(m_actsymbolDetectStageB, SIGNAL(triggered()), this, SLOT(doDetectStage2()));
	*/
}

bool AutomationElementsWidget::eventFilter(QObject* target,QEvent* event)
{
	QMessageBox msgbox;
	if (event->type()==QEvent::GraphicsSceneDrop)
	{
		//Some drop has happened..
		//msgbox.setText("Dropped");
		//msgbox.exec();
		this->refreshActionList();
		//return true;
	}
	if (event->type()==QEvent::GraphicsSceneContextMenu)
	{

        QAction* action;
        action = (QAction*) target;
        if (action->data() ==123)
        //if (target->objectName()=="m_actClearAll")
		{
		//Some move has happened..
		msgbox.setText("Conext menu clear");
		msgbox.exec();
		}
		//return true;
	}
    if (event->type()==QEvent::ChildRemoved)
    {

        //Cleared items redirected using this
        refreshActionList();
        //msgbox.setText("Conext menu clear");
        //msgbox.exec();

        //return true;
    }
	
	return QWidget::eventFilter(target,event);
}

QString AutomationElementsWidget::getInstanceIdentifier(int index)
{
	int positioninList=0;
	/*
	foreach(BOMInstance* inst,this->m_BOMInstancesList)
	{
		if (inst->GetContainedBOMType()->GetModelIdentification()->GetName()!="COM_BUS")
		{
			break;
		} else
		{
			positioninList++;
			break;
		}
		positioninList++;
	}*/
	BOMInstance* instance=this->m_BOMInstancesList.at(index);
	if (instance->GetContainedBOMType()->GetModelIdentification()->GetName()=="COM_BUS")
	{
		
		instance=this->m_BOMInstancesList.at(index+1);
	}
	
	
	QString instIdentify= instance->GetContainedBOMType()->GetModelIdentification()->GetName() + "." + QString::number( instance->GetInstanceNumber());
	return instIdentify;

}

void AutomationElementsWidget::setActionList()
{
	this->m_currentSceneActions= QList<SceneAction*>();
	for(int i=0; i<this->m_tblAllocation->rowCount(); i++)
	{
		QString order= this->m_tblAllocation->item(i, 0)->text();
		QString type= this->m_tblAllocation->item(i, 1)->text();

		QComboBox* combo=(QComboBox*)this->m_tblAllocation->cellWidget(i,2);  
		int selIndex=combo->currentIndex();
		
		QString source= getInstanceIdentifier(selIndex);
		QComboBox* comboDest=(QComboBox*)this->m_tblAllocation->cellWidget(i,3);  
		int selIndexDest=comboDest->currentIndex();
		
		QString dest= getInstanceIdentifier(selIndexDest);
		QString repeat= this->m_tblAllocation->item(i, 4)->text();
		QString waittime= this->m_tblAllocation->item(i, 5)->text();
		if (order!="" && source!="")
		{
		SceneAction* sceneAction= new SceneAction(QString::number(i),type.toInt(),order.toInt(), source,dest,repeat.toInt(),waittime.toInt());
		this->m_currentSceneActions.append(sceneAction);
		}

	}
	this->m_currentView->setCurrentSceneActionList(this->m_currentSceneActions);

}

//When an Item is added this gets triggered and adds rows
void AutomationElementsWidget::refreshActionList()
{
	
	this->m_BOMInstancesList= this->m_currentView->getCurrentScene()->getBOMInstanceList();
	//if nof instances *2 should be the number of rows
	int count=this->m_BOMInstancesList.count();
    //this->m_tblAllocation->clear();
    //createAllocationTableView();
    this->m_tblAllocation->setRowCount(count*2);
	int actualCount=0;
    int i=count;
    if (count <2) return;
    for(int i=0;i<count*2;i++)
	{

        m_Order ++;
        QComboBox* m_ComboSource;
        m_ComboSource= new QComboBox(this);
		QComboBox* m_ComboDest;
		m_ComboDest= new QComboBox(this);
        QComboBox* m_ComboActionType;
        m_ComboActionType= new QComboBox(this);
        m_ComboActionType->addItem("1"); //Message
        m_ComboActionType->addItem("2"); //Signal
        m_ComboActionType->addItem("3");//Steam/Heat
        m_ComboActionType->addItem("4");//Callout
        m_ComboActionType->setToolTip("1-Message,2-Signal,3-SteamorHeat,4-Callout");
		foreach (BOMInstance* inst,this->m_BOMInstancesList)
		{
			if (inst->GetContainedBOMType()->GetModelIdentification()->GetName()!="COM_BUS")
			{
			QString identifier= inst->GetContainedBOMType()->GetModelIdentification()->GetName() + "." + QString::number(inst->GetInstanceNumber());
			m_ComboSource->addItem(identifier);
            m_ComboDest->addItem(identifier);
			actualCount++;
			}
		}
        QTableWidgetItem *itabOrder;
        itabOrder= new QTableWidgetItem();
        itabOrder->setText(QString::number( i+1)); //QString::number(m_Order));
        this->m_tblAllocation->setItem (i, 0,itabOrder );
        m_ComboSource->setToolTip("Select Source Object");
        m_ComboDest->setToolTip("Select Destination Object");
        this->m_tblAllocation->setCellWidget(i, 1, m_ComboActionType);
        this->m_tblAllocation->setCellWidget(i, 2, m_ComboSource);
        this->m_tblAllocation->setCellWidget(i, 3, m_ComboDest);

        QTableWidgetItem *itabTimeToNextAction;
        itabTimeToNextAction= new QTableWidgetItem();
        itabTimeToNextAction->setText("1000");
        itabOrder->setToolTip("Specify Order");
        itabTimeToNextAction->setToolTip("Specify Time to wait in ms before next action");
        this->m_tblAllocation->setItem (i, 5,itabTimeToNextAction );
        QTableWidgetItem *itabReatNoofTimes;
        itabReatNoofTimes= new QTableWidgetItem();
        itabReatNoofTimes->setToolTip("Specify No of Times the action is to be performed");
        itabReatNoofTimes->setText("3");
        this->m_tblAllocation->setItem (i, 4,itabReatNoofTimes );


	}	
	
}
void AutomationElementsWidget::openScenarioFromFile()
{
	/*QString selfilter = tr("XML (*.xml)");
	QString fileName = QFileDialog::getOpenFileName(this,"Open Scene File","C:",  tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" ), &selfilter );
	ReadScenario(fileName);*/

		//from instances 

	
	
}


/*void AutomationElementsWidget::doDetection()
{
	
	
}*/

/*void AutomationElementsWidget::performDetectionStage()
{
	
}*/
void AutomationElementsWidget::contextMenuEvent(QContextMenuEvent *event)
 {
     //QMenu menu(this);
	 QMenu menu(this->m_currentView);
     menu.addAction(m_actrefreshActionList);
	 menu.addAction(m_actsetActionList);
	 /* not used
     menu.addAction(m_actDrillDown);
	 menu.addAction(m_actCompare);
	 menu.addAction(m_actsymbolDetectStageA);
	 menu.addAction(m_actsymbolDetectStageB);
	 //m_actsymbolDetectStage2.Enabled(false);
	 //menu.addAction(m_actCompare);
	 //menu.addAction(m_actgetProperties);
	 //removed now -menu.addAction(m_actAllocation); */

     menu.exec(event->globalPos());
 }


/*void AutomationElementsWidget::doDetectionOld()
{
	
}*/
/*void AutomationElementsWidget::openScannedDiagram()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
	 QStringList fileNames;
	 
	if (dialog.exec())
		fileNames = dialog.selectedFiles();
	QString firstFileName= fileNames.at(0);
	this->m_ScanFileName=firstFileName;
	QGraphicsScene* scene= new QGraphicsScene(this);
	QPixmap pix( firstFileName );
	scene->addPixmap( pix );
	this->m_currentView->setScene(scene);

}*/

	
	void AutomationElementsWidget::createMessageTableView()
{
	this->m_tblMessages= new QTableWidget;
	this->m_tblMessages->setColumnCount(4);
	this->m_tblMessages->setRowCount(5);
	QStringList msgHeaders;
	msgHeaders.append("Category");
	msgHeaders.append("Title");
	msgHeaders.append("Description");
	msgHeaders.append("Recommendation");
	this->m_tblMessages->setHorizontalHeaderLabels(msgHeaders);
	/* comment the button display
	QPushButton* button= new QPushButton();
	QPalette p= button->palette();
	p.setColor(QPalette::Button, QColor(250,13,13 )); //QColor("#ffffff"));
	button->setPalette(p);
	button->setText("Testme");
	button->setFlat(true);
	button->setAutoFillBackground(true);
	this->m_tblMessages->setCellWidget(1,1,button); */

}

void AutomationElementsWidget::createAllocationTableView()
{
	//Alloaction table here
	this->m_tblAllocation= new QTableWidget;
	this->m_tblAllocation->setColumnCount(6);
	this->m_tblAllocation->setRowCount(2);
	QStringList msgHeaders;
	msgHeaders.append("Order");
	msgHeaders.append("Type");
	msgHeaders.append("Source");
	msgHeaders.append("Destination");
	msgHeaders.append("NoofTimesToRepeat");
	msgHeaders.append("TimeToWaitTillNextStep");
	this->m_tblAllocation->setHorizontalHeaderLabels(msgHeaders);
	
		//from scl

	
}

void AutomationElementsWidget::createPropertyTableView()
{

	this->m_objectProperties= new QTableWidget;
	//this->m_objectProperties->insertColumn(1);
	this->m_objectProperties->setColumnCount(1);
	this->m_objectProperties->setRowCount(5);
	QStringList properties;
	properties.append("Selected BOM");
	properties.append("Properties");
	this->m_objectProperties->setHorizontalHeaderLabels(properties);
	QStringList propertiesList;
	propertiesList.append("Type");
	propertiesList.append("Name");
	propertiesList.append("Instance Number");
	propertiesList.append("Description");
	propertiesList.append("Purpose");
	this->m_objectProperties->setVerticalHeaderLabels(propertiesList);
	//default values
	QTableWidgetItem* item= new QTableWidgetItem("Type");
	this->m_objectProperties->setItem(0,0,item);
	QTableWidgetItem* itemName= new QTableWidgetItem("Name");
	this->m_objectProperties->setItem(1,0,itemName);

	QTableWidgetItem* itemInstNo= new QTableWidgetItem("Instance Number");
	this->m_objectProperties->setItem(2,0,itemInstNo);
	
	
}




