import { RedisFactory } from "./RedisFactory";
import { Config } from "./config";

export abstract class BaseRoute {
        private rootpath: string;
        private router: any;
        private redisFactory: RedisFactory;

        constructor(rootpath: string) {            
            this.rootpath = Config.API_PREFIX + rootpath;

            const express = require('express');
            this.router = express.Router();            
        }

        abstract buildRoutes(): void;

        getRoutes() {
            this.buildRoutes();

            return this.router;
        }

        getRedisFactory() {
            let redisFactory = new RedisFactory(Config.REDIS_DATABASE_HOSTNAME, Config.REDIS_DATABASE_PORT);
            
            return redisFactory.rClient();
        }

        addGetRoute(routepath, method) {            
            this.router.get(this.rootpath + routepath, method);
        }

        addPostRoute(routepath, method) {
            this.router.post(this.rootpath + routepath, method);
        }
    }
