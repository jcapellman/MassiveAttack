export class MessageQueue {
    private readonly connection: any;

    constructor(amqpHost:string) {
        const amqp = require("amqp");

        this.connection = amqp.createConnection({ host: amqpHost });
        
        this.connection.on("error", e => {
            console.log("Error from amqp: ", e);
        });
        
        this.connection.on("ready", () => {
            console.log("Connected to RabbitMQ");
        });
    }

    addMessage(messege:string) {
        this.connection.queue(messege, q => {
            q.bind("#");

            q.subscribe(message => {
                console.log(message);
            });
        });
    }
}