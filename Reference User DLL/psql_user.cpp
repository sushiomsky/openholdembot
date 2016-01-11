#include "psql_user.h"

/* Establish connection to database */
PGconn *ConnectDB()
{
	PGconn *conn = NULL;

	// Make a connection to the database
	conn = PQconnectdb("user=postgres password=2236 dbname='PT4DB' hostaddr=192.168.0.115 port=5432");

	// Check to see that the backend connection was successfully made 
    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("Connection to database failed\n");
        CloseConn(conn);
    }

	//printf("Connection to database - OK\n");
	return conn;
}

/* Close connection to database */
void CloseConn(PGconn *conn)
{
    PQfinish(conn);
}

