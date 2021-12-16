#ifndef TREELIST_H
#define TREELIST_H 
 
#include "wx/wx.h"
#include "wx/wxprec.h"

#include "wx/treelist.h"
#include "wx/artprov.h"
#include "ruby.h"

enum
{
    Col_Component,
    Col_Files,
    Col_Size
};

class MyComparator : public wxTreeListItemComparator
{
	public:
		virtual int
			Compare(wxTreeListCtrl* treelist,
					unsigned column,
					wxTreeListItem item1,
					wxTreeListItem item2) wxOVERRIDE
			{
				wxString text1 = treelist->GetItemText(item1, column),
				text2 = treelist->GetItemText(item2, column);

				switch ( column )
				{
					case Col_Component:
						// Simple alphabetical comparison is fine for those.
						return text1.CmpNoCase(text2);

					case Col_Files:
						// Compare strings as numbers.
						return GetNumFilesFromText(text1) - GetNumFilesFromText(text2);

					case Col_Size:
						// Compare strings as numbers but also take care of "KiB" and
						// "MiB" suffixes.
						return GetSizeFromText(text1) - GetSizeFromText(text2);
				}

				wxFAIL_MSG( "Sorting on unknown column?" );

				return 0;
			}
	private:
		// Return the number of files handling special value "many". Notice that
		// the returned value is signed to allow using it in subtraction above.
		int GetNumFilesFromText(const wxString& text) const
		{
			unsigned long n;
			if ( !text.ToULong(&n) )
			{
				if ( text == "many" )
					n = 9999;
				else
					n = 0;
			}

			return n;
		}
		// Return the size in KiB from a string with either KiB or MiB suffix.
		int GetSizeFromText(const wxString& text) const
		{
			wxString size;
			unsigned factor = 1;
			if ( text.EndsWith(" MiB", &size) )
				factor = 1024;
			else if ( !text.EndsWith(" KiB", &size) )
				return 0;

			unsigned long n = 0;
			size.ToULong(&n);

			return n*factor;
		}
};

class TreeList :public wxObject
{
private:
	wxTreeListCtrl* m_treelist_ctrl;
	wxImageList* m_imageList;
	MyComparator m_comparator;
	enum
	{
		Icon_File,
		Icon_FolderClosed,
		Icon_FolderOpened
	};
	enum
	{
			Col_Component,
			Col_Files,
			Col_Size
	};
	 
	bool m_isFlat;

	 
public:
	TreeList(int nargs, VALUE *args);
	virtual ~TreeList (){};
	wxTreeListCtrl* GetTreeListCtrl(){
		return m_treelist_ctrl;
	};
	void InitImageList();

	 
};
#endif
