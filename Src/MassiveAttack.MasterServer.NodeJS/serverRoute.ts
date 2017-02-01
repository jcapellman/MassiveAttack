import { Router, Request, Response, NextFunction } from 'express';
import br = require('./BaseRoute');
import mq = require('./MessageQueue');
import { Config } from './config';

export class ServerRoute extends br.BaseRoute {    
    constructor() {
        super('server');        
    }

    getServerList(req, res) {
        super.getRedisFactory().get('ServerList', function (err, reply) {
            return res.json({ message: reply });
        });
    }

    // Add Server List to processing list
    addToServerList(req:Request, res:Response) {
        var obj = req.body;

        var messq = new mq.MessageQueue(Config.RABBITMQ_HOST);

        messq.addMessage(obj);
    }

    buildRoutes() {
        // Get Server List
        super.addGetRoute('', this.getServerList);        

        // Add to Server List
        super.addPostRoute('', this.addToServerList);
    }
}