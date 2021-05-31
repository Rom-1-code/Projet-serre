const fetch = require("./node_modules/node-fetch");

module.exports = class Capteur {

    constructor(IdCapteur) //constructeur general
        {
            this.ID = IdCapteur;

            if (this.ID == 'humidSol') {
                this.humid = this.MoyenneHumidSol(callback);
            }

            this.GetValue();
        }

    GetValue() {
        var that = this;

        var data = function(json) {
            switch (that.ID) {
                case 'tempInt':
                    that.valeur = json.Monitor.S.S1.item1.value;
                    break;
                case 'tempExt':
                    that.valeur = json.Monitor.S.S1.item1.value;
                    break;
                case 'humidAir':
                    that.valeur = json.Monitor.S.S1.item2.value;
                    break;
                case 'humidSol1':
                    that.valeur = json.Monitor.S.S1.item1.value;
                    break;
                case 'humidSol2':
                    that.valeur = json.Monitor.S.S1.item1.value;
                    break;
                case 'humidSol3':
                    that.valeur = json.Monitor.S.S1.item1.value;
                    break;
            }
        }

        fetch('http://192.168.65.8/status.json?a=admin:admin', {
                method: 'GET'
            })
            .then(reponse => reponse.json())
            .then(json => data(json));

        return this.valeur;
    }










}