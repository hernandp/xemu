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
#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>

typedef CGPoint NSPoint;

static id auto_release_pool;
static id application;

const unsigned long NSFileHandlingPanelOKButton = 1;
const unsigned long NSFileHandlingPanelCancelButton = 0;

// New Apple SDKs objc_msgSend prototype changed to *force* callers
// to cast to proper types!. So this is ugly, but works.
//

// Name format: PFN_OBJC_MSGSEND_rettype[_param0t_param1_t ... paramN_t]
// 
// Return: V = void  I = id  B = bool 

typedef void (* PFN_OBJC_MSGSEND_VV) (id, SEL);
typedef id   (* PFN_OBJC_MSGSEND_IDV)(id, SEL);
typedef NSPoint (* PFN_OBJC_MSGSEND_POINTV)(id, SEL);
typedef void (* PFN_OBJC_MSGSEND_VID)(id, SEL, id);
typedef id   (* PFN_OBJC_MSGSEND_IDID)(id, SEL, id);
typedef id   (* PFN_OBJC_MSGSEND_IDUINT)(id, SEL, unsigned long);
typedef void (* PFN_OBJC_MSGSEND_VBOOL)(id, SEL, BOOL);
typedef void (* PFN_OBJC_MSGSEND_VID2)(id, SEL, id, id);
typedef void (* PFN_OBJC_MSGSEND_VID3)(id, SEL, id, id, id);
typedef BOOL (* PFN_OBJC_MSGSEND_BOOLID3)(id, SEL, id, id, id);
typedef BOOL (* PFN_OBJC_MSGSEND_BOOL_ID_POINT_ID)(id, SEL, id, NSPoint, id);
typedef BOOL (* PFN_OBJC_MSGSEND_BOOLIDSELID)(id, SEL, id, SEL, id);
typedef id   (* PFN_OBJC_MSGSEND_IDIDSELID)(id, SEL, id, SEL, id);
typedef id   (* PFN_OBJC_MSGSEND_IDSTR)(id, SEL, const char*);
typedef void (* PFN_OBJC_MSGSEND_VSTR) (id, SEL, const char*);


static PFN_OBJC_MSGSEND_VV  		pfn_objc_msgsend_vv  = 		(PFN_OBJC_MSGSEND_VV)  objc_msgSend; 
static PFN_OBJC_MSGSEND_IDV 		pfn_objc_msgsend_idv = 		(PFN_OBJC_MSGSEND_IDV) objc_msgSend; 
static PFN_OBJC_MSGSEND_POINTV 		pfn_objc_msgsend_pointv = 	(PFN_OBJC_MSGSEND_POINTV) objc_msgSend; 
static PFN_OBJC_MSGSEND_VID 		pfn_objc_msgsend_vid = 		(PFN_OBJC_MSGSEND_VID) objc_msgSend;
static PFN_OBJC_MSGSEND_IDID 		pfn_objc_msgsend_idid = 	(PFN_OBJC_MSGSEND_IDID) objc_msgSend;
static PFN_OBJC_MSGSEND_IDUINT		pfn_objc_msgsend_iduint = 	(PFN_OBJC_MSGSEND_IDUINT) objc_msgSend;
static PFN_OBJC_MSGSEND_VBOOL 		pfn_objc_msgsend_vbool = 	(PFN_OBJC_MSGSEND_VBOOL) objc_msgSend;
static PFN_OBJC_MSGSEND_VID2 		pfn_objc_msgsend_vid2 =		(PFN_OBJC_MSGSEND_VID2)  objc_msgSend;
static PFN_OBJC_MSGSEND_VID3 		pfn_objc_msgsend_vid3 =		(PFN_OBJC_MSGSEND_VID3)  objc_msgSend;
static PFN_OBJC_MSGSEND_BOOLID3 	pfn_objc_msgsend_bid3 =		(PFN_OBJC_MSGSEND_BOOLID3)objc_msgSend;
static PFN_OBJC_MSGSEND_BOOLIDSELID pfn_objc_msgsend_bidselid = (PFN_OBJC_MSGSEND_BOOLIDSELID)objc_msgSend;
static PFN_OBJC_MSGSEND_BOOL_ID_POINT_ID pfn_objc_msgsend_b_idpointid = (PFN_OBJC_MSGSEND_BOOL_ID_POINT_ID)objc_msgSend;
static PFN_OBJC_MSGSEND_IDIDSELID   pfn_objc_msgsend_ididselid =(PFN_OBJC_MSGSEND_IDIDSELID)objc_msgSend;
static PFN_OBJC_MSGSEND_IDSTR 		pfn_objc_msgsend_idstr = 	(PFN_OBJC_MSGSEND_IDSTR) objc_msgSend;
static PFN_OBJC_MSGSEND_VSTR 		pfn_objc_msgsend_vstr = 	(PFN_OBJC_MSGSEND_VSTR) objc_msgSend;

static void _xemumacgui_menu_action_handler(id self, SEL selector, id sender) 
{
	id menu_obj = pfn_objc_msgsend_idv(sender, sel_registerName("representedObject"));
	const struct menu_st* menu_item = (const struct menu_st*) pfn_objc_msgsend_idv(menu_obj, sel_registerName("pointerValue"));
	if (menu_item && menu_item->type == XEMUGUI_MENUID_CALLABLE)
	{
		DEBUGPRINT("GUI: menu point \"%s\" has been activated." NL,  menu_item->name);
		((xemugui_callback_t)(menu_item->handler))(menu_item, NULL);
	}
}

