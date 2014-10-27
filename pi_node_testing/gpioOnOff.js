var Gpio = require('onoff').Gpio,
  led = new Gpio(17, 'out'),
  button = new Gpio(27, 'in', 'both');

console.log('please press button');

button.watch(function(err, value) {
  if(err) throw err;
  console.log('button Pressed!, its value was ' + value);
  led.writeSync(value);
//  button.unexport();
});


/*
iv = setInterval(function() {
  led.writeSync(led.readSync() === 0 ? 1 : 0);
  console.log("switch");
}, 200);

setTimeout(function() {
  clearInterval(iv);
  led.writeSync(0);
  led.unexport();
}, 5000);

*/
