var net = require('net');


const port = 2590;
const host = '192.168.64.183';

// création d'un nouveau client
const client = new net.Socket();
// requette de connexion au serveur
client.connect({ port: port, host: host }),
    function() {
        // If there is no error, the server has accepted the request and created a new 
        // socket dedicated to us.
        console.log('TCP connection established with the server.');

        // The client can now send data to the server by writing to its socket.
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