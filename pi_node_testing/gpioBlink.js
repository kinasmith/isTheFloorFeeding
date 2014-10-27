var gpio = require("pi-gpio");

var intervalId;
var durationId;
var gpioPin = 21;
var gpioReadPin = 23;

gpio.open(gpioPin, "output", function(err) {
  var on = 1;
  console.log('GPIO pin '+gpioPin+' is open. Toggling LED every 100mS for 10s');
  intervalId = setInterval( function() {
    gpio.write(gpioPin, on, function() {
      on = (on + 1) % 2;
    });
  }, 100);
});


gpio.open(gpioReadPin, "input", function(err) {
  console.log('GPIO pin ' +gpioReadPin+ ' is Open, Reading');
  var ee = new process.EventEmitter(),
  buttonState;

  ee.on('stateChange', function(previousValue, value) {
    console.log('button state changed from', previousValue, 'to', value);
  });

  setInterval(function(){
    gpio.read(gpioReadPin, function(err, value) {
      if(err){
       ee.emit('error', err);
      } else {
        if(buttonState !== value) {
          var previousState = buttonState;
          buttonState = value;
          ee.emit('stateChange', previousState, value);
        }
      }
    })
  }, 50);
});

durationId = setTimeout( function() {
  clearInterval(intervalId);
  clearTimeout(durationId);
  console.log('10 seconds blinking completed');
  gpio.write(gpioPin, 0, function() {
    gpio.close(gpioPin);
    process.exit(0);
  });
}, 10000);
