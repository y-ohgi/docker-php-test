<?php

class BlogService{
    public static function getUserBlogs($user_id){
        $sql = "SELECT Blogs.id, Blogs.title, Blogs.description, Blogs.created_at, Blogs.updated_at FROM Blogs LEFT JOIN BlogUsers ON Blogs.id = BlogUsers.blog_id WHERE BlogUsers.user_id = :user_id;";
        $stmt = Dbh::get()->prepare($sql);
        $stmt->bindValue(":user_id", $user_id, PDO::PARAM_INT);
        $stmt->execute();
        $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

        return $rows;
    }
}
