{include file='./header.tpl'}

<h1>Signin</h1>

<form action="signin.php" method="POST">
    <input name="email" type="text" value="" placeholder="メールアドレス" /><br/>
    
    <input name="password" type="password" value="" placeholder="パスワード" /><br/>
    
    <input type="submit" value="ログイン" />
</form>


{include file='./footer.tpl'}
