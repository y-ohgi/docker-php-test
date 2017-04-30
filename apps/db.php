<?php

define('DB_DATABASE','blog');
define('DB_USERNAME','root');
define('DB_PASSWORD','');
define('DB_HOST','mysql');
define('PDO_DSN','mysql:host='. DB_HOST. ';dbname=' . DB_DATABASE);

try{
    $db = new PDO(PDO_DSN,DB_USERNAME,DB_PASSWORD);
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch(PDOException $e){
    echo "error</br>";
    var_dump($e->getMessage());
    exit;
}

var_dump($db);