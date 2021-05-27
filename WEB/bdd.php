<?php
class bdd
{
    private $_bdd;
    public function __construct()
    {
    }
  
    public function connectbdd()
    {
        try {
            $bdd = new PDO('mysql:host=localhost; dbname=projets serre; charset=utf8', 'root', '');
        } catch (Exception $erreur) {
            echo 'Erreur : ' . $erreur->getMessage();
        }
        $this->_bdd=$bdd;
        return $this->_bdd;
    }

    public function getBdd(){

        return $this->_bdd;

    }
        
}