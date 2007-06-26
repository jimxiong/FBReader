/*
 * FBReader -- electronic book reader
 * Copyright (C) 2004-2007 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __BOOKTEXTVIEW_H__
#define __BOOKTEXTVIEW_H__

#include <deque>

#include <ZLOptions.h>

#include "FBView.h"

class BookTextView : public FBView {

public:
	ZLBooleanOption ShowTOCMarksOption;

public:
	BookTextView(FBReader &reader, ZLPaintContext &context);
	~BookTextView();

	void setModel(shared_ptr<ZLTextModel> model, const std::string &name);
	void setContentsModel(shared_ptr<ZLTextModel> contentsModel);
	void saveState();

	void gotoParagraph(int num, bool last = false);
	bool canUndoPageMove();
	void undoPageMove();
	bool canRedoPageMove();
	void redoPageMove();

	bool _onStylusPress(int x, int y);
	bool onStylusMove(int x, int y);

private:
	void pushCurrentPositionIntoStack();
	void replaceCurrentPositionInStack();

	void preparePaintInfo();

	bool getHyperlinkId(const ZLTextElementArea &area, std::string &id, bool &isExternal) const;

	shared_ptr<PositionIndicator> createPositionIndicator();

private:
	class PositionIndicatorWithLabels : public PositionIndicator {

	public:
		PositionIndicatorWithLabels(BookTextView &bookTextView);

	private:
		void draw();
	};

	friend class BookTextView::PositionIndicatorWithLabels;

private:
	shared_ptr<ZLTextModel> myContentsModel;

	typedef std::pair<int,int> Position;
	typedef std::deque<Position> PositionStack;
	PositionStack myPositionStack;
	unsigned int myCurrentPointInStack;
	unsigned int myMaxStackSize;

	bool myLockUndoStackChanges;
};

inline void BookTextView::preparePaintInfo() {
	ZLTextView::preparePaintInfo();
	saveState();
}

#endif /* __BOOKTEXTVIEW_H__ */
