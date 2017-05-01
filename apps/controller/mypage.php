<?php

require_once(__DIR__. '/../initialize.php');
require_once(__DIR__. '/controller.inc');

require_once(__DIR__. '/../model/user.inc');
require_once(__DIR__. '/../service/blog_service.inc');

class MypageController extends Controller{
    
    public function __construct(){
        parent::__construct();

        $this->signedOnly();

        if($_SERVER['REQUEST_METHOD'] == "POST"){
            $this->create();
        }else{
            $this->index();
        }
    }

    // 一覧
    private function index(){
        $this->display_tpl = "mypage.tpl";
        $user = User::myself();
        $user["blogs"] = BlogService::getUserBlogs($user["id"]);
        $this->smarty->assign('user', $user);
    }
}

$page = new MypageController();
$page->view();