<?php
    include "config.php";

    // config.php should contain information about the database
    // run this script to wipe and create new database
    
    init ();

    function init () {
        $conn = connect_to_DB_server ();
        drop_database ($conn);
        create_database ($conn);
        create_table_users ($conn);
        create_table_conferences ($conn);
        //create_table_participants ($conn);
        create_table_ConferenceData ($conn);
    }

    function connect_to_DB_server () {
        global $DB_NAME, $DB_USER, $DB_PASS;

        $conn = null;
        try {
            $conn = new PDO("mysql:host=localhost", $DB_USER, $DB_PASS);
            // set the PDO error mode to exception
            $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            
        } catch (PDOException $e) {
            die ( "($DB_PASS) Connecting to DB server failed" . "<br>" . $e->getMessage());
        }
        return $conn;
    }
    
    function drop_database ($conn) {
        global $DB_NAME;
        $sql = "DROP DATABASE IF EXISTS $DB_NAME;";
        try {    
            $conn->exec($sql);
        } catch (PDOException $e) {
            die ($sql . "<br>" . $e->getMessage());
        }
    }

    function create_database ($conn) {
        global $DB_NAME;
        $sql = "CREATE DATABASE `$DB_NAME`;
                USE $DB_NAME;";
        try {    
            $conn->exec($sql);
        }catch (PDOException $e) {
            die ($sql . "<br>" . $e->getMessage());
        }
    }

    function create_table_users ($conn) {
        // sql to create table User
        // for password we will use SHA-1 so we need 40 symbols
        $sql = "CREATE TABLE Users (
                id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
                username VARCHAR(30) NOT NULL UNIQUE,
                password VARCHAR(40) NOT NULL,
                email VARCHAR(30) NOT NULL UNIQUE
                );";

        try {    
            $conn->exec($sql);
        }catch (PDOException $e) {
            die ($sql . "<br>" . $e->getMessage());
        }
    }

    function create_table_conferences ($conn) {
        // sql to create table Conferences
        $sql = "CREATE TABLE Conferences (
                id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
                name VARCHAR(30) NOT NULL UNIQUE,
                description VARCHAR(300),
                place VARCHAR(100) NOT NULL,
                time DATETIME NOT NULL
                )";

        try {    
            $conn->exec($sql);
        }catch (PDOException $e) {
            die ($sql . "<br>" . $e->getMessage());
        }
    }

    function create_table_participants ($conn) {
        // sql to create table Participants (many to many table)
        $sql = "CREATE TABLE Participants (
                id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
                id_user INT(6) UNSIGNED,
                id_conference INT(6) UNSIGNED, 
                FOREIGN KEY (id_user)
                    REFERENCES Users(id),
                FOREIGN KEY (id_conference)
                    REFERENCES Conferences(id)
                
                )";
        try {    
            $conn->exec($sql);
        }catch (PDOException $e) {
            die ($sql . "<br>" . $e->getMessage());
        }
    }

    function create_table_ConferenceData ($conn) {
        // sql to create table ConferenceData (many to many table)
        $sql = "CREATE TABLE ConferenceData (
                id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
                id_user INT(6) UNSIGNED,
                id_conference INT(6) UNSIGNED,
                date DATETIME NOT NULL,
                comment VARCHAR (300) NOT NULL,
                file_id VARCHAR (6),
                FOREIGN KEY (id_user)
                    REFERENCES Users(id),
                FOREIGN KEY (id_conference)
                    REFERENCES Conferences(id)
                
                )";
        try {    
            $conn->exec($sql);
        }catch (PDOException $e) {
            die ($sql . "<br>" . $e->getMessage());
        }
    }
?>


