export class MessageQueue {
    private readonly producer: any;

    constructor(kafkaHost:string) {
        var kafka = require('kafka-node'),
            Producer = kafka.Producer,
            client = new kafka.Client(kafkaHost);

        this.producer = new Producer(client);

        this.producer.on('ready', () => {
            console.log("Kafka Connected");
        });
    }

    addMessage(request: string) {
        this.producer.send(request,
            (err, data) => {
                console.log(data);
            });
    }
}