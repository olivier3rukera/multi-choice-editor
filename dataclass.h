#ifndef DATACLASS_H
#define DATACLASS_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMap>
#include <QSqlQueryModel>
#include <QString>
#include <QVariant>
#include <QDebug>

class DataClass:public QObject
{
    public:
        DataClass();
        bool deleteQuestion(QString id);
        bool openDataBase(QString path);
        bool refreshQuestionsTabModel();
        bool saveInfoExam(QMap<QString,QString>);
        bool saveQuestion(QMap<QString,QString>);
        QMap<QString,QString> getInfosExam();
        QMap<QString,QString> getQuestion(QString id);

        QSqlQueryModel m_questionsTabModel;

    private:
        QSqlDatabase m_examDb;
        QSqlQuery m_examQuery;
};

#endif // DATACLASS_H
