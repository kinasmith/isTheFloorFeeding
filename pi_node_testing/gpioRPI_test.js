var gpio = require('rpi-gpio');


gpio.on('change', function(channel, value) {
  console.log('Channel' +channel+ ' value is now ' +value);
});
gpio.setup(23, gpio.DIR_IN);




/*
function readInput() {
  gpio.read(23, function(err, value) {
    console.log('The value is ' + value);
  });
}
*/
