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

    buildRoutes() {
        // Get Server List
        super.addGetRoute('', this.getServerList);        
    }
}