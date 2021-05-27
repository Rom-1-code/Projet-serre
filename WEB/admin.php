<?php

class admin
{

    private $_idAdmin;
    private $_nom;
    private $_mdp;
    private $_mail;
    private $_bdd;
    public function __construct($bdd)
    {
    
       
        $this->_bdd=$bdd;
    }
  

    public function connexion($nom, $mdp)
    {
        $req = "SELECT * FROM `Admin` WHERE Nom ='" . $nom . "' AND Mdp = '" . $mdp . "'";
        $request = $this->_bdd->query($req);
        

        if ($userinfo = $request->fetch()) {
            $_SESSION['Nom'] = $userinfo['Nom'];
            $_SESSION['id'] = $userinfo['id_Admin'];

            header("Location: Seuil.php");
            die();
        } else {

            echo "Identifiant ou mot de passe incorrect ! ";
        }
    }
}
