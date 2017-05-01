<?php

require_once(__DIR__. '/../initialize.php');
require_once(__DIR__. '/controller.inc');

require_once(__DIR__. '/../model/user.inc');

class SignupController extends Controller{
    
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
        $this->display_tpl = "signup.tpl";
    }

    // ユーザー登録
    private function create(){
        $user_id = User::create($_POST["name"], $_POST["password"], $_POST["email"]);
        if($user_id){
            User::updateDescription($user_id, $_POST["description"]);
            header('Location: http://'. $_SERVER["HTTP_HOST"]. '/index.php');
            die();
        }else{
            $this->smarty->assign('errors', User::getMessages());
            $this->display_tpl = "signup.tpl";
        }
    }
}

$page = new SignupController();
$page->view();