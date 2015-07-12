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

class COpenHoldemStarter {
 public:
  COpenHoldemStarter();
  ~COpenHoldemStarter();
 public:
  // To be called by the auto-connector on connection
  void StartOpenHoldemInstanceIfNeeded();
 public:
  // Works only if called within the "main thread"
  // that contains a message/handler for WM_QUIT
  void CloseOpenHoldemIfInstanceNotNeeded();
 private:
  bool NewInstanceNeeded();
  void StartOpenHoldemInstance();
 private:
  // Works only if called within the "main thread"
  // that contains a message/handler for WM_QUIT
  void Terminate();
  bool InstanceMayBeClosed();
};