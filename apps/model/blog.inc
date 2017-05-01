<?php

require_once(__DIR__. '/model.inc');

class Blog extends Model{
    
    public static function all(){
        $sql = "SELECT * FROM Blogs;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->execute();
        $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

        return $rows;
    }
    
    public static function find($id){
        $sql = "SELECT Blogs.id, Blogs.title, Blogs.description, Categories.name AS category FROM Blogs LEFT JOIN Categories ON Blogs.category_id = Categories.id WHERE Blogs.id = :id;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->bindValue(":id", $id, PDO::PARAM_INT);
        $stmt->execute();
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        return $row;
    }

    public static function create($user_id, $title, $description){
        try{
            Dbh::get()->beginTransaction();
            
            if(static::isExist($title)) return false;

            // TODO: category_idを良い感じにする
            $sql = "INSERT INTO Blogs(title, description, category_id) VALUES(:title, :description, 1)";
            $stmt = Dbh::get()->prepare($sql);
            $stmt->bindValue(":title", $title);
            $stmt->bindValue(":description", $description);
            $stmt->execute();
            $blog_id = Dbh::get()->lastInsertId();
            
            $sql = "INSERT INTO BlogUsers(blog_id, user_id) VALUES(:blog_id, :user_id)";
            $stmt = Dbh::get()->prepare($sql);
            $stmt->bindValue(":blog_id", $blog_id);
            $stmt->bindValue(":user_id", $user_id);
            $stmt->execute();
            $id = Dbh::get()->lastInsertId();

            Dbh::get()->commit();
        }catch(Exception $e){
            Dbh::get()->rollback();
            die();
            static::$messages[] = $e->getMessage();
        }

        return $blog_id;

    }

    private static function isExist($title){
        $sql = "SELECT id FROM Blogs WHERE title = :title;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->bindValue(":title", $title);
        $stmt->execute();
        
        if($stmt->fetchColumn()){
            static::$messages[] = "既に存在するブログ名です";
            return true;
        }

        return false;
    }
}