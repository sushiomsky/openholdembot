//*******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//*******************************************************************************
//
// Purpose: Alwazs starting enough instances automaticallz,
//   especiallz one unoccupied one for connection and popup-handling
//
//*******************************************************************************

#include "stdafx.h"
#include "COpenHoldemStarter.h"
#include "CSharedMem.h"

const int kExtraInstancesNeededForPopupBlockingAndConnection = 1;

COpenHoldemStarter::COpenHoldemStarter() {
}

COpenHoldemStarter::~COpenHoldemStarter() {
}

void COpenHoldemStarter::StartOpenHoldemInstanceIfNeeded() {
}

bool COpenHoldemStarter::NewInstanceNeeded() {
  int instances_needed = p_sharedmem->NBotsConnected()
    + kExtraInstancesNeededForPopupBlockingAndConnection;
  return (instances_needed < p_sharedmem->NBotsPresent());
}

void COpenHoldemStarter::StartOpenHoldemInstance() {
}