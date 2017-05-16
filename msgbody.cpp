#include "msgbody.h"

msgBody::msgBody()
{

}

QString msgBody::getBase() const{
    return base;
}

QString msgBody::getContentType() const{
    return contenttype;
}

QString msgBody::getMessage() const{
    return message;
}

QString msgBody::getCharset() const{
    return charset;
}

void msgBody::setBase(QString a){
    base = a;
}

void msgBody::setContentType(QString a){
    contenttype = a;
}

void msgBody::setMessage(QString a){
    message=a;
}

void msgBody::setCharset(QString a){
    charset = a;
}
