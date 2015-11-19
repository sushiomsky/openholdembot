//*******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//*******************************************************************************
//
// Purpose: Shared info for auto/connector and table/positioner
//   * window handle
//   * position on screen
//
//*******************************************************************************

#include "stdafx.h"
#include "CSharedTableInfo.h"

CSharedTableInfo::CSharedTableInfo() {
  _window_handle = NULL;
  _position.bottom = 0;
  _position.left = 0;
  _position.right = 0;
  _position.top = 0;
}

CSharedTableInfo::~CSharedTableInfo() {
  // Don't destruct anything here.
  // Other instances might still use this table object
  _window_handle = NULL;
  _position.bottom = 0;
  _position.left = 0;
  _position.right = 0;
  _position.top = 0;
}

void CSharedTableInfo::SetWindowHandle(HWND handle) {
  _window_handle = handle;
}

void CSharedTableInfo::SetPosition(RECT position) {
  _position.bottom = position.bottom;
  _position.left   = position.left;
  _position.right  = position.right;
  _position.top    = position.top;
}

HWND CSharedTableInfo::window_handle() {
  return _window_handle;
}

void CSharedTableInfo::GetPosition(RECT *position) {
  position->left   = _position.left;
  position->right  = _position.right;
  position->top    = _position.top;
}

int CSharedTableInfo::width() {
  return (_position.right - _position.left + 1);
}

int CSharedTableInfo::height() {
  return (_position.bottom - _position.top + 1);
}

bool CSharedTableInfo::OverlapsTable(CSharedTableInfo *other_table) {
  RECT other_position;
  other_table->GetPosition(&other_position);
  if (left   > other_position.right)  return false;
  if (top    > other_position.bottom) return false;
  if (right  < other_position.left)   return false;
  if (bottom < other_position.top)    return false;
  return true;
}
