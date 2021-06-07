//const app1 = require('./app');
const { Sequelize } = require('sequelize');
const bodyParser = require('body-parser')
const express = require('express')
const mysql = require('mysql');
const app = express()


// ajout de socket.io
const server = require('http').Server(app)
const io = require('socket.io')(server)

var Chart = require('chart.js');



app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))
app.use(express.static('public'))
app.get('/', function(req, res) {
    res.sendFile('index.html', { root: __dirname })
})

app.get('/json', function(req, res) {
    res.status(200).json({ "message": "ok" })
})

const sequelize = new Sequelize("Projet_Serre", "root", "root", {
    dialect: "mysql",
    host: "192.168.65.216"
});

io.on('connection', (socket) => {
    console.log(`Connecté au client ${socket.id}`)
    try {
        sequelize.authenticate();
        console.log('Connecté à la base de données MySQL!');
        sequelize.query("SELECT * FROM ValeurNum").then(([results, metadata]) => {

            io.emit('news', results[0]);
            for (var i = 0; i < results.length; i++) {
                console.log("Température intérieur " + i + " : " + results[i].Temperature_Int);
                console.log("Température extérieur " + i + " : " + results[i].Temperature_Ext);
                console.log("humidite terre " + i + " : " + results[i].HumiditeTerre);
                console.log("humidite air " + i + " : " + results[i].HumiditeAir);
                console.log("Date : " + i + " : " + results[i].Date);
            }

        })
    } catch (error) {
        console.error('Impossible de se connecter, erreur suivante :', error);
    }
})

server.listen(8080, function() {
    console.log('Votre app est disponible sur localhost:8080 !')
})