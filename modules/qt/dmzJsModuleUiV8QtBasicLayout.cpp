#include "dmzJsModuleUiV8QtBasic.h"
#include <dmzJsV8UtilConvert.h>
#include <QtGui/QBoxLayout>


dmz::V8Value
dmz::JsModuleUiV8QtBasic::create_v8_layout (QLayout *value) {

   v8::Context::Scope cscope (_state.context);
   v8::HandleScope scope;

   V8Value result = v8::Undefined ();

   if (value) {

      V8Object obj;

      if (value->inherits ("QHBoxLayout")) {

         if (!_hBoxLayoutCtor.IsEmpty ()) {

            obj = _hBoxLayoutCtor->NewInstance ();
         }
      }
      else if (value->inherits ("QVBoxLayout")) {

         if (!_vBoxLayoutCtor.IsEmpty ()) {

            obj = _vBoxLayoutCtor->NewInstance ();
         }
      }
      else if (value->inherits ("QBoxLayout")) {

         if (!_boxLayoutCtor.IsEmpty ()) {

            obj = _boxLayoutCtor->NewInstance ();
         }
      }
      else if (value->inherits ("QLayout")) {

         if (!_layoutCtor.IsEmpty ()) {

            obj = _layoutCtor->NewInstance ();
         }
      }

      if (!obj.IsEmpty ()) {

         obj->SetInternalField (0, v8::External::Wrap ((void *)value));
         result = obj;
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_layout_index_of (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         QWidget *qw = self->_to_qt_widget (Args[0]);

         if (qw) {

            result = v8::Number::New (layout->indexOf (qw));
         }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_layout_enabled (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         if (Args.Length () > 0) {

            bool val = v8_to_boolean (Args[0]);
            layout->setEnabled (val);
         }
         else {

            result = v8::Boolean::New (layout->isEnabled ());
         }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_layout_at (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         if (Args.Length () > 0) {

            QWidget *qw = layout->itemAt (v8_to_int32 (Args[0]))->widget ();

            if (qw) {

               result = self->create_v8_widget (qw);
            }
         }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_layout_count (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         result = v8::Number::New (layout->count ());
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_layout_parent (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         QObject *obj = layout->parent ();
         QWidget *parent_widget = qobject_cast<QWidget *>(obj);
         QLayout *parent_layout = qobject_cast<QLayout *>(obj);

         if (parent_widget) { result = self->create_v8_widget (parent_widget); }
         else if (parent_layout) { result = self->create_v8_layout (parent_layout); }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_layout_parent_widget (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         QWidget *widget = layout->parentWidget ();
         if (widget) {

            result = self->create_v8_widget (widget);
         }
      }
   }

   return scope.Close (result);
}


void
dmz::JsModuleUiV8QtBasic::_init_layout () {

   v8::HandleScope scope;

   _layoutTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());

   V8ObjectTemplate instance = _layoutTemp->InstanceTemplate ();
   instance->SetInternalFieldCount (1);

   V8ObjectTemplate proto = _layoutTemp->PrototypeTemplate ();
   proto->Set ("indexOf", v8::FunctionTemplate::New (_layout_index_of, _self));
   proto->Set ("enabled", v8::FunctionTemplate::New (_layout_enabled, _self));
   proto->Set ("at", v8::FunctionTemplate::New (_layout_at, _self));
   proto->Set ("count", v8::FunctionTemplate::New (_layout_count, _self));
   proto->Set ("parent", v8::FunctionTemplate::New (_layout_parent, _self));
   proto->Set ("parentWidget", v8::FunctionTemplate::New (_layout_parent_widget, _self));
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_box_layout_add_layout (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         QBoxLayout *bl = qobject_cast<QBoxLayout *>(layout);
         if (bl) {

            if (Args.Length () > 0) {

               QLayout *ql = self->_to_qt_layout (Args[0]);
               if (ql) {

                  bl->addLayout (ql);
               }
            }
         }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_box_layout_add_stretch (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         QBoxLayout *bl = qobject_cast<QBoxLayout *>(layout);
         if (bl) {

            if (Args.Length () > 0) {

               bl->addStretch (v8_to_int32 (Args[0]));
            }
         }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_box_layout_add_widget (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         QBoxLayout *bl = qobject_cast<QBoxLayout *>(layout);
         if (bl) {

            if (Args.Length () > 0) {

               QWidget *widget = self->_to_qt_widget (Args[0]);
               if (widget) {

                  bl->addWidget (widget);
               }
            }
         }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_box_layout_direction (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QLayout *layout = self->_to_qt_layout (Args.This ());

      if (layout) {

         QBoxLayout *bl = qobject_cast<QBoxLayout *>(layout);
         if (bl) {

            if (Args.Length () > 0) {

               int direction = v8_to_int32 (Args[0]);
               if ((direction < 0) || (direction > 3)) {

                  direction = 0;
               }
               bl->setDirection ((QBoxLayout::Direction)direction);
            }
         }
      }
   }

   return scope.Close (result);
}


void
dmz::JsModuleUiV8QtBasic::_init_box_layout () {

   v8::HandleScope scope;

   _boxLayoutTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());
   _boxLayoutTemp->Inherit (_layoutTemp);

   V8ObjectTemplate instance = _boxLayoutTemp->InstanceTemplate ();
   instance->SetInternalFieldCount (1);

   V8ObjectTemplate proto = _boxLayoutTemp->PrototypeTemplate ();
   proto->Set ("addLayout", v8::FunctionTemplate::New (_box_layout_add_layout, _self));
   proto->Set ("addStretch", v8::FunctionTemplate::New (_box_layout_add_stretch, _self));
   proto->Set ("addWidget", v8::FunctionTemplate::New (_box_layout_add_widget, _self));
   proto->Set ("direction", v8::FunctionTemplate::New (_box_layout_direction, _self));

   _layoutApi.add_constant ("LeftToRight", (UInt32)QBoxLayout::LeftToRight);
   _layoutApi.add_constant ("RightToLeft", (UInt32)QBoxLayout::RightToLeft);
   _layoutApi.add_constant ("TopToBottom", (UInt32)QBoxLayout::TopToBottom);
   _layoutApi.add_constant ("BottomToTop", (UInt32)QBoxLayout::BottomToTop);
   _layoutApi.add_function ("createBoxLayout", _create_box_layout, _self);
}

void
dmz::JsModuleUiV8QtBasic::_init_hbox_layout () {

   v8::HandleScope scope;

   _hBoxLayoutTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());
   _hBoxLayoutTemp->Inherit (_boxLayoutTemp);

   V8ObjectTemplate instance = _hBoxLayoutTemp->InstanceTemplate ();
   instance->SetInternalFieldCount (1);

   _layoutApi.add_function ("createHBoxLayout", _create_hbox_layout, _self);
}

void
dmz::JsModuleUiV8QtBasic::_init_vbox_layout () {

   v8::HandleScope scope;

   _vBoxLayoutTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());
   _vBoxLayoutTemp->Inherit (_boxLayoutTemp);

   V8ObjectTemplate instance = _vBoxLayoutTemp->InstanceTemplate ();
   instance->SetInternalFieldCount (1);

   _layoutApi.add_function ("createVBoxLayout", _create_vbox_layout, _self);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_create_box_layout (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QWidget *parent (0);
      int direction = 0;
      if (Args.Length () > 0) {
         direction = v8_to_int32 (Args[0]);
         if ((direction < 0) || (direction > 3)) {

            direction = 0;
         }
      }

      if (Args.Length () > 1) {

         parent = self->_to_qt_widget (Args[1]);
      }

      QBoxLayout *layout = new QBoxLayout((QBoxLayout::Direction)direction, parent);
      result = self->create_v8_layout (layout);
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_create_hbox_layout (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QWidget *parent = self->_to_qt_widget (Args[0]);

      QHBoxLayout *layout = new QHBoxLayout(parent);
      result = self->create_v8_layout (layout);
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_create_vbox_layout (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QWidget *parent = self->_to_qt_widget (Args[0]);

      QVBoxLayout *layout = new QVBoxLayout(parent);
      result = self->create_v8_layout (layout);
   }

   return scope.Close (result);
}
