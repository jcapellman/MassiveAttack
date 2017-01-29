import { Router, Request, Response, NextFunction } from 'express';
import br = require('./BaseRoute');

export class ServerRoute extends br.BaseRoute {    
    constructor() {
        super('server');        
    }

    getServerList(req, res) {
        super.getRedisFactory().get('ServerList', function (err, reply) {
            return res.json({ message: reply });
        });
    }

    addToServerList(req:Request, res:Response) {
        var obj = req.body;
        
        super.getRedisFactory().set('ServerList', obj, function (err, reply) {
            return res.json({ message: reply });
        });
    }

    buildRoutes() {
        // Get Server List
        super.addGetRoute('', this.getServerList);        

        // Add to Server List
        super.addPostRoute('', this.addToServerList);
    }
}