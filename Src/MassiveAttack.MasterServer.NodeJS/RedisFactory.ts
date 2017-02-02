var redis = require("redis");

export class RedisFactory {
    private readonly client: any;
    
    constructor(redisHostName: string, redisPort: number) {               
        this.client = redis.createClient(redisPort, redisHostName);
        
        this.client.on("error", err => {
            console.log(`redisdb: ${err}`);
        });

        this.client.on("connect", () => {
            console.log(`Successfully connected to Redis DB @ ${redisHostName}:${redisPort}`);
        });           
    }
    
    rClient() {
        return this.client;
    }
}