var express = require('express'); //load in Express module

var app = express(); //initialize
//app.listen(8080); //start server on port 8080
app.set('port', (process.env.PORT || 5000))
app.use(express.static(__dirname + '/public'))

app.listen(app.get('port'), function() {
    console.log("Node app is running at localhost:" + app.get('port'))
})


var foodState,
    foodType,
    foodAmount; //create variable for data storage

//console.log("server started @ 8080"); //confirm server has started

//respond to root directory by sending out index.html page
app.get('/', function(req, res) {
    res.sendFile(__dirname + '/public/index.html')
    //console.log("sent index.html");
});

//for each route, respond with a JSON string with that routes current data

app.get('/state', function(req, res) { //this should be be /state instead to be consistent with the messaging system.
    res.send({
        state: foodState
    });
});
//Set the value in that route, and respond with all of the current stored data
app.get('/state/:state', function(req, res) {
    foodState = parseInt(req.params.state);
    var json = JSON.stringify({
        state: foodState
    });
    res.send(json);
});

app.get('/type', function(req, res) {
    res.send({
        type: foodType
    });
});
app.get('/type/:type', function(req, res) {
    foodType = parseInt(req.params.type);
    var json = JSON.stringify({
        type: foodType
    });
    res.send(json);
});

app.get('/amount', function(req, res) {
    res.json({
        amount: foodAmount
    });

});
app.get('/amount/:amount', function(req, res) {
    foodAmount = parseInt(req.params.amount);
    var json = JSON.stringify({
        amount: foodAmount
    });
    res.send(json);
});
//Send out all the data. (this is redundant, I know.)
app.get('/status', function(req, res) {
    var json = JSON.stringify({
        state: foodState,
        type: foodType,
        amount: foodAmount
    });
    res.send(json);
})