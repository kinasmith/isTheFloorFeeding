var gpio = require("gpio");
var gpio22, gpio4, intervalTimer;

gpio22 = gpio.export(22, {
  ready: function() {
    console.log("22 ready");
    intervalTimer = setInterval(function() {
      gpio22.set();
      console.log("22 high");
      setTimeout(function() {
        console.log("22 Reset");
        gpio22.reset(); 
      }, 500);
    }, 1000);
  }
});

gpio4 = gpio.export(4, {
  ready: function() {
    gpio22.on("change", function(val) {
      gpio4.set(1-val);
    });
  }
});

setTimeout(function() {
  clearInterval(intervalTimer);
  gpio22.removeAllListeners('change');
  gpio22.reset();
  gpio22.unexport();

  gpio4.reset();
  gpio4.unexport(function() {
    process.exit();
  });
}, 1000)
