var express = require('express'),
    Gpio = require('onoff').Gpio,
    led = new Gpio(17, 'out'),
    button = new Gpio(27, 'in', 'both');

var app = express();
app.listen(8080);

var foodBoolean = 1, // 0: food == false, 1: food == true
    foodType = 2, // 0: neutral, 1: sweet, 2: savory
    foodAmount = 4; // map(food amount, small, great, 0, 4)

console.log("server started @ 8080");
console.log("please press button");

function sendData(request) {
    request.respond(latestData);
}

button.watch(function(err, value) {
    if (err) throw err;
    console.log(value);
    led.writeSync(value);
    foodBoolean = value;
});

app.get('/', function(request, response) {
    response.sendFile(__dirname + '/public/index.html')
    console.log("sent index.html");
});

app.get('/food', function(request, response) {
    response.sendStatus("<b>" + foodBoolean + "</b>");
});

app.get('/type', function(request, response) {
    response.sendStatus(foodType);
});

app.get('/amount', function(request, response) {
    response.sendStatus(foodAmount);
});
