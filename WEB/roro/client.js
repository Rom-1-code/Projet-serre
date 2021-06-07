var net = require('net');


const port = 2525;
const host = '192.168.65.62';

// Create a new TCP client.
const client = new net.Socket();
// Send a connection request to the server.
client.connect({ port: port, host: host }),
    function() {
        // If there is no error, the server has accepted the request and created a new 
        // socket dedicated to us.
        console.log('TCP connection established with the server.');

        // The client can now send data to the server by writing to its socket.
        client.write('Hello, server.');
    };

client.setEncoding('utf8');

client.on('data', function(data) {
    console.log('Data from server:' + data);
});

setTimeout(function() {
    client.end('Bye bye server');
}, 10000);