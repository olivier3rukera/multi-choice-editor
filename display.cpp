#include "display.h"

Display::Display(QWidget *parent)
    : QMainWindow(parent)
{
    //QFile fichier("/../../style.css");
    QFile fichier("D:/Projets/MultiChoice/MultiChoiceEditor/MultiChoiceEditor/style.css");
    fichier.open(QIODevice::ReadOnly);
    QString style(fichier.readAll());
    this->setStyleSheet(style);
    m_new=false;
    m_questionEdition=false;
    m_centralWidget=new QWidget();
    m_centralWidget->setObjectName("centralWidget");
    this->setCentralWidget(m_centralWidget);

    QVBoxLayout *centralLayout=new QVBoxLayout();
    m_centralWidget->setLayout(centralLayout);

    m_home=new QLabel("MultiChoice Editor");
    m_home->setAlignment(Qt::AlignHCenter);
    m_home->setObjectName("home");
    centralLayout->addWidget(m_home);

    //QIcon icon("D:/Projets/MultiChoice/MultiChoiceEditor/MultiChoiceEditor/icon.ico");
    m_newExam=new QPushButton("Create New Exam");
    m_newExam->setObjectName("newExam");
    connect(m_newExam,SIGNAL(clicked(bool)),this,SLOT(editNewExam()));

    m_continueExam=new QPushButton("Continue To Edit An Exam");
    m_continueExam->setObjectName("continueExam");
    connect(m_continueExam,SIGNAL(clicked(bool)),this,SLOT(continueToEditExam()));

    QHBoxLayout *firstChoiceLayout=new QHBoxLayout();
    firstChoiceLayout->addWidget(m_newExam);
    firstChoiceLayout->addWidget(m_continueExam);

    m_questionsList= new QTableView();
    m_questionsList->setModel(&(m_dataClass.m_questionsTabModel));
    m_questionsList->setVisible(false);
    m_questionsList->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_questionsList->setSelectionMode(QAbstractItemView::SingleSelection);
    m_questionsList->setColumnHidden(0,true);
    connect(m_questionsList,SIGNAL(clicked(QModelIndex)),this,SLOT(questionClicked(QModelIndex)));

    centralLayout->addWidget(m_questionsList);

    m_addQuestions=new QPushButton("Add Questions");
    m_addQuestions->setVisible(false);
    connect(m_addQuestions,SIGNAL(clicked()),this,SLOT(addQuestions()));

    m_editQuestions=new QPushButton("Edit Former Questions");
    m_editQuestions->setVisible(false);
    connect(m_editQuestions,SIGNAL(clicked()),this,SLOT(editQuestions()));

    m_editQuestion=new QPushButton("Edit Question");
    m_editQuestion->setVisible(false);
    m_editQuestion->setEnabled(false);
    connect(m_editQuestion,SIGNAL(clicked(bool)),this,SLOT(editQuestion()));

    m_deleteQuestion=new QPushButton("Delete Question");
    m_deleteQuestion->setVisible(false);
    m_deleteQuestion->setEnabled(false);
    connect(m_deleteQuestion,SIGNAL(clicked()),this,SLOT(deleteQuestion()));

    m_editInfosExam=new QPushButton("Edit Info About Exam");
    m_editInfosExam->setVisible(false);
    m_editInfosExam->setEnabled(false);
    connect(m_editInfosExam,SIGNAL(clicked()),this,SLOT(editInfosExam()));

    firstChoiceLayout->addWidget(m_addQuestions);
    firstChoiceLayout->addWidget(m_editQuestions);
    firstChoiceLayout->addWidget(m_editInfosExam);


    firstChoiceLayout->addWidget(m_editQuestion);
    firstChoiceLayout->addWidget(m_deleteQuestion);


    centralLayout->addLayout(firstChoiceLayout);

    m_infoExamGroupBox=new QGroupBox();
    m_infoExamGroupBox->setObjectName("infoExamGroupBox");
    m_infoExamGroupBox->setVisible(false);
    centralLayout->addWidget(m_infoExamGroupBox);

    QGridLayout *infoExamLayout=new QGridLayout();
    m_infoExamGroupBox->setLayout(infoExamLayout);

    m_errorsInfoExam=new QLabel();
    m_errorsInfoExam->setObjectName("errorInfoExam");

    //infoExamLayout->addWidget(m_errorsInfoExam,0,0,1,3);

    m_codeLabel=new QLabel("Code Of Exam");
    m_codeLabel->setObjectName("codeEdit");
    m_codeEdit=new QLineEdit();
    m_codeEdit->setObjectName("codeEdit");

    infoExamLayout->addWidget(m_codeLabel,1,0);
    infoExamLayout->addWidget(m_codeEdit,1,1,1,2);

    m_nameLabel=new QLabel("Name Of The Course");
    m_nameLabel->setObjectName("nameLabel");
    m_nameEdit=new QLineEdit();
    m_nameEdit->setObjectName("nameEdit");

    infoExamLayout->addWidget(m_nameLabel,2,0);
    infoExamLayout->addWidget(m_nameEdit,2,1,1,2);

    m_classLabel=new QLabel("Class");
    m_classLabel->setObjectName("classLabel");
    m_yearEdit= new QComboBox();
    QStringList yearList;
    yearList<<"Year 1"<<"Year 2"<<"Year 3";
    m_yearEdit->addItems(yearList);

    m_departementEdit=new QComboBox();
    QStringList departementList;
    departementList<<"Computer Science"<<"Construction"<<"ELT"<<"ETT";
    m_departementEdit->addItems(departementList);

    infoExamLayout->addWidget(m_classLabel,3,0);
    infoExamLayout->addWidget(m_yearEdit,3,1);
    infoExamLayout->addWidget(m_departementEdit,3,2);

    m_lecturesLabel=new QLabel("Names Of Lecturers");
    m_lecturesLabel->setObjectName("lecturersLabel");
    m_lecturerEditA=new QLineEdit();
    m_lecturerEditB=new QLineEdit();
    m_lecturerEditC=new QLineEdit();
    m_lecturerEditD=new QLineEdit();

    infoExamLayout->addWidget(m_lecturesLabel,4,0);
    infoExamLayout->addWidget(m_lecturerEditA,4,1,1,2);
    infoExamLayout->addWidget(m_lecturerEditB,5,1,1,2);
    infoExamLayout->addWidget(m_lecturerEditC,6,1,1,2);
    infoExamLayout->addWidget(m_lecturerEditD,7,1,1,2);

    m_saveInfoExam=new QPushButton("Save Infos");
    m_saveInfoExam->setObjectName("saveInfoExam");
    connect(m_saveInfoExam,SIGNAL(clicked()),this,SLOT(checkAndSaveInfosExam()));

    infoExamLayout->addWidget(m_saveInfoExam,8,1,1,1);

    m_questionGroupBox=new QGroupBox();
    m_questionGroupBox->setObjectName("questionGroupBox");
    m_questionGroupBox->setVisible(false);
    centralLayout->addWidget(m_questionGroupBox);

    QGridLayout *questionLayout=new QGridLayout();
    m_questionGroupBox->setLayout(questionLayout);

    m_questionLabel=new QLabel("Write The Question");
    m_questionLabel->setObjectName("questionLabel");
    m_questionEdit=new QTextEdit();
    m_questionEdit->setObjectName("questionEdit");

    questionLayout->addWidget(m_questionLabel,0,0,1,1);
    questionLayout->addWidget(m_questionEdit,0,1,1,3);

    m_answerLabel=new QLabel("Enter The True Answer");
    m_answerLabel->setObjectName("answerLabel");
    m_answerEdit=new QTextEdit();
    m_answerEdit->setObjectName("answerEdit");

    m_timeLabel=new QLabel("Time For The Question In Seconds");
    m_timeLabel->setObjectName("timeLabel");

    m_timeEdit=new QComboBox();
    QStringList timeList;
    timeList<<"090 sec( 1.5 min)"<<"120 sec(2 min)"<<"180 sec (3 min)"<<"240 sec(4 min)";
    timeList<<"300 sec(5 min)";
    m_timeEdit->addItems(timeList);
    m_timeEdit->setObjectName("timeEdit");

    questionLayout->addWidget(m_answerLabel,2,0);
    questionLayout->addWidget(m_answerEdit,2,1);
    questionLayout->addWidget(m_timeLabel,2,2);
    questionLayout->addWidget(m_timeEdit,2,3);

    QLabel *strech=new QLabel();
    questionLayout->addWidget(strech,3,1,2,4);

    m_choicesLabel=new QLabel("Other Answers");
    m_choicesLabel->setObjectName("choicesLabel");

    m_choice1=new QTextEdit();
    m_choice1->setObjectName("choice1");
    m_choice2=new QTextEdit();
    m_choice2->setObjectName("m_choice2");
    m_choice3=new QTextEdit();
    m_choice3->setObjectName("choice3");
    m_choice4=new QTextEdit();
    m_choice4->setObjectName("choice4");

    questionLayout->addWidget(m_choicesLabel,5,0,5,1);
    questionLayout->addWidget(m_choice1,6,1,1,3);
    questionLayout->addWidget(m_choice2,7,1,1,3);
    questionLayout->addWidget(m_choice3,8,1,1,3);
    questionLayout->addWidget(m_choice4,9,1,1,3);

    m_saveQuestion=new QPushButton("Save question and continue");
    m_saveQuestion->setObjectName("saveQuestion");
    connect(m_saveQuestion,SIGNAL(clicked(bool)),this,SLOT(saveQuestion()));

    questionLayout->addWidget(m_saveQuestion,10,1,1,2);





}

