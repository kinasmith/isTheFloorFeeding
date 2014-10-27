var servi = require("servi"),
  Gpio = require('onoff').Gpio, 
  led = new Gpio(17, 'out'), 
  button = new Gpio(27, 'in', 'both');

var latestData = 0;

var app = new servi(false);
app.port(8080);
app.serveFiles("public");
app.route('/data', sendData);
app.start();

console.log("server is running");
console.log("please press button");

function sendData(request) {   
 request.respond(latestData);
}

button.watch(function(err, value) {
  if(err) throw err;
  console.log(value);
  led.writeSync(value);
  latestData = value;
});

