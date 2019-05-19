#ifndef DISPLAY_H
#define DISPLAY_H

#include <QComboBox>
#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QTableView>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "dataclass.h"

class Display : public QMainWindow
{
    Q_OBJECT

    public:
        Display(QWidget *parent = 0);
        ~Display();
    private:
        QWidget *m_centralWidget;
        QLabel *m_home;
        QPushButton *m_newExam, *m_continueExam;
        QPushButton *m_addQuestions, *m_editQuestions, *m_editInfosExam;
        QGroupBox *m_infoExamGroupBox;
        QLabel *m_errorsInfoExam;
        QLabel *m_codeLabel, *m_nameLabel, *m_classLabel, *m_lecturesLabel;
        QLineEdit *m_codeEdit, *m_nameEdit;
        QLineEdit *m_lecturerEditA, *m_lecturerEditB, *m_lecturerEditC, *m_lecturerEditD;
        QComboBox *m_yearEdit, *m_departementEdit;
        QPushButton *m_saveInfoExam;
        QGroupBox *m_questionGroupBox;
        QLabel *m_questionLabel, *m_answerLabel, *m_choicesLabel, *m_timeLabel;
        QTextEdit *m_questionEdit, *m_answerEdit, *m_choice1,*m_choice2,*m_choice3, *m_choice4;
        QComboBox *m_timeEdit;
        QPushButton *m_saveQuestion;
        QPushButton *m_editQuestion, *m_deleteQuestion;
        QMap<QString,QString> m_infoExamTab;
        QMap<QString,QString> m_questionTab;
        bool m_new;
        bool m_questionEdition;
        QString m_idQuestion;
        DataClass m_dataClass;
        QTableView *m_questionsList;

    public slots:
        void addQuestions();
        void deleteQuestion();
        void questionClicked(QModelIndex);
        void editQuestion();
        void editQuestions();
        void editInfosExam();
        void editNewExam();
        void checkAndSaveInfosExam();
        void continueToEditExam();
        void saveQuestion();

};

#endif // DISPLAY_H
