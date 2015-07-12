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

#include "CAutoConnector.h"
#include "CFilenames.h"
#include "CPreferences.h"
#include "CSharedMem.h"

const int kExtraInstancesNeededForPopupBlockingAndConnection = 1;

COpenHoldemStarter::COpenHoldemStarter() {
}

COpenHoldemStarter::~COpenHoldemStarter() {
}

void COpenHoldemStarter::StartOpenHoldemInstanceIfNeeded() {
  if (NewInstanceNeeded()) {
    StartOpenHoldemInstance();
  }
}

bool COpenHoldemStarter::NewInstanceNeeded() {
  int instances_needed = p_sharedmem->NBotsConnected()
    + kExtraInstancesNeededForPopupBlockingAndConnection;
  write_log(preferences.debug_openholdem_starter(), "[COpenHoldemStarter] Bots present:   %i\n", p_sharedmem->NBotsPresent());
  write_log(preferences.debug_openholdem_starter(), "[COpenHoldemStarter] Bots connected: %i\n", p_sharedmem->NBotsConnected());
  write_log(preferences.debug_openholdem_starter(), "[COpenHoldemStarter] Bots needed:    %i\n", instances_needed);
  if (instances_needed > p_sharedmem->NBotsPresent()) {
    write_log(preferences.debug_openholdem_starter(), "[COpenHoldemStarter] New instance needed\n");
    return true;
  }
  write_log(preferences.debug_openholdem_starter(), "[COpenHoldemStarter] No new instance needed\n");
  return false;
}

void COpenHoldemStarter::StartOpenHoldemInstance() {
  write_log(preferences.debug_openholdem_starter(), "[COpenHoldemStarter] Starting new instance\n");
  // OpenHoldem MUST exist in the working directory.
  // No error-checking here~> if it does not work, then we silently fail.
  // http://msdn.microsoft.com/en-us/library/windows/desktop/bb762153%28v=vs.85%29.aspx
  ShellExecute(
		NULL,                               // Pointer to parent window; not needed
		"open",                             // "open" == "execute" for an executable
		p_filenames->PathOfExecutable(), 	  // OpenHoldem to be executed
		NULL, 		                          // Parameters
		p_filenames->OpenHoldemDirectory(), // Working directory
		SW_SHOWNORMAL);		                  // Active window, default size
}

void COpenHoldemStarter::CloseOpenHoldemIfInstanceNotNeeded() {
  if (InstanceMayBeClosed()) {
    Terminate();
  }
}

void COpenHoldemStarter::Terminate() {
  // Works only if called within the "main thread"
  // that contains a message/handler for WM_QUIT
  write_log(preferences.debug_openholdem_starter(), "[COpenHoldemStarter] Going to terminate\n");
  PostQuitMessage(0);
}

bool COpenHoldemStarter::InstanceMayBeClosed() {
  if (p_autoconnector->IsConnected()) return false;
  if (p_sharedmem->NBotsPresent() - p_sharedmem->NBotsConnected() 
      < kExtraInstancesNeededForPopupBlockingAndConnection)return false;
  // Otherwise: not connected and not needed
  return true;
}