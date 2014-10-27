var express = require('express'),
  app = express();

app.listen(8080);
console.log('Server is listening to port 8080');

function sendIndexPage(request, response) {
  response.sendfile(__dirname + '/public/index.html');
}


function respondToClient(req, res) {
	console.log("request from: ");
	console.log(req.connection.remoteAddress);
	console.log("URL:");
	console.log(req.url);
	
	res.writeHead(200, {"Content-Type": "text/html"});
	res.write("Hello: " + req.connection.remoteAddress);
	res.end();
};
