var express = require('express');
var app = express();
app.listen(8080);

var foodBoolean = 1, // 0: food == false, 1: food == true
    foodType = 2, // 0: neutral, 1: sweet, 2: savory
    foodAmount = 4; // map(food amount, small, great, 0, 4)

console.log("server started @ 8080");

app.get('/', function(request, response) {
    response.sendFile(__dirname + '/public/index.html')
    console.log("sent index.html");
});

app.get('/food', function(request, response) {
    response.sendStatus(foodBoolean);
});

app.get('/type', function(request, response) {
    response.sendStatus(foodType);
});

app.get('/amount', function(request, response) {
    response.sendStatus(foodAmount);
});