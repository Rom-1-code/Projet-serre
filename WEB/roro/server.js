const app1 = require('./app');
const express = require('express')
const bodyParser = require('body-parser')
const app = express()
const mysql = require('mysql');
var notes = [];
var net = require('net');
var Chart = require('chart.js');
// ajout de socket.io
const server = require('http').Server(app)
const io = require('socket.io')(server)
    // ----------------TCP-------------
let server1 = net.createServer(connection => {
    //nouvelle connexion à la connexion du client
    console.log("new connection");

    connection.on("data", data => {
        //fonction qui permet d'afficher les données reçu dans la console
        console.log(data.toString());
    });
});
server1.listen(3000, () => {
    console.log("waiting for a connection");
});

var db = mysql.createConnection({
    host: "192.168.65.216",
    user: "root",
    password: "root",
    database: "Projet_Serre"
})

db.connect(function(err) {
    if (err) console.log(err);
    console.log("Connexion à la BDD OK");
})

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))
app.use(express.static('public'))
app.get('/', function(req, res) {
    res.sendFile('index.html', { root: __dirname })
})

app.get('/json', function(req, res) {
    res.status(200).json({ "message": "ok" })
})

// établissement de la connexion
io.on('connection', (socket) => {
    console.log(`Connecté au client ${socket.id}`)
        //io.emit('news', 'Voici un nouvel élément envoyé par le serveur and value random : ' + Math.random());
    db.query("SELECT * FROM ValeurNum")
        .on('result', function(data) {
            notes.push(data);
            io.emit('news', notes[0]);
            for (var i = 0; i < notes.length; i++) {
                console.log("Température intérieur " + i + " : " + notes[i].Temperature_Int);
                console.log("Température extérieur " + i + " : " + notes[i].Temperature_Ext);
                console.log("humidite terre " + i + " : " + notes[i].HumiditeTerre);
                console.log("humidite air " + i + " : " + notes[i].HumiditeAir);
                console.log("Date : " + i + " : " + notes[i].Date);
            }
        })
})

// on change app par server
server.listen(8080, function() {
    console.log('Votre app est disponible sur localhost:8080 !')
})