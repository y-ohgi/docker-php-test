<?php

class Dbh{
    protected static $dbh = null;

    protected function __construct(){}

    public static function get(){
        if(static::$dbh == null){
            static::connect();
        }
        return static::$dbh;
    }

    public static function disconnect(){
        if(static::$dbh){
            static::$dbh = null;
        }
    }

    protected static function connect(){
        try{
            static::$dbh = new PDO(DATABASE_DSN, DATABASE_USER, DATABASE_PASSWORD);
        }catch(PDOException $e){
            var_dump($e->getMessage());
            die();
        }
    }
}
