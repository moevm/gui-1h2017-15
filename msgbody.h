#ifndef MSGBODY_H
#define MSGBODY_H

#include <QString>

class msgBody
{
public:
    msgBody();
    QString getContentType() const;
    QString getCharset() const;
    QString getBase() const;
    QString getMessage() const;


    void setContentType(QString contenttype);
    void setCharset(QString charset);
    void setBase(QString base);
    void setMessage(QString message);


private:
    QString contenttype;
    QString charset;
    QString base;
    QString message;
};

#endif // MSGBODY_H
