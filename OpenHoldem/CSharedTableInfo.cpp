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

#include "CPreferences.h"
#include "CSessionCounter.h"
#include "..\CTablemap\CTableMapAccess.h"

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

void CSharedTableInfo::StorePosition(int left, int top, int right, int bottom) {
  _position.bottom = bottom;
  _position.left   = left;
  _position.right  = right;
  _position.top    = top;
}

HWND CSharedTableInfo::window_handle() {
  return _window_handle;
}

void CSharedTableInfo::GetPosition(RECT *position) {
  position->left   = _position.left;
  position->top    = _position.top;
  position->right  = _position.right;
  position->bottom = _position.bottom;
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
  return OverlapsRegion(&other_position);
}

bool CSharedTableInfo::OverlapsRegion(RECT *region) {
  return OverlapsRegion(region->left, region->top,
    region->right, region->bottom);
}

bool CSharedTableInfo::OverlapsRegion(int left, int top, int right, int bottom) {
  if (_position.left   > right)  return false;
  if (_position.top    > bottom) return false;
  if (_position.right  < left)   return false;
  if (_position.bottom < top)    return false;
  return true;
}
/*
void CSharedMem::StoreTablePosition(int left, int top, int right, int bottom) {
  ENT;
  int session_ID = p_sessioncounter->session_id();
  table_positions[session_ID].left   = left;
  table_positions[session_ID].top    = top;
  table_positions[session_ID].right  = right;
  table_positions[session_ID].bottom = bottom;
}
*/

void CSharedTableInfo::MoveToTopLeft() {
	write_log(preferences.debug_table_positioner(), "[CTablePositioner] MoveToTopLeft()\n");
	Move(0, 0);
}

void CSharedTableInfo::Move(int left, int top) {
  RECT old_position;
  GetWindowRect(_window_handle, &old_position);
  int width  = old_position.right - old_position.left;
  int height = old_position.bottom - old_position.top;
  int right  = left + width;
  int bottom = top + height;
  assert(width  >= 0);
  assert(height >= 0);
  MoveWindow(_window_handle, left, top, width, height, true);
  StorePosition(left, top, right, bottom);
}

void CSharedTableInfo::ResizeToTargetSize() {
  int width;
  int height;
  p_tablemap_access->SetClientSize("targetsize", &width, &height);
  if (width <= 0 || height <= 0) {
    write_log(preferences.debug_table_positioner(), "[CTablePositioner] target size <= 0\n");
    return;
  }
  ResizeToClientSize(width, height);
}

void CSharedTableInfo::ResizeToClientSize(int new_width, int new_height) {
  assert(new_width > 0);
  assert(new_height > 0);
  RECT old_client_size;
  GetClientRect(_window_handle, &old_client_size);
  int old_width  = old_client_size.right - old_client_size.left;
  int old_height = old_client_size.bottom - old_client_size.top;
  write_log(preferences.debug_table_positioner(), "[CTablePositioner] current client size: %i, %i\n",
    old_width, old_height);
  write_log(preferences.debug_table_positioner(), "[CTablePositioner] target client size: %i, %i\n",
    new_width, new_height);
  if (old_width == new_width && old_height == new_height) return;
  RECT old_position;
  GetWindowRect(_window_handle, &old_position);
  int new_total_width = old_position.right - old_position.left
    + new_width- old_width;
  int new_total_height = old_position.bottom - old_position.top
    + new_height - old_height;
  ResizeToTotalSize(new_total_width, new_total_height);
}

void CSharedTableInfo::ResizeToTotalSize(int new_width, int new_height) {
  write_log(preferences.debug_table_positioner(), 
    "[CTablePositioner] Resizing window to total size %i, %i. Keeping old position\n",
    new_width, new_height);
  RECT old_position;
  GetWindowRect(_window_handle, &old_position);
  MoveWindow(_window_handle, 
    old_position.left, old_position.top,
    new_width, new_height,
		true);	// true = Redraw the table.
  // Update shared mem
  int right = old_position.left + new_width - 1;
  int bottom = old_position.top * new_height - 1;
  StorePosition(old_position.left, old_position.top,
    right, bottom);
}

void CSharedTableInfo::Dump() {
  write_log(preferences.debug_table_positioner(), "[CTablePositioner] Table %i: [%i, %i, %i, %i] size [%i, %i] handle %i\n",
    p_sessioncounter->session_id(),
    _position.left, _position.top, _position.right, _position.bottom,
    width(), height(), 
    _window_handle);
}

/*
// Precondition: position and size defined
void CTablePositioner::MoveWindowToItsPosition() {
	write_log(preferences.debug_table_positioner(), "[CTablePositioner] MoveWindowToItsPosition()\n");
  // Consistancy checks
	if (_new_left_x      < 0 || _new_left_x   > _desktop_rectangle.right
	  	|| _new_top_y    < 0 || _new_top_y    > _desktop_rectangle.bottom
		  || _table_size_x < 1 || _table_size_x > _desktop_rectangle.right
		  || _table_size_y < 1 || _table_size_y > _desktop_rectangle.bottom) {
		// Values out of sane range
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] Values out of sane range; probably not yet initialized\n");
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] _new_left_x   = %i\n", _new_left_x);
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] _new_top_y    = %i\n", _new_top_y);
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] _table_size_x = %i\n", _table_size_x);
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] _table_size_y = %i\n", _table_size_y);
		return;
	}
  MoveWindow(p_autoconnector->attached_hwnd(), 
		_new_left_x, _new_top_y, 
		_table_size_x, _table_size_y, 
		true);	// true = Redraw the table.
  // Update shared mem
  int right = _new_left_x + _table_size_x - 1;
  int bottom = _new_top_y + _table_size_y - 1;
  p_sharedmem->StoreTablePosition(_new_left_x, _new_top_y, 
    right, bottom);
}




*/