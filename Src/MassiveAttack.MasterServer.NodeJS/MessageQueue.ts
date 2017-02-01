export class MessageQueue {
    private connection: any;

    constructor(amqpHost:string) {
        var amqp = require('amqp');

        this.connection = amqp.createConnection({ host: amqpHost });
        
        this.connection.on('error', function (e) {
            console.log("Error from amqp: ", e);
        });
        
        this.connection.on('ready', function () {
            console.log("Connected to RabbitMQ");
        });
    }

    public addMessage(messege:string) {
        this.connection.queue(messege, function (q) {
            q.bind('#');

            q.subscribe(function (message) {
                console.log(message);
            });
        });
    }
}