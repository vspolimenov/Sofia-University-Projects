<?php
    include "../../config.php";

    function connect_to_DB_server () {
        global $DB_SERVER, $DB_NAME, $DB_USER, $DB_PASS;

        $conn = null;
        try {
            $conn = new PDO("mysql:host=$DB_SERVER;dbname=$DB_NAME", $DB_USER, $DB_PASS);
            // set the PDO error mode to exception
            $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            
        } catch (PDOException $e) {
            die ( "($DB_PASS) Connecting to DB server failed" . "<br>" . $e->getMessage());
        }
        return $conn;
    }
?>

