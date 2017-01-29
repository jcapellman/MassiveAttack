var config = require('./config');
var express = require('express');
var redisdb = require('./redisdb');

var rootpath = config.API_PREFIX + 'server';

var router = express.Router();

router.get(rootpath, function (req, res) {
    redisdb.get('test', function (err, reply) {
        return res.json({ message: reply });
    });
});

module.exports = router;