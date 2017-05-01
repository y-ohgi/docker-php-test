<?php

require_once(__DIR__. '/../initialize.php');
require_once(__DIR__. '/controller.inc');

require_once(__DIR__. '/../model/blog.inc');
require_once(__DIR__. '/../model/user.inc');

class BlogsController extends Controller{
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
        $this->display_tpl = "blogs.tpl";
        $this->smarty->assign('blogs', Blog::all());
    }

    // 詳細
    private function show($id){
        $this->display_tpl = "blog.tpl";
        $this->smarty->assign('blog', Blog::find($id));
    }

    // ブログの作成
    private function create(){

        $user = User::myself();
        

        $blog_id = Blog::create($user["id"], $_POST["title"], $_POST["description"]);

        if($blog_id){
            header('Location: http://'. $_SERVER["HTTP_HOST"]. '/blogs.php?id='.$blog_id);
            die();
        }else{

            $this->smarty->assign('errors', User::getMessages());
            $this->display_tpl = "mypage.tpl";
        }
    }
}

$page = new BlogsController();
$page->view();
