<?php

class seuil 
{

    private $temperature_int;
    private $temperature_ext;
    private $Humidité_air;
    private $Humidite_Tere;
    private $_bdd;
    public function __construct($bdd)
    {

        
        $this->_bdd=$bdd;
    }
    public function envoie($temperature_int, $temperature_ext, $Humidité_air, $Humidite_Tere)
    {  
        $req="INSERT INTO `Seuil` (`Temperature_int`, `Temperature_Ext`, `Humidite_Air`, `Humidite_Tere`) VALUES ('$temperature_int', '$temperature_ext', '$Humidité_air', '$Humidite_Tere');" ;
        $request = $this->_bdd->query($req);
        echo $req;

        if ($seuilinfo=$request->fetch()){
            $_SESSION['temperature_int'] = $seuilinfo['temperature_int'];
            $_SESSION['temperature_ext'] = $seuilinfo['temperature_ext'];
            $_SESSION['Humidité_air'] = $seuilinfo['Humidité_air'];
            $_SESSION['Humidite_Tere'] = $seuilinfo['Humidite_Tere'];
                                        }


             else {

            echo "marche pas ! ";
        }
    }
}