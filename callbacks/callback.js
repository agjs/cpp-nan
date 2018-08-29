const callback = require('./build/Release/callback_addon');
var callme = function(a) {
  console.log(a);
};
callback.foo(callme, 5);
