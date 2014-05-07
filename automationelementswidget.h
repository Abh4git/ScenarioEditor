#ifndef AUTOMATIONELEMENTSWIDGET_H
#define AUTOMATIONELEMENTSWIDGET_H

#include <QWidget>
#include "ui_automationelementswidget.h"
#include <qpluginloader.h>
#include <qplugin.h>
#include <qframe.h>
#include <QHBoxLayout>
#include <qgraphicsview.h>
#include <qtablewidget.h>
#include "ObjectsList.h"
#include "../BOMLibrary/IBOMTypeLoadInterface.h"
#include "../BOMGraphicalLibrary/IBOMInstanceCreation.h"
#include "../BOMGraphicalLibrary/connectorgraphicitem.h"
#include "../BOMGraphicalLibrary/MsgGraphicsItem.h"
#include "../BOMGraphicalLibrary/ActionGraphicsItem.h"
#include "AutomGraphicsView.h"
#include <qmenu.h>
#include <qaction.h>
#include <QContextMenuEvent>
#include <qsplitter.h>
#include "../BOMGraphicalLibrary/msgGraphicsItemWithText.h"
 #include <QFileDialog>
#include <qcombobox.h>
using namespace BOMLIB;
#include <ScenarioReader.h>
//! AutomationElementsWidget Class
/*!
	Responsibility: Container for AutomGraphicsView and AutomGraphicsScene
	with context menu to perform Save and Open for Scenarios. Has the objectsList
	appearing in left from where we can drag and drop BOMObjects to the AutomGraphView/Scene.
*/
class AutomationElementsWidget : public QWidget
{
	Q_OBJECT

public:
	//! Constructor
	AutomationElementsWidget(QWidget *parent = 0);
	//! Destructor
	~AutomationElementsWidget();
protected:
	//! contextMenuEvent override for ContextMenu to appear
     void contextMenuEvent(QContextMenuEvent *event);

public slots:
	
	//void performDetectionStage(void);
	//void doDetectionOld();
private slots:
	//void openScannedDiagram();
	//void doDetection();
	//! openScenarioFromFile
	/*!
		Open Scenario From File and load the SceneItems, Actions in memory
	*/
	void openScenarioFromFile();
	//! refreshActionList
	/*!
		Refresh Actions based on SceneItems added
	*/
	void refreshActionList();
	//! setActionList
	/*!
		Scene Actions based on SceneItems added
	*/
	void setActionList();

private:
	Ui::AutomationElementsWidget ui;

	void setupWidgets();
	void LoadPlugins();
	void loadTypeDefinitions();
	QString getInstanceIdentifier(int index);
	//void ReadScenario(QString fileName);
	//void CreateBOMGraphics();
	BOMInstance* findInstance(QString name,int instNo);
	IBOMTypeLoadInterface* m_BOMTypeLoader;
	IBOMInstanceCreation* m_BOMInstanceCreator;
	QGraphicsScene* m_graphicsScene;
	QGraphicsView* m_graphicsView;
	//AutomGraphicsScene m_graphicsScene;
	void createMessageTableView(); //gui related management
	void createAllocationTableView();
	void createPropertyTableView();
	bool eventFilter(QObject* target,QEvent* event);
	BOMObject* FindBOMType(QString BOMTypeName);
	
	//widget
	ObjectsList *objectsList;
	//QGraphicsView* m_currentView;
	//add ur GView
	
	AutomGraphicsView* m_currentView;


	//newly added for ieds controllers
	ObjectsList* m_SecondaryObjectsList;
	QTableWidget* m_objectProperties;
	QTableWidget* m_tblAllocation;
	QTableWidget* m_tblMessages;
	//models
	QList<BOMObject*> m_BOMTypesList;
	QList<BOMObject*> m_BOMSecondaryTypesList;
	
	//forms
	
	//actions
	QAction* m_actrefreshActionList;
	QAction* m_actsetActionList;
	QAction* m_actOpenScenarioFromFile;
	QAction* m_actDrillDown;
	QAction* m_actCompare;
	QAction* m_actsymbolDetectStageA;
	QAction* m_actsymbolDetectStageB;
	//current selection
	BOMInstance* m_currentSelectedBOMInstance;
	//QMap<QString key, QString value > m_mapFunctionAllocation;

	bool m_IRunningMode;
	QString m_ScanFileName;

	//List of Connections
    QList<ConnectorGraphicitem*> m_Connections;
	QList<BOMInstance*> m_BOMInstancesList;
	ConnectorGraphicitem* findConnection(QString connectIdentifer);

	//current Actions and Topology
	QList<SceneAction*> m_currentSceneActions;
	QList<SceneItem*> m_currentSceneItems;

	QString m_applicationPath;
    int m_Order;
};

#endif // AUTOMATIONELEMENTSWIDGET_H
