/* Part of the Xemu project, please visit: https://github.com/lgblgblgb/xemu
   Copyright (C)2016,2019 LGB (Gábor Lénárt) <lgblgblgb@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <objc/objc-runtime.h>

// Object 

static id auto_release_pool;
static id application;
static id menu;

// New Apple SDKs objc_msgSend prototype changed to *force* callers
// to cast to proper types!. So this is ugly, but works.
//

// Function pointer name format: PFN_OBJC_MSGSEND_(rettype)(parmtypes)

typedef void (* PFN_OBJC_MSGSEND_VV) (id, SEL);
typedef id   (* PFN_OBJC_MSGSEND_IDV)(id, SEL);
typedef void (* PFN_OBJC_MSGSEND_VID)(id, SEL, id);
typedef void (* PFN_OBJC_MSGSEND_VID3)(id, SEL, id, id, id);
typedef void (* PFN_OBJC_MSGSEND_VIDSELID)(id, SEL, id, SEL, id);
typedef id   (* PFN_OBJC_MSGSEND_IDSTR)(id, SEL, char*);

static PFN_OBJC_MSGSEND_VV  pfn_objc_msgsend_vv  = (PFN_OBJC_MSGSEND_VV)  objc_msgSend; 
static PFN_OBJC_MSGSEND_IDV pfn_objc_msgsend_idv = (PFN_OBJC_MSGSEND_IDV) objc_msgSend; 
static PFN_OBJC_MSGSEND_VID pfn_objc_msgsend_vid = (PFN_OBJC_MSGSEND_VID) objc_msgSend;
static PFN_OBJC_MSGSEND_VID3 pfn_objc_msgsend_vid3 =(PFN_OBJC_MSGSEND_VID3)objc_msgSend;
static PFN_OBJC_MSGSEND_VIDSELID pfn_objc_msgsend_vidselid = (PFN_OBJC_MSGSEND_VIDSELID)objc_msgSend;
static PFN_OBJC_MSGSEND_IDSTR pfn_objc_msgsend_idstr = (PFN_OBJC_MSGSEND_IDSTR) objc_msgSend;

static int xemumacgui_init(void) 
{
	DEBUGPRINT("GUI: macOS Cocoa initialization" NL);

	auto_release_pool = pfn_objc_msgsend_idv(objc_getClass("NSAutoreleasePool"), sel_registerName("new"));

	// Our delegate class that implement NSApplicationDelegate protocol.

	Class xemu_ui_delegate_class = objc_allocateClassPair(objc_getClass("NSObject"), "Xemu_UI", 0);
    class_addProtocol(xemu_ui_delegate_class, objc_getProtocol("NSApplicationDelegate"));
    //class_addMethod(xemu_ui_delegate_class, sel_registerName("menuCallback:"), (IMP)menu_callback, "v@:@");
    objc_registerClassPair(xemu_ui_delegate_class); 

  	id xemu_ui_delegate = pfn_objc_msgsend_idv((id)xemu_ui_delegate_class, sel_registerName("new"));
  
	// Create application and set our delegate instance

	application = pfn_objc_msgsend_idv(objc_getClass("NSApplication"), sel_registerName("sharedApplication"));
	pfn_objc_msgsend_vid(application, sel_registerName("setDelegate:"), xemu_ui_delegate);

	// Create our popup menu

	menu = pfn_objc_msgsend_idv(objc_getClass("NSMenu"), sel_registerName("new"));
	pfn_objc_msgsend_vv(menu, sel_registerName("autorelease"));
	id menu_item = pfn_objc_msgsend_idv(objc_getClass("NSMenuItem"), sel_registerName("alloc"));

	pfn_objc_msgsend_vidselid(menu_item, sel_registerName("initWithTitle:action:keyEquivalent:"),  
		pfn_objc_msgsend_idstr(objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), "SAMPLE"),
        nil,
        pfn_objc_msgsend_idstr(objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), "X"));

	pfn_objc_msgsend_vid(menu, sel_registerName("addItem:"), menu_item);
}

static int xemumacgui_popup(const struct menu_st* menu) 
{
  	// id alert = pfn_objc_msgsend_idv((id)objc_getClass("NSAlert"), sel_registerName("new"));
	// pfn_objc_msgsend_vv(alert, sel_registerName("runModal"));
	//[theMenu popUpMenuPositioningItem:nil atLocation:[NSEvent mouseLocation] inView:nil];

	id mouse_location = pfn_objc_msgsend_idv(objc_getClass("NSEvent"), sel_registerName("mouseLocation"));
	pfn_objc_msgsend_vid3(menu, 
		sel_registerName("popUpMenuPositioningItem:atLocation:inView:"), nil, mouse_location, nil);
    return 0;
}

static int xemumacgui_file_selector(void) 
{
}

static const struct xemugui_descriptor_st xemumacosgui_descriptor = {
	"macos",					// name
	"macOS API based Xemu UI implementation",	// desc
	xemumacgui_init,
	NULL,						// shutdown (we don't need shutdown for windows?)
	NULL,						// iteration (we don't need iteration for windows?)
	xemumacgui_file_selector,
	xemumacgui_popup
};
