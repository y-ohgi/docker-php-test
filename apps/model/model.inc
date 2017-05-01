<?php

require_once(__DIR__. '/dbh.inc');

abstract class Model{
    protected static $messages = [];
    
    public static function getMessages(){
        return static::$messages;
    }
}