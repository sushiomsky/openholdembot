#ifndef OH_GENERAL_H
#define OH_GENERAL_H

///////////////////////////////////// 
//card macros 
#define RANK(c)	         ((c>>4)&0x0f) 
#define SUIT(c)          ((c>>0)&0x0f) 
#define ISCARDBACK(c)	 (c==0xff) 
#define ISUNKNOWN(c)	 (c==0) 
///////////////////////////////////// 

//////////////////////////////////// 
//consecutive states 
holdem_state    m_holdem_state[256]; 
unsigned char   m_ndx; 
////////////////////////////////////

//////////////////////////////////// 
//versus list & prwin
phl1k_t m_phl1k;
pp13 prw1326;
////////////////////////////////////

//////////////////////////////////// 
//WH symbols
pfgws_t m_pget_winholdem_symbol;
////////////////////////////////////

double gws(int chair, const char* name, bool& iserr){ 
	return (*m_pget_winholdem_symbol)(chair,name,iserr); 
} 

double gws(const char* name){ 
	bool iserr; 
	int mychair = (int)gws(0,"userchair",iserr); 
	return gws(mychair,name,iserr); 
}

bool hlset( int rank0, int rank1, int listnum, bool onoff ){
   return ((*m_phl1k)[listnum][rank0-2][rank1-2] = onoff);
}

bool hlget( int rank0, int rank1, int listnum ){
   return ((*m_phl1k)[listnum][rank0-2][rank1-2]);
}

//////////////////////////////////////////////////////////////////////////
//OWN VARIABLES AND FUNC
//////////////////////////////////////////////////////////////////////////

#endif