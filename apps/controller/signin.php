<?php

require_once(__DIR__. '/../initialize.php');
require_once(__DIR__. '/controller.inc');

require_once(__DIR__. '/../model/user.inc');

class SigninController extends Controller{
    
    public function __construct(){
        parent::__construct();

        if($_SERVER['REQUEST_METHOD'] == "POST"){
            $this->create();
        }else{
            $this->index();
        }
    }

    // 一覧
    private function index(){
        $this->display_tpl = "signin.tpl";
    }

    // ログイン
    private function create(){
        $user = User::verify($_POST["password"], $_POST["email"]);

        if($user){
            $_SESSION["user"]["name"] = $user["name"];
            $_SESSION["user"]["id"] = $user["id"];
            header('Location: http://'. $_SERVER["HTTP_HOST"]. '/mypage.php');
            die();
        }else{
            $this->smarty->assign('errors', User::getMessages());
            $this->display_tpl = "signin.tpl";
        }
    }
}

$page = new SigninController();
$page->view();