#define WHUSER_EXPORTS 

#include "OH-DLL.h"
#include <windows.h>
#include <bitset>

using namespace std;

#include "OH-general.h"
#include "SQL_test.h"

double process_query(const char* pquery){

	if(pquery==NULL)
		return 0;
	//example
	if(strcmp(pquery,"dll$test")==0)
	{
		//just trying to connect to db (password to db is needed)
		PGconn *conn = NULL;
		conn = ConnectDB();
		CloseConn(conn);
		return 1;
	}

	return 0;

}

double process_state(holdem_state* pstate){

	if(pstate!=NULL)
      m_holdem_state[ (++m_ndx)&0xff ] = *pstate;

	return 0;

}
///////////////////////////////////////////////////// 
//WINHOLDEM RUNTIME ENTRY POINT 
///////////////////////////////////////////////////// 
WHUSER_API double process_message(const char* pmessage, const void* param){

	if(pmessage==NULL){
		return 0;
	}
	if(param==NULL){
		return 0;
	}
	if(strcmp(pmessage,"state")==0){
		return process_state( (holdem_state*)param );
	}
	if(strcmp(pmessage,"phl1k")==0){   
		m_phl1k = (phl1k_t)param;
		return 0;
	}
	if(strcmp(pmessage,"prw1326")==0){	
		prw1326 = (pp13)param;
		return 0;
	}
	if(strcmp(pmessage,"query")==0){ 
		return process_query((const char*)param);
	}
	if(strcmp(pmessage,"pfgws")==0){
		m_pget_winholdem_symbol = (pfgws_t)param;
		return 0;
	}

	return 0;

}
///////////////////////////////// 
//DLLMAIN 
///////////////////////////////// 
BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

	switch(ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			break; 
		case DLL_THREAD_ATTACH:
			break; 
		case DLL_THREAD_DETACH:
			break; 
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}