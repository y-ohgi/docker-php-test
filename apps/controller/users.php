<?php

require_once(__DIR__. '/../initialize.php');
require_once(__DIR__. '/controller.inc');

require_once(__DIR__. '/../model/user.inc');

class UsersController extends Controller{
    
    public function __construct(){
        parent::__construct();

        $this->index();
    }

    // 一覧
    private function index(){
        $this->display_tpl = "users.tpl";
        $this->smarty->assign('users', User::all());
    }
}

$page = new UsersController();
$page->view();