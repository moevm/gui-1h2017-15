#include "myparser.h"

MyParser::MyParser()
{

}

Message MyParser::parseMail(QString input)
{
    Message msg;
    QString ib = input;
    //    QRegExp big = QRegExp("[^\[\]\r\\]");
    //    int aa = big.indexIn(input);
    //    QStringList a = big.capturedTexts();
    //    qDebug() << QString::number(aa);

    QStringList allFields = input.split("\r\n");
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
    QRegExp rTheme = QRegExp("Subject:\\s([A-z0-9=?-]*)");
    int nrTheme = rTheme.indexIn(input);
    QStringList stlTheme = rTheme.capturedTexts();
    QString theme = stlTheme.at(0);
    theme.remove(0,9);
    if (theme.contains("=?UTF-8"))
    {
        theme.remove(theme.size()-2,2);
        theme.remove(0,10);
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
    QRegExp rDate = QRegExp("Date:\\s([A-z0-9,\\s:+]*)");
    int nrDate = rDate.indexIn(input);
    //qDebug()<<"num Date - "<<QString::number(nrDate);
    QStringList stlDate = rDate.capturedTexts();
    QString test = stlDate.at(1);
    test.remove(test.length()-7,7); // last 2 = 1
    //    qDebug()<<"Date - "<<test;
    QDateTime dt = QDateTime::fromString(stlDate.at(1), Qt::RFC2822Date);
    msg.setDateTime(dt);
    //    qDebug() << dt.toString();


    // BODY
    QRegExp rBody = QRegExp("Body msg(.*)");

    int nrBody = rBody.indexIn(input);
//    qDebug()<<"num Body - "<<QString::number(nrBody);

    if (nrBody > -1)
    {
        QStringList stlBody = rBody.capturedTexts();
        QString test1 = stlBody.at(1);
        QStringList bres = test1.split("\r\n");

        int titleCntr = 0;
        for (int i = 0; i < bres.size(); i++) // фильтр
        {
            if (bres.at(i) == "")
            {
                bres.replace(i, "\n");
            }

            body.append(bres.at(i));
            body.append(" ");

            if (bres.at(i) != "\n" && titleCntr < 5)
            {

                title.append(bres.at(i));
                title.append(" ");
                titleCntr++;
            }

        }

        msg.setTitle(title);

        msgBody tmp;
        tmp.setMessage(body);
        msg.setBodyHTML(tmp);
        msg.setBodyText(tmp);

    } else {
        QList <msgBody> la;
        la = parseBody(ib);
        if (la.size() < 2)
        {
            qDebug() << "Error, last stage ";
        } else {
            msg.setBodyText(la.at(0));
            msg.setBodyHTML(la.at(1));
            msg.setTitle(la.at(0).getMessage());
        }

    }

    return msg;
}

QList<msgBody> MyParser::parseBody(QString input)
{
//    qDebug()<<"parsBody() input : \n" << input;
    QList<msgBody> a;
    QStringList input1 = input.split("\r\n\t");

    for(int i = 0; i < input1.size(); i++)
    {
        //        qDebug()<<"Field " << i << " = " << input1.at(i);
    }

    if(input1.size() < 4)
    {
        qDebug() << "Error, stage 1";
        msgBody f;
        return a;

    } else {
        QString needed = input1.at(4); // here

        QStringList input2 = needed.split("\r\n");

        for(int i = 0; i < input2.size(); i++)
        {
            //        qDebug()<<"Field " << i << " = " << input2.at(i);
        }

        //    QRegExp big = QRegExp("[^\[\]\r\\]");
        //    int aa = big.indexIn(input);
        //    QStringList a = big.capturedTexts();
        //    qDebug() << QString::number(aa);

        for(int i = 0; i < input2.size(); i++)
        {
            int j = i;
            if (input2.at(j).startsWith("----ALT"))
            {
                if (input2.at(j+1).startsWith("Content"))
                {
                    QRegExp rContent = QRegExp("Content-Type:\\s([A-z]*.[A-z]*)");
                    int aa = rContent.indexIn(input2.at(j+1));
                    QStringList rContentL = rContent.capturedTexts();

                    //                qDebug() << "CONTENT" << QString::number(aa);
                    //                qDebug() << ;

                    QRegExp rCharset = QRegExp("charset=([A-z]*-[0-9]*)");
                    int a1 = rCharset.indexIn(input2.at(j+1));
                    QStringList rCharsetL = rCharset.capturedTexts();




                    QRegExp rTransfer = QRegExp("Content-Transfer-Encoding:\\s([A-z0-9]*)");
                    int a2 = rTransfer.indexIn(input2.at(j+2));
                    QStringList rTransferL = rTransfer.capturedTexts();

                    QStringList mss;
                    if (input2.at(j+3) == "")
                    {
                        int y = j+4;

                        while (!input2.at(y).endsWith("=="))
                        {
                            if(input2.at(y).startsWith("----ALT"))
                                break;
                            mss.append(input2.at(y));
                            y++;
                        }
                        if(!input2.at(y).startsWith("----ALT"))
                            mss.append(input2.at(y));

                        QString resM;


                        for(int i = 0; i < mss.size(); i++)
                        {

                            resM.append(mss.at(i));


                        }

                        if (resM.endsWith("=="))
                            resM.remove(resM.length()-2,2);

                        QByteArray ba;
                        ba.append(resM);
                        resM = QByteArray::fromBase64(ba);

                        msgBody m;

                        m.setContentType(rContentL.at(1));
                        m.setCharset(rCharsetL.at(1));
                        m.setBase(rTransferL.at(1));
                        m.setMessage(resM);

                        a.append(m);
                    }

                }

                j++;
            }

        }
        return a;
    }




}
