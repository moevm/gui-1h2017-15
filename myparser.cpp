#include "myparser.h"

MyParser::MyParser()
{

}

Message MyParser::parseMail(QString input)
{
    Message msg;
    //    QRegExp big = QRegExp("[^\[\]\r\\]");
    //    int aa = big.indexIn(input);
    //    QStringList a = big.capturedTexts();
    //    qDebug() << QString::number(aa);

    QStringList allFields = input.split("\\r\\n");
    //    for(int i=0; i<allFields.count(); i++)
    //    {
    //        qDebug()<<""<< i << " Da Value Thing: " << allFields.at(i);
    //    }


    // Receiver WORKS
    QRegExp rReceiver = QRegExp("Delivered-To:\\s*([A-z0-9_\.-]+@[A-z0-9\.]+)");

    rReceiver.indexIn(allFields.at(0));
    QStringList qsl = rReceiver.capturedTexts();
    receiver = qsl.at(1);
    //    qDebug()<<"Receiver - " << receiver;
    msg.setReceiver(receiver);

    // THEME WORKS
    QRegExp rTheme = QRegExp("Subject:\\s([A-z0-9=?-]*\\br\\b)");
    int nrTheme = rTheme.indexIn(input);
    QStringList stlTheme = rTheme.capturedTexts();
    QString theme = stlTheme.at(0);
    theme.remove(theme.size()-2,2);
    theme.remove(0,9);
    if (theme.contains("=?UTF-8"))
    {
        theme.remove(0,9);
        QByteArray ba;
        ba.append(theme);
        theme = QByteArray::fromBase64(ba);
    }
    //    qDebug() << "Theme - " << theme;
    msg.setTheme(theme);


    // SENDER WORKS
    QRegExp rSender = QRegExp("Return-path:\\s*<([A-z0-9_\.-]+@[A-z0-9\.]+)");
    int nrSender = rSender.indexIn(input);
    //    qDebug()<<QString::number(nrSender);
    QStringList stlSender = rSender.capturedTexts();
    QString sender = stlSender.at(0);
    sender.remove(0, 14);
    //    qDebug()<<"Sender - "<< sender;
    msg.setSender(sender);

    // DATE WORKS
    QRegExp rDate = QRegExp("Date:\\s([A-z0-9,\\s:+]*\\br\\b)");
    int nrDate = rDate.indexIn(input);
    //qDebug()<<"num Date - "<<QString::number(nrDate);
    QStringList stlDate = rDate.capturedTexts();
    QString test = stlDate.at(1);
    test.remove(test.length()-2,2);
    //    qDebug()<<"Date - "<<test;
    QDateTime dt = QDateTime::fromString(stlDate.at(1), Qt::RFC2822Date);
    msg.setDateTime(dt);
    //    qDebug() << dt.toString();


    // BODY
    QRegExp rBody = QRegExp("Body msg(.*\\br\\b)");
    int nrBody = rBody.indexIn(input);
//    qDebug()<<"num Body - "<<QString::number(nrBody);
    QStringList stlBody = rBody.capturedTexts();
    QString test1 = stlBody.at(1);
    QStringList bres = test1.split("\\r\\n");

    for (int i = 0; i < bres.size(); i++) // фильтр
    {
        if (bres.at(i) == "")
        {
            bres.replace(i, "\\n");
        }

        body.append(bres.at(i));
        body.append(" ");

        if (i < 4)
        {
            title.append(bres.at(i));
            title.append(" ");
        }

    }
    msg.setBody(body);
    msg.setTitle(title);
    return msg;
}
