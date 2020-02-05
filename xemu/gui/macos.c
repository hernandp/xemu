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

static id auto_release_pool;
static id application;

// New Apple SDKs objc_msgSend prototype changed to *force* callers
// to cast to proper types!. So this is ugly, but works.
//

// Function pointer name format: PFN_OBJC_MSGSEND_(rettype)(parmtypes)

typedef void (* PFN_OBJC_MSGSEND_VV) (id, SEL);
typedef id   (* PFN_OBJC_MSGSEND_IDV)(id, SEL);
typedef void (* PFN_OBJC_MSGSEND_VID)(id, SEL, id);
typedef id   (* PFN_OBJC_MSGSEND_IDID)(id, SEL, id);
typedef void (* PFN_OBJC_MSGSEND_VBOOL)(id, SEL, BOOL);
typedef void (* PFN_OBJC_MSGSEND_VID3)(id, SEL, id, id, id);
typedef BOOL (* PFN_OBJC_MSGSEND_BOOLID3)(id, SEL, id, id, id);
typedef BOOL (* PFN_OBJC_MSGSEND_BOOLIDSELID)(id, SEL, id, SEL, id);
typedef id   (* PFN_OBJC_MSGSEND_IDSTR)(id, SEL, char*);

static PFN_OBJC_MSGSEND_VV  		pfn_objc_msgsend_vv  = 		(PFN_OBJC_MSGSEND_VV)  objc_msgSend; 
static PFN_OBJC_MSGSEND_IDV 		pfn_objc_msgsend_idv = 		(PFN_OBJC_MSGSEND_IDV) objc_msgSend; 
static PFN_OBJC_MSGSEND_VID 		pfn_objc_msgsend_vid = 		(PFN_OBJC_MSGSEND_VID) objc_msgSend;
static PFN_OBJC_MSGSEND_IDID 		pfn_objc_msgsend_idid = 	(PFN_OBJC_MSGSEND_IDID) objc_msgSend;
static PFN_OBJC_MSGSEND_VBOOL 		pfn_objc_msgsend_vbool = 	(PFN_OBJC_MSGSEND_VBOOL) objc_msgSend;
static PFN_OBJC_MSGSEND_VID3 		pfn_objc_msgsend_vid3 =		(PFN_OBJC_MSGSEND_VID3)objc_msgSend;
static PFN_OBJC_MSGSEND_BOOLID3 	pfn_objc_msgsend_bid3 =		(PFN_OBJC_MSGSEND_BOOLID3)objc_msgSend;
static PFN_OBJC_MSGSEND_BOOLIDSELID pfn_objc_msgsend_bidselid = (PFN_OBJC_MSGSEND_BOOLIDSELID)objc_msgSend;
static PFN_OBJC_MSGSEND_IDSTR 		pfn_objc_msgsend_idstr = 	(PFN_OBJC_MSGSEND_IDSTR) objc_msgSend;

static void _xemumacgui_menu_action_handler(id self, SEL selector, id sender) 
{

}

static int xemumacgui_init(void) 
{
	DEBUGPRINT("GUI: macOS Cocoa initialization" NL);

	auto_release_pool = pfn_objc_msgsend_idv((id)objc_getClass("NSAutoreleasePool"), sel_registerName("new"));

	// Our delegate class that implement NSApplicationDelegate protocol.

	Class xemu_ui_delegate_class = objc_allocateClassPair(objc_getClass("NSObject"), "Xemu_UI", 0);
    class_addProtocol(xemu_ui_delegate_class, objc_getProtocol("NSApplicationDelegate"));
    class_addMethod(xemu_ui_delegate_class, sel_registerName("menuActionHandler"), (IMP)_xemumacgui_menu_action_handler, "v@:@");
    objc_registerClassPair(xemu_ui_delegate_class); 

  	id xemu_ui_delegate = pfn_objc_msgsend_idv((id)xemu_ui_delegate_class, sel_registerName("new"));
  
	// Create application and set our delegate instance

	application = pfn_objc_msgsend_idv((id)objc_getClass("NSApplication"), sel_registerName("sharedApplication"));
	pfn_objc_msgsend_vid(application, sel_registerName("setDelegate:"), xemu_ui_delegate);

	return 1;
}

static int xemumacgui_popup(const struct menu_st desc[]) 
{
	id ui_menu = pfn_objc_msgsend_idv((id)objc_getClass("NSMenu"), sel_registerName("new"));
	pfn_objc_msgsend_vv(ui_menu, sel_registerName("autorelease"));

	for (int i = 0; desc[i].name; i++) 
	{
		id menu_item = pfn_objc_msgsend_idv(objc_getClass("NSMenuItem"), sel_registerName("alloc"));

		pfn_objc_msgsend_vid3(menu_item, sel_registerName("initWithTitle:action:keyEquivalent:"),  
			pfn_objc_msgsend_idstr(objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), desc[i].name),
        	sel_registerName("menuActionHandler"),
        	pfn_objc_msgsend_idstr(objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), ""));

		pfn_objc_msgsend_vbool(menu_item, sel_registerName("setEnabled:"), YES);

		id menu_object = pfn_objc_msgsend_idid((id)objc_getClass("NSValue"), sel_registerName("valueWithPointer:"), &desc[i]);
		pfn_objc_msgsend_vid(menu_item, sel_registerName("setRepresentedObject:"), menu_object);

		pfn_objc_msgsend_vid(ui_menu, sel_registerName("addItem:"), menu_item);
	}

	id mouse_location = pfn_objc_msgsend_idv((id)objc_getClass("NSEvent"), sel_registerName("mouseLocation"));
	
	BOOL s = pfn_objc_msgsend_bid3(ui_menu, 
		sel_registerName("popUpMenuPositioningItem:atLocation:inView:"), nil, (id) mouse_location, nil);

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
