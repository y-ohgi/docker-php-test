{include file='./header.tpl'}

<h1>ブログ</h1>

<ul>
    <li><a href="blogs.php">ブログ一覧</a></li>
    <li><a href="users.php">ユーザー一覧</a></li>
</ul>

{if loggedin}
    <ul>
	<li><a href="/mypage.php">mypage</a></li>
    </ul>
{else}
    <ul>
	<li><a href="signup.php">ユーザー登録</a></li>
	<li><a href="signin.php">ユーザーログイン</a></li>
    </ul>

{/if}

{include file='./footer.tpl'}
