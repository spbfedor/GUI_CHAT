#include"Data.h"

#define DATABASE "QPSQL"
#define HOSTNAME "localhost"
#define DATABASENAME "chatdata"
#define USERNAME "postgres"
#define PASSWORD "789"

Data::Data() = default;
Data::~Data() = default;

void Data::openData()
{
    _db = QSqlDatabase::addDatabase ("QPSQL") ;
    _db.setHostName(HOSTNAME);
    _db.setDatabaseName(DATABASENAME);
    _db.setUserName (USERNAME);
    _db.setPassword (PASSWORD) ;

    if (!_db.open())
    {
        qDebug() << "Cannot open database:" << _db.lastError();
        exit(1);
    }
    qDebug() << "База открыта";
}

void Data::createDataTable()
{
    QSqlQuery _my_query(_db);
    _my_query.exec("create table if not exists users1 (id serial primary key not null, 	\
                  name varchar(200) not null,	login varchar(200) unique not null, user_password varchar(200))");
    _my_query.exec( "create table if not exists messages1 (id serial primary key not null,\
                  from_id integer, foreign key (from_id) references users1(id) on delete cascade on update cascade, \
                   to_id integer, foreign key (to_id) references users1(id) on delete cascade on update cascade,  text varchar(500))");
    _my_query.exec( "create table if not exists messagesAll1 (id serial primary key not null, \
                  from_id integer, foreign key (from_id) references users1(id) on delete cascade on update cascade, text varchar(500))");
}

bool Data::insirtDataUser(const QString &name, const QString &login, const QString &password)
{
    QSqlQuery _my_query(_db);
    const QString str = "insert into users1 (id, name, login, user_password) values \
     (default, '" + name + "', '" + login + "', '" + password + "')";
    //qDebug() << str;

    if(!_my_query.exec(str))
    {
        qDebug() << _db.lastError().text();
        return false;
    }
	else
    {
        return true;
    }
}

bool Data::entranceDataUser(const QString &login, const QString &password)
{
    QSqlQuery _my_query(_db);
    const QString str = "select login, user_password from users1 where login='" + login +"' and \
      user_password = '" + password +"'";

    if(_my_query.exec(str))
    {
        if (_my_query.size())
        {
            //qDebug() << _my_query.size();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        qDebug() << _db.lastError().text();
        return false;
    }
}

bool Data::insertDataMessage(const QString &from, const QString &to, const QString &text)
{
    QSqlQuery _my_query(_db);
    const QString str = "insert into messages1 (id, from_id, to_id, text) values (default, \
     (select id from users1 where login = '" + from + "'), (select id from users1 where \
     login ='" + to + "'), '" + text + "')";

    if(!_my_query.exec(str))
    {
        //qDebug() << str;
        return false;
    }
    else
    {
        return true;
    }
}

bool Data::insertDataMessageAll(const QString &from,const QString &text)
{
    QSqlQuery _my_query(_db);
    const QString str = "insert into messagesAll1 (id, from_id, text) values (default, \
     (select id from users1 where login = '" + from + "'), '" + text + "')";

    if(!_my_query.exec(str))
    {
        //qDebug() << str;
        return false;
    }
    else
    {
        return true;
    }
}

QString Data::readDataUsersLogin(const QString &login)
{
    QSqlQuery _my_query(_db);
    const QString str = "SELECT login FROM users1 where login != '" + login + "'";
    _my_query.exec(str);
    QString tmp;
    if (_my_query.exec(str))
    {
        while (_my_query.next())
        {
            tmp = tmp + _my_query.value(0).toString() +  "\n";
            //qDebug() << tmp;
        }
    }
	    
    return tmp;
}

bool Data::correctDataInputAbonent(const QString& login_to)
{
    QSqlQuery _my_query(_db);
    const QString str = "SELECT login FROM users1 ";

    if (_my_query.exec(str))
    {
        while (_my_query.next())
        {
            if(_my_query.value(0).toString() == login_to)
            {
                //qDebug() << _my_query.value(0).toString();
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

QString Data::readDataMessage(const QString &login)
{
    QSqlQuery _my_query(_db);
    const QString str = "select users1.login, text from \
     (select from_id, text from messages1 join users1 on messages1.to_id=users1.id \
     where users1.login = '" + login + "') as s join users1 on s.from_id = users1.id";

    QString tmp;

    if (_my_query.exec(str))
    {
        while (_my_query.next())
        {
            tmp = tmp + " < " + _my_query.value(0).toString() +  " > " + _my_query.value(1).toString() + "\n";
            //qDebug() << tmp;
        }
    }
    return tmp;
}

QString Data::readDataMessageAll()
{
    QSqlQuery _my_query(_db);
    const QString str = "select login, text from messagesAll1 join users1 on messagesAll1.from_id=users1.id";
        
    QString tmp;

    if (_my_query.exec(str))
    {
        while (_my_query.next())
        {
            tmp = tmp + " < " + _my_query.value(0).toString() +  " > " + _my_query.value(1).toString() + "\n";

            //tmp = tmp + ;
            //qDebug() << tmp;
        }
    }

    return tmp;
}

void Data::closeData()
{
    //std::cout << "База дисконнект" << std::endl;
    _db.close();
}

QString Data::readDataUsers()
{
    QSqlQuery _my_query(_db);
    const QString str = "SELECT login FROM users1";
    _my_query.exec(str);
    QString tmp;
    if (_my_query.exec(str))
    {
        while (_my_query.next())
        {
            tmp = tmp + _my_query.value(0).toString() +  " \n ";
            //qDebug() << tmp;
        }
    }

    return tmp;
}
