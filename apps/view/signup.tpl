{include file='./header.tpl'}

<h1>Signup</h1>

<form action="signup.php" method="POST">
    <input name="name" type="text" value="" placeholder="名前" /><br/>
    
    <input name="email" type="text" value="" placeholder="メールアドレス" /><br/>
    
    <input name="password" type="password" value="" placeholder="パスワード" /><br/>
    
    <input name="password_confirm" type="password" value="" placeholder="パスワード(確認)" /><br/>
    
    <textarea cols="30" id="" name="description" rows="10"></textarea><br/>
    
    <input type="submit" value="登録" />
</form>



{include file='./footer.tpl'}
