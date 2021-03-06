var dmz =
       { module: require('dmz/runtime/module')
       , ui:
          { consts: require('dmz/ui/consts')
          , loader: require('dmz/ui/uiLoader')
          , widget: require("dmz/ui/widget")
          }
       , timer: require('dmz/runtime/time')
       }
   , _main
   , _exports = {}
   , puts = require('sys').puts
   , form = dmz.ui.loader.load("./scripts/ToolBoxForm.ui")
  , pbar = dmz.ui.loader.load("./scripts/ProgressBarForm.ui")
  , widget = dmz.ui.loader.load("./scripts/SliderForm.ui")
  , cb = dmz.ui.loader.load("./scripts/CheckBoxForm.ui")
  , label = dmz.ui.loader.load("./scripts/LabelForm.ui")
  , combo = dmz.ui.loader.load("./scripts/comboBoxForm.ui")
  , tb
  , at
  ;

puts("Script: " + self.name);

form.show();

tb = form.lookup("toolBox");

form.observe(self, "add", "clicked", function () {

   tb.addItem(label, "label");
   tb.addItem(cb, "cb");
   tb.addItem(pbar, "pbar");
   tb.addItem(combo, "combo");
   tb.insertItem(widget, "slider", 1);
});

puts("item text:",tb.itemText(1));

tb.observe(self, "currentChanged", function (val) {

   puts("tb.observe");
   puts("changed to:", val);
   puts("tT:", tb.itemText(val), "cI:", tb.currentIndex());
   puts("at:", tb.currentWidget());
   puts(tb.itemText(tb.indexOf(tb.currentWidget())));
});

puts("tab count:", tb.count());
tb.removeItem(2);
puts("tab count2:", tb.count());
at = tb.widget(1);
puts("cw:", tb.currentWidget());
tb.currentWidget(cb);
puts("at:", at);
tb.currentWidget(at);
puts("finished cW");
tb.currentIndex(tb.indexOf(tb.widget(2)));

dmz.module.subscribe(self, "main", function (Mode, module) {

   if (Mode === dmz.module.Activate) {

      _main = module
      _main.addPage (self.name, form);
   }
});

puts("Done.");
