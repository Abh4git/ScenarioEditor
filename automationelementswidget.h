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
/* Includes from BOMLibrary */
#include "../BOMLibrary/IBOMTypeLoadInterface.h"
/* Includes from BOMGraphicalLibrary */
#include "../BOMGraphicalLibrary/IBOMInstanceCreation.h"
#include "../BOMGraphicalLibrary/connectorgraphicitem.h"
#include "../BOMGraphicalLibrary/MsgGraphicsItem.h"
#include "../BOMGraphicalLibrary/ActionGraphicsItem.h"
#include "../BOMGraphicalLibrary/msgGraphicsItemWithText.h"
#include "AutomGraphicsView.h"
#include <qmenu.h>
#include <qaction.h>
#include <QContextMenuEvent>
#include <qsplitter.h>
 #include <QFileDialog>
#include <qcombobox.h>
#include <ScenarioReader.h>
using namespace BOMLIB;
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
private slots:
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
    //! setupWidgets
    /*!
        Creates the visual Objects and Layouts
    */
	void setupWidgets();
    //! LoadPlugins
    /*!
        Loads the QPlugins using QPluginLoader
    */
	void LoadPlugins();
    //! loadTypeDefinitions
    /*!
        loads the type defintions from metadata XML files
        present in ModelElementsFolder
    */
	void loadTypeDefinitions();
    //! getInstanceIdentifier
    /*!
        Get the Identifier for the instance
        \param index int
    */
    QString getInstanceIdentifier(int index);
    //! findInstance
    /*!
        Search and find the instance based on name and return the same
        \param name string
        \param instNo int
    */
    BOMInstance* findInstance(QString name,int instNo);

    //! createMessageTableView
    /*!
        Creates A Message Table to display some messages of the actions
    */
    void createMessageTableView(); //gui related management
    //! createSceneActionTableView
    /*!
        Creates SceneAction Table where the actions of the scene and interactions
        are described.
    */
    void createSceneActionTableView();
    //! createPropertyTableView
    /*!
        Creates PropertyTable which can present the properties of selected BOMInstance.
    */
    void createPropertyTableView();
    //! eventFilter
    /*!
        Filters events that happen on GraphicsScene and provide a handler in the Form
        even before the action is completed in GraphicsScene. In this case used for
        detecting the GraphicsScene Drop event and ContextMenu ClearAll. On detecting
        ClearAll it raises an event ChildRemoved, which in turn is captured in the
        eventFilter to remove all objects from the right pane of SceneActions.
    */
    bool eventFilter(QObject* target,QEvent* event);
    //! FindBOMType
    /*!
        From the BOMType Name, finds and returns a BOMObject.
    */
    BOMObject* FindBOMType(QString BOMTypeName);
    //! findConnection
    /*!
        From the connectIdentifier, return a ConnectGraphicItem*.
    */
    ConnectorGraphicitem* findConnection(QString connectIdentifer);

    //! private Objects
    /*!
        IBOMTypeLoadInterface* ,  IBOMInstanceCreation*
        QGraphicsScene*,QGraphicsView*
    */
    IBOMTypeLoadInterface* m_BOMTypeLoader;
	IBOMInstanceCreation* m_BOMInstanceCreator;
	QGraphicsScene* m_graphicsScene;
	QGraphicsView* m_graphicsView;
    //! ObjectsList - Shows up as Toolbox Pane in left
    ObjectsList *objectsList;
    //! GraphicsView - Customized in AutomGraphicsView for Zoom capabilities
    AutomGraphicsView* m_currentView;
   //newly added for ieds controllers
	ObjectsList* m_SecondaryObjectsList;
	QTableWidget* m_objectProperties;
	QTableWidget* m_tblAllocation;
	QTableWidget* m_tblMessages;
	//models
	QList<BOMObject*> m_BOMTypesList;
	QList<BOMObject*> m_BOMSecondaryTypesList;
    //! Actions From Menu
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
    bool m_IRunningMode;
	QString m_ScanFileName;
	//List of Connections
    QList<ConnectorGraphicitem*> m_Connections;
	QList<BOMInstance*> m_BOMInstancesList;
    //current Actions and Topology
	QList<SceneAction*> m_currentSceneActions;
	QList<SceneItem*> m_currentSceneItems;
	QString m_applicationPath;
    int m_Order;
};

#endif // AUTOMATIONELEMENTSWIDGET_H
