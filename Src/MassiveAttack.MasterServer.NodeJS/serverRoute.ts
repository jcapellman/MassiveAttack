import { Router, Request, Response, NextFunction } from "express";
import * as br from "./BaseRoute";
import * as mq from "./MessageQueue";
import { Config } from "./config";

export class ServerRoute extends br.BaseRoute {    
    constructor() {
        super("server");        
    }

    getServerList(req, res) {
        super.getRedisFactory().hget("ServerList", "name", (err, reply) => res.json({ message: reply }));
    }

    // Add Server List to processing list
    addToServerList(req:Request, res:Response) {
        const obj = req.body;

        const messq = new mq.MessageQueue(Config.KAFKA_HOST);

        messq.addMessage(obj);
    }

    buildRoutes() {
        // Get Server List
        super.addGetRoute("", this.getServerList);        

        // Add to Server List
        super.addPostRoute("", this.addToServerList);
    }
}