Display::~Display()
{

}


void Display::addQuestions()
{
    m_questionsList->setVisible(false);

    m_addQuestions->setVisible(false);
    m_editInfosExam->setVisible(false);
    m_editQuestions->setVisible(false);
    m_editQuestion->setVisible(false);
    m_deleteQuestion->setVisible(false);
    m_questionGroupBox->setVisible(true);
}


void Display::checkAndSaveInfosExam()
{
    QString errors;
    m_errorsInfoExam->setText("");
    if(m_nameEdit->text().isEmpty())
    {
        errors+="<H1>You Must enter a name for the course</H1>";
        m_errorsInfoExam->setText(errors);
    }
    else{m_infoExamTab["Name Of Course"]=m_nameEdit->text();}
    m_infoExamTab["Code Of Course"]=m_codeEdit->text();
    m_infoExamTab["Names Of Lectures"]=m_lecturerEditA->text()+", "+m_lecturerEditB->text()+", "
            +m_lecturerEditC->text()+", "+m_lecturerEditD->text();
    m_infoExamTab["Class"]=m_yearEdit->currentText()+" "+m_departementEdit->currentText();
    if(m_dataClass.saveInfoExam(m_infoExamTab))
    {
        m_saveInfoExam->setEnabled(false);
        m_infoExamGroupBox->setVisible(false);
        m_questionGroupBox->setVisible(true);
    }
    else
    {
        QMessageBox::warning(this,"DataBase Error","Information  Not Saved "
                           "Try Again");
    }

}


