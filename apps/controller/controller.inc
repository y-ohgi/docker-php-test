<?php

require_once(__DIR__. '/../model/user.inc');

abstract class Controller{
    protected $smarty = null;
    protected $display_tpl = ""; // 表示するテンプレート

    protected function __construct(){
        $this->smarty = new Smarty();
    }

    public function view(){
        $loggedin = false;
        if(User::myself()) $loggedin = true;
        $this->smarty->assign("loggedin", $loggedin);

        $this->smarty->display(__DIR__.'/../view/'.$this->display_tpl);
    }


    protected function signedOnly(){
        if(!$_SESSION["user"]["id"]) {
            header('Location: http://'. $_SERVER["HTTP_HOST"]. '/signin.php');
        }
    }
}