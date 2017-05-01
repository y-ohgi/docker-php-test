<!doctype html>

<html lang="ja">
    <head>
	<meta charset="utf-8">

	<title>The HTML5 Herald</title>

	<!--[if lt IE 9]>
	    <script src="https://cdnjs.cloudflare.com/ajax/libs/html5shiv/3.7.3/html5shiv.js"></script>
	<![endif]-->
    </head>
    <body>
<ul>
    {foreach $errors as $error}
	<li>
	    <font color="red">{$error}</font>
	</li>
    {/foreach}
</ul>
