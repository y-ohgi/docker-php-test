<?php

require_once(__DIR__. '/../initialize.php');
require_once(__DIR__. '/controller.inc');

class IndexController extends Controller{
    public function __construct(){
        parent::__construct();

        $this->index();
    }

    private function index(){
        $this->display_tpl = "index.tpl";
    }
}

$page = new IndexController();
$page->view();
