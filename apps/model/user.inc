<?php

require_once(__DIR__. '/model.inc');

class User extends Model{

    public static function myself(){
        if(!$_SESSION["user"])return false;

        $sql = "SELECT * FROM Users WHERE id = :id;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->bindValue(":id", $_SESSION["user"]["id"], PDO::PARAM_INT);
        $stmt->execute();
        $user = $stmt->fetch(PDO::FETCH_ASSOC);

        return $user;
    }

    public static function all(){
        $sql = "SELECT * FROM Users;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->execute();
        $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

        return $rows;
    }
    
    /**
     *
     * TODO: emailのフォーマットの評価
     *
     */
    public static function create($name, $password, $email){
        try{
            Dbh::get()->beginTransaction();
            
            if(static::isExist($name, $email)) return false;
            
            $sql = "INSERT INTO Users(name, password, email) VALUES(:name, :password, :email)";
            $stmt = Dbh::get()->prepare($sql);
            $stmt->bindValue(":name", $name);
            $stmt->bindValue(":password", password_hash($password, PASSWORD_DEFAULT));
            $stmt->bindValue(":email", $email);
            $stmt->execute();
            $id = Dbh::get()->lastInsertId();

            Dbh::get()->commit();
        }catch(Exception $e){
            Dbh::get()->rollback();
            static::$messages[] = $e->getMessage();
        }

        return $id;
    }


    public static function verify($password, $email){
        try{
            $sql = "SELECT * FROM Users WHERE email = :email";
            $stmt = Dbh::get()->prepare($sql);
            $stmt->bindValue(":email", $email);
            $stmt->execute();
            $user = $stmt->fetch(PDO::FETCH_ASSOC);
            
            if(!password_verify($password, $user["password"])){
                static::$messages[] = "パスワードかメールアドレスが間違っています";
                return false;
            }

        }catch(Exception $e){
            Dbh::get()->rollback();
            static::$messages[] = $e->getMessage();
        }

        return $user;
    }
    

    public static function updateDescription($id, $desc){
        try{
            $sql = "UPDATE Users SET description = :description WHERE id = :id";
            $stmt = Dbh::get()->prepare($sql);
            $stmt->bindValue(":id", $id);
            $stmt->bindValue(":description", h($desc));
            $stmt->execute();
        }catch(Exception $e){
            static::$messages[] = $e->getMessage();
            return false;
        }
        return true;
    }

    private static function isExist($name, $email){
        $sql = "SELECT id FROM Users WHERE name = :name OR email = :email;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->bindValue(":name", $name);
        $stmt->bindValue(":email", $email);
        $stmt->execute();
        
        if($stmt->fetchColumn()){
            static::$messages[] = "既に存在するユーザーです";
            return true;
        }

        return false;
    }
}