var net = require('net');


const port = 2590;
const host = '192.168.64.183';

// création d'un nouveau client
const client = new net.Socket();
// requette de connexion au serveur
client.connect({ port: port, host: host }),

    function() {
        console.log('TCP connection established with the server.');
        client.write('Hello, server.');
    };

client.setEncoding('utf8');
//afficher les données envoyer par le serveur
client.on('data', function(data) {
    console.log('Data from server:' + data);
});
// message de fin de connexion
setTimeout(function() {
    client.end('Bye bye server');
}, 10000);