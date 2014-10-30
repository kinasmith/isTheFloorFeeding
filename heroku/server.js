var express = require('express'); //load in Express module

var app = express(); //initialize
//app.listen(8080); //start server on port 8080
app.set('port', (process.env.PORT || 5000))
app.use(express.static(__dirname + '/public'))

app.listen(app.get('port'), function() {
    console.log("Node app is running at localhost:" + app.get('port'))
})


var foodState, foodType, foodAmount; //create variable for data storage

//console.log("server started @ 8080"); //confirm server has started

//respond to root directory by sending out index.html page
app.get('/', function(req, res) {
    res.sendFile(__dirname + '/public/index.html')
    //console.log("sent index.html");
});

//for each route, respond with a JSON string with that routes current data
app.get('/food', function(req, res) {
    res.send({
        state: foodState
    });
});
//Set the value in that route, and respond with all of the current stored data
app.get('/food/:state', function(req, res) {
    foodState = req.params.state;
    sendState(res);
});

app.get('/type', function(req, res) {
    res.send({
        type: foodType
    });
});
app.get('/type/:type', function(req, res) {
    foodType = req.params.type;
    sendState(res);
});

app.get('/amount', function(req, res) {
    res.send({
        amount: foodAmount
    });

});
app.get('/amount/:amount', function(req, res) {
    foodAmount = req.params.amount;
    sendState(res);
});
//Send out all the data. (this is redundant, I know.)
app.get('/status', function(req, res) {
    sendState(res);
})

//sends the chunk of JSON that includes the state of all the stored data
function sendState(data) {
    data.send({
        state: foodState,
        type: foodType,
        amount: foodAmount
    });
}