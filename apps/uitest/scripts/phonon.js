var dmz =
   { module: require('dmz/runtime/module')
   , ui:
      { consts: require('dmz/ui/consts')
      , layout: require("dmz/ui/layout")
      , loader: require('dmz/ui/uiLoader')
      , phonon: require("dmz/ui/phonon")
      , widget: require("dmz/ui/widget")
      }
   }
   , _main
   , _exports = {}
   , puts = require('sys').puts
   , video = dmz.ui.phonon.createVideoPlayer()
   , source = dmz.ui.phonon.createMediaObject("http://www.chds.us/media/viewpoints/mov/chds_viewpoints%2029_rodrigo_gomez.mov")
   ;

puts("Script: " + self.name);

dmz.ui.phonon.createPath(source, video);

dmz.module.subscribe(self, "main", function (Mode, module) {

   if (Mode === dmz.module.Activate) {

      _main = module
      _main.addPage (self.name, video);
      source.play();
   }
});

puts("Done.");
