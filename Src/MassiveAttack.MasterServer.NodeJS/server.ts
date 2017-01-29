var express = require('express');
var app = express();

var config = require('./config');

app.use(require('./serverRoute'));

app.listen(config.HTTP_SERVER_PORT);