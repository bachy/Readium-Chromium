// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_MESSAGE_POPUP_BUBBLE_H_
#define UI_MESSAGE_CENTER_MESSAGE_POPUP_BUBBLE_H_

#include "base/timer.h"
#include "ui/message_center/message_bubble_base.h"
#include "ui/message_center/message_center_export.h"
#include "ui/message_center/notification_list.h"

namespace message_center {

class PopupBubbleContentsView;

// Bubble for popup notifications.
class MESSAGE_CENTER_EXPORT MessagePopupBubble : public MessageBubbleBase {
 public:
  explicit MessagePopupBubble(NotificationList::Delegate* delegate);

  virtual ~MessagePopupBubble();

  void StartAutoCloseTimer();
  void StopAutoCloseTimer();

  // Overridden from MessageBubbleBase.
  virtual views::TrayBubbleView::InitParams GetInitParams(
      views::TrayBubbleView::AnchorAlignment anchor_alignment) OVERRIDE;
  virtual void InitializeContents(views::TrayBubbleView* bubble_view) OVERRIDE;
  virtual void OnBubbleViewDestroyed() OVERRIDE;
  virtual void UpdateBubbleView() OVERRIDE;
  virtual void OnMouseEnteredView() OVERRIDE;
  virtual void OnMouseExitedView() OVERRIDE;

   size_t NumMessageViewsForTest() const;

 private:
  void OnAutoClose();

  base::OneShotTimer<MessagePopupBubble> autoclose_;
  PopupBubbleContentsView* contents_view_;
  size_t num_popups_;

  DISALLOW_COPY_AND_ASSIGN(MessagePopupBubble);
};

}  // namespace message_center

#endif // UI_MESSAGE_CENTER_MESSAGE_POPUP_BUBBLE_H_
