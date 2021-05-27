<?php session_start(); ?>
<?php include "temperature.php";
include "admin.php"; 
include "bdd.php";
$bdd = new bdd();
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>testseuil</title>

    <h1>envoyer seuil</h1>
    <form method="POST">
        <label>temperature intérieur</label>
        <input name="Temperature" type="text">
        <p></p>
        <label>Température extérieur</label>
        <input name="temperature_ext" type="text">
        <p></p>
        <label>Humidité_air</label>
        <input name="Humidité_air" type="text">
        <p></p>
        <label>Humidité_Tere</label>
        <input name="Humidité_Tere" type="text">
        <p></p>
        <button type="submit">Envoi</button>

        <?php // Tout les champs du formulaire
        if (isset($_POST['Temperature']) && isset($_POST['temperature_ext']) && isset($_POST['Humidité_air']) && isset($_POST['Humidité_Tere'])) {
            $cotemp = new seuil($bdd->connectbdd());

            $cotemp->envoie($_POST['Temperature'], $_POST['temperature_ext'], $_POST['Humidité_air'], $_POST['Humidité_Tere']);
        }
        ?>

        </body>

</html>