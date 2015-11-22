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

#include <windef.h>

class CSharedTableInfo {
 public:
  CSharedTableInfo();
  ~CSharedTableInfo();
 public: 
  // CSharedTableInfo gets stored in shared memory
  // Each process must only set the values for his own tables
  void SetWindowHandle(HWND handle);
  void SetPosition(RECT position);
 public:
  HWND window_handle();
  void GetPosition(RECT *position);
  int width();
  int height();
 public:
  bool OverlapsTable(CSharedTableInfo *other_table);
  bool OverlapsRegion(RECT *region);
  bool OverlapsRegion(int left, int top, int right, int bottom);
 public:
  void Move(int left, int top);
  void MoveToTopLeft();
  void ResizeToTargetSize();
  void ResizeToTotalSize(int new_width, int new_height);
  void ResizeToClientSize(int new_width, int new_height);
 private:
  void Storeposition();
 private:
  HWND _window_handle;
  RECT _position;
};