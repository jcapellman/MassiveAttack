var bodyParser = require('body-parser');

var express = require('express');
var app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

import { Config } from "./config";

// Add Server Routes
import { ServerRoute } from "./ServerRoute";
let serverRoute = new ServerRoute();
app.use(serverRoute.GetRoutes());

app.listen(Config.HTTP_SERVER_PORT);

console.log('Master Game REST Server running on port ' + Config.HTTP_SERVER_PORT);