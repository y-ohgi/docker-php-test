<?php

require_once(__DIR__. '/model.inc');

class Post extends Model{
    
    public static function all(){
        $sql = "SELECT * FROM Posts;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->execute();
        $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

        return $rows;
    }
    
    public static function find($id){
        $sql = "SELECT * FROM Posts WHERE id = :id";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->bindValue(":id", $id, PDO::PARAM_INT);
        $stmt->execute();
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        return $row;
    }

    public static function create($user_id, $blog_id, $title, $content){
        try{
            Dbh::get()->beginTransaction();
            
            if(!static::hasBlog($user_id, $blog_id)) return false;

            // TODO: publish_state_idを良い感じにする
            $sql = "INSERT INTO Posts(user_id, blog_id, publish_state_id, title, content) VALUES(:user_id, :blog_id, 1, :title, :content)";
            $stmt = Dbh::get()->prepare($sql);
            $stmt->bindValue(":user_id", $user_id);
            $stmt->bindValue(":blog_id", $blog_id);
            $stmt->bindValue(":title", h($title));
            $stmt->bindValue(":content", h($content));
            $stmt->execute();
            $post_id = Dbh::get()->lastInsertId();
            
            Dbh::get()->commit();
        }catch(Exception $e){
            Dbh::get()->rollback();
            die();
            static::$messages[] = $e->getMessage();
        }

        return $post_id;

    }

    private static function hasBlog($user_id, $blog_id){
        $sql = "SELECT * FROM BlogUsers WHERE user_id = :user_id AND blog_id = :blog_id;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->bindValue(":user_id", $user_id);
        $stmt->bindValue(":blog_id", $blog_id);
        $stmt->execute();
        
        if(!$stmt->fetch()){
            static::$messages[] = "あなたのブログではない";
            return false;
        }

        return true;
    }
}