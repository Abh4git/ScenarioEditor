#include "automationwizard.h"
#include <qmessagebox.h>
AutomationWizard::AutomationWizard(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QAction* actnewScene= new QAction(QIcon( ":/icons/newscene.ico"),"New Scenario",this);
	actnewScene->setEnabled(false);
	ui.mainToolBar->addAction(actnewScene);
    QAction* actopenScene= new QAction(QIcon( ":/icons/openscene.ico"),"Open Scenario",this);
    connect(actopenScene,SIGNAL(triggered()),this,SLOT(loadScenario()));
	//connect(actopenScene, SIGNAL(triggered()), this->m_currentSubWindow, SLOT(this->m_currentSubWindow->loadScenario()));
	

	m_openAction=actopenScene;
	ui.mainToolBar->addAction(actopenScene);
	QAction* actplay=new QAction(QIcon( ":/icons/playscene.ico"),"Play Scenario",this);
	actplay->setEnabled(true);
	m_playScenario=actplay;
	ui.mainToolBar->addAction(actplay);
	//connect(m_playScenario,SIGNAL(triggered()),this,SLOT(openScenarioPlayer()));
	connect(actplay,SIGNAL(triggered()), this,SLOT(openScenarioPlayer()));
	
}

void AutomationWizard::loadScenario()
{
}

void AutomationWizard::openScenarioPlayer()
{
	QMessageBox box;
    //box.setText("starting player");

    QString path = QDir::currentPath();
    QString workingDir= QDir::currentPath();;
	//QCoreApplication::applicationDirPath ();
    //path.append("/ScenarioViewer.exe");
    //box.setText(path);
    ///box.exec();
    QProcess *engine = new QProcess(this);
    engine->setWorkingDirectory(workingDir);
    engine->start("ScenarioViewer.exe");
    if (engine->waitForStarted(1000))
    {
        if (engine->error())
        {
            box.setText(engine->errorString());
            box.exec();
        }
    }

}
AutomationWizard::~AutomationWizard()
{

}
