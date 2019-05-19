#include "dataclass.h"

DataClass::DataClass()
{
    m_examDb=QSqlDatabase::addDatabase("QSQLITE","mainCnx");
    m_examQuery=QSqlQuery(m_examDb);

    m_questionsTabModel.setParent(this);
}


bool DataClass::deleteQuestion(QString id)
{
    QString instructions="DELETE FROM questionsTab WHERE id=="+id;
    if(m_examQuery.exec(instructions))
    {
        return true;
    }
    else
    {
        return false;
    }
}


QMap<QString,QString> DataClass::getQuestion(QString id)
{
    QString instruction="SELECT question,answer,choiceA,choiceB,choiceC,choiceD,temps FROM "
                        " questionsTab WHERE id=="+id;
    QMap<QString,QString> question;
    if(m_examQuery.exec(instruction))
    {
        m_examQuery.next();
        question["question"]=m_examQuery.value(0).toString();
        question["answer"]=m_examQuery.value(1).toString();
        question["choiceA"]=m_examQuery.value(2).toString();
        question["choiceB"]=m_examQuery.value(3).toString();
        question["choiceC"]=m_examQuery.value(4).toString();
        question["choiceD"]=m_examQuery.value(5).toString();
        question["temps"]=m_examQuery.value(6).toString();


    }
    return question;
}


bool DataClass::openDataBase(QString path)
{
    m_examDb.setDatabaseName(path);
    m_examDb.open();
    return true;
}


bool DataClass::refreshQuestionsTabModel()
{
    m_questionsTabModel.setQuery("SELECT * FROM questionsTab",m_examDb);
    return true;
}


bool DataClass::saveInfoExam(QMap<QString, QString> infoTab)
{
    QString dbName="D:/"+infoTab["Name Of Course"]+" Exam ULk.db";
    if(dbName.size()<16)
    {
        return false;
    }
    m_examDb.setDatabaseName(dbName);
    if(!m_examDb.open())
    {
        return false;
    }
    else
    {
        if(!(m_examQuery.exec("CREATE TABLE infoAboutExam(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,dataNames TEXT,dataValues TEXT)")
            && m_examQuery.exec("CREATE TABLE questionsTab(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,question TEXT, answer TEXT,"
            "choiceA TEXT,choiceB TEXT,choiceC TEXT,choiceD TEXT, temps INTEGER)")))
        {
            return false;
        }
        else
        {
            m_examQuery.exec("DELETE * FROM infoAboutExam");
            QMap<QString,QString>::ConstIterator it=infoTab.constBegin();
            while(it!=infoTab.constEnd())
            {
                m_examQuery.prepare("INSERT INTO infoAboutExam (dataNames,dataValues) values(?,?)");
                m_examQuery.addBindValue(it.key());
                m_examQuery.addBindValue(it.value());
                m_examQuery.exec();
                ++it;
            }
            return true;
        }
    }

}


bool DataClass::saveQuestion(QMap<QString, QString> question)
{
    m_examQuery.prepare("INSERT INTO questionsTab(question,answer,choiceA,choiceB,choiceC,"
                "choiceD,temps) values(?,?,?,?,?,?,?)");
    m_examQuery.addBindValue(question["question"]);
    m_examQuery.addBindValue(question["answer"]);
    m_examQuery.addBindValue(question["choiceA"]);
    m_examQuery.addBindValue(question["choiceB"]);
    m_examQuery.addBindValue(question["choiceC"]);
    m_examQuery.addBindValue(question["choiceD"]);
    m_examQuery.addBindValue(question["temps"].toInt());
    return m_examQuery.exec();
}
