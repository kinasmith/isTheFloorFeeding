var express = require('express'); //,
//  Gpio = require('onoff').Gpio,
//  led = new Gpio(17, 'out'),
//  button = new Gpio(27, 'in', 'both');

var app = express();
app.listen(8080);

var foodState = 1, // 0: food == false, 1: food == true
    foodType = 2, // 0: neutral, 1: sweet, 2: savory
    foodAmount = 4; // map(food amount, small, great, 0, 4)

console.log("server started @ 8080");
console.log("please press button");

function sendData(request) {
    request.respond(latestData);
}
/*
button.watch(function(err, value) {
    if (err) throw err;
    console.log(value);
    led.writeSync(value);
    foodBoolean = value;
});
*/
app.get('/', function(req, res) {
    response.sendFile(__dirname + '/public/index.html')
    console.log("sent index.html");
});

app.get('/food', function(req, res) {
    response.send({
        state: foodState
    });
});
app.get('/food/:state', function(req, res) {
    foodState = req.params.state;
    sendState(res);
});

app.get('/type', function(req, res) {
    response.send({
        type: foodType
    });
});
app.get('/type/:type', function(req, res) {
    foodType = req.params.type;
    sendState(res);
});

app.get('/amount', function(req, res) {
    response.send({
        amount: foodAmount
    });

});
app.get('/amount/:amount', function(req, res) {
    foodAmount = req.params.amount;
    sendState(res);
});

function sendState(data) {
    data.send({
        state: foodState,
        type: foodType,
        amount: foodAmount
    });
}