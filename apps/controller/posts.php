<?php

require_once(__DIR__. '/../initialize.php');
require_once(__DIR__. '/controller.inc');

require_once(__DIR__. '/../model/post.inc');
require_once(__DIR__. '/../model/user.inc');

require_once(__DIR__. '/../service/blog_service.inc');

class PostsController extends Controller{
    public function __construct(){
        parent::__construct();

        if($_SERVER['REQUEST_METHOD'] == "POST"){
            $this->signedOnly();
            $this->create();
        }else if($_GET["id"]){
            $this->show(h($_GET["id"]));
        }else{
            $this->index();
        }
    }
    
    // 一覧
    private function index(){
        $this->display_tpl = "posts.tpl";
        $this->smarty->assign('posts', Blog::all());
    }

    // 詳細
    private function show($id){
        $this->display_tpl = "post.tpl";
        $this->smarty->assign('post', Post::find($id));
    }

    // 記事の投稿
    private function create(){
        $user = User::myself();

        $post_id = Post::create($user["id"], $_POST["blog_id"], $_POST["title"], $_POST["content"]);

        if($post_id){
            header('Location: http://'. $_SERVER["HTTP_HOST"]. '/posts.php?id='.$post_id);
            die();
        }else{
            $this->smarty->assign('errors', User::getMessages());
            $user["blogs"] = BlogService::getUserBlogs($user["id"]);
            $this->smarty->assign('user', $user);
            $this->display_tpl = "mypage.tpl";
        }
    }
}

$page = new PostsController();
$page->view();
