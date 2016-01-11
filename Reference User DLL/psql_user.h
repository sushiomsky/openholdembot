#ifndef PSQL_USER_H
#define PSQL_USER_H

#include "libpq-fe.h"
#include "postgres_ext.h"
/* Establish connection to database */
PGconn *ConnectDB();//need to make the connection info dynamic in the future!!!!

/* Close connection to database */
void CloseConn(PGconn *conn);

#endif
