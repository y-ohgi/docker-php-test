{include file='./header.tpl'}

<h1>Mypage</h1>

{if $user["blogs"]}
    <h2>記事の投稿</h2>
    <form action="posts.php" method="POST">
	<select id="" name="blog_id">
	    {foreach $user["blogs"] as $blog}
		<option value="{$blog["id"]}">{$blog["title"]}</option>
	    {/foreach}
	</select>
	
	<input name="title" type="text" value="" placeholder="記事タイトル" /><br/>
	<textarea cols="30" id="" name="content" rows="10"></textarea> <br/>
	
	<input type="submit" value="投稿" />
    </form>
{/if}

<h2>ブログの作成</h2>
<form action="blogs.php" method="POST">
    <input name="title" type="text" value="" placeholder="ブログタイトル" /><br/>
    <textarea cols="30" id="" name="description" rows="10"></textarea> <br/>
    
    <input type="submit" value="ブログ作成" />
</form>


{include file='./footer.tpl'}