void Display::continueToEditExam()
{
    QString path=QFileDialog::getOpenFileName(this,"Choose The DataBase Wich Contains The Exam"
                 ,"","Sqlite file(*.db *.db3 *.sqlite *sqlite3)");
    if(path!="")
    {
        m_newExam->setVisible(false);
        m_continueExam->setVisible(false);
        m_addQuestions->setVisible(true);
        m_editInfosExam->setVisible(true);
        m_editQuestions->setVisible(true);
        m_dataClass.openDataBase(path);

    }
    else return;
}


void Display::deleteQuestion()
{
    m_idQuestion=m_questionsList->selectionModel()->selectedRows(0).value(0).data().toString();
    m_dataClass.deleteQuestion(m_idQuestion);

}


void Display::editNewExam()
{
    m_newExam->setVisible(false);
    m_continueExam->setVisible(false);
    m_infoExamGroupBox->setVisible(true);
}


void Display::editInfosExam()
{
    m_infoExamGroupBox->setVisible(true);
    m_addQuestions->setVisible(false);
    m_editQuestions->setVisible(false);
    m_editInfosExam->setVisible(false);
}


void Display::editQuestion()
{
    m_idQuestion=m_questionsList->selectionModel()->selectedRows(0).value(0).data().toString();
    m_questionEdition=true;
    qDebug()<<" Display  "<<m_idQuestion;
    QMap<QString,QString> question=m_dataClass.getQuestion(m_idQuestion);
    if(!(question.isEmpty()))
    {
        m_questionEdit->setText(question["question"]);
        m_answerEdit->setText(question["answer"]);
        m_choice1->setText(question["choiceA"]);
        m_choice2->setText(question["choiceB"]);
        m_choice3->setText(question["choiceC"]);
        m_choice4->setText(question["choiceD"]);

        m_saveQuestion->setText("Save Changes");

        m_questionsList->setVisible(false);
        m_editQuestion->setVisible(false);
        m_deleteQuestion->setVisible(false);
        m_addQuestions->setVisible(false);

        m_questionGroupBox->setVisible(true);
    }

}


