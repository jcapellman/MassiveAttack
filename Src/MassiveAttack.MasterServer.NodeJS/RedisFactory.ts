var redis = require('redis');

export class RedisFactory {
    private client: any;
    private subscriber: any;

    constructor(redisHostName: string, redisPort: number) {               
        this.client = redis.createClient(redisPort, redisHostName);
        
        this.client.on("error", function (err) {
            console.log("redisdb: " + err);
        });

        this.client.on("connect", function () {
            console.log('Successfully connected to Redis DB @ ' + redisHostName + ':' + redisPort);
        });           

        this.subscriber.on("message", function (channel, message) {
            console.log(message);
        });
    }
    
    rClient() {
        return this.client;
    }
}