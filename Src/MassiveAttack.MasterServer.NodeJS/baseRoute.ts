import { RedisFactory } from "./RedisFactory";
import { Config } from "./config";

export abstract class BaseRoute {
        _rootpath: string;
        _router: any;
        _redisFactory: RedisFactory;

        constructor(rootpath: string) {            
            this._rootpath = Config.API_PREFIX + rootpath;

            var express = require('express');
            this._router = express.Router();            
        }

        abstract buildRoutes(): void;

        GetRoutes() {
            this.buildRoutes();

            return this._router;
        }

        getRedisFactory() {
            let redisFactory = new RedisFactory(Config.REDIS_DATABASE_HOSTNAME, Config.REDIS_DATABASE_PORT);
            
            return redisFactory.rClient();
        }

        addGetRoute(routepath, method) {            
            this._router.get(this._rootpath + routepath, method);
        }
    }
