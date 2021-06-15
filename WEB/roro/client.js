var net = require('net');


const port = 2525;
const host = '192.168.65.62';

// Create a new TCP client.
const client = new net.Socket();
// Send a connection request to the server.
client.connect({ port: port, host: host }),

    function() {
        console.log('TCP connection established with the server.');
        client.write('Hello, server.');
    };

client.setEncoding('utf8');

client.on('data', function(data) {
    console.log('Data from server:' + data);
});

setTimeout(function() {
    client.end('Bye bye server');
}, 10000);