void Display::editQuestions()
{
    m_dataClass.refreshQuestionsTabModel();
    m_questionsList->setVisible(true);

    m_editInfosExam->setVisible(false);
    m_editQuestions->setVisible(false);

    m_editQuestion->setVisible(true);
    m_deleteQuestion->setVisible(true);
}


void Display::questionClicked(QModelIndex index)
{
    m_editQuestion->setEnabled(true);
    m_deleteQuestion->setEnabled(true);
}


void Display::saveQuestion()
{
    if(!(m_questionEdit->toPlainText().isEmpty()||m_answerEdit->toPlainText().isEmpty()
        ||m_choice1->toPlainText().isEmpty()||m_choice2->toPlainText().isEmpty()
        ||m_choice3->toPlainText().isEmpty()||m_choice4->toPlainText().isEmpty()))
    {
        m_questionTab["question"]=m_questionEdit->toPlainText();
        m_questionTab["answer"]=m_answerEdit->toPlainText();
        m_questionTab["choiceA"]=m_choice1->toPlainText();
        m_questionTab["choiceB"]=m_choice2->toPlainText();
        m_questionTab["choiceC"]=m_choice3->toPlainText();
        m_questionTab["choiceD"]=m_choice4->toPlainText();

        QString temps=m_timeEdit->currentText();
        temps.truncate(3);

        m_questionTab["temps"]=temps;
        if(m_dataClass.saveQuestion(m_questionTab))
        {
            m_questionEdit->clear();
            m_answerEdit->clear();
            m_choice1->clear();
            m_choice2->clear();
            m_choice3->clear();
            m_choice4->clear();
            m_questionTab.clear();
            if(m_questionEdition)
            {
                m_dataClass.deleteQuestion(m_idQuestion);
                m_saveQuestion->setText("Save And Continue");
                m_questionEdition=false;

                m_questionGroupBox->setVisible(false);

                m_dataClass.refreshQuestionsTabModel();
                m_questionsList->setVisible(true);
                m_editQuestion->setVisible(true);
                m_addQuestions->setVisible(true);
                m_deleteQuestion->setVisible(true);

                m_editQuestion->setEnabled(false);
                m_deleteQuestion->setEnabled(false);

            }
        }

    }
}