static id _xemumacgui_r_menu_builder(const struct menu_st desc[])
{
	id ui_menu = pfn_objc_msgsend_idv((id)objc_getClass("NSMenu"), sel_registerName("new"));
	pfn_objc_msgsend_vv(ui_menu, sel_registerName("autorelease"));

	for (int i = 0; desc[i].name; i++) 
	{
		if (!desc[i].handler || !desc[i].name) {
			DEBUGPRINT("GUI: invalid meny entry found, skipping it" NL);
			continue;
		}

		id menu_item = pfn_objc_msgsend_idv((id) objc_getClass("NSMenuItem"), sel_registerName("alloc"));
		pfn_objc_msgsend_vv(menu_item, sel_registerName("autorelease"));

		pfn_objc_msgsend_ididselid(menu_item, sel_registerName("initWithTitle:action:keyEquivalent:"),  
			pfn_objc_msgsend_idstr((id) objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), desc[i].name),
        	sel_registerName("menuActionHandler"),
        	pfn_objc_msgsend_idstr((id) objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), ""));

		pfn_objc_msgsend_vbool(menu_item, sel_registerName("setEnabled:"), YES);

		id menu_object = pfn_objc_msgsend_idid((id)objc_getClass("NSValue"), sel_registerName("valueWithPointer:"),(id) &desc[i]);
		pfn_objc_msgsend_vid(menu_item, sel_registerName("setRepresentedObject:"), menu_object);

		pfn_objc_msgsend_vid(ui_menu, sel_registerName("addItem:"), menu_item);

		if (desc[i].type == XEMUGUI_MENUID_SUBMENU)
		{
			// Recurse

			id sub_menu = _xemumacgui_r_menu_builder(desc[i].handler);
			pfn_objc_msgsend_vid2(ui_menu, sel_registerName("setSubmenu:forItem:"), sub_menu, menu_item);
		}
	}

	return ui_menu;
}

static int xemumacgui_init(void) 
{
	DEBUGPRINT("GUI: macOS Cocoa initialization" NL);

	auto_release_pool = pfn_objc_msgsend_idv((id)objc_getClass("NSAutoreleasePool"), sel_registerName("new"));
	application = pfn_objc_msgsend_idv((id)objc_getClass("NSApplication"), sel_registerName("sharedApplication"));
	id app_delegate = pfn_objc_msgsend_idv(application, sel_registerName("delegate"));
	id xemu_ui_delegate_class = pfn_objc_msgsend_idv(app_delegate, sel_registerName("class"));
    class_addMethod(xemu_ui_delegate_class, sel_registerName("menuActionHandler"), (IMP)_xemumacgui_menu_action_handler, "v@:@");
	return 0;
}

static int xemumacgui_popup(const struct menu_st desc[]) 
{
	// If the SDL window is not active, make this right-click to do application activation.
	//
	if ( ! (((id(*)(id,SEL))objc_msgSend) (application, sel_registerName("mainWindow"))))
	{
		((void(*)(id,SEL,BOOL))objc_msgSend) (application, sel_registerName("activateIgnoringOtherApps:"), YES);
		return 0;
	}
	id ui_menu = _xemumacgui_r_menu_builder(desc);
	if (!ui_menu)
	{
		DEBUGPRINT("GUI: Error building menu");
		return 1;
	}

	NSPoint mouse_location = pfn_objc_msgsend_pointv((id)objc_getClass("NSEvent"), sel_registerName("mouseLocation"));
	pfn_objc_msgsend_b_idpointid(ui_menu, sel_registerName("popUpMenuPositioningItem:atLocation:inView:"), nil, mouse_location, nil);

    return 0;
}

static int xemumacgui_file_selector(int dialog_mode, const char *dialog_title, char *default_dir, char *selected, int path_max_size )
{
	*selected = '\0';
	id open_panel = pfn_objc_msgsend_idv((id) objc_getClass("NSOpenPanel"), sel_registerName("openPanel"));
	pfn_objc_msgsend_vv(open_panel, sel_registerName("autorelease"));

	id main_window = pfn_objc_msgsend_idv(application, sel_registerName("mainWindow"));
	DEBUGPRINT("mainWindow = 0x%x", main_window);

	pfn_objc_msgsend_vbool(open_panel, sel_registerName("setCanChooseDirectories:"), NO);
	pfn_objc_msgsend_vbool(open_panel, sel_registerName("setAllowsMultipleSelection:"), NO);
	pfn_objc_msgsend_vid(open_panel, sel_registerName("setMessage:"), 
		pfn_objc_msgsend_idstr((id) objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), dialog_title));

	id panel_result = pfn_objc_msgsend_idv(open_panel, sel_registerName("runModal"));

	pfn_objc_msgsend_vv(main_window, sel_registerName("makeKeyWindow"));

	if ( (unsigned long) panel_result == NSFileHandlingPanelOKButton)
	{
		DEBUGPRINT("GUI: macOS panel OK button pressed" NL );
		id url_array = pfn_objc_msgsend_idv(open_panel, sel_registerName("URLs"));
		id filename_url = pfn_objc_msgsend_iduint(url_array, sel_registerName("objectAtIndex:"), 0);
		const char* filename = (const char*)pfn_objc_msgsend_idv(filename_url, sel_registerName("fileSystemRepresentation"));
		strcpy(selected, filename);
		store_dir_from_file_selection(default_dir, filename, dialog_mode);

		return 0;
	}

	return 1;
}

static const struct xemugui_descriptor_st xemumacosgui_descriptor = {
	"macos",					// name
	"macOS native API Xemu UI implementation",	// desc
	xemumacgui_init,
	NULL,						
	NULL,						
	xemumacgui_file_selector,
	xemumacgui_popup
};
