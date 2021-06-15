var net = require('net');

let server1 = net.createServer(connection => {
    // run all of this when a client connects
    console.log("new connection");

    connection.on("data", data => {
        // run this when data is received
        console.log(data.toString()); // prints the data
    });
});
server1.listen(3000, () => {
    console.log("waiting for a connection"); // prints on start
});