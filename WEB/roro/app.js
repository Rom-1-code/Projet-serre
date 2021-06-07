const express = require('express');
const app = express();
var mysql = require('mysql');
var fs = require('fs');
app.set('view engine', 'jade');
app.set("views", "views");
const Capteur = require("./Capteur");
var http = require('http');
/*app.use((req, res) => {
    res.json('Votre requête a bien été reçue !');
});*/

function recupTemp() {
    let valeurt = capteurT.GetValue();
    let valeurh = capteurH.GetValue();
    io.sockets.emit('ValHumidAir', valeurh);
    io.sockets.emit('valTemp', valeurt);
}

var capteurT = new Capteur('tempInt');
var capteurH = new Capteur('humidAir');


/*
app.get('/test', function(req, res) {

    con.query("SELECT * FROM ValeurNum", function(err, result) {
        if (err) throw err;
        MaVariable = result[0].Date;
        var results = [];
        result.forEach(element => {

            console.log(element.Date);
            element.Date + " - ";
            console.log(JSON.stringify(element));

            console.log(element.Id_Valeur);
            console.log(element.Température_Int);
            console.log(element.Température_Ext);
            console.log(element.HumiditéTerre);
            console.log(element.Etat);
            results.push(element);
        });
        console.log(MaVariable);
        res.render('index', {
            title: MaVariable,
            toto: "coucou",
            Value: JSON.stringify(results)
        });

    });



})
module.exports = app;